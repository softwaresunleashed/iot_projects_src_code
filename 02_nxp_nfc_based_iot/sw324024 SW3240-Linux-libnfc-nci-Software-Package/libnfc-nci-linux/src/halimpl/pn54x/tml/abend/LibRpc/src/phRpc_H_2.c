
/*
*                  Copyright (c), NXP Semiconductors
*
*                      (C)NXP Semiconductors
*        All rights are reserved. Reproduction in whole or in part is
*       prohibited without the written consent of the copyright owner.
*   NXP reserves the right to make changes without notice at any time.
*  NXP makes no warranty, expressed, implied or statutory, including but
*  not limited to any implied warranty of merchantability or fitness for any
* particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* Project: RPC Host Library / ARM-Board for PN547 V&V.
* $Author: atp01705 $
* $Revision: 19533 $
* $Date: 2013-05-22 19:03:21 +0200 (Mi, 22 Mai 2013) $
*
*/

#include <stdlib.h>
#include <string.h>

#include "phSwId.h"

#include "phRpc_HostIo.h"
#include "phRpc_H_2.h"
#include "phRpc_H_Diversity.h"
#include "phRpc_HostCtx.h"

#include "phRpc_HostSerialiser_2.h"
#include "phRpc_HostDeSerialiser_2.h"

// ________________________________________________________________________________________________
//
// LOCAL PROTOTYPES
// ________________________________________________________________________________________________

uint8_t phRpc_2_H_DutTRxAux(void *hdl, uint8_t cmd_rw, uint32_t *trxFlags, uint8_t **xBuf, uint16_t *txBufLen, uint16_t *rxBufLen);
uint8_t phRpc_2_H_IoCtlAux(void *hdl, const wchar_t *fName, const uint8_t fnSelect, uint8_t ctrlMj, uint8_t ctrlMn, uint32_t *ctrlOpt);
void    phRpc_2_H_LimitLength(uint16_t *txBufLen, uint16_t *rxBufLen);

// ________________________________________________________________________________________________
//
// IMPLEMENTATION
// ________________________________________________________________________________________________

#define PH_RPC_DAQ_DBG 0

#if PH_RPC_DAQ_DBG != 0
#include <stdio.h>
#endif

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DeviceDaq(void *hdl, uint32_t daqAddr, uint16_t daqSetLength, uint16_t daqGetLength, uint8_t **daqData)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_2_CMD_USER_DATA_BUFSIZE;

    if ((NULL != hdl) && (NULL != daqData))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            #if PH_RPC_DAQ_DBG != 0
            #warning DAQ Debug = ON: NOT FOR PRODUCTION.
            uint8_t i;
            printf("DAQ Set Len = %d: ", daqSetLength);
            printf("daqAddr = %08X, ", daqAddr);
            printf("*daqData = %p, ", *daqData);
            printf("daqData = %p, ", daqData);
            for (i = 0; i  < daqSetLength; i++)
            {
                printf("%02X", (*daqData)[i]);
            }
            printf("\n");
            #endif

            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            // Send request:
            if (0 != h->CompactRPC)
            {
                ret = phRpc_2_V_H00_DeviceDaq(h->OutBuf, &len, daqAddr, daqSetLength, daqGetLength, *daqData);
            } else
            {
                ret = phRpc_2_H00_DeviceDaq(h->OutBuf, &len, daqAddr, daqSetLength, daqGetLength, *daqData);
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
                        ret = phRpc_2_V_D11_DeviceDaq(h->InBuf, len, &h->LastError.CommStatusM, &daq_addr, &daq_res_len, daqData);
                    } else
                    {
                        ret = phRpc_2_D11_DeviceDaq(h->InBuf, len, &h->LastError.CommStatusM, &daq_addr, &daq_res_len, daqData);
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
            phRpc_H_LogWStr(h, L"phRpc_2_H_DeviceDaq");
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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DutInit(void *hdl, uint8_t hiFn , uint8_t hiAddr, uint32_t hiSpeed, uint8_t hiClkPol, uint8_t hiClkPha)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_2_H_DEVBUFLEN;

    if ((NULL != hdl) && ((0 != hiSpeed) || (PH_RPC_2_CMD_DEV_DISABLE_EXT_INTF == hiFn)))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_2_H00_DutInit(h->OutBuf, &len, hiFn, hiAddr, hiSpeed, hiClkPol, hiClkPha);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_2_H_DEVBUFLEN;
                    ret = phRpc_2_D11_DutInit(h->InBuf, len, &h->LastError.CommStatusM);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_2_H_DutInit");
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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DutGetMode(void *hdl, uint32_t *hiMode)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_2_H_DEVBUFLEN;

    if ((NULL != hdl) && (NULL != hiMode))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_2_H00_DutGetMode(h->OutBuf, &len);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_2_H_DEVBUFLEN;
                    ret = phRpc_2_D11_DutGetMode(h->InBuf, len, &h->LastError.CommStatusM, hiMode);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_2_H_DutGetMode");
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

    return ret;}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DutRx(void *hdl, uint32_t *rxFlags, uint8_t **rxBuf, uint16_t *rxBufLen)
{
    uint16_t tx_len = 0;
    uint8_t  ret    = 0;

    // Log
    if (NULL != hdl)
    {
        phRpc_H_LogWStr(hdl, L"phRpc_2_H_DutRx");
    }

    // We will not serialise down anything, so the buffer will be set to NULL explicitly:
    if (NULL != rxBuf)
    {
        *rxBuf = NULL;
    } else { }
    ret = phRpc_2_H_DutTRxAux(hdl, PH_RPC_2_CMD_DEV_R, rxFlags, rxBuf, &tx_len, rxBufLen);

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DutTx(void *hdl, uint32_t txFlags, uint8_t **txBuf, uint16_t *txBufLen)
{
    uint8_t     ret     = 0;
    uint16_t    rx_len  = PH_RPC_2_H_DEVBUFLEN;
    uint32_t    flags   = txFlags;

    // Log
    if (NULL != hdl)
    {
        phRpc_H_LogWStr(hdl, L"phRpc_2_H_DutTx");
    }

    ret = phRpc_2_H_DutTRxAux(hdl, PH_RPC_2_CMD_DEV_W, &flags, txBuf, txBufLen, &rx_len);
    if ((0 == ret) && (NULL != txBufLen))
    {
        *txBufLen = rx_len;
    } else { }

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DevIoCtl(void *hdl, uint8_t ctrlMj, uint8_t ctrlMn, uint32_t *ctrlOpt)
{
    const wchar_t fname[] = L"phRpc_2_H_DevIoCtl";
    const uint8_t f_sel   = PH_RPC_H_IOCTLFNSELECT_DEVIOCTL;
    return phRpc_2_H_IoCtlAux(hdl, fname, f_sel, ctrlMj, ctrlMn, ctrlOpt);
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DevIoLineCtl(void *hdl, uint8_t ctrlItem, uint8_t ctrlAction, uint32_t *ctrlOpt)
{
    const wchar_t fname[] = L"phRpc_2_H_DevIoLineCtl";
    const uint8_t f_sel   = PH_RPC_H_IOCTLFNSELECT_DEVIOLINECTL;
    return phRpc_2_H_IoCtlAux(hdl, fname, f_sel, ctrlItem, ctrlAction, ctrlOpt);
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_GetTransferLog(void *hdl, uint8_t rxNotTx, uint8_t *numTransfers, uint32_t *transferData, uint16_t *transferLen)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_2_H_DEVBUFLEN;

    if ((NULL != hdl) && (NULL != numTransfers) && (NULL != transferData) && (NULL != transferLen))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_2_H00_GetTransferLog(h->OutBuf, &len, rxNotTx, *numTransfers);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_2_H_DEVBUFLEN;
                    //ret = phRpc_2_D11_DutInit(h->InBuf, len, &h->LastError.CommStatusM);
                    ret = phRpc_2_D11_GetTransferLog(h->InBuf, len, &h->LastError.CommStatusM, numTransfers, transferData, transferLen);
                } else { }
            } else { }

            // Log
            phRpc_H_LogWStr(h, L"phRpc_2_H_GetTransferLog");
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

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DeviceCommCheckWTX(void *hdl, uint8_t *inBuf, uint16_t inBufLen, uint16_t msWait, uint8_t **outBuf, uint16_t *outBufLen)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_2_H_DEVBUFLEN;

    if ((NULL != hdl) && (NULL != inBuf) && (NULL != outBuf) && (NULL != outBufLen))
    {
        h = (phRpc_H_t*)hdl;
        if (PH_RPC_H_HDL_OK(h))
        {
            phRpc_H_Lock(h, PH_RPC_H_LOCK_ACQUIRE);

            ret = phRpc_2_H00_DeviceCommCheckWTX(h->OutBuf, &len, msWait, inBufLen, inBuf);
            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_2_H_DEVBUFLEN;
                    if (0 == h->CompactRPC)
                    {
                        ret = phRpc_2_D11_DeviceCommCheckWTX(h->InBuf, len, &h->LastError.CommStatusM, outBufLen, outBuf);
                    } else
                    {
                        ret = phRpc_2_V_D11_DeviceCommCheckWTX(h->InBuf, len, &h->LastError.CommStatusM, outBufLen, outBuf);
                    }
                } else { }
            } else { }
            // Log
            phRpc_H_LogWStr(h, L"phRpc_2_H_DeviceCommCheckWTX");
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

// ________________________________________________________________________________________________
//
// AUX
// ________________________________________________________________________________________________

uint8_t phRpc_2_H_DutTRxAux(void *hdl, uint8_t cmd_rw, uint32_t *trxFlags, uint8_t **xBuf, uint16_t *txBufLen, uint16_t *rxBufLen)
{
    uint8_t     ret                             = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h                               = NULL;
    uint16_t    len                             = PH_RPC_2_H_DEVBUFLEN;
    uint8_t    *pre_buf;

    uint8_t    *xbuf_in;
    uint16_t    txbuf_len_in;
    uint16_t    rxbuf_len_in;

    if ((NULL != hdl) && (NULL != trxFlags) && (NULL != xBuf) && (NULL != txBufLen) && (NULL != rxBufLen) &&
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
            phRpc_2_H_LimitLength(txBufLen, rxBufLen);

            if (0 == h->CompactRPC)
            {
                ret = phRpc_2_H00_DutRWLong(h->OutBuf, &len, cmd_rw, *trxFlags, *rxBufLen, *txBufLen, &pre_buf, *xBuf);
            } else
            {
                ret = phRpc_2_V_H00_DutRWLong(h->OutBuf, &len, cmd_rw, *trxFlags, *rxBufLen, *txBufLen, &pre_buf, *xBuf);
            }

            // We received the address of the "pre-buf" within the serialised buffer: Preset its contents:
            memset(pre_buf, 0xA5, PH_RPC_2_CMD_PREPEND_LEN);

            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_2_H_DEVBUFLEN;

                    if (0 == h->CompactRPC)
                    {
                        ret = phRpc_2_D11_DutRWLong(h->InBuf, len, &h->LastError.CommStatusM, trxFlags, rxBufLen, txBufLen, &pre_buf, xBuf);
                    } else
                    {
                        ret = phRpc_2_V_D11_DutRWLong(h->InBuf, len, &h->LastError.CommStatusM, trxFlags, rxBufLen, txBufLen, &pre_buf, xBuf);
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

uint8_t phRpc_2_H_IoCtlAux(void *hdl, const wchar_t *fName, const uint8_t fnSelect, uint8_t ctrlMj, uint8_t ctrlMn, uint32_t *ctrlOpt)
{
    uint8_t     ret     = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h       = NULL;
    uint16_t    len     = PH_RPC_2_H_DEVBUFLEN;
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
                    opt = PH_RPC_2_IOCTL_OPT_NOT_APPLICABLE;
                    break;

                default:
                case PH_RPC_H_IOCTLFNSELECT_DEVIOLINECTL:
                    opt = PH_RPC_2_IO_LINE_CTL_OPT_NOT_APPLICABLE;
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
                    ret = phRpc_2_H00_DevIoCtrl(h->OutBuf, &len, ctrlMj, ctrlMn, opt);
                    break;

                case PH_RPC_H_IOCTLFNSELECT_DEVIOLINECTL:
                default:
                    ret = phRpc_2_H00_DevIoLineCtrl(h->OutBuf, &len, ctrlMj, ctrlMn, opt);
                    break;
            }

            if (0 == ret)
            {
                ret = phRpc_H_RWData(h, &len);
                if (0 == ret)
                {
                    len = PH_RPC_2_H_DEVBUFLEN;

                    switch (fnSelect)
                    {
                        case PH_RPC_H_IOCTLFNSELECT_DEVIOCTL:
                            ret = phRpc_2_D11_DevIoCtrl(h->InBuf, len, &h->LastError.CommStatusM, &opt);
                            break;

                        case PH_RPC_H_IOCTLFNSELECT_DEVIOLINECTL:
                        default:
                            ret = phRpc_2_D11_DevIoLineCtrl(h->InBuf, len, &h->LastError.CommStatusM, &opt);
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
    } else { /* Param check error */ }

    return ret;
}

void phRpc_2_H_LimitLength(uint16_t *txBufLen, uint16_t *rxBufLen)
{
    if (NULL != txBufLen)
    {
        *txBufLen = ((*txBufLen) >= PH_RPC_2_H_USABLE_LEN) ? PH_RPC_2_H_USABLE_LEN : (*txBufLen);
    } else { }

    if (NULL != rxBufLen)
    {
        *rxBufLen = ((*rxBufLen) >= PH_RPC_2_H_USABLE_LEN) ? PH_RPC_2_H_USABLE_LEN : (*rxBufLen);
    } else { }
}

