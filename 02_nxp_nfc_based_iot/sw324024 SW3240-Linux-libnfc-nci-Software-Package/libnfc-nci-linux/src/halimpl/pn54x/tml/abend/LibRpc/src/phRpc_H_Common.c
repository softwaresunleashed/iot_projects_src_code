
/*
*                   Copyright (c), NXP Semiconductors
*
*                      (C)NXP Semiconductors
*        All rights are reserved. Reproduction in whole or in part is
*       prohibited without the written consent of the copyright owner.
*   NXP reserves the right to make changes without notice at any time.
*  NXP makes no warranty, expressed, implied or statutory, including but
*  not limited to any implied warranty of merchantability or fitness for any
* particular purpose, or that the use will not infringe any third party patent,
*  copyright or trademark. NXP must not be liable for any loss or damage
*                           arising from its use.
*/

/** \file
* Project: RPC Host Library Low Level / ARM-Board for PN547 V&V.
* $Author: atp01705 $
* $Revision: 19533 $
* $Date: 2013-05-22 19:03:21 +0200 (Mi, 22 Mai 2013) $
*
*/

#include "phSwId.h"
#include "phRpc_H_Common.h"
#include "phRpc_Platform.h"
#include "phRpc_HostIo.h"
#include "phRpc_HostCtx.h"
#include "phRpc_H_Diversity.h"

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_SetTimeout(void *hdl, uint16_t msTo)
{
    uint8_t     ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h   = NULL;

    if ((NULL != hdl) && (0 != msTo))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            h->TimeoutMillisec = (msTo > PH_RPC_CMD_MIN_HOST_TIMEOUT_MILLISECONDS) ? msTo : PH_RPC_CMD_MIN_HOST_TIMEOUT_MILLISECONDS;
            ret = 0;

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_SetTimeout");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, msTo, 10);

            // Lib Status
            h->LastError.PcLibStatus = ret;

            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_SetLockD(void *hdl, pphRpc_H_LockD_t lockD, void *userData)
{
    uint8_t     ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h   = NULL;

    if (NULL != hdl)
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            // As setting the lock function here, we cannot lock the process of course ;-)
            h->LockD        = lockD;
            h->LockUserData = userData;
            ret             = PH_RPC_H_STATUS_OK;
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_SetLogF(void *hdl, pphRpc_H_LogF_t logF, void *userData)
{
    uint8_t     ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h   = NULL;

    if (NULL != hdl)
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            h->LogF         = logF;
            h->LogUserData  = userData;
            ret             = PH_RPC_H_STATUS_OK;

            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_SetHookF(void *hdl, pphRpc_H_EventHook_t hookF, void *userData)
{
    uint8_t     ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h   = NULL;

    if (NULL != hdl)
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            h->HookF    = hookF;
            h->UserData = userData;
            ret         = PH_RPC_H_STATUS_OK;

            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_GetLastError(void *hdl, phRpc_Status_t **lastError)
{
    uint8_t     ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h   = NULL;

    if ((NULL != hdl) && (NULL != lastError))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            *lastError = &(h->LastError);
            ret = 0;

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_GetLastError");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogPtr(h, *lastError);

            // Lib Status
            h->LastError.PcLibStatus = ret;
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_GetHostInfo(void *hdl, uint8_t infoType, uint32_t *infoNum, uint8_t **infoBuf, uint8_t *infoLen)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;

    if ((NULL != hdl) && (NULL != infoBuf) && (NULL != infoLen))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            switch (infoType)
            {
                case PH_RPC_CMD_HOSTINFO_PCLIB_SWID:
                    phSwId_GetPcLibID(infoBuf, infoLen);
                    ret = 0;
                    break;

                case PH_RPC_CMD_HOSTINFO_PCLIB_ENGDATA:
                    if (NULL != infoNum)
                    {
                        *infoNum = 0;
                    }
                    *infoLen = sizeof(void*);
                    *infoBuf = (uint8_t*)phRpc_H_GetEngData(hdl);
                    ret = 0;
                    break;

                default:
                    break;
            }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_GetHostInfo");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, infoType, 16);
            if (NULL != infoNum)
            {
                phRpc_H_LogInt(h, *infoNum, 16);
            } else
            {
                phRpc_H_LogPtr(h, NULL);
            }
            phRpc_H_LogPtr(h, *infoBuf);
            phRpc_H_LogInt(h, *infoLen, 10);

            // Lib Status
            h->LastError.PcLibStatus = ret;
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else
    {
        // Param check error. Individual fields are reset, if possible.
        if (NULL != infoNum)
        {
            *infoNum = 0;
        }
        if (NULL != infoBuf)
        {
            *infoBuf = NULL;
        }
        if (NULL != infoLen)
        {
            *infoLen = 0;
        }
    }

    return ret;
}

// ________________________________________________________________________________________________
//
// Administrative Commands
// ________________________________________________________________________________________________

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_GetDeviceInfo(void *hdl, uint8_t infoType, uint32_t *infoNum, uint8_t **infoBuf, uint8_t *infoLen)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = phRpc_H_Diversity_GetDeviceBufferSize();
    uint16_t    info_len;

    if ((NULL != hdl) && (NULL != infoBuf) && (NULL != infoLen))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H_Diversity_GetDeviceInfo(h->OutBuf, &len, infoType);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = phRpc_H_Diversity_GetDeviceBufferSize();
                    info_len = 0; // Will be set by function below.
                    ret = phRpc_D_Diversity_GetDeviceInfo(h->InBuf, len, h->CompactRPC, &h->LastError.CommStatusM, infoNum, &info_len, infoBuf);
                    *infoLen = (uint8_t)info_len;
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_GetDeviceInfo");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, infoType, 16);
            if (NULL != infoNum)
            {
                phRpc_H_LogInt(h, *infoNum, 16);
            } else
            {
                phRpc_H_LogPtr(h, NULL);
            }
            phRpc_H_LogPtr(h, *infoBuf);
            phRpc_H_LogInt(h, *infoLen, 10);

            // Lib Status
            h->LastError.PcLibStatus = ret;

            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_SetCommParam(void *hdl)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = phRpc_H_Diversity_GetDeviceBufferSize();
    uint32_t    opt      = 0;

    if (NULL != hdl)
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            // Check for any needed comm options (Workaround, padding, etc.)
            if (0 != h->PadPlus1)
            {
                opt |= PH_RPC_CMD_PAD_PLUS_1;
            } else { }
            // Request usage of variable-length RPC, if supported
            opt |= PH_RPC_CMD_VARIABLE_LEN_RPCBUF;

            h->PadMul = (0 == h->PadMul) ? 1u : h->PadMul;
            opt |= ((((uint32_t)(h->PadMul)) << PH_RPC_CMD_PAD_MUL_SHIFT) & PH_RPC_CMD_PAD_MUL_MASK);
            // Serialise
            ret = phRpc_H_Diversity_SetCommParam(h->OutBuf, &len, opt, h->TimeoutMillisec);
            if (0 == ret)
            {
                // TRX
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    // De-Serialise
                    len = phRpc_H_Diversity_GetDeviceBufferSize();
                    ret = phRpc_D_Diversity_SetCommParam(h->InBuf, len, &h->LastError.CommStatusM);
                } else { /* TRX error */ }
            } else { /* Error serialising data */ }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_SetCommParam");
            phRpc_H_LogPtr(h, h);

            // Lib Status
            h->LastError.PcLibStatus = ret;

            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_CancelIo(void *hdl)
{
    uint8_t     ret     = PH_RPC_CANCELRESULT_OK;

    if (NULL != hdl)
    {
        phRpc_H_t *h = (phRpc_H_t*)hdl;
        if (NULL == h->LowerRawCmd)
        {
            // Cancel together with WTX
            uint8_t cst = phRpc_AuxIsIoPending(hdl);
            if (0 != cst)
            {
                // NO locking of this function as it shall be used from within another thread!
                // I/O Pending, try to cancel it:
                phRpc_AuxSetCancelFlag(hdl);
            } else
            {
                // Finished already; nothing to do
            }
        } else
        {
            // Forward to lower layer:
            ret = h->LowerRawCmd(h->LowerHandle, NULL, ((uint16_t)-1), NULL, NULL); // A little hack: Length set to max. means CANCEL.
        }
    } else
    {
        /* Param error */
        ret = PH_RPC_CANCELRESULT_ERROR;
    }
    return ret;
}

// ________________________________________________________________________________________________
//
// Analog/Digital I/O System
// ________________________________________________________________________________________________


phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_AdcGetValue(void *hdl, uint8_t channelID, int32_t *daqVal)
{
    uint8_t ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    uint16_t len = phRpc_H_Diversity_GetDeviceBufferSize();
    phRpc_H_t *h = NULL;

    if ((NULL != hdl) && (NULL != daqVal))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H_Diversity_AdcGetValue(h->OutBuf, &len, channelID);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = phRpc_H_Diversity_GetDeviceBufferSize();
                    ret = phRpc_D_Diversity_AdcGetValue(h->InBuf, len, &h->LastError.CommStatusM, daqVal);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_AdcGetValue");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, channelID, 10);
            phRpc_H_LogInt(h, *daqVal, 10);

            // Lib Status
            h->LastError.PcLibStatus = ret;
            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }
    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DacSetValue(void *hdl, uint8_t channelID, int32_t newValue)
{
    uint8_t ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    uint16_t len = phRpc_H_Diversity_GetDeviceBufferSize();
    phRpc_H_t *h = NULL;

    if (NULL != hdl)
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H_Diversity_DacSetValue(h->OutBuf, &len, channelID, newValue);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = phRpc_H_Diversity_GetDeviceBufferSize();
                    ret = phRpc_D_Diversity_DacSetValue(h->InBuf, len, &h->LastError.CommStatusM);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DacSetValue");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, channelID, 10);
            phRpc_H_LogInt(h, newValue, 10);

            // Lib Status
            h->LastError.PcLibStatus = ret;
            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }
    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DacSetWave(void *hdl, uint8_t channelID, uint8_t waveType, uint32_t waveFrequency,
                                                     int32_t waveAmplitude, int32_t waveOffset)
{
    uint8_t ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    uint16_t len = phRpc_H_Diversity_GetDeviceBufferSize();
    phRpc_H_t *h = NULL;

    if (NULL != hdl)
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H_Diversity_DacSetWave(h->OutBuf, &len,
                                               channelID,
                                               waveType,
                                               waveFrequency,
                                               waveAmplitude,
                                               waveOffset);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = phRpc_H_Diversity_GetDeviceBufferSize();
                    ret = phRpc_D_Diversity_DacSetWave(h->InBuf, len, &h->LastError.CommStatusM);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DacSetWave");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, channelID, 10);
            phRpc_H_LogInt(h, waveType, 10);
            phRpc_H_LogInt(h, waveFrequency, 10);
            phRpc_H_LogInt(h, waveAmplitude, 10);
            phRpc_H_LogInt(h, waveOffset, 10);

            // Lib Status
            h->LastError.PcLibStatus = ret;
            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }
    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DaqGetVRef(void *hdl, uint32_t *vrefVal)
{
    uint8_t ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    uint16_t len = phRpc_H_Diversity_GetDeviceBufferSize();
    phRpc_H_t *h = NULL;

    if ((NULL != hdl) && (NULL != vrefVal))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H_Diversity_DaqGetVRef(h->OutBuf, &len);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = phRpc_H_Diversity_GetDeviceBufferSize();
                    ret = phRpc_D_Diversity_DaqGetVRef(h->InBuf, len, &h->LastError.CommStatusM, vrefVal);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DaqGetVRef");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, *vrefVal, 10);

            // Lib Status
            h->LastError.PcLibStatus = ret;
            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }
    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DaqSetVRef(void *hdl, uint32_t vrefVal)
{
    uint8_t ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    uint16_t len = phRpc_H_Diversity_GetDeviceBufferSize();
    phRpc_H_t *h = NULL;

    if (NULL != hdl)
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H_Diversity_DaqSetVRef(h->OutBuf, &len, vrefVal);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = phRpc_H_Diversity_GetDeviceBufferSize();
                    ret = phRpc_D_Diversity_DaqSetVRef(h->InBuf, len, &h->LastError.CommStatusM);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DaqSetVRef");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, vrefVal, 10);

            // Lib Status
            h->LastError.PcLibStatus = ret;
            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }
    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DaqSetGain(void *hdl, uint8_t hwType, uint8_t channelID, int32_t gainVal)
{
    uint8_t ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    uint16_t len = phRpc_H_Diversity_GetDeviceBufferSize();
    phRpc_H_t *h = NULL;

    if (NULL != hdl)
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H_Diversity_DaqSetGain(h->OutBuf, &len, hwType, channelID, gainVal);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = phRpc_H_Diversity_GetDeviceBufferSize();
                    ret = phRpc_D_Diversity_DaqSetGain(h->InBuf, len, &h->LastError.CommStatusM);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DaqSetGain");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, hwType, 10);
            phRpc_H_LogInt(h, channelID, 10);
            phRpc_H_LogInt(h, gainVal, 10);

            // Lib Status
            h->LastError.PcLibStatus = ret;
            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }
    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DaqGetGain(void *hdl, uint8_t hwType, uint8_t channelID, int32_t *gainVal)
{
    uint8_t ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    uint16_t len = phRpc_H_Diversity_GetDeviceBufferSize();
    phRpc_H_t *h = NULL;

    if ((NULL != hdl) && (NULL != gainVal))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H_Diversity_DaqGetGain(h->OutBuf, &len, hwType, channelID);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = phRpc_H_Diversity_GetDeviceBufferSize();
                    ret = phRpc_D_Diversity_DaqGetGain(h->InBuf, len, &h->LastError.CommStatusM, gainVal);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DaqGetGain");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, hwType, 10);
            phRpc_H_LogInt(h, channelID, 10);
            phRpc_H_LogInt(h, *gainVal, 10);

            // Lib Status
            h->LastError.PcLibStatus = ret;
            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }
    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DacGetFrequency(void *hdl, uint8_t channelID, uint32_t *frequencyVal)
{
    uint8_t ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    uint16_t len = phRpc_H_Diversity_GetDeviceBufferSize();
    phRpc_H_t *h = NULL;

    if ((NULL != hdl) && (NULL != frequencyVal))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H_Diversity_DacGetFrequency(h->OutBuf, &len, channelID);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = phRpc_H_Diversity_GetDeviceBufferSize();
                    ret = phRpc_D_Diversity_DacGetFrequency(h->InBuf, len, &h->LastError.CommStatusM, frequencyVal);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DacGetFrequency");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, channelID, 10);
            phRpc_H_LogInt(h, *frequencyVal, 10);

            // Lib Status
            h->LastError.PcLibStatus = ret;
            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }
    return ret;
}

// ________________________________________________________________________________________________
//
// AUX
// ________________________________________________________________________________________________

void phRpc_H_Lock(void *hdl, uint8_t lockAction)
{
    phRpc_H_t *h = (phRpc_H_t*)hdl;
    if (NULL != h->LockD) // Hdl NULL pointer check done in calling fn.
    {
        h->LockD(h->LockUserData, lockAction);
    }
}
