#include "applibs/remotex.h"

int BEGIN_API(ctx_block, RemoteX_PlatformInformation, char *buffer, size_t buffer_length)
{
    ctx_block.length = buffer_length;

    SEND_MSG(RemoteX_PlatformInformation,
             CORE_BLOCK_SIZE(RemoteX_PlatformInformation),
             VARIABLE_BLOCK_SIZE(RemoteX_PlatformInformation, buffer_length),
             true);

    memset(buffer, 0x00, buffer_length);
    memcpy(buffer, ctx_block.data_block.data, ctx_block.header.returns);
}
END_API

static int BEGIN_API(ctx_block, RemoteX_Write, int fd, const void *writeData, size_t lenWriteData)
{
    if (lenWriteData > DATA_BLOCK_DATA_SIZE(RemoteX_Write))
    {
        return -1;
    }

    ctx_block.fd = fd;
    ctx_block.length = lenWriteData;
    memcpy(ctx_block.data_block.data, writeData, lenWriteData);

    SEND_MSG(RemoteX_Write,
             VARIABLE_BLOCK_SIZE(RemoteX_Write, lenWriteData),
             CORE_BLOCK_SIZE(RemoteX_Write),
             true);
}
END_API

static int BEGIN_API(ctx_block, RemoteX_Read, int fd, uint8_t *readData, size_t lenReadData)
{
    if (lenReadData > DATA_BLOCK_DATA_SIZE(RemoteX_Read))
    {
        return -1;
    }

    ctx_block.fd = fd;
    ctx_block.length = lenReadData;

    SEND_MSG(RemoteX_Read,
             CORE_BLOCK_SIZE(RemoteX_Read),
             VARIABLE_BLOCK_SIZE(RemoteX_Read, lenReadData),
             true);

    memcpy(readData, ctx_block.data_block.data, ctx_block.length);
}
END_API

static int64_t BEGIN_API(ctx_block, RemoteX_Lseek, int fd, uint64_t offset, int whence)
{
    ctx_block.fd = fd;
    ctx_block.offset = offset;
    ctx_block.whence = whence;

    SEND_MSG_WITH_DEFAULTS(RemoteX_Lseek, true);
}
END_API

static int64_t BEGIN_API(ctx_block, RemoteX_Close, int fd)
{
    ctx_block.fd = fd;
    SEND_MSG_WITH_DEFAULTS(RemoteX_Close, true);
}
END_API

int __wrap_close(int fd)
{
    return RemoteX_Close(fd);
}

off_t __wrap_lseek(int fd, off_t offset, int whence)
{
    return RemoteX_Lseek(fd, offset, whence);
}

ssize_t __wrap_read(int fd, void *buf, size_t count)
{
    return RemoteX_Read(fd, buf, count);
}

ssize_t __wrap_write(int fd, const void *buf, size_t count)
{
    return RemoteX_Write(fd, buf, count);
}