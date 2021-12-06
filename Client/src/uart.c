#include "applibs/uart.h"
#include "contract.h"
#include "comms_manager.h"
#include <errno.h>

int BEGIN_API(ctx_block, UART_InitConfig, UART_Config *uartConfig)
{
    SEND_MSG(UART_InitConfig, CORE_BLOCK_SIZE(UART_InitConfig), VARIABLE_BLOCK_SIZE(UART_InitConfig, sizeof(UART_Config)), true);
    memcpy(uartConfig, &ctx_block.data_block.data, sizeof(UART_Config));
}
END_API

int BEGIN_API(ctx_block, UART_Open, UART_Id uartId, const UART_Config *uartConfig)
{
    ctx_block.uartId = uartId;
    memcpy(&ctx_block.data_block.data, uartConfig, sizeof(UART_Config));
    SEND_MSG(UART_Open, VARIABLE_BLOCK_SIZE(UART_Open, sizeof(UART_Config)), CORE_BLOCK_SIZE(UART_Open), true);
}
END_API