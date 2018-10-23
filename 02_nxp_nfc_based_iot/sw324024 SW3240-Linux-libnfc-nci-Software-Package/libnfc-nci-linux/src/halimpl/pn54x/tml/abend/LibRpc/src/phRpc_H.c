/*
*                  Copyright (c), NXP Semiconductors
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* Project: RPC Host Library / ARM-Board for PN547 V&V.
* $Author: atp01705 $
* $Revision: 29472 $
* $Date: 2014-09-09 09:25:58 +0200 (mar., 09 sept. 2014) $
*
*/

#include <stdlib.h>
#include <string.h>

#include "phPN547Dl_Common.h"

#include "phRpc_HostIo.h"
#include "phRpc_H.h"
#include "phRpc_H_Diversity.h"
#include "phRpc_HostCtx.h"

// ________________________________________________________________________________________________
//
// LOCAL PROTOTYPES
// ________________________________________________________________________________________________

uint8_t phRpc_H_DutTRxAux(void *hdl, uint8_t cmd_rw, uint8_t **xBuf, uint16_t *txBufLen, uint16_t *rxBufLen);
uint8_t phRpc_H_IoCtlAux(void *hdl, const wchar_t *fName, const uint8_t fnSelect, uint8_t ctrlMj, uint8_t ctrlMn, uint32_t *ctrlOpt);

// ________________________________________________________________________________________________
//
// IMPLEMENTATION
// ________________________________________________________________________________________________

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_GetCompatibilityInfo(void *hdl, uint8_t *cptLvl)
{
    uint8_t     ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h   = NULL;

    if ((NULL != hdl) && (NULL != cptLvl))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            ret = PH_RPC_H_STATUS_OK;
            if (0 != h->NewRPC)
            {
                if (0 != h->CompactRPC)
                {
                    *cptLvl = PH_RPC_H_COMPAT_OK;
                } else
                {
                    *cptLvl = PH_RPC_H_COMPAT_WARNING;
                }
                /// \todo Distinguish more for future RPC versions!
            } else
            {
                // Old RPC, not compatible
                *cptLvl = PH_RPC_H_COMPAT_ERROR;
            }
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_GetBuffers(void *hdl, uint8_t **outBuf, uint16_t *numSent, uint8_t **inBuf, uint16_t *numReceived)
{
    uint8_t     ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h   = NULL;

    if (NULL != hdl)
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_GetBuffers");
            phRpc_H_LogPtr(h, h);

            if (NULL != outBuf)
            {
                *outBuf = h->OutBuf;
                phRpc_H_LogPtr(h, *outBuf);
            } else
            {
                phRpc_H_LogPtr(h, NULL);
            }

            if (NULL != numSent)
            {
                *numSent      = h->NumSent;
                phRpc_H_LogInt(h, *numSent, 10);
            } else
            {
                phRpc_H_LogPtr(h, NULL);
            }

            if (NULL != inBuf)
            {
                *inBuf        = h->InBuf;
                phRpc_H_LogPtr(h, *inBuf);
            } else
            {
                phRpc_H_LogPtr(h, NULL);
            }

            if (NULL != numReceived)
            {
                *numReceived  = h->NumReceived;
                phRpc_H_LogInt(h, *numReceived, 10);
            } else
            {
                phRpc_H_LogPtr(h, NULL);
            }
            ret = 0;

            // Lib Status
            h->LastError.PcLibStatus = ret;
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_HostIoCtl(void *hdl, uint8_t ctrlMj, uint8_t ctrlMn, uint32_t *ctrlOpt)
{
    uint8_t     ret     = PH_RPC_H_STATUS_OK;
    phRpc_H_t  *h       = NULL;
    uint32_t    opt     = 0;

    if (NULL != hdl)
    {
        if (NULL != ctrlOpt)
        {
            opt = *ctrlOpt;
        } else
        {
            opt = 0;
        }

        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            switch (ctrlMj)
            {
                case PH_RPC_IOCTL_MJ_HOST_SETTRSZMUL:
                    break;

                case PH_RPC_IOCTL_MJ_HOST_PROPAGATE_DEV_ERR_RETVAL:
                    switch (ctrlMn)
                    {
                        case PH_RPC_IOCTL_MN_ENABLE:
                            h->PropagateDevErrToRetVal = 1u;
                            break;

                        case PH_RPC_IOCTL_MN_DISABLE:
                        default:
                            h->PropagateDevErrToRetVal = 0;
                            break;
                    }
                    break;

                case PH_RPC_IOCTL_MJ_HOST_FAST_CANCEL:
                    // We don't use it, it has no effect either.
                    ret = PH_RPC_H_STATUS_OK;
                    break;

                default:
                    ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
                    break;
            }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_HostIoCtl");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, ctrlMj, 16);
            phRpc_H_LogInt(h, ctrlMn, 16);

            // In case the optional parameter may be given back:
            if ((0 == ret) && (NULL != ctrlOpt))
            {
                phRpc_H_LogInt(h, *ctrlOpt, 16);
                phRpc_H_LogWStr(h, L"->");
                phRpc_H_LogInt(h, opt, 16);

                *ctrlOpt = opt;
            } else
            {
                phRpc_H_LogPtr(h, NULL);
            }

            // Lib Status
            h->LastError.PcLibStatus = ret;

            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else
    {
        ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    }

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_Raw(void *hdl, uint8_t *txBuf, uint16_t txBufLen, uint8_t *rxBuf, uint16_t *rxBufLen)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    uint16_t    len;
    phRpc_H_t  *h = (phRpc_H_t*)hdl;

    if (NULL != h)
    {
        if (PH_RPC_H_HDL_OK(h))
        {
            if ((NULL != txBuf) && (NULL != rxBuf) && (NULL != rxBufLen))
            {
                phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

                if ((txBufLen <= PH_RPC_H_DEVBUFLEN) && ((*rxBufLen) <= PH_RPC_H_DEVBUFLEN))
                {
                    len = txBufLen;
                    memcpy(h->OutBuf, txBuf, txBufLen);
                    ret = phRpc_H_RWData(h, &len);
                    if ((0 == ret) && (h->NumReceived <= (*rxBufLen)))
                    {
                        *rxBufLen = h->NumReceived;
                        memcpy(rxBuf, h->InBuf, h->NumReceived);
                    } else
                    {
                        // TRX Error:
                        *rxBufLen = 0;
                    }

                    // Log
                    phRpc_H_LogWStr(h, L"phRpc_H_Raw");
                    phRpc_H_LogPtr(h, h);
                    phRpc_H_LogPtr(h, txBuf);
                    phRpc_H_LogInt(h, txBufLen, 10);
                    phRpc_H_LogPtr(h, rxBuf);
                    phRpc_H_LogInt(h, *rxBufLen, 10);

                } else { /* Buffer too small */ }

                // Lib Status
                h->LastError.PcLibStatus = ret;

                phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
            } else
            {
                if (((uint16_t)-1) == txBufLen)
                {
                    // "Secret code" for Cancel:
                    ret = phRpc_H_CancelIo(h);
                    h->LastError.PcLibStatus = ret;
                } else
                {
                    // Param error
                }
            }
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else
    {
        // Param error
    }
    return ret;
}

// ________________________________________________________________________________________________
//
// Administrative Commands
// ________________________________________________________________________________________________

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DeviceDaq(void *hdl, uint32_t daqAddr, uint16_t daqSetLength, uint16_t daqGetLength, uint8_t **daqData)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_CMD_USER_DATA_BUFSIZE;

    if ((NULL != hdl) && (NULL != daqData))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            // Send request:
            if (0 != h->CompactRPC)
            {
                ret = phRpc_V_H00_DeviceDaq(h->OutBuf, &len, daqAddr, daqSetLength, daqGetLength, *daqData);
            } else
            {
                ret = phRpc_H00_DeviceDaq(h->OutBuf, &len, daqAddr, daqSetLength, daqGetLength, *daqData);
            }
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    uint32_t daq_addr;
                    uint16_t daq_res_len;

                    if (0 != h->CompactRPC)
                    {
                        ret = phRpc_V_D11_DeviceDaq(h->InBuf, len, &h->LastError.CommStatusM, &daq_addr, &daq_res_len, daqData);
                    } else
                    {
                        ret = phRpc_D11_DeviceDaq(h->InBuf, len, &h->LastError.CommStatusM, &daq_addr, &daq_res_len, daqData);
                    }

                    if (0 == ret)
                    {
                        if ((daq_addr != daqAddr) || (daq_res_len != daqGetLength))
                        {
                            // Same must be returned:
                            ret = PH_RPC_H_STATUS_DATA_ERROR;
                        }
                    }
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DeviceDaq");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, daqAddr, 16);
            phRpc_H_LogInt(h, daqSetLength, 10);
            phRpc_H_LogInt(h, daqGetLength, 10);
            phRpc_H_LogPtr(h, daqData);

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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_CtrlDeviceDiag(void *hdl, uint8_t **diagBuffer, uint16_t *diagLength, uint8_t diagJob)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_CMD_USER_BUFSIZE;
    uint16_t    diag_len;
    uint8_t    *req_buf;
    uint8_t    *res_buf;

    if (NULL != hdl)
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            if (NULL == diagLength)
            {
                // Nothing to be sent
                diag_len = 0;
            } else
            {
                diag_len = (*diagLength > PH_RPC_CMD_CTRLDIAG_BUFLEN) ? PH_RPC_CMD_CTRLDIAG_BUFLEN : *diagLength;
            }
            if (NULL == diagBuffer)
            {
                // Nothing can be sent
                diag_len = 0;
            } else { }

            if (0 == h->CompactRPC)
            {
                ret = phRpc_H00_CtrlDeviceDiag(h->OutBuf, &len, diagJob, diag_len, &req_buf);
            } else
            {
                ret = phRpc_V_H00_CtrlDeviceDiag(h->OutBuf, &len, diagJob, diag_len, &req_buf);
            }

            if ((NULL != diagBuffer) && (NULL != *diagBuffer))
            {
                // Copy the data into the buffer indicated:
                memcpy(req_buf, *diagBuffer, diag_len);
            }

            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_CMD_USER_BUFSIZE;
                    diag_len = PH_RPC_CMD_CTRLDIAG_BUFLEN;

                    if (0 == h->CompactRPC)
                    {
                        ret = phRpc_D11_CtrlDeviceDiag(h->InBuf, len, &h->LastError.CommStatusM, &diag_len, &res_buf);
                    } else
                    {
                        ret = phRpc_V_D11_CtrlDeviceDiag(h->InBuf, len, &h->LastError.CommStatusM, &diag_len, &res_buf);
                    }

                    if (NULL == diagLength)
                    {
                        // Nothing can be received
                    } else
                    {
                        *diagLength = (diag_len > PH_RPC_CMD_CTRLDIAG_BUFLEN) ? PH_RPC_CMD_CTRLDIAG_BUFLEN : diag_len;
                    }

                    if (NULL == diagBuffer)
                    {
                        // Not possible to return data
                    } else
                    {
                        *diagBuffer = res_buf;
                    }
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_CtrlDeviceDiag");
            phRpc_H_LogPtr(h, h);

            if ((NULL != diagBuffer) && (NULL != *diagBuffer))
            {
                phRpc_H_LogPtr(h, *diagBuffer);
            } else
            {
                phRpc_H_LogPtr(h, NULL);
            }
            if (NULL != diagLength)
            {
                phRpc_H_LogInt(h, *diagLength, 10);
            } else
            {
                phRpc_H_LogInt(h, 0, 10);
            }
            phRpc_H_LogInt(h, diagJob, 10);

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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_SetDeviceMode(void *hdl, uint8_t mode)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_H_DEVBUFLEN;

    if (NULL != hdl)
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H00_SetDeviceMode(h->OutBuf, &len, mode);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_H_DEVBUFLEN;
                    ret = phRpc_D11_SetDeviceMode(h->InBuf, len, &h->LastError.CommStatusM);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_SetDeviceMode");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, mode, 16);

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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_GetDeviceCtInfo(void *hdl, uint8_t infoType, uint32_t *infoNum, uint8_t **infoBuf, uint8_t *infoLen)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_H_DEVBUFLEN;
    uint16_t    info_len;

    if ((NULL != hdl) && (NULL != infoBuf) && (NULL != infoLen))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H00_GetDeviceCtInfo(h->OutBuf, &len, infoType);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_H_DEVBUFLEN;
                    info_len = *infoLen;
                    if (0 == h->CompactRPC)
                    {
                        ret = phRpc_D11_GetDeviceCtInfo(h->InBuf, len, &h->LastError.CommStatusM, infoNum, &info_len, infoBuf);
                    } else
                    {
                        ret = phRpc_V_D11_GetDeviceCtInfo(h->InBuf, len, &h->LastError.CommStatusM, infoNum, &info_len, infoBuf);
                    }
                    *infoLen = (uint8_t)info_len;
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_GetDeviceCtInfo");
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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_EE(void *hdl, uint8_t eeCmd, uint16_t eeAddr, uint8_t **eeBuf, uint8_t *eeLen)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_H_DEVBUFLEN;
    uint8_t    *pre_buf = NULL;
    uint16_t    ee_len;

    if ((NULL != hdl) && (NULL != eeBuf) && (NULL != eeLen))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ee_len = *eeLen;

            if (0 == h->CompactRPC)
            {
                ret = phRpc_H00_EE(h->OutBuf, &len, eeCmd, eeAddr, ee_len, &pre_buf, *eeBuf);
            } else
            {
                ret = phRpc_V_H00_EE(h->OutBuf, &len, eeCmd, eeAddr, ee_len, &pre_buf, *eeBuf);
            }

            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_H_DEVBUFLEN;
                    if (0 == h->CompactRPC)
                    {
                        ret = phRpc_D11_EE(h->InBuf, len, &h->LastError.CommStatusM, eeBuf, &ee_len);
                    } else
                    {
                        ret = phRpc_V_D11_EE(h->InBuf, len, &h->LastError.CommStatusM, eeBuf, &ee_len);
                    }
                    *eeLen = (uint8_t)ee_len;
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_EE");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, eeCmd, 16);
            phRpc_H_LogInt(h, eeAddr, 16);
            if (NULL != *eeBuf)
            {
                phRpc_H_LogPtr(h, eeBuf);
            } else
            {
                phRpc_H_LogPtr(h, NULL);
            }
            phRpc_H_LogInt(h, *eeLen, 10);

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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_EECfg(void *hdl, uint8_t eeCmd)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_H_DEVBUFLEN;

    if (NULL != hdl)
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H00_EECfg(h->OutBuf, &len, eeCmd);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_H_DEVBUFLEN;
                    ret = phRpc_D11_EECfg(h->InBuf, len, &h->LastError.CommStatusM);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_EECfg");
            phRpc_H_LogInt(h, eeCmd, 16);

            // Lib Status
            h->LastError.PcLibStatus = ret;

            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else
    {
    }

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_StartTestSw(void *hdl, uint32_t startParam, uint8_t *startStatus)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_H_DEVBUFLEN;

    if ((NULL != hdl) && (NULL != startStatus))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H00_StartTestSwCt(h->OutBuf, &len, startParam);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_H_DEVBUFLEN;
                    ret = phRpc_D11_StartTestSwCt(h->InBuf, len, &h->LastError.CommStatusM, startStatus);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_StartTestSw");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, startParam, 16);
            phRpc_H_LogInt(h, *startStatus, 16);

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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_StopTestSw(void *hdl, uint8_t *stopStatus)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_H_DEVBUFLEN;

    if ((NULL != hdl) && (NULL != stopStatus))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H00_StopTestSwCt(h->OutBuf, &len);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_H_DEVBUFLEN;
                    ret = phRpc_D11_StopTestSwCt(h->InBuf, len, &h->LastError.CommStatusM, stopStatus);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_StopTestSw");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, *stopStatus, 16);

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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DataExchangeTestSw(void *hdl, uint8_t **xBuf, uint16_t *txBufLen, uint16_t *rxBufLen)
{
    uint8_t     ret         = 1u;
    phRpc_H_t  *h           = NULL;
    uint16_t    len         = PH_RPC_H_DEVBUFLEN;
    uint16_t    in_rxlen    = 0;

    if ((NULL != hdl) && (NULL != xBuf) && (NULL != xBuf) && (NULL != txBufLen) && (NULL != rxBufLen))
    {
        phRpc_H_LimitLength(txBufLen, rxBufLen);
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            in_rxlen = *rxBufLen;

            if (0 == h->CompactRPC)
            {
                ret = phRpc_H00_DataExchangeTestSwCt(h->OutBuf, &len, *rxBufLen, *txBufLen, *xBuf);
            } else
            {
                ret = phRpc_V_H00_DataExchangeTestSwCt(h->OutBuf, &len, *rxBufLen, *txBufLen, *xBuf);
            }

            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_H_DEVBUFLEN;
                    if (0 == h->CompactRPC)
                    {
                        ret = phRpc_D11_DataExchangeTestSwCt(h->InBuf, len, &h->LastError.CommStatusM, rxBufLen, txBufLen, xBuf);
                    } else
                    {
                        ret = phRpc_V_D11_DataExchangeTestSwCt(h->InBuf, len, &h->LastError.CommStatusM, rxBufLen, txBufLen, xBuf);
                    }
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DataExchangeTestSw");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogPtr(h, xBuf);
            phRpc_H_LogInt(h, *txBufLen, 10);
            phRpc_H_LogInt(h, in_rxlen, 10);
            phRpc_H_LogWStr(h, L"->");
            phRpc_H_LogInt(h, *rxBufLen, 10);

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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DutInit(void *hdl, uint8_t hiFn, uint8_t hiAddr, uint32_t hiSpeed, uint8_t hiClkPol, uint8_t hiClkPha)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_H_DEVBUFLEN;

    if ((NULL != hdl) && ((0 != hiSpeed) || (PH_RPC_CMD_DEV_DISABLE_EXT_INTF == hiFn)))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H00_DutInit(h->OutBuf, &len, hiFn, hiAddr, hiSpeed, hiClkPol, hiClkPha);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_H_DEVBUFLEN;
                    ret = phRpc_D11_DutInit(h->InBuf, len, &h->LastError.CommStatusM);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DutInit");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, hiFn, 16);
            phRpc_H_LogInt(h, hiAddr, 16);
            phRpc_H_LogInt(h, hiSpeed, 10);
            phRpc_H_LogInt(h, hiClkPol, 16);
            phRpc_H_LogInt(h, hiClkPha, 16);

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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DutGetMode(void *hdl, uint32_t *hiMode)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_H_DEVBUFLEN;

    if ((NULL != hdl) && (NULL != hiMode))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H00_DutGetMode(h->OutBuf, &len);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_H_DEVBUFLEN;
                    ret = phRpc_D11_DutGetMode(h->InBuf, len, &h->LastError.CommStatusM, hiMode);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DutGetMode");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogInt(h, *hiMode, 16);

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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DutRx(void *hdl, uint8_t **xBuf, uint16_t *rxBufLen)
{
    uint16_t tx_len = 0;

    // Log
    if (NULL != hdl)
    {
        phRpc_H_LogWStr(hdl, L"phRpc_H_DutRx");
    }

    // We will not serialise down anything, so the buffer will be set to NULL explicitly:
    if (NULL != xBuf)
    {
        *xBuf = NULL;
    } else { }
    return phRpc_H_DutTRxAux(hdl, PH_RPC_CMD_DEV_R, xBuf, &tx_len, rxBufLen);
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DutTx(void *hdl, uint8_t **xBuf, uint16_t *xBufLen)
{
    uint8_t     ret     = 0;
    uint16_t    rx_len  = PH_RPC_H_DEVBUFLEN;

    // Log
    if (NULL != hdl)
    {
        phRpc_H_LogWStr(hdl, L"phRpc_H_DutTx");
    }

    ret = phRpc_H_DutTRxAux(hdl, PH_RPC_CMD_DEV_W, xBuf, xBufLen, &rx_len);
    if ((0 == ret) && (NULL != xBufLen))
    {
        *xBufLen = rx_len;
    } else { }

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DutTRx(void *hdl, uint8_t **xBuf, uint16_t *txBufLen, uint16_t *rxBufLen)
{
    // Log
    if (NULL != hdl)
    {
        phRpc_H_LogWStr(hdl, L"phRpc_H_DutTRx");
    }

    return phRpc_H_DutTRxAux(hdl, PH_RPC_CMD_DEV_RW, xBuf, txBufLen, rxBufLen);
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DevIoCtl(void *hdl, uint8_t ctrlMj, uint8_t ctrlMn, uint32_t *ctrlOpt)
{
    const wchar_t fname[] = L"phRpc_H_DevIoCtl";
    const uint8_t f_sel   = PH_RPC_H_IOCTLFNSELECT_DEVIOCTL;
    return phRpc_H_IoCtlAux(hdl, fname, f_sel, ctrlMj, ctrlMn, ctrlOpt);
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DevIoLineCtl(void *hdl, uint8_t ctrlItem, uint8_t ctrlAction, uint32_t *ctrlOpt)
{
    const wchar_t fname[] = L"phRpc_H_DevIoLineCtl";
    const uint8_t f_sel   = PH_RPC_H_IOCTLFNSELECT_DEVIOLINECTL;
    return phRpc_H_IoCtlAux(hdl, fname, f_sel, ctrlItem, ctrlAction, ctrlOpt);
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DutSetMinIOMode(void *hdl, uint8_t *altAddr, uint8_t activationState)
{
    uint8_t          ret    = PH_RPC_H_STATUS_INVALID_PARAMETER;
    uint32_t         param  = 0;
    phRpc_H_t       *h      = NULL;
    phRpc_H_MinIO_t *md     = NULL;

    if ((NULL != hdl) && (NULL != altAddr))
    {
        h  = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            md = &(h->MinIOData);
            switch (activationState)
            {
                case 1u:
                    // Activate
                    if (0 == md->Active)
                    {
                        ret = phRpc_H_DutGetMode(h, &param);
                        if (0 == ret)
                        {
                            md->RawMode    = (0 != (param & PH_PN547DL_RAWMODE_MASK))           ? 1u : 0;
                            md->HandleIntr = (0 != (param & PH_PN547DL_ENABLE_EINT_SENSE_MASK)) ? 1u : 0;
                            md->CalcCrc    = (0 != (param & PH_PN547DL_ENABLE_CRC_MASK))        ? 1u : 0;
                            param = 0xFFFFFFFFu;
                            ret += phRpc_H_DevIoCtl(h, PH_RPC_IOCTL_MJ_DEV_RAWMODE, PH_RPC_IOCTL_MN_ENABLE, &param);
                            ret += phRpc_H_DevIoCtl(h, PH_RPC_IOCTL_MJ_DEV_EINT_SENSE_ENABLE, PH_RPC_IOCTL_MN_DISABLE, &param);
                            ret += phRpc_H_DevIoCtl(h, PH_RPC_IOCTL_MJ_DEV_CRC_ENABLE, PH_RPC_IOCTL_MN_DISABLE, &param);
                            param = *altAddr;
                            ret += phRpc_H_DevIoCtl(h, PH_RPC_IOCTL_MJ_DEV_SET_I2C_ADDRESS, PH_RPC_IOCTL_MN_VOID, &param);
                            *altAddr = (uint8_t)param;
                        } else { }
                    } else { }
                    break;

                case 0:
                default:
                    // Deactivate
                    if (0 == md->Active)
                    {
                        ret = 0;
                        param = 0xFFFFFFFFu;
                        ret += phRpc_H_DevIoCtl(h, PH_RPC_IOCTL_MJ_DEV_RAWMODE,
                                                (0 == md->RawMode) ? PH_RPC_IOCTL_MN_DISABLE : PH_RPC_IOCTL_MN_ENABLE,
                                                &param);
                        ret += phRpc_H_DevIoCtl(h, PH_RPC_IOCTL_MJ_DEV_EINT_SENSE_ENABLE,
                                                (0 == md->HandleIntr) ? PH_RPC_IOCTL_MN_DISABLE : PH_RPC_IOCTL_MN_ENABLE,
                                                &param);
                        ret += phRpc_H_DevIoCtl(h, PH_RPC_IOCTL_MJ_DEV_CRC_ENABLE,
                                                (0 == md->CalcCrc) ? PH_RPC_IOCTL_MN_DISABLE : PH_RPC_IOCTL_MN_ENABLE,
                                                &param);
                        param = *altAddr;
                        ret += phRpc_H_DevIoCtl(h, PH_RPC_IOCTL_MJ_DEV_SET_I2C_ADDRESS, PH_RPC_IOCTL_MN_VOID, &param);
                        *altAddr = (uint8_t)param;
                    } else { }
                    break;
            }
            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DutSetMinIOMode");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogPtr(h, altAddr);
            phRpc_H_LogInt(h, activationState, 10);

            // Lib Status
            h->LastError.PcLibStatus = ret;
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else { /* Param check error */ }

    return (ret > 0) ? 1u : 0;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DeviceCommCheck(void *hdl, uint8_t *inBuf, uint8_t inBufLen, uint8_t msWait, uint8_t **outBuf, uint8_t *outBufLen)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_H_DEVBUFLEN;
    uint16_t    o_len;

    if ((NULL != hdl) && (NULL != inBuf) && (NULL != outBuf) && (NULL != outBufLen))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            if (0 == h->CompactRPC)
            {
                ret = phRpc_H00_DeviceCommCheck(h->OutBuf, &len, msWait, inBufLen, inBuf);
            } else
            {
                ret = phRpc_V_H00_DeviceCommCheck(h->OutBuf, &len, msWait, inBufLen, inBuf);
            }

            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_H_DEVBUFLEN;
                    o_len = *outBufLen;
                    if (0 == h->CompactRPC)
                    {
                        ret = phRpc_D11_DeviceCommCheck(h->InBuf, len, &h->LastError.CommStatusM, &o_len, outBuf);
                    } else
                    {
                        ret = phRpc_V_D11_DeviceCommCheck(h->InBuf, len, &h->LastError.CommStatusM, &o_len, outBuf);
                    }
                    *outBufLen = (uint8_t)o_len;
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DeviceCommCheck");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogPtr(h, inBuf);
            phRpc_H_LogInt(h, inBufLen, 10);
            phRpc_H_LogInt(h, msWait, 10);
            phRpc_H_LogPtr(h, *outBuf);
            phRpc_H_LogInt(h, *outBufLen, 10);

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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DeviceCommCheckLong(void *hdl, uint8_t *inBuf, uint16_t inBufLen, uint8_t msWait, uint8_t **outBuf, uint16_t *outBufLen)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_H_DEVBUFLEN;

    if ((NULL != hdl) && (NULL != inBuf) && (NULL != outBuf) && (NULL != outBufLen))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            if (0 == h->CompactRPC)
            {
                ret = phRpc_H00_DeviceCommCheckL(h->OutBuf, &len, msWait, inBufLen, inBuf);
            } else
            {
                ret = phRpc_V_H00_DeviceCommCheckL(h->OutBuf, &len, msWait, inBufLen, inBuf);
            }

            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_H_DEVBUFLEN;
                    if (0 == h->CompactRPC)
                    {
                        ret = phRpc_D11_DeviceCommCheckL(h->InBuf, len, &h->LastError.CommStatusM, outBufLen, outBuf);
                    } else
                    {
                        ret = phRpc_V_D11_DeviceCommCheckL(h->InBuf, len, &h->LastError.CommStatusM, outBufLen, outBuf);
                    }
                } else { }
            } else { }
            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DeviceCommCheckLong");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogPtr(h, inBuf);
            phRpc_H_LogInt(h, inBufLen, 10);
            phRpc_H_LogInt(h, msWait, 10);
            phRpc_H_LogPtr(h, *outBuf);
            phRpc_H_LogInt(h, *outBufLen, 10);

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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DeviceCommCheckWTX(void *hdl, uint8_t *inBuf, uint16_t inBufLen, uint16_t msWait, uint8_t **outBuf, uint16_t *outBufLen)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_H_DEVBUFLEN;

    if ((NULL != hdl) && (NULL != inBuf) && (NULL != outBuf) && (NULL != outBufLen))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_H00_DeviceCommCheckWTX(h->OutBuf, &len, inBufLen, msWait, inBuf);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_H_DEVBUFLEN;
                    if (0 == h->CompactRPC)
                    {
                        ret = phRpc_D11_DeviceCommCheckWTX(h->InBuf, len, &h->LastError.CommStatusM, outBufLen, outBuf);
                    } else
                    {
                        ret = phRpc_V_D11_DeviceCommCheckWTX(h->InBuf, len, &h->LastError.CommStatusM, outBufLen, outBuf);
                    }
                } else { }
            } else { }
            // Log
            phRpc_H_LogWStr(h, L"phRpc_H_DeviceCommCheckWTX");
            phRpc_H_LogPtr(h, h);
            phRpc_H_LogPtr(h, inBuf);
            phRpc_H_LogInt(h, inBufLen, 10);
            phRpc_H_LogInt(h, msWait, 10);
            phRpc_H_LogPtr(h, *outBuf);
            phRpc_H_LogInt(h, *outBufLen, 10);

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

uint8_t PH_RPC_H_LIBFUNC *phRpc_H_GetErrorText(phRpc_Status_t *rpcStatus)
{
    static const char* err_text[] =
    {
        /* 0x00 */ "Operation finished normally",
        /* 0x01 */ "An initialisation failed",
        /* 0x02 */ "An I/O operation timed out",
        /* 0x03 */ "The device sent/received less data than requested",
        /* 0x04 */ "A parameter is not valid (e.g. out of range)",
        /* 0x05 */ "CRC Error",
        /* 0x06 */ "Invalid device state",
        /* 0x07 */ "Hardware failure detected",
        /* 0x08 */ "FIFO Overrun",
        /* 0x09 */ "Framing error",
        /* 0x0A */ "", /* Reserved */
        /* 0x0B */ "", /* Reserved */
        /* 0x0C */ "", /* Reserved */
        /* 0x0D */ "", /* Reserved */
        /* 0x0E */ "", /* Reserved */
        /* 0x0F */ "", /* Reserved */
        /* 0x10 */ "Break Condition",
        /* 0x11 */ "FIFO Error",
        /* 0x12 */ "DMA Error",
        /* 0x13 */ "TX Timeout Error",
        /* 0x14 */ "The provided buffer is too small to hold the response",
        /* 0x15 */ "Length error or mismatch in the received data",
        /* 0x16 */ "Error occurred during transmission",
        /* 0x17 */ "Error occurred during reception",
        /* 0x18 */ "The transfer has been aborted by the device",
        /* 0x19 */ "Invalid header or protocol control byte",
        /* 0x1A */ "", /* Reserved */
        /* 0x1B */ "", /* Reserved */
        /* 0x1C */ "", /* Reserved */
        /* 0x1d */ "", /* Reserved */
        /* 0x1D */ "", /* Reserved */
        /* 0x1F */ "", /* Reserved */
        /* 0x20 */ "The descriptor is wrong" ,
        /* 0x21 */ "An internal re-synchronization was done",
        /* 0x22 */ "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        /* 0x30 */ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        /* 0x40 */ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        /* 0x50 */ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        /* 0x60 */ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        /* 0x70 */ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        /* 0x80 */ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        /* 0x90 */ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        /* 0xA0 */ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        /* 0xB0 */ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        /* 0xC0 */ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        /* 0xD0 */ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        /* 0xE0 */ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        /* 0xF0 */ "", "", "", "", "", "", "", "",
        /* 0xF8 */ "An internal error has occurred",
        /* 0xF9 */ "An invalid request has been issued",
        /* 0xFA */ "An other, unspecified error has occurred",
        /* 0xFB */ "The I/O operation was cancelled",
        /* 0xFC */ "", "", "",
        /* 0xFF */ "X" /* X..Test */
    };
    static const char invalid_param_txt[] = "[Lookup Error: INVALID PARAMETER]";
    static const char invalid_code_txt[]  = "[Lookup Error: INVALID ERROR CODE]";
    char *pmsg;

    if (NULL != rpcStatus)
    {
        pmsg = (char*)err_text[PH_RPC_GET_STATUS(rpcStatus)];
        if (0 == pmsg[0])
        {
            pmsg = (char*)invalid_code_txt;
        } else { /* OK */ }
    } else
    {
        pmsg = (char*)invalid_param_txt;
    }

    return (uint8_t*)pmsg;
}

uint8_t PH_RPC_H_LIBFUNC *phRpc_H_GetHostErrorText(phRpc_Status_t *rpcStatus)
{
    static const char* err_text[] =
    {
        "The operation was successful.",                                    // 0
        "One or more parameters are invalid.",                              // 1
        "The function is not implemented.",                                 // 2
        "The handle is invalid.",                                           // 3
        "An I/O error or warning on the device has occurred.",              // 4
        "A communication framing error has occurred.",                      // 5
        "A communication timeout error has occurred.",                      // 6
        "The I/O library or driver has malfunctioned.",                     // 7
        "The I/O library or driver could not be opened.",                   // 8
        "Unknown error."                                                    // 9
        "", "", "", "", "", "", "",                                         // 0x10
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",     // 0x20
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",     // 0x30
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",     // 0x40
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",     // 0x50
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",     // 0x60
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",     // 0x70
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",     // 0x80
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",     // 0x90
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",     // 0xA0
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",     // 0xB0
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",     // 0xC0
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",     // 0xD0
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",     // 0xE0
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",     // 0xF0
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "X"     // 0xFF     X..Test
    };
    static const char invalid_param_txt[] = "[Lookup Error: INVALID PARAMETER]";
    static const char invalid_code_txt[]  = "[Lookup Error: INVALID ERROR CODE]";
    char *pmsg;

    if (NULL != rpcStatus)
    {
        pmsg = (char*)err_text[(uint8_t)(rpcStatus->PcLibStatus)];
        if (0 == pmsg[0])
        {
            pmsg = (char*)invalid_code_txt;
        } else { /* OK */ }
    } else
    {
        pmsg = (char*)invalid_param_txt;
    }

    return (uint8_t*)pmsg;
}

uint8_t PH_RPC_H_LIBFUNC phRpc_H_GetHostCtxText(void *hdl, int itemNum, wchar_t *txtBuf, size_t *txtBufLen)
{
    uint8_t ret = PH_RPC_H_STATUS_OK;

    if ((NULL != hdl) && (NULL != txtBuf) && (NULL != txtBufLen))
    {
        phRpc_H_t *h = (phRpc_H_t*)hdl;
        phRpc_H_ToString(h, itemNum, txtBuf, txtBufLen);
    } else
    {
        ret = PH_RPC_H_STATUS_INVALID_HANDLE;
    }

    return ret;
}

// ________________________________________________________________________________________________
//
// AUX
// ________________________________________________________________________________________________

uint8_t phRpc_H_DutTRxAux(void *hdl, uint8_t cmd_rw, uint8_t **xBuf, uint16_t *txBufLen, uint16_t *rxBufLen)
{
    uint8_t     ret                             = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h                               = NULL;
    uint16_t    len                             = PH_RPC_H_DEVBUFLEN;
    uint8_t    *pre_buf;

    uint8_t    *xbuf_in;
    uint16_t    txbuf_len_in;
    uint16_t    rxbuf_len_in;

    if ((NULL != hdl) && (NULL != xBuf) && (NULL != txBufLen) && (NULL != rxBufLen) &&
        ((0 != *txBufLen) || (0 != *rxBufLen)))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            xbuf_in      = *xBuf;
            txbuf_len_in = *txBufLen;
            rxbuf_len_in = *rxBufLen;

            // Limit to what is allowed
            phRpc_H_LimitLength(txBufLen, rxBufLen);

            if ((*txBufLen < PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT) && (*rxBufLen < PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT))
            {
                if (0 == h->CompactRPC)
                {
                    ret = phRpc_H00_DutRWShort(h->OutBuf, &len, cmd_rw, *rxBufLen, *txBufLen, &pre_buf, *xBuf);
                } else
                {
                    ret = phRpc_V_H00_DutRWShort(h->OutBuf, &len, cmd_rw, *rxBufLen, *txBufLen, &pre_buf, *xBuf);
                }
            } else
            {
                if (0 == h->CompactRPC)
                {
                    ret = phRpc_H00_DutRWLong(h->OutBuf, &len, cmd_rw, *rxBufLen, *txBufLen, &pre_buf, *xBuf);
                } else
                {
                    ret = phRpc_V_H00_DutRWLong(h->OutBuf, &len, cmd_rw, *rxBufLen, *txBufLen, &pre_buf, *xBuf);
                }
            }

            // We received the address of the "pre-buf" within the serialised buffer: Preset its contents:
            memset(pre_buf, 0xA5, PH_RPC_CMD_PREPEND_LEN);

            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_H_DEVBUFLEN;

                    // Device auto-selects short or long serialisation, depending on number of bytes to return:
                    switch (phRpc_H_GetFid(h->InBuf))
                    {
                        case PH_RPC_CMD_DEV_RW_SHORT:
                            if (0 == h->CompactRPC)
                            {
                                ret = phRpc_D11_DutRWShort(h->InBuf, len, &h->LastError.CommStatusM, rxBufLen, txBufLen, &pre_buf, xBuf);
                            } else
                            {
                                ret = phRpc_V_D11_DutRWShort(h->InBuf, len, &h->LastError.CommStatusM, rxBufLen, txBufLen, &pre_buf, xBuf);
                            }
                            break;

                        case PH_RPC_CMD_DEV_RW_LONG:
                            if (0 == h->CompactRPC)
                            {
                                ret = phRpc_D11_DutRWLong(h->InBuf, len, &h->LastError.CommStatusM, rxBufLen, txBufLen, &pre_buf, xBuf);
                            } else
                            {
                                ret = phRpc_V_D11_DutRWLong(h->InBuf, len, &h->LastError.CommStatusM, rxBufLen, txBufLen, &pre_buf, xBuf);
                            }
                            break;

                        default:
                            // The data (from which the deserialisation function ID is determined) in the input buffer is invalid.
                            // Most likely there was a device malfunction or a USB error.
                            ret = PH_RPC_H_STATUS_FRAMING_ERROR;
                            break;
                    }
                } else
                {
                    // I/O error
                }
            } else { }

            // Error on the device
            if (0 != h->PropagateDevErrToRetVal)
            {
                if ((0 == ret) && (PH_RPC_STATUS_OK != (h->LastError.CommStatusM & 0xFFu)))
                {
                    ret = PH_RPC_H_STATUS_DEVICE_IO;
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"AUX:");
            phRpc_H_LogPtr(h, xbuf_in);
            phRpc_H_LogWStr(h, L"( ->");
            phRpc_H_LogPtr(h, xBuf);
            phRpc_H_LogWStr(h, L")");
            phRpc_H_LogInt(h, txbuf_len_in, 10);
            phRpc_H_LogWStr(h, L"( ->");
            phRpc_H_LogInt(h, *txBufLen, 10);
            phRpc_H_LogWStr(h, L")");
            phRpc_H_LogInt(h, rxbuf_len_in, 10);
            phRpc_H_LogWStr(h, L"( ->");
            phRpc_H_LogInt(h, *rxBufLen, 10);
            phRpc_H_LogWStr(h, L")");

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

uint8_t phRpc_H_IoCtlAux(void *hdl, const wchar_t *fName, const uint8_t fnSelect, uint8_t ctrlMj, uint8_t ctrlMn, uint32_t *ctrlOpt)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_H_DEVBUFLEN;
    uint32_t    opt     = 0;

    if (NULL != hdl)
    {
        if (NULL != ctrlOpt)
        {
            opt = *ctrlOpt;
        } else
        {
            switch (fnSelect)
            {
                case PH_RPC_H_IOCTLFNSELECT_DEVIOCTL:
                    opt = PH_RPC_IOCTL_OPT_NOT_APPLICABLE;
                    break;

                default:
                case PH_RPC_H_IOCTLFNSELECT_DEVIOLINECTL:
                    opt = PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE;
                    break;
            }
        }

        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            switch (fnSelect)
            {
                case PH_RPC_H_IOCTLFNSELECT_DEVIOCTL:
                    ret = phRpc_H00_DevIoCtrl(h->OutBuf, &len, ctrlMj, ctrlMn, opt);
                    break;

                case PH_RPC_H_IOCTLFNSELECT_DEVIOLINECTL:
                default:
                    ret = phRpc_H00_DevIoLineCtrl(h->OutBuf, &len, ctrlMj, ctrlMn, opt);
                    break;
            }

            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_H_DEVBUFLEN;

                    switch (fnSelect)
                    {
                        case PH_RPC_H_IOCTLFNSELECT_DEVIOCTL:
                            ret = phRpc_D11_DevIoCtrl(h->InBuf, len, &h->LastError.CommStatusM, &opt);
                            break;

                        case PH_RPC_H_IOCTLFNSELECT_DEVIOLINECTL:
                        default:
                            ret = phRpc_D11_DevIoLineCtrl(h->InBuf, len, &h->LastError.CommStatusM, &opt);
                            break;
                    }

                    // Error on the device
                    if (0 != h->PropagateDevErrToRetVal)
                    {
                        if ((0 == ret) && (PH_RPC_STATUS_OK != (h->LastError.CommStatusM & 0xFFu)))
                        {
                            ret = PH_RPC_H_STATUS_DEVICE_IO;
                        } else { }
                    } else { }

                    // Log
                    phRpc_H_LogWStr(h, (wchar_t*)fName);
                    phRpc_H_LogPtr(h, h);
                    phRpc_H_LogInt(h, ctrlMj, 16);
                    phRpc_H_LogInt(h, ctrlMn, 16);

                    if (NULL != ctrlOpt)
                    {
                        phRpc_H_LogInt(h, *ctrlOpt, 16);
                        phRpc_H_LogWStr(h, L"->");
                        phRpc_H_LogInt(h, opt, 16);

                        *ctrlOpt = opt;
                    } else { }
                } else { }
            } else { }

            // Lib Status
            h->LastError.PcLibStatus = ret;

            phRpc_H_Lock(h, PH_RPC_H_LOCK_RELEASE);
        } else
        {
            ret = PH_RPC_H_STATUS_INVALID_HANDLE;
        }
    } else
    {
        /* Param check error */
        ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    }

    if (ret     == PH_RPC_H_STATUS_INVALID_PARAMETER)
    {
        ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    }

    return ret;
}

void phRpc_H_LimitLength(uint16_t *txBufLen, uint16_t *rxBufLen)
{
    if (NULL != txBufLen)
    {
        *txBufLen = ((*txBufLen) >= PH_RPC_H_USABLE_LEN) ? PH_RPC_H_USABLE_LEN : (*txBufLen);
    } else { }

    if (NULL != rxBufLen)
    {
        *rxBufLen = ((*rxBufLen) >= PH_RPC_H_USABLE_LEN) ? PH_RPC_H_USABLE_LEN : (*rxBufLen);
    } else { }
}
