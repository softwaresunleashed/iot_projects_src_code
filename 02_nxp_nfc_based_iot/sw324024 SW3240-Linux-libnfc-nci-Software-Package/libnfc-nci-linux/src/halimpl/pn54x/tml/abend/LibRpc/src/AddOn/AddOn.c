
// Add On file for Android Build

#include <stdint.h>
#include <stdlib.h>
#include "phRpc_D.h"

uint8_t phRpc_D_Handler_DispatchCompletion(void *rpc_ch, uint8_t result)
{
    return phRpc_D_DispatchCompletion((phRpc_D_t*)rpc_ch, result);
}

uint8_t phRpc_2_D_Handler_DispatchCompletion(void *rpc_ch, uint8_t result)
{
    return phRpc_D_DispatchCompletion((phRpc_D_t*)rpc_ch, result);
}