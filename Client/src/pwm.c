#include "applibs/pwm.h"

int BEGIN_API(ctx_block, PWM_Open, PWM_ControllerId pwm)
{
    ctx_block.pwm = pwm;
    SEND_MSG_WITH_DEFAULTS(PWM_Open, true);
}
END_API

int BEGIN_API(ctx_block, PWM_Apply, int pwmFd, PWM_ChannelId pwmChannel, const PwmState *newState)
{
    ctx_block.pwmFd = pwmFd;
    ctx_block.pwmChannel = pwmChannel;
    memcpy(ctx_block.data_block.data, newState, sizeof(PwmState));

    SEND_MSG(PWM_Apply,
             VARIABLE_BLOCK_SIZE(PWM_Apply, sizeof(PwmState)),
             CORE_BLOCK_SIZE(PWM_Apply),
             true);
}
END_API