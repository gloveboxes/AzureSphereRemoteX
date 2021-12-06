#include "applibs/adc.h"

int BEGIN_API(ctx_block, ADC_Open, ADC_ControllerId id)
{
    ctx_block.id = id;
    SEND_MSG_WITH_DEFAULTS(ADC_Open, true)
}
END_API

int BEGIN_API(ctx_block, ADC_GetSampleBitCount, int fd, ADC_ChannelId channel)
{
    ctx_block.fd = fd;
    ctx_block.channel = channel;
    SEND_MSG_WITH_DEFAULTS(ADC_GetSampleBitCount, true);
}
END_API

int BEGIN_API(ctx_block, ADC_SetReferenceVoltage, int fd, ADC_ChannelId channel, float referenceVoltage)
{
    ctx_block.fd = fd;
    ctx_block.channel = channel;
    ctx_block.referenceVoltage = referenceVoltage;
    SEND_MSG_WITH_DEFAULTS(ADC_SetReferenceVoltage, true);
}
END_API

int BEGIN_API(ctx_block, ADC_Poll, int fd, ADC_ChannelId channel, uint32_t *outSampleValue)
{
    ctx_block.fd = fd;
    ctx_block.channel = channel;
    SEND_MSG_WITH_DEFAULTS(ADC_Poll, true);

    *outSampleValue = ctx_block.outSampleValue;
}
END_API