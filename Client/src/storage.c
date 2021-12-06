#include "applibs/storage.h"

#include "contract.h"
#include "comms_manager.h"
#include <errno.h>

int BEGIN_API(ctx_block, Storage_OpenMutableFile, void)
{
    SEND_MSG_WITH_DEFAULTS(Storage_OpenMutableFile, true);
}
END_API

int BEGIN_API(ctx_block, Storage_DeleteMutableFile, void)
{
    SEND_MSG_WITH_DEFAULTS(Storage_DeleteMutableFile, true);
}
END_API
