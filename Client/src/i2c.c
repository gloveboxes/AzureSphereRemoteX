#include "applibs/i2c.h"

int BEGIN_API(ctx_block, I2CMaster_Open, I2C_InterfaceId id)
{
    ctx_block.I2C_InterfaceId = id;
    SEND_MSG_WITH_DEFAULTS(I2CMaster_Open, true);
}
END_API

int BEGIN_API(ctx_block, I2CMaster_SetBusSpeed, int fd, uint32_t speedInHz)
{
    ctx_block.fd = fd;
    ctx_block.speedInHz = speedInHz;
    SEND_MSG_WITH_DEFAULTS(I2CMaster_SetBusSpeed, true);
}
END_API

int BEGIN_API(ctx_block, I2CMaster_SetTimeout, int fd, uint32_t timeoutInMs)
{
    ctx_block.fd = fd;
    ctx_block.timeoutInMs = timeoutInMs;
    SEND_MSG_WITH_DEFAULTS(I2CMaster_SetTimeout, true);
}
END_API

ssize_t BEGIN_API(ctx_block, I2CMaster_Write, int fd, I2C_DeviceAddress address, const uint8_t *data, size_t length)
{
    if (length > sizeof(ctx_block.data_block.data))
    {
        return -1;
    }

    ctx_block.fd = fd;
    ctx_block.address = address;
    ctx_block.length = length;
    memcpy(&ctx_block.data_block.data, data, length);

    SEND_MSG(I2CMaster_Write,
             VARIABLE_BLOCK_SIZE(I2CMaster_Write, length),
             CORE_BLOCK_SIZE(I2CMaster_Write),
             true);
}
END_API

ssize_t BEGIN_API(ctx_block, I2CMaster_WriteThenRead, int fd, I2C_DeviceAddress address, const uint8_t *writeData,
                  size_t lenWriteData, uint8_t *readData, size_t lenReadData)
{
    if (lenWriteData > sizeof(ctx_block.data_block.data) || lenReadData > sizeof(ctx_block.data_block.data))
    {
        return -1;
    }

    ctx_block.fd = fd;
    ctx_block.address = address;
    ctx_block.lenWriteData = lenWriteData;
    ctx_block.lenReadData = lenReadData;

    memcpy(&ctx_block.data_block.data, writeData, lenWriteData);

    SEND_MSG(I2CMaster_WriteThenRead,
             VARIABLE_BLOCK_SIZE(I2CMaster_WriteThenRead, lenWriteData),
             VARIABLE_BLOCK_SIZE(I2CMaster_WriteThenRead, lenReadData),
             true);

    memcpy(readData, ctx_block.data_block.data, lenReadData);
}
END_API

ssize_t BEGIN_API(ctx_block, I2CMaster_Read, int fd, I2C_DeviceAddress address, uint8_t *buffer, size_t maxLength)
{
    if (maxLength > sizeof(ctx_block.data_block.data))
    {
        return -1;
    }

    ctx_block.fd = fd;
    ctx_block.address = address;
    ctx_block.maxLength = maxLength;

    SEND_MSG(I2CMaster_Read,
             CORE_BLOCK_SIZE(I2CMaster_Read),
             VARIABLE_BLOCK_SIZE(I2CMaster_Read, maxLength),
             true);

    if (ctx_block.header.returns > 0)
    {
        memcpy(buffer, ctx_block.data_block.data, ctx_block.header.returns);
    }
}
END_API

int BEGIN_API(ctx_block, I2CMaster_SetDefaultTargetAddress, int fd, I2C_DeviceAddress address)
{
    ctx_block.fd = fd;
    ctx_block.address = address;

    SEND_MSG_WITH_DEFAULTS(I2CMaster_SetDefaultTargetAddress, true);
}
END_API