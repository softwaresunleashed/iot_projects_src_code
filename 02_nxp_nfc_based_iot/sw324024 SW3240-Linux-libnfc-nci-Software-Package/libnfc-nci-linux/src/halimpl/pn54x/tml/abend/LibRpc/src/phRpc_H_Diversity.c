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
* $Revision: 19228 $
* $Date: 2013-05-14 08:40:36 +0200 (Di, 14 Mai 2013) $
*
*/

// ________________________________________________________________________________________________
//
// INCLUDE
// ________________________________________________________________________________________________

#include "phRpc_Platform.h"
#include "phRpc_H_Diversity.h"

#include <string.h>

#if defined PH_RPC_H_PLAT_WINDOWS
#  include <malloc.h>
#elif defined (PH_RPC_H_PLAT_LINUX)
#  include <malloc.h>
#else
#  include <malloc/malloc.h>
#endif

#include "phRpc_HostIo.h"
#include "phRpc_Cmd.h"
#include "phRpc_Types.h"

#ifdef SECONDARY_PCLIB
    #include "phRpc_H_2.h"
#else
    #include "phRpc_H.h"
#endif

// Last include
#include "phRpc_HostCtx.h"

// ________________________________________________________________________________________________
//
// DEFINE
// ________________________________________________________________________________________________

#define PH_RPC_H_DIVERSITY_GUARD_1  0x5Au   //
#define PH_RPC_H_DIVERSITY_GUARD_2  0xA5u   //
#define PH_RPC_H_DIVERSITY_GUARD_L  2u      //

// ________________________________________________________________________________________________
//
// IMPLEMENTATION
// ________________________________________________________________________________________________

void* phRpc_H_Diversity_Alloc(void)
{
#   ifdef SECONDARY_PCLIB
    const uint16_t in_buf_len  = PH_RPC_2_H_DEVBUFLEN + PH_RPC_H_DIVERSITY_GUARD_L;
    const uint16_t out_buf_len = PH_RPC_2_H_DEVBUFLEN + PH_RPC_H_DIVERSITY_GUARD_L;
#else
    const uint16_t in_buf_len  = PH_RPC_H_DEVBUFLEN + PH_RPC_H_DIVERSITY_GUARD_L;
    const uint16_t out_buf_len = PH_RPC_H_DEVBUFLEN + PH_RPC_H_DIVERSITY_GUARD_L;
#endif
    phRpc_H_t *h;

    h = malloc (sizeof (phRpc_H_t));
    if (NULL != h)
    {
        memset(h, 0, sizeof(phRpc_H_t));
        h->InBuf  = malloc(in_buf_len);
        h->OutBuf = malloc(out_buf_len);
        // Check
        if ((NULL == h->InBuf) || (NULL == h->OutBuf))
        {
            // Alloc error for struct members
            phRpc_H_Diversity_Free(h);
        } else
        {
            memset(h->InBuf , 0, in_buf_len);
            memset(h->OutBuf, 0, out_buf_len);
            h->InBuf [in_buf_len  - PH_RPC_H_DIVERSITY_GUARD_L     ] = PH_RPC_H_DIVERSITY_GUARD_1;
            h->InBuf [in_buf_len  - PH_RPC_H_DIVERSITY_GUARD_L + 1u] = PH_RPC_H_DIVERSITY_GUARD_2;
            h->OutBuf[out_buf_len - PH_RPC_H_DIVERSITY_GUARD_L     ] = PH_RPC_H_DIVERSITY_GUARD_1;
            h->OutBuf[out_buf_len - PH_RPC_H_DIVERSITY_GUARD_L + 1u] = PH_RPC_H_DIVERSITY_GUARD_2;
        }
    } else
    {
        // Alloc error for struct
    }

    return h;
}

void  phRpc_H_Diversity_Free(void *pToFree)
{
    if (NULL != pToFree)
    {
        phRpc_H_t *h = (phRpc_H_t*)pToFree;
        if (NULL != h)
        {
            if (NULL != h->InBuf)
            {
                free(h->InBuf);
            }
            if (NULL != h->OutBuf)
            {
                free(h->OutBuf);
            }
            h->MagicID = 0; // In case someone continues to use it.
            free(h);
        }
    }
}

uint16_t phRpc_H_Diversity_GetDeviceBufferSize(void)
{
    uint16_t dbs = PH_RPC_H_DEVBUFLEN;
#   ifdef SECONDARY_PCLIB
    dbs = PH_RPC_2_H_DEVBUFLEN;
#   endif
    return dbs;
}

#if defined PH_RPC_H_PLAT_WINDOWS

int phRpc_H_Diversity_GetInterfaceNr(void)
{
    int if_nr = PH_RPC_H_INTF;
#   ifdef SECONDARY_PCLIB
    if_nr = PH_RPC_H_INTF_2;
#   endif
    return if_nr;
}

int phRpc_H_Diversity_GetInEp(void)
{
    int ep_nr = PH_RPC_H_EP_IN;
#   ifdef SECONDARY_PCLIB
    ep_nr = PH_RPC_H_EP_IN_2;
#   endif
    return ep_nr;
}

int phRpc_H_Diversity_GetOutEp(void)
{
    int ep_nr = PH_RPC_H_EP_OUT;
#   ifdef SECONDARY_PCLIB
    ep_nr = PH_RPC_H_EP_OUT_2;
#   endif
    return ep_nr;
}

#endif // PH_RPC_H_PLAT_WINDOWS

size_t phRpc_H_Diversity_GetNumBytesFromBuffer(uint8_t *rpcBuffer)
{
#   ifdef SECONDARY_PCLIB
    return (size_t)phRpc_2_H_GetNumBytes(rpcBuffer);
#   else
    return (size_t)phRpc_H_GetNumBytes(rpcBuffer);
#   endif
}

uint8_t phRpc_H_Diversity_BuildWTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t cancelReq)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H00_WTX(rpcBuf, rpcBufLen, cancelReq);
#   else
    return phRpc_H00_WTX(rpcBuf, rpcBufLen, cancelReq);
#   endif
}

uint8_t phRpc_H_Diversity_SetSeqNum(uint8_t *rpcBuf, uint8_t seqNum)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H_SetSeqNum(rpcBuf, seqNum);
#   else
    return phRpc_H_SetSeqNum(rpcBuf, seqNum);
#   endif
}

void phRpc_H_Diversity_SetCh2Id(uint8_t *rpcBuf)
{
#   ifdef SECONDARY_PCLIB
    phRpc_2_H_SetCh2Id(rpcBuf);
#   else
    phRpc_H_SetCh2Id(rpcBuf);
#   endif
}

uint8_t phRpc_H_Diversity_GetLastResponse(uint8_t *rpcBuf, uint16_t *rpcBufLen)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H00_GetLastResponse(rpcBuf, rpcBufLen);
#   else
    return phRpc_H00_GetLastResponse(rpcBuf, rpcBufLen);
#   endif
}

uint8_t phRpc_H_Diversity_GetSeqNum(uint8_t *rpcBuf)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H_GetSeqNum(rpcBuf);
#   else
    return phRpc_H_GetSeqNum(rpcBuf);
#   endif
}

uint8_t phRpc_H_Diversity_GetFidFromBuffer(uint8_t *rpcBuf)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H_GetFid(rpcBuf);
#   else
    return phRpc_H_GetFid(rpcBuf);
#   endif
}

uint8_t phRpc_H_Diversity_GetWtxFid(void)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H_FID_WTX;
#   else
    return phRpc_H_FID_WTX;
#   endif
}

uint8_t phRpc_H_Diversity_GetDevCompatInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t infoType)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H00_GetDevCompatInfo(rpcBuf, rpcBufLen, infoType);
#   else
    return phRpc_H00_GetDevCompatInfo(rpcBuf, rpcBufLen, infoType);
#   endif
}

uint8_t phRpc_D_Diversity_GetDevCompatInfo(uint8_t *rpcBuf, uint16_t rpcBufLen,
                                           uint16_t *rpcStatus,
                                           uint16_t *compatInfo,
                                           uint8_t *featureCode,
                                           uint8_t *valLevel,
                                           uint8_t *majorVersion,
                                           uint8_t *minorVersion)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_D11_GetDevCompatInfo(rpcBuf, rpcBufLen, rpcStatus, compatInfo, featureCode, valLevel, majorVersion, minorVersion);
#   else
    return phRpc_D11_GetDevCompatInfo(rpcBuf, rpcBufLen, rpcStatus, compatInfo, featureCode, valLevel, majorVersion, minorVersion);
#   endif
}

uint8_t phRpc_H_Diversity_GetDeviceInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t infoType)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H00_GetDeviceInfo(rpcBuf, rpcBufLen, infoType);
#   else
    return phRpc_H00_GetDeviceInfo(rpcBuf, rpcBufLen, infoType);
#   endif
}

uint8_t phRpc_D_Diversity_GetDeviceInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, uint8_t varSize,
                                uint16_t *rpcStatus,
                                uint32_t *infoNum,
                                uint16_t *infoBufLen,
                                uint8_t **infoBuf)
{
    uint8_t ret = 0;

#   ifdef SECONDARY_PCLIB
    ret = phRpc_2_V_D11_GetDeviceInfo(rpcBuf, rpcBufLen, rpcStatus, infoNum, infoBufLen, infoBuf);
    (void)varSize;
#   else
    if (0 == varSize)
    {
        ret = phRpc_D11_GetDeviceInfo(rpcBuf, rpcBufLen, rpcStatus, infoNum, infoBufLen, infoBuf);
    } else
    {
        ret = phRpc_V_D11_GetDeviceInfo(rpcBuf, rpcBufLen, rpcStatus, infoNum, infoBufLen, infoBuf);
    }
#   endif
    return ret;
}


uint8_t phRpc_H_Diversity_SetCommParam(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint32_t commSettings, uint16_t msTimeout)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H00_SetCommParam(rpcBuf, rpcBufLen, commSettings, msTimeout);
#   else
    return phRpc_H00_SetCommParam(rpcBuf, rpcBufLen, commSettings, msTimeout);
#   endif
}

uint8_t phRpc_D_Diversity_SetCommParam(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_D11_SetCommParam(rpcBuf, rpcBufLen, rpcStatus);
#   else
    return phRpc_D11_SetCommParam(rpcBuf, rpcBufLen, rpcStatus);
#   endif
}

// ________________________________________________________________________________________________
//
// ADC/DAC
// ________________________________________________________________________________________________

#define phRpc_2_H00_ 1;
#define phRpc_H00_ 1;
#define phRpc_2_D11_ 1;
#define phRpc_D11_ 1;

uint8_t phRpc_H_Diversity_AdcGetValue(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t channelID)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H00_AdcGetValue(rpcBuf, rpcBufLen, channelID);
#   else
    return phRpc_H00_AdcGetValue(rpcBuf, rpcBufLen, channelID);
#   endif
}

uint8_t phRpc_D_Diversity_AdcGetValue(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus, int32_t *daqVal)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_D11_AdcGetValue(rpcBuf, rpcBufLen, rpcStatus, daqVal);
#   else
    return phRpc_D11_AdcGetValue(rpcBuf, rpcBufLen, rpcStatus, daqVal);
#   endif
}

uint8_t phRpc_H_Diversity_DacSetValue(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t channelID, int32_t newValue)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H00_DacSetValue(rpcBuf, rpcBufLen, channelID, newValue);
#   else
    return phRpc_H00_DacSetValue(rpcBuf, rpcBufLen, channelID, newValue);
#   endif
}

uint8_t phRpc_D_Diversity_DacSetValue(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_D11_DacSetValue(rpcBuf, rpcBufLen, rpcStatus);
#   else
    return phRpc_D11_DacSetValue(rpcBuf, rpcBufLen, rpcStatus);
#   endif
}

uint8_t phRpc_H_Diversity_DacSetWave(uint8_t *rpcBuf, uint16_t *rpcBufLen,
                                     uint8_t channelID,
                                     uint8_t waveType,
                                     uint32_t waveFrequency,
                                     int32_t waveAmplitude,
                                     int32_t waveOffset)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H00_DacSetWave(rpcBuf, rpcBufLen, channelID, waveType, waveFrequency, waveAmplitude, waveOffset);
#   else
    return phRpc_H00_DacSetWave(rpcBuf, rpcBufLen, channelID, waveType, waveFrequency, waveAmplitude, waveOffset);
#   endif
}

uint8_t phRpc_D_Diversity_DacSetWave(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_D11_DacSetWave(rpcBuf, rpcBufLen, rpcStatus);
#   else
    return phRpc_D11_DacSetWave(rpcBuf, rpcBufLen, rpcStatus);
#   endif
}

uint8_t phRpc_H_Diversity_DaqGetVRef(uint8_t *rpcBuf, uint16_t *rpcBufLen)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H00_DaqGetVRef(rpcBuf, rpcBufLen);
#   else
    return phRpc_H00_DaqGetVRef(rpcBuf, rpcBufLen);
#   endif
}

uint8_t phRpc_D_Diversity_DaqGetVRef(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus, uint32_t *vrefVal)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_D11_DaqGetVRef(rpcBuf, rpcBufLen, rpcStatus, vrefVal);
#   else
    return phRpc_D11_DaqGetVRef(rpcBuf, rpcBufLen, rpcStatus, vrefVal);
#   endif
}

uint8_t phRpc_H_Diversity_DaqSetVRef(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint32_t vrefVal)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H00_DaqSetVRef(rpcBuf, rpcBufLen, vrefVal);
#   else
    return phRpc_H00_DaqSetVRef(rpcBuf, rpcBufLen, vrefVal);
#   endif
}

uint8_t phRpc_D_Diversity_DaqSetVRef(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_D11_DaqSetVRef(rpcBuf, rpcBufLen, rpcStatus);
#   else
    return phRpc_D11_DaqSetVRef(rpcBuf, rpcBufLen, rpcStatus);
#   endif
}

uint8_t phRpc_H_Diversity_DaqSetGain(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t hwType, uint8_t channelID, int32_t gainVal)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H00_DaqSetGain(rpcBuf, rpcBufLen, hwType, channelID, gainVal);
#   else
    return phRpc_H00_DaqSetGain(rpcBuf, rpcBufLen, hwType, channelID, gainVal);
#   endif
}

uint8_t phRpc_D_Diversity_DaqSetGain(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_D11_DaqSetGain(rpcBuf, rpcBufLen, rpcStatus);
#   else
    return phRpc_D11_DaqSetGain(rpcBuf, rpcBufLen, rpcStatus);
#   endif
}

uint8_t phRpc_H_Diversity_DaqGetGain(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t hwType, uint8_t channelID)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H00_DaqGetGain(rpcBuf, rpcBufLen, hwType, channelID);
#   else
    return phRpc_H00_DaqGetGain(rpcBuf, rpcBufLen, hwType, channelID);
#   endif
}

uint8_t phRpc_D_Diversity_DaqGetGain(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus, int32_t *gainVal)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_D11_DaqGetGain(rpcBuf, rpcBufLen, rpcStatus, gainVal);
#   else
    return phRpc_D11_DaqGetGain(rpcBuf, rpcBufLen, rpcStatus, gainVal);
#   endif
}

uint8_t phRpc_H_Diversity_DacGetFrequency(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t channelID)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_H00_DacGetFrequency(rpcBuf, rpcBufLen, channelID);
#   else
    return phRpc_H00_DacGetFrequency(rpcBuf, rpcBufLen, channelID);
#   endif
}

uint8_t phRpc_D_Diversity_DacGetFrequency(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus, uint32_t *frequencyVal)
{
#   ifdef SECONDARY_PCLIB
    return phRpc_2_D11_DacGetFrequency(rpcBuf, rpcBufLen, rpcStatus, frequencyVal);
#   else
    return phRpc_D11_DacGetFrequency(rpcBuf, rpcBufLen, rpcStatus, frequencyVal);
#   endif
}
