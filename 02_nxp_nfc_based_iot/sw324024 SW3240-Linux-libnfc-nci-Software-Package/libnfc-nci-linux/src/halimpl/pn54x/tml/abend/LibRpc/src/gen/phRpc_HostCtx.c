
//
// Generated File. Do not edit.
// Generator = C:\Work\pn547_sw\Tools\ARM_Board\trunk\ARMBoard_SW\comps\phRpc\src\cfg\ctx_gen_cfg.py
//


#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "phRpc_Cmd.h"
#include "phRpc_Types.h"
#include "phRpc_Status.h"
#include "phRpc_HostIo.h"
#include "phRpc_H_Common.h"
#include "phRpc_HostCtx.h"
 

//
// Specific text/code would go here
//


void phRpc_H_ToString(phRpc_H_t *compCtx, int index, wchar_t *txtBuf, size_t *txtBufLen)

{
    switch (index)
    {
        default: *txtBufLen = 0; break;
        case phRpc_H_E_MinorVersion:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"MinorVersion = 0x%02X", compCtx->MinorVersion);
            break;
        case phRpc_H_E_Retry:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"Retry = %d", compCtx->Retry);
            break;
        case phRpc_H_E_InBuf:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"InBuf = 0x%p", compCtx->InBuf);
            break;
        case phRpc_H_E_LockD:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"LockD = 0x%p", compCtx->LockD);
            break;
        case phRpc_H_E_MajorVersion:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"MajorVersion = 0x%02X", compCtx->MajorVersion);
            break;
        case phRpc_H_E_LockUserData:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"LockUserData = 0x%p", compCtx->LockUserData);
            break;
        case phRpc_H_E_NewRPC:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"NewRPC = 0x%02X", compCtx->NewRPC);
            break;
        case phRpc_H_E_FeatureCode:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"FeatureCode = 0x%02X", compCtx->FeatureCode);
            break;
        case phRpc_H_E_NumSent:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"NumSent = %d", compCtx->NumSent);
            break;
        case phRpc_H_E_PadMul:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"PadMul = %d", compCtx->PadMul);
            break;
        case phRpc_H_E_LogF:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"LogF = 0x%p", compCtx->LogF);
            break;
        case phRpc_H_E_CompatInfo:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"CompatInfo = 0x%04X", compCtx->CompatInfo);
            break;
        case phRpc_H_E_Flags:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"Flags = 0x%08X", compCtx->Flags);
            break;
        case phRpc_H_E_CancelFlag:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"CancelFlag = 0x%02X", compCtx->CancelFlag);
            break;
        case phRpc_H_E_device_PH_RPC_H_DEVNAMELEN_:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"device[PH_RPC_H_DEVNAMELEN] = NA");
            break;
        case phRpc_H_E_CompactRPC:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"CompactRPC = 0x%02X", compCtx->CompactRPC);
            break;
        case phRpc_H_E_LastError:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"LastError = NA");
            break;
        case phRpc_H_E_HookF:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"HookF = 0x%p", compCtx->HookF);
            break;
        case phRpc_H_E_MagicID:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"MagicID = 0x%08X", compCtx->MagicID);
            break;
        case phRpc_H_E_CancelInitial:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"CancelInitial = 0x%02X", compCtx->CancelInitial);
            break;
        case phRpc_H_E_UserData:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"UserData = 0x%p", compCtx->UserData);
            break;
        case phRpc_H_E_OutBuf:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"OutBuf = 0x%p", compCtx->OutBuf);
            break;
        case phRpc_H_E_TimeoutMillisec:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"TimeoutMillisec = %d", compCtx->TimeoutMillisec);
            break;
        case phRpc_H_E_PadPlus1:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"PadPlus1 = 0x%02X", compCtx->PadPlus1);
            break;
        case phRpc_H_E_LowerHandle:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"LowerHandle = 0x%p", compCtx->LowerHandle);
            break;
        case phRpc_H_E_NumReceived:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"NumReceived = %d", compCtx->NumReceived);
            break;
        case phRpc_H_E_LowerRawCmd:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"LowerRawCmd = 0x%p", compCtx->LowerRawCmd);
            break;
        case phRpc_H_E_MinIOData:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"MinIOData = NA");
            break;
        case phRpc_H_E_Guard:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"Guard = 0x%08X", compCtx->Guard);
            break;
        case phRpc_H_E_IoSysData:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"IoSysData = NA");
            break;
        case phRpc_H_E_PropagateDevErrToRetVal:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"PropagateDevErrToRetVal = 0x%02X", compCtx->PropagateDevErrToRetVal);
            break;
        case phRpc_H_E_TRxMutex:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"TRxMutex = NA");
            break;
        case phRpc_H_E_SeqNr:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"SeqNr = 0x%02X", compCtx->SeqNr);
            break;
        case phRpc_H_E_LogUserData:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"LogUserData = 0x%p", compCtx->LogUserData);
            break;
        case phRpc_H_E_ValLevel:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"ValLevel = 0x%02X", compCtx->ValLevel);
            break;
        case phRpc_H_E_IoPdFlag:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"IoPdFlag = 0x%02X", compCtx->IoPdFlag);
            break;
#if defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
        case phRpc_H_E_wfds:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"wfds = NA");
            break;
        case phRpc_H_E_rfds:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"rfds = NA");
            break;
        case phRpc_H_E_fd:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"fd = 0x%08X", compCtx->fd);
            break;
        case phRpc_H_E_old_tios:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"old_tios = NA");
            break;
#elif defined PH_RPC_H_PLAT_WINDOWS
        case phRpc_H_E_OldTimeouts:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"OldTimeouts = NA");
            break;
        case phRpc_H_E_OvR:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"OvR = NA");
            break;
        case phRpc_H_E_Dcb:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"Dcb = NA");
            break;
        case phRpc_H_E_OldDcb:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"OldDcb = NA");
            break;
        case phRpc_H_E_OvW:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"OvW = NA");
            break;
        case phRpc_H_E_Timeouts:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"Timeouts = NA");
            break;
        case phRpc_H_E_hc:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"hc = 0x%p", compCtx->hc);
            break;
        case phRpc_H_E_CommInterface:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"CommInterface = NA");
            break;
        case phRpc_H_E_dev:
            *txtBufLen = PH_RPC_H_SWPRINTF(txtBuf, *txtBufLen, L"dev = 0x%p", compCtx->dev);
            break;
#endif 
    }
}


