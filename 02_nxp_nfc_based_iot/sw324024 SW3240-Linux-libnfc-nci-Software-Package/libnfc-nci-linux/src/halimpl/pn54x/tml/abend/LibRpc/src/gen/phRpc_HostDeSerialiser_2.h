//
// AUTO-GENERATED: DO NOT EDIT. 
//
 

// _________________________________________________________________________________________________
 
#ifndef phRpc_211DH_h
#define phRpc_211DH_h

#include <stdint.h>
#include <string.h>

/** 
 * @addtogroup grp_rpcf_ll_d2h_2_r
 * @{ 
 */ 
 
/// @brief Function ID Enumeration 
typedef enum
{
    phRpc_2_H_FID_SetCommParam = 1, ///< Apply specific communication settings to the device
    phRpc_2_H_FID_GetDeviceInfo = 2, ///< Get Device Information
    phRpc_2_H_FID_DeviceDaq = 12, ///< Device DAQ
    phRpc_2_H_FID_GetDevCompatInfo = 13, ///< Get Device Compatibility Information
    phRpc_2_H_FID_WTX = 14, ///< Response to: WTX
    phRpc_2_H_FID_GetLastResponse = 15, ///< Response to: GetLastResponse
    phRpc_2_H_FID_DutInit = 64, ///< Response to INIT
    phRpc_2_H_FID_DutGetMode = 65, ///< Get DUT Interface Mode
    phRpc_2_H_FID_DutRWLong = 66, ///< Data Exchange with the DUT - Long Buffer
    phRpc_2_H_FID_DevIoCtrl = 67, ///< I/O Control Function
    phRpc_2_H_FID_DevIoLineCtrl = 68, ///< I/O Line Control Function
    phRpc_2_H_FID_GetTransferLog = 69, ///< Get transfer log
    phRpc_2_H_FID_AdcGetValue = 70, ///< Get Acquired Value
    phRpc_2_H_FID_DacSetValue = 71, ///< Set Value
    phRpc_2_H_FID_DacSetWave = 72, ///< Set Wave
    phRpc_2_H_FID_DaqGetVRef = 73, ///< Get the Reference Voltage
    phRpc_2_H_FID_DaqSetVRef = 74, ///< Set the Reference Voltage
    phRpc_2_H_FID_DaqSetGain = 75, ///< Set the Gain of a Channel
    phRpc_2_H_FID_DaqGetGain = 76, ///< Get the Gain of a Channel
    phRpc_2_H_FID_DacGetFrequency = 77, ///< Get the Frequency of a Channel
    phRpc_2_H_FID_DeviceCommCheckWTX = 240, ///< Communication Check - Long Buffer
    phRpc_2_H_FID_Max
} phRpc_2_H_FID_t;

// _________________________________________________________________________________________________
 
/// @brief Completion Handler
uint8_t phRpc_2_H_Handler_DispatchCompletion(void *rpcCtx, uint8_t dispatchResult);

/// @brief Get the number of bytes
uint16_t phRpc_2_H_GetNumBytes(uint8_t *rpcBuf);

/// @brief Function ID Getter
uint16_t phRpc_2_H_GetFid(uint8_t *rpcBuf);

/// @brief Sequence Number Getter
uint8_t phRpc_2_H_GetSeqNum(uint8_t *rpcBuf);

/// @brief Check the CH2 ID bit
uint8_t phRpc_2_H_IsCh2Id(uint8_t *rpcBuf);

/// @brief Clear the CH2 ID bit
void phRpc_2_H_ClearCh2Id(uint8_t *rpcBuf);

/// @brief RPC Dispatcher/Entry Handler

// _________________________________________________________________________________________________
 
// No dispatcher and handler functions are generated in the current configuration.

// _________________________________________________________________________________________________
 
/** 
@brief Apply specific communication settings to the device

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_SetCommParam(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                 uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_2_D11_SetCommParam
typedef uint8_t (*pphRpc_2_D11_SetCommParam)(uint8_t*, uint16_t, uint16_t *);
 
/** 
@brief Get Device Information

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  infoNum  Numerical information
@param  infoBufLen  Information Buffer
@param  infoBuf  Information Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  infoNum[4]  infoBufLen[2]  infoBuf[PH_RPC_2_CMD_DEVINFO_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_GetDeviceInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint16_t *rpcStatus, 
                                  uint32_t *infoNum, 
                                  uint16_t *infoBufLen, 
                                  uint8_t **infoBuf);
/// @brief Function pointer for @ref phRpc_2_D11_GetDeviceInfo
typedef uint8_t (*pphRpc_2_D11_GetDeviceInfo)(uint8_t*, uint16_t, uint16_t *, uint32_t *, uint16_t *, uint8_t **);
 
/** 
@brief Get Device Information

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  infoNum  Numerical information
@param  infoBufLen  Information Buffer
@param  infoBuf  Information Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  infoNum[4]  infoBufLen[2]  infoBuf[infoBufLen <= PH_RPC_2_CMD_DEVINFO_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of infoBuf is variable, depends on infoBufLen and has a maximum length of PH_RPC_2_CMD_DEVINFO_BUFLEN.
*/ 
uint8_t phRpc_2_V_D11_GetDeviceInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                    uint16_t *rpcStatus, 
                                    uint32_t *infoNum, 
                                    uint16_t *infoBufLen, 
                                    uint8_t **infoBuf);
/// @brief Function pointer for @ref phRpc_2_V_D11_GetDeviceInfo
typedef uint8_t (*pphRpc_2_V_D11_GetDeviceInfo)(uint8_t*, uint16_t, uint16_t *, uint32_t *, uint16_t *, uint8_t **);
 
/** 
@brief Device DAQ

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  daqAddress  DAQ start address
@param  daqLength  DAQ length in bytes
@param  daqBuffer  DAQ Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  daqAddress[4]  daqLength[2]  daqBuffer[PH_RPC_2_CMD_USER_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_DeviceDaq(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint16_t *rpcStatus, 
                              uint32_t *daqAddress, 
                              uint16_t *daqLength, 
                              uint8_t **daqBuffer);
/// @brief Function pointer for @ref phRpc_2_D11_DeviceDaq
typedef uint8_t (*pphRpc_2_D11_DeviceDaq)(uint8_t*, uint16_t, uint16_t *, uint32_t *, uint16_t *, uint8_t **);
 
/** 
@brief Device DAQ

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  daqAddress  DAQ start address
@param  daqLength  DAQ length in bytes
@param  daqBuffer  DAQ Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  daqAddress[4]  daqLength[2]  daqBuffer[daqLength <= PH_RPC_2_CMD_USER_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of daqBuffer is variable, depends on daqLength and has a maximum length of PH_RPC_2_CMD_USER_BUFSIZE.
*/ 
uint8_t phRpc_2_V_D11_DeviceDaq(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint16_t *rpcStatus, 
                                uint32_t *daqAddress, 
                                uint16_t *daqLength, 
                                uint8_t **daqBuffer);
/// @brief Function pointer for @ref phRpc_2_V_D11_DeviceDaq
typedef uint8_t (*pphRpc_2_V_D11_DeviceDaq)(uint8_t*, uint16_t, uint16_t *, uint32_t *, uint16_t *, uint8_t **);
 
/** 
@brief Get Device Compatibility Information

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  compatInfo  Compatibility Information
@param  featureCode  FeatureCode
@param  valLevel  Validation Level
@param  majorVersion  Major Version
@param  minorVersion  Minor Version
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  compatInfo[2]  featureCode[1]  valLevel[1]  majorVersion[1]  minorVersion[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_GetDevCompatInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                     uint16_t *rpcStatus, 
                                     uint16_t *compatInfo, 
                                     uint8_t *featureCode, 
                                     uint8_t *valLevel, 
                                     uint8_t *majorVersion, 
                                     uint8_t *minorVersion);
/// @brief Function pointer for @ref phRpc_2_D11_GetDevCompatInfo
typedef uint8_t (*pphRpc_2_D11_GetDevCompatInfo)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t *, uint8_t *, uint8_t *, uint8_t *);
 
/** 
@brief Response to: WTX

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_WTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                        uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_2_D11_WTX
typedef uint8_t (*pphRpc_2_D11_WTX)(uint8_t*, uint16_t, uint16_t *);
 
/** 
@brief Response to: GetLastResponse

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_GetLastResponse(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                    uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_2_D11_GetLastResponse
typedef uint8_t (*pphRpc_2_D11_GetLastResponse)(uint8_t*, uint16_t, uint16_t *);
 
/** 
@brief Response to INIT

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_DutInit(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                            uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_2_D11_DutInit
typedef uint8_t (*pphRpc_2_D11_DutInit)(uint8_t*, uint16_t, uint16_t *);
 
/** 
@brief Get DUT Interface Mode

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  intfMode  Interface Mode
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  intfMode[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_DutGetMode(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus, 
                               uint32_t *intfMode);
/// @brief Function pointer for @ref phRpc_2_D11_DutGetMode
typedef uint8_t (*pphRpc_2_D11_DutGetMode)(uint8_t*, uint16_t, uint16_t *, uint32_t *);
 
/** 
@brief Data Exchange with the DUT - Long Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  rwFlags  Flags that control the function behaviour
@param  rxLength  Receive Length
@param  txLength  Transmit Length
@param  preBuf  Prepend Buffer
@param  xBuffer  Exchange Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  rwFlags[4]  rxLength[2]  txLength[2]  preBuf[PH_RPC_2_CMD_PREPEND_LEN]  xBuffer[PH_RPC_2_CMD_USER_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_DutRWLong(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint16_t *rpcStatus, 
                              uint32_t *rwFlags, 
                              uint16_t *rxLength, 
                              uint16_t *txLength, 
                              uint8_t **preBuf, 
                              uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_2_D11_DutRWLong
typedef uint8_t (*pphRpc_2_D11_DutRWLong)(uint8_t*, uint16_t, uint16_t *, uint32_t *, uint16_t *, uint16_t *, uint8_t **, uint8_t **);
 
/** 
@brief Data Exchange with the DUT - Long Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  rwFlags  Flags that control the function behaviour
@param  rxLength  Receive Length
@param  txLength  Transmit Length
@param  preBuf  Prepend Buffer
@param  xBuffer  Exchange Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  rwFlags[4]  rxLength[2]  txLength[2]  preBuf[PH_RPC_2_CMD_PREPEND_LEN]  xBuffer[rxLength <= PH_RPC_2_CMD_USER_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of xBuffer is variable, depends on rxLength and has a maximum length of PH_RPC_2_CMD_USER_BUFSIZE.
*/ 
uint8_t phRpc_2_V_D11_DutRWLong(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint16_t *rpcStatus, 
                                uint32_t *rwFlags, 
                                uint16_t *rxLength, 
                                uint16_t *txLength, 
                                uint8_t **preBuf, 
                                uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_2_V_D11_DutRWLong
typedef uint8_t (*pphRpc_2_V_D11_DutRWLong)(uint8_t*, uint16_t, uint16_t *, uint32_t *, uint16_t *, uint16_t *, uint8_t **, uint8_t **);
 
/** 
@brief I/O Control Function

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  ioctlOpt  Optional Parameter
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  ioctlOpt[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_DevIoCtrl(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint16_t *rpcStatus, 
                              uint32_t *ioctlOpt);
/// @brief Function pointer for @ref phRpc_2_D11_DevIoCtrl
typedef uint8_t (*pphRpc_2_D11_DevIoCtrl)(uint8_t*, uint16_t, uint16_t *, uint32_t *);
 
/** 
@brief I/O Line Control Function

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  ioLineCtlOpt  Optional Parameter
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  ioLineCtlOpt[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_DevIoLineCtrl(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint16_t *rpcStatus, 
                                  uint32_t *ioLineCtlOpt);
/// @brief Function pointer for @ref phRpc_2_D11_DevIoLineCtrl
typedef uint8_t (*pphRpc_2_D11_DevIoLineCtrl)(uint8_t*, uint16_t, uint16_t *, uint32_t *);
 
/** 
@brief Get transfer log

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  numTransfers  Number of transfers
@param  transferData  Transfer data
@param  transferLen  Transfer length
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  numTransfers[1]  transferData[4]  transferLen[2]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_GetTransferLog(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                   uint16_t *rpcStatus, 
                                   uint8_t *numTransfers, 
                                   uint32_t *transferData, 
                                   uint16_t *transferLen);
/// @brief Function pointer for @ref phRpc_2_D11_GetTransferLog
typedef uint8_t (*pphRpc_2_D11_GetTransferLog)(uint8_t*, uint16_t, uint16_t *, uint8_t *, uint32_t *, uint16_t *);
 
/** 
@brief Get Acquired Value

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  daqVal  Acquired Value
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  daqVal[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_AdcGetValue(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint16_t *rpcStatus, 
                                int32_t *daqVal);
/// @brief Function pointer for @ref phRpc_2_D11_AdcGetValue
typedef uint8_t (*pphRpc_2_D11_AdcGetValue)(uint8_t*, uint16_t, uint16_t *, int32_t *);
 
/** 
@brief Set Value

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_DacSetValue(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_2_D11_DacSetValue
typedef uint8_t (*pphRpc_2_D11_DacSetValue)(uint8_t*, uint16_t, uint16_t *);
 
/** 
@brief Set Wave

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_DacSetWave(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_2_D11_DacSetWave
typedef uint8_t (*pphRpc_2_D11_DacSetWave)(uint8_t*, uint16_t, uint16_t *);
 
/** 
@brief Get the Reference Voltage

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  vrefVal  Reference Voltage Value
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  vrefVal[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_DaqGetVRef(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus, 
                               uint32_t *vrefVal);
/// @brief Function pointer for @ref phRpc_2_D11_DaqGetVRef
typedef uint8_t (*pphRpc_2_D11_DaqGetVRef)(uint8_t*, uint16_t, uint16_t *, uint32_t *);
 
/** 
@brief Set the Reference Voltage

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_DaqSetVRef(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_2_D11_DaqSetVRef
typedef uint8_t (*pphRpc_2_D11_DaqSetVRef)(uint8_t*, uint16_t, uint16_t *);
 
/** 
@brief Set the Gain of a Channel

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_DaqSetGain(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_2_D11_DaqSetGain
typedef uint8_t (*pphRpc_2_D11_DaqSetGain)(uint8_t*, uint16_t, uint16_t *);
 
/** 
@brief Get the Gain of a Channel

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  gainVal  Gain Value
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  gainVal[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_DaqGetGain(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus, 
                               int32_t *gainVal);
/// @brief Function pointer for @ref phRpc_2_D11_DaqGetGain
typedef uint8_t (*pphRpc_2_D11_DaqGetGain)(uint8_t*, uint16_t, uint16_t *, int32_t *);
 
/** 
@brief Get the Frequency of a Channel

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  actualF  Frequency
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  actualF[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_DacGetFrequency(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                    uint16_t *rpcStatus, 
                                    uint32_t *actualF);
/// @brief Function pointer for @ref phRpc_2_D11_DacGetFrequency
typedef uint8_t (*pphRpc_2_D11_DacGetFrequency)(uint8_t*, uint16_t, uint16_t *, uint32_t *);
 
/** 
@brief Communication Check - Long Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  xLength  Length
@param  xBuffer  Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  xLength[2]  xBuffer[PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_2_D11_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                       uint16_t *rpcStatus, 
                                       uint16_t *xLength, 
                                       uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_2_D11_DeviceCommCheckWTX
typedef uint8_t (*pphRpc_2_D11_DeviceCommCheckWTX)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t **);
 
/** 
@brief Communication Check - Long Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  xLength  Length
@param  xBuffer  Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  xLength[2]  xBuffer[xLength <= PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of xBuffer is variable, depends on xLength and has a maximum length of PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN.
*/ 
uint8_t phRpc_2_V_D11_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                         uint16_t *rpcStatus, 
                                         uint16_t *xLength, 
                                         uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_2_V_D11_DeviceCommCheckWTX
typedef uint8_t (*pphRpc_2_V_D11_DeviceCommCheckWTX)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t **);
 
/** @} */ // grp_rpcf_ll_d2h_2_r
 

#endif // Guard
