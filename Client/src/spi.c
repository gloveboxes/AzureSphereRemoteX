#include "applibs/spi.h"

static SPIMaster_Transfer *cached_transfers = NULL;

int BEGIN_API(ctx_block, SPIMaster_Open, SPI_InterfaceId interfaceId, SPI_ChipSelectId chipSelectId, const SPIMaster_Config *config)
{
    ctx_block.interfaceId = interfaceId;
    ctx_block.chipSelectId = chipSelectId;
    memcpy(ctx_block.data_block.data, config, sizeof(SPIMaster_Config));
    
    SEND_MSG(SPIMaster_Open,
             VARIABLE_BLOCK_SIZE(SPIMaster_Open, sizeof(SPIMaster_Config)),
             CORE_BLOCK_SIZE(SPIMaster_Open),
             true);
}
END_API

int BEGIN_API(ctx_block, SPIMaster_InitConfig, SPIMaster_Config *config)
{
    SEND_MSG(SPIMaster_InitConfig,
             CORE_BLOCK_SIZE(SPIMaster_InitConfig),
             VARIABLE_BLOCK_SIZE(SPIMaster_InitConfig, sizeof(SPIMaster_Config)),
             true);
    memcpy(config, &ctx_block.data_block.data, sizeof(SPIMaster_Config));
}
END_API

int BEGIN_API(ctx_block, SPIMaster_SetBusSpeed, int fd, uint32_t speedInHz)
{
    ctx_block.fd = fd;
    ctx_block.speedInHz = speedInHz;
    SEND_MSG_WITH_DEFAULTS(SPIMaster_SetBusSpeed, true);
}
END_API

int BEGIN_API(ctx_block, SPIMaster_SetMode, int fd, SPI_Mode mode)
{
    ctx_block.fd = fd;
    ctx_block.mode = mode;
    SEND_MSG_WITH_DEFAULTS(SPIMaster_SetMode, true);
}
END_API

int BEGIN_API(ctx_block, SPIMaster_SetBitOrder, int fd, SPI_BitOrder order)
{
    ctx_block.fd = fd;
    ctx_block.order = order;
    SEND_MSG_WITH_DEFAULTS(SPIMaster_SetBitOrder, true);
}
END_API

ssize_t BEGIN_API(ctx_block, SPIMaster_WriteThenRead, int fd, const uint8_t *writeData, size_t lenWriteData,
                  uint8_t *readData, size_t lenReadData)
{
    if (lenWriteData > sizeof(ctx_block.data_block.data) || lenReadData > sizeof(ctx_block.data_block.data))
    {
        return -1;
    }

    ctx_block.fd = fd;
    ctx_block.lenWriteData = lenWriteData;
    ctx_block.lenReadData = lenReadData;
    memcpy(&ctx_block.data_block.data, writeData, lenWriteData);

    SEND_MSG(SPIMaster_WriteThenRead,
             VARIABLE_BLOCK_SIZE(SPIMaster_WriteThenRead, lenWriteData),
             VARIABLE_BLOCK_SIZE(SPIMaster_WriteThenRead, lenReadData),
             true);

    memcpy(readData, ctx_block.data_block.data, lenReadData);
}
END_API

int SPIMaster_InitTransfers(SPIMaster_Transfer *transfers, size_t transferCount)
{
    for (size_t i = 0; i < transferCount; i++)
    {
        memset(&transfers[i], 0x00, sizeof(SPIMaster_Transfer));
    }

    errno = 0;
    return 0;
}

int calc_total_transfer_size(const SPIMaster_Transfer *transfers, size_t transferCount)
{
    size_t size = 0;
    for (size_t i = 0; i < transferCount; i++)
    {
        size += transfers[i].length;
    }
    return size;
}

ssize_t BEGIN_API(ctx_block, SPIMaster_TransferSequential, int fd, const SPIMaster_Transfer *transfers,
                  size_t transferCount)
{
    bool read_transfer = false, write_transfer = false;
    int total_length = 0;
    size_t response_length = 0;

    if (calc_total_transfer_size(transfers, transferCount) > sizeof(ctx_block.data_block.data))
    {
        printf("Total transfer size exceeds data buffer size of %d\n", (int)sizeof(ctx_block.data_block.data));
        return -1;
    }

    ctx_block.fd = fd;
    ctx_block.transferCount = transferCount;
    ctx_block.length = 0;

    /*  Data is structured as follows in the data block
        Block 1 is SPIMaster_TransferSequential_t data structure
        Block 2 is SPI Transfer configs (multiple)
        Block 3 is Any Write data (multiple)
    */

    uint8_t *data_ptr = ctx_block.data_block.data;

    // Write SPI Transfer configs
    for (size_t i = 0; i < transferCount; i++)
    {
        SPI_TransferConfig *transfer_data = (SPI_TransferConfig *)data_ptr;

        transfer_data->flags = (uint8_t)transfers[i].flags;
        transfer_data->length = (uint16_t)transfers[i].length;

        data_ptr += sizeof(SPI_TransferConfig);
        ctx_block.length += sizeof(SPI_TransferConfig);

        read_transfer = transfers[i].flags == SPI_TransferFlags_Read ? true : read_transfer;
        write_transfer = transfers[i].flags == SPI_TransferFlags_Write ? true : write_transfer;
    }

    if (read_transfer && write_transfer)
    {
        printf("You can not mix read and write transfers in one SPI transaction\n");
        // https://docs.microsoft.com/en-us/azure-sphere/reference/applibs-reference/applibs-spi/function-spimaster-transfersequential
        return -1;
    }

    // Copy transfer write blocks
    if (write_transfer)
    {
        for (size_t i = 0; i < transferCount; i++)
        {
            memcpy(data_ptr, transfers[i].writeData, transfers[i].length);
            data_ptr += transfers[i].length;
            ctx_block.length += transfers[i].length;
            total_length += transfers[i].length;
        }
        response_length = CORE_BLOCK_SIZE(SPIMaster_TransferSequential);
    }

    if (read_transfer)
    {
        for (size_t i = 0; i < transferCount; i++)
        {
            total_length += transfers[i].length;
        }
        response_length = VARIABLE_BLOCK_SIZE(SPIMaster_TransferSequential, total_length);
    }

    SEND_MSG(SPIMaster_TransferSequential,
             VARIABLE_BLOCK_SIZE(SPIMaster_TransferSequential, ctx_block.length),
             (ssize_t)response_length,
             transfers->flags == SPI_TransferFlags_Read);

    if (read_transfer)
    {
        data_ptr = ctx_block.data_block.data;

        for (size_t i = 0; i < transferCount; i++)
        {
            memcpy(transfers[i].readData, data_ptr, transfers[i].length);
            data_ptr += transfers[i].length;
        }

        errno = ctx_block.header.err_no;
    }
    else
    {
        ctx_block.header.returns = total_length;
    }
}
END_API
