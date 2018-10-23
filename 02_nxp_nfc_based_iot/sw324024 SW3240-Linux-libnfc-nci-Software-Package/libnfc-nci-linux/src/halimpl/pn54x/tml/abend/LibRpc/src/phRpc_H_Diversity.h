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

#ifndef PHRPC_H_ALLOC_H
#define PHRPC_H_ALLOC_H

#include <stdlib.h>
#include <stdint.h>

#include "phRpc_Platform.h"
#include "phRpc_Common.h"

#ifdef SECONDARY_PCLIB
    #include "phRpc_HostDeSerialiser_2.h"
    #include "phRpc_HostSerialiser_2.h"
#else
    #include "phRpc_HostDeSerialiser.h"
    #include "phRpc_HostSerialiser.h"
#endif

// ________________________________________________________________________________________________
//
// Define
// ________________________________________________________________________________________________

#ifdef SECONDARY_PCLIB
    #define PH_RPC_H_NO_COMPACT_RPC_AVAILABLE   {' '}                // LPC SW Versions (features) that support no compact buffer RPC
#else
    #define PH_RPC_H_NO_COMPACT_RPC_AVAILABLE   {'C', 'E', 'F', 'G'} // LPC SW Versions (features) that support no compact buffer RPC
#endif

#if defined (PH_RPC_H_PLAT_IOS)
    //
#elif defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
    //
#elif defined PH_RPC_H_PLAT_WINDOWS
    // Device vendor and product id.
#   define PH_RPC_H_VID             PH_RPC_COMMON_VID
#   define PH_RPC_H_PID             PH_RPC_COMMON_PID
#   define PH_RPC_H_PID_SINGLE      PH_RPC_COMMON_PID_SINGLE
    // Device configuration and interface id.
#   define PH_RPC_H_CONFIG          1
#   define PH_RPC_H_INTF            PH_RPC_COMMON_INTERFACE_COMM
#   define PH_RPC_H_INTF_2          PH_RPC_COMMON_INTERFACE_COMM_2
    // Device endpoint(s)
#   define PH_RPC_H_EP_IN           PH_RPC_COMMON_BULK_IN_EP
#   define PH_RPC_H_EP_OUT          PH_RPC_COMMON_BULK_OUT_EP
#   define PH_RPC_H_EP_IN_2         PH_RPC_COMMON_2_BULK_IN_EP
#   define PH_RPC_H_EP_OUT_2        PH_RPC_COMMON_2_BULK_OUT_EP
#else
#   error "No platform specified"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

// ________________________________________________________________________________________________
//
// CONFIGURATION/ALLOCATION
// ________________________________________________________________________________________________

/**
 * \brief Allocate the memory for the RPC host library
 *
 * \return Pointer to the allocated storage.
 */
void* phRpc_H_Diversity_Alloc(void);

/**
 * \brief Free the memory of the RPC host library
 *
 * \param[in,out] Pointer to the allocated storage.
 *
 */
void phRpc_H_Diversity_Free(void *pToFree);

/**
 * \brief Get the device buffer size
 *
 * \return Device buffer size
 *
 */
uint16_t phRpc_H_Diversity_GetDeviceBufferSize(void);

/**
 * \brief Get the interface to claim when using LibUSB
 *
 * \return Interface Number
 *
 */
int phRpc_H_Diversity_GetInterfaceNr(void);

/**
 * \brief Get the IN endpoint number when using LibUSB
 *
 * \return Endpoint Number
 *
 */
int phRpc_H_Diversity_GetInEp(void);

/**
 * \brief Get the OUT endpoint number when using LibUSB
 * \return Endpoint Number
 *
 */
int phRpc_H_Diversity_GetOutEp(void);

// ________________________________________________________________________________________________
//
// RPC
// ________________________________________________________________________________________________

/**
 * \brief Get the number of bytes in a buffer
 *
 * \param rpcBuffer Buffer
 *
 * \return Number of bytes
 *
 */
size_t phRpc_H_Diversity_GetNumBytesFromBuffer(uint8_t *rpcBuffer);

/**
 * \brief Put together a host WTX
 *
 * \param rpcBuf    Buffer
 * \param rpcBufLen Length of buffer
 * \param cancelReq Cancel Request
 *
 * \return Status
 *
 */
uint8_t phRpc_H_Diversity_BuildWTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t cancelReq);

/**
 * \brief Set the sequence number
 *
 * \param rpcBuf    Buffer
 * \param seqNum    Sequence Number
 *
 * \return 0
 *
 */
uint8_t phRpc_H_Diversity_SetSeqNum(uint8_t *rpcBuf, uint8_t seqNum);

/**
 * \brief Set the ID bit for USB CH 2
 *
 * \param rpcBuf    Buffer
 *
 */
void phRpc_H_Diversity_SetCh2Id(uint8_t *rpcBuf);

/**
 * \brief Get last response
 *
 * \param rpcBuf    Buffer
 * \param rpcBufLen Length of buffer
 *
 * \return Status
 *
 */
uint8_t phRpc_H_Diversity_GetLastResponse(uint8_t *rpcBuf, uint16_t *rpcBufLen);

/**
 * \brief Get the sequence number
 *
 * \param rpcBuf    Buffer
 *
 * \return Sequence number
 *
 */
uint8_t phRpc_H_Diversity_GetSeqNum(uint8_t *rpcBuf);

/**
 * \brief Get the function ID
 *
 * \param rpcBuf    Buffer
 *
 * \return Function ID
 *
 */
uint8_t phRpc_H_Diversity_GetFidFromBuffer(uint8_t *rpcBuf);

/**
 * \brief Get the function ID
 *
 * \return Function ID for WTX
 *
 */
uint8_t phRpc_H_Diversity_GetWtxFid(void);

/**
 * \brief Get compatibility information - serialiser
 *
 * \param rpcBuf    Buffer
 * \param rpcBufLen Length of buffer
 * \param infoType  Information type
 *
 * \return Status
 *
 */
uint8_t phRpc_H_Diversity_GetDevCompatInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t infoType);

/**
 * \brief Get compatibility information - deserialiser
 *
 * \param rpcBuf        Buffer
 * \param rpcBufLen     Length of buffer
 * \param rpcStatus     Status
 * \param compatInfo    Compatibility information
 * \param featureCode   Feature
 * \param valLevel      Validation level
 * \param majorVersion  Major
 * \param minorVersion  Minor
 *
 * \return Status
 *
 */
uint8_t phRpc_D_Diversity_GetDevCompatInfo(uint8_t *rpcBuf, uint16_t rpcBufLen,
                                           uint16_t *rpcStatus,
                                           uint16_t *compatInfo,
                                           uint8_t *featureCode,
                                           uint8_t *valLevel,
                                           uint8_t *majorVersion,
                                           uint8_t *minorVersion);

/**
 * \brief Get Device Information
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  infoType  Type of information to get
 *
 * \return Status
 *
 */
uint8_t phRpc_H_Diversity_GetDeviceInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t infoType);

/**
 * \brief Get Device Information
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  rpcStatus  Status
 * \param  infoNum  Numerical information
 * \param  infoBufLen  Information Buffer
 * \param  infoBuf  Information Buffer
 *
 * \return Status
 *
 */
uint8_t phRpc_D_Diversity_GetDeviceInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, uint8_t varSize,
                                uint16_t *rpcStatus,
                                uint32_t *infoNum,
                                uint16_t *infoBufLen,
                                uint8_t **infoBuf);

/**
 * \brief Set Comm Param
 *
 * \param rpcBuf        Buffer
 * \param rpcBufLen     Length of buffer
 * \param commSettings  Communication Settings
 * \param msTimeout     Timeout in ms
 *
 * \return Status
 *
 */
uint8_t phRpc_H_Diversity_SetCommParam(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint32_t commSettings, uint16_t msTimeout);

/**
 * \brief Apply specific communication settings to the device
 *
 * \param  rpcBuf       Serialisation Buffer
 * \param  rpcBufLen    Serialisation Buffer Length
 * \param  rpcStatus    Status
 *
 * \return Status
 *
 */
uint8_t phRpc_D_Diversity_SetCommParam(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus);

// ________________________________________________________________________________________________
//
// DAQ A/D I/O
// ________________________________________________________________________________________________

/**
 * \brief Get Acquired Value
 *
 * \param  rpcBuf     Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  channelID  Channel to query
 *
 * \return Status
 *
 */
uint8_t phRpc_H_Diversity_AdcGetValue(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t channelID);

/**
 * \brief Get Acquired Value
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  rpcStatus  Status
 * \param  daqVal  Acquired Value
 *
 * \return Status
 *
 */
uint8_t phRpc_D_Diversity_AdcGetValue(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus, int32_t *daqVal);

/**
 * \brief Set Value
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  channelID  Channel to control
 * \param  newValue  New value to set
 *
 * \return Status
 *
 */
uint8_t phRpc_H_Diversity_DacSetValue(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t channelID, int32_t newValue);

/**
 * \brief Set Value
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  rpcStatus  Status
 *
 * \return Status
 *
 */
uint8_t phRpc_D_Diversity_DacSetValue(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus);

/**
 * \brief Set Wave
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  channelID  Channel to control
 * \param  waveType  Wave Type
 * \param  waveFrequency  Wave Frequency
 * \param  waveAmplitude  Wave Amplitude
 * \param  waveOffset  Wave Offset
 *
 * \return Status
 *
 */
uint8_t phRpc_H_Diversity_DacSetWave(uint8_t *rpcBuf, uint16_t *rpcBufLen,
                                     uint8_t channelID,
                                     uint8_t waveType,
                                     uint32_t waveFrequency,
                                     int32_t waveAmplitude,
                                     int32_t waveOffset);

/**
 * \brief Set Wave
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  rpcStatus  Status
 *
 * \return Status
 *
 */
uint8_t phRpc_D_Diversity_DacSetWave(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus);

/**
 * \brief Get the Reference Voltage
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 *
 * \return Status
 *
 */
uint8_t phRpc_H_Diversity_DaqGetVRef(uint8_t *rpcBuf, uint16_t *rpcBufLen);

/**
 * \brief Get the Reference Voltage
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  rpcStatus  Status
 * \param  vrefVal  Reference Voltage Value
 *
 * \return Status
 *
 */
uint8_t phRpc_D_Diversity_DaqGetVRef(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus, uint32_t *vrefVal);

/**
 * \brief Set the Reference Voltage
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  vrefVal  New Reference Voltage Value
 *
 * \return Status
 *
 */
uint8_t phRpc_H_Diversity_DaqSetVRef(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint32_t vrefVal);

/**
 * \brief Set the Reference Voltage
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  rpcStatus  Status
 *
 * \return Status
 *
 */
uint8_t phRpc_D_Diversity_DaqSetVRef(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus);

/**
 * \brief Set the Gain of a Channel
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  hwType  ADC or DAC
 * \param  channelID  Channel to control
 * \param  gainVal  New Gain Value
 *
 * \return Status
 *
 */
uint8_t phRpc_H_Diversity_DaqSetGain(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t hwType, uint8_t channelID, int32_t gainVal);

/**
 * \brief Set the Gain of a Channel
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  rpcStatus  Status
 *
 * \return Status
 *
 */
uint8_t phRpc_D_Diversity_DaqSetGain(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus);

/**
 * \brief Get the Gain of a Channel
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  hwType  ADC or DAC
 * \param  channelID  Channel to query
 *
 * \return Status
 *
 */
uint8_t phRpc_H_Diversity_DaqGetGain(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t hwType, uint8_t channelID);

/**
 * \brief Get the Gain of a Channel
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  rpcStatus  Status
 * \param  gainVal  Gain Value
 *
 * \return Status
 *
 */
uint8_t phRpc_D_Diversity_DaqGetGain(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus, int32_t *gainVal);

/**
 * \brief Get the Frequency of a Channel
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  channelID  Channel to query
 *
 * \return Status
 *
 */
uint8_t phRpc_H_Diversity_DacGetFrequency(uint8_t *rpcBuf, uint16_t *rpcBufLen, uint8_t channelID);

/**
 * \brief Get the Frequency of a Channel
 *
 * \param  rpcBuf  Serialisation Buffer
 * \param  rpcBufLen  Serialisation Buffer Length
 * \param  rpcStatus  Status
 * \param  frequencyVal  Frequency
 *
 * \return Status
 *
 */
uint8_t phRpc_D_Diversity_DacGetFrequency(uint8_t *rpcBuf, uint16_t rpcBufLen, uint16_t *rpcStatus, uint32_t *frequencyVal);

#ifdef __cplusplus
}
#endif

#endif // Guard
