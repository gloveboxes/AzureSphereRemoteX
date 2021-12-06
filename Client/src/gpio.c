#include "applibs/gpio.h"

int BEGIN_API(ctx_block, GPIO_OpenAsOutput, GPIO_Id gpioId, GPIO_OutputMode_Type outputMode, GPIO_Value_Type initialValue)
{
    ctx_block.gpioId = gpioId;
    ctx_block.outputMode = outputMode;
    ctx_block.initialValue = initialValue;
    SEND_MSG_WITH_DEFAULTS(GPIO_OpenAsOutput, true);
}
END_API

int BEGIN_API(ctx_block, GPIO_SetValue, int gpioFd, GPIO_Value_Type value)
{
    ctx_block.gpioFd = gpioFd;
    ctx_block.value = value;
    SEND_MSG_WITH_DEFAULTS(GPIO_SetValue, true);
}
END_API

int BEGIN_API(ctx_block, GPIO_OpenAsInput, GPIO_Id gpioId)
{
    ctx_block.gpioId = gpioId;
    SEND_MSG_WITH_DEFAULTS(GPIO_OpenAsInput, true);
}
END_API

int BEGIN_API(ctx_block, GPIO_GetValue, int gpioFd, GPIO_Value_Type *outValue)
{
    ctx_block.gpioFd = gpioFd;
    SEND_MSG_WITH_DEFAULTS(GPIO_GetValue, true);
    *outValue = ctx_block.outValue;
}
END_API
