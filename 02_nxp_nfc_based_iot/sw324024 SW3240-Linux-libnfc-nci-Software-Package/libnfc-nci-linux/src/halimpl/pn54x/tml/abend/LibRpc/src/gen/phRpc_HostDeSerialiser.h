//
// AUTO-GENERATED: DO NOT EDIT. 
//
 

// _________________________________________________________________________________________________
 
#ifndef phRpc11DH_h
#define phRpc11DH_h

#include <stdint.h>
#include <string.h>

/** 
 * @addtogroup grp_rpcf_ll_d2h_r
 * @{ 
 */ 
 
/// @brief Function ID Enumeration 
typedef enum
{
    phRpc_H_FID_SetCommParam = 1, ///< Apply specific communication settings to the device
    phRpc_H_FID_GetDeviceInfo = 2, ///< Get Device Information
    phRpc_H_FID_CtrlDeviceDiag = 3, ///< Response to Control Diagnostics
    phRpc_H_FID_SetDeviceMode = 4, ///< Response to: Re-Initialise device and put it into specified operating mode
    phRpc_H_FID_GetDeviceCtInfo = 5, ///< Response: Get Secondary Firmware Information
    phRpc_H_FID_DeviceDaq = 12, ///< Device DAQ
    phRpc_H_FID_GetDevCompatInfo = 13, ///< Get Device Compatibility Information
    phRpc_H_FID_WTX = 14, ///< Response to: WTX
    phRpc_H_FID_GetLastResponse = 15, ///< Response to: GetLastResponse
    phRpc_H_FID_EE = 16, ///< Response: EE Function
    phRpc_H_FID_EECfg = 17, ///< Response to: EECfg
    phRpc_H_FID_StartTestSwCt = 18, ///< Response to Start the Secondary Firmware
    phRpc_H_FID_StopTestSwCt = 19, ///< Response to Stop the Secondary Firmware
    phRpc_H_FID_DataExchangeTestSwCt = 20, ///< Data Exchange between Secondary Firmware and Host
    phRpc_H_FID_DutInit = 64, ///< Response to INIT
    phRpc_H_FID_DutGetMode = 65, ///< Get DUT Interface Mode
    phRpc_H_FID_DutRWShort = 66, ///< Data Exchange with the DUT - Short Buffer
    phRpc_H_FID_DutRWLong = 67, ///< Data Exchange with the DUT - Long Buffer
    phRpc_H_FID_DevIoCtrl = 68, ///< I/O Control Function
    phRpc_H_FID_DevIoLineCtrl = 69, ///< I/O Line Control Function
    phRpc_H_FID_AdcGetValue = 70, ///< Get Acquired Value
    phRpc_H_FID_DacSetValue = 71, ///< Set Value
    phRpc_H_FID_DacSetWave = 72, ///< Set Wave
    phRpc_H_FID_DaqGetVRef = 73, ///< Get the Reference Voltage
    phRpc_H_FID_DaqSetVRef = 74, ///< Set the Reference Voltage
    phRpc_H_FID_DaqSetGain = 75, ///< Set the Gain of a Channel
    phRpc_H_FID_DaqGetGain = 76, ///< Get the Gain of a Channel
    phRpc_H_FID_DacGetFrequency = 77, ///< Get the Frequency of a Channel
    phRpc_H_FID_DeviceCommCheck = 241, ///< Communication Check - Short Buffer
    phRpc_H_FID_DeviceCommCheckL = 242, ///< Communication Check - Long Buffer
    phRpc_H_FID_DeviceCommCheckWTX = 243, ///< Communication Check - Long Buffer
    phRpc_H_FID_D_TEST1 = 255, ///< Test Function 1
    phRpc_H_FID_D_TEST2 = 254, ///< Test Function 2
    phRpc_H_FID_D_TEST3 = 253, ///< Test Function 3
    phRpc_H_FID_D_TEST4 = 252, ///< Test Function 4
    phRpc_H_FID_Max
} phRpc_H_FID_t;

// _________________________________________________________________________________________________
 
/// @brief Completion Handler
uint8_t phRpc_H_Handler_DispatchCompletion(void *rpcCtx, uint8_t dispatchResult);

/// @brief Get the number of bytes
uint16_t phRpc_H_GetNumBytes(uint8_t *rpcBuf);

/// @brief Function ID Getter
uint16_t phRpc_H_GetFid(uint8_t *rpcBuf);

/// @brief Sequence Number Getter
uint8_t phRpc_H_GetSeqNum(uint8_t *rpcBuf);

/// @brief Check the CH2 ID bit
uint8_t phRpc_H_IsCh2Id(uint8_t *rpcBuf);

/// @brief Clear the CH2 ID bit
void phRpc_H_ClearCh2Id(uint8_t *rpcBuf);

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
uint8_t phRpc_D11_SetCommParam(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_D11_SetCommParam
typedef uint8_t (*pphRpc_D11_SetCommParam)(uint8_t*, uint16_t, uint16_t *);
 
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
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  infoNum[4]  infoBufLen[2]  infoBuf[PH_RPC_CMD_DEVINFO_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_GetDeviceInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint16_t *rpcStatus, 
                                uint32_t *infoNum, 
                                uint16_t *infoBufLen, 
                                uint8_t **infoBuf);
/// @brief Function pointer for @ref phRpc_D11_GetDeviceInfo
typedef uint8_t (*pphRpc_D11_GetDeviceInfo)(uint8_t*, uint16_t, uint16_t *, uint32_t *, uint16_t *, uint8_t **);
 
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
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  infoNum[4]  infoBufLen[2]  infoBuf[infoBufLen <= PH_RPC_CMD_DEVINFO_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of infoBuf is variable, depends on infoBufLen and has a maximum length of PH_RPC_CMD_DEVINFO_BUFLEN.
*/ 
uint8_t phRpc_V_D11_GetDeviceInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint16_t *rpcStatus, 
                                  uint32_t *infoNum, 
                                  uint16_t *infoBufLen, 
                                  uint8_t **infoBuf);
/// @brief Function pointer for @ref phRpc_V_D11_GetDeviceInfo
typedef uint8_t (*pphRpc_V_D11_GetDeviceInfo)(uint8_t*, uint16_t, uint16_t *, uint32_t *, uint16_t *, uint8_t **);
 
/** 
@brief Response to Control Diagnostics

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  infoBufLen  Information Buffer
@param  infoBuf  Diagnostic Information Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  infoBufLen[2]  infoBuf[PH_RPC_CMD_CTRLDIAG_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_CtrlDeviceDiag(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                 uint16_t *rpcStatus, 
                                 uint16_t *infoBufLen, 
                                 uint8_t **infoBuf);
/// @brief Function pointer for @ref phRpc_D11_CtrlDeviceDiag
typedef uint8_t (*pphRpc_D11_CtrlDeviceDiag)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t **);
 
/** 
@brief Response to Control Diagnostics

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  infoBufLen  Information Buffer
@param  infoBuf  Diagnostic Information Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  infoBufLen[2]  infoBuf[infoBufLen <= PH_RPC_CMD_CTRLDIAG_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of infoBuf is variable, depends on infoBufLen and has a maximum length of PH_RPC_CMD_CTRLDIAG_BUFLEN.
*/ 
uint8_t phRpc_V_D11_CtrlDeviceDiag(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                   uint16_t *rpcStatus, 
                                   uint16_t *infoBufLen, 
                                   uint8_t **infoBuf);
/// @brief Function pointer for @ref phRpc_V_D11_CtrlDeviceDiag
typedef uint8_t (*pphRpc_V_D11_CtrlDeviceDiag)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t **);
 
/** 
@brief Response to: Re-Initialise device and put it into specified operating mode

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
uint8_t phRpc_D11_SetDeviceMode(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_D11_SetDeviceMode
typedef uint8_t (*pphRpc_D11_SetDeviceMode)(uint8_t*, uint16_t, uint16_t *);
 
/** 
@brief Response: Get Secondary Firmware Information

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
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  infoNum[4]  infoBufLen[2]  infoBuf[PH_RPC_CMD_DEVINFO_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_GetDeviceCtInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint16_t *rpcStatus, 
                                  uint32_t *infoNum, 
                                  uint16_t *infoBufLen, 
                                  uint8_t **infoBuf);
/// @brief Function pointer for @ref phRpc_D11_GetDeviceCtInfo
typedef uint8_t (*pphRpc_D11_GetDeviceCtInfo)(uint8_t*, uint16_t, uint16_t *, uint32_t *, uint16_t *, uint8_t **);
 
/** 
@brief Response: Get Secondary Firmware Information

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
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  infoNum[4]  infoBufLen[2]  infoBuf[infoBufLen <= PH_RPC_CMD_DEVINFO_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of infoBuf is variable, depends on infoBufLen and has a maximum length of PH_RPC_CMD_DEVINFO_BUFLEN.
*/ 
uint8_t phRpc_V_D11_GetDeviceCtInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                    uint16_t *rpcStatus, 
                                    uint32_t *infoNum, 
                                    uint16_t *infoBufLen, 
                                    uint8_t **infoBuf);
/// @brief Function pointer for @ref phRpc_V_D11_GetDeviceCtInfo
typedef uint8_t (*pphRpc_V_D11_GetDeviceCtInfo)(uint8_t*, uint16_t, uint16_t *, uint32_t *, uint16_t *, uint8_t **);
 
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
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  daqAddress[4]  daqLength[2]  daqBuffer[PH_RPC_CMD_EXT_DEV_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_DeviceDaq(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                            uint16_t *rpcStatus, 
                            uint32_t *daqAddress, 
                            uint16_t *daqLength, 
                            uint8_t **daqBuffer);
/// @brief Function pointer for @ref phRpc_D11_DeviceDaq
typedef uint8_t (*pphRpc_D11_DeviceDaq)(uint8_t*, uint16_t, uint16_t *, uint32_t *, uint16_t *, uint8_t **);
 
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
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  daqAddress[4]  daqLength[2]  daqBuffer[daqLength <= PH_RPC_CMD_EXT_DEV_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of daqBuffer is variable, depends on daqLength and has a maximum length of PH_RPC_CMD_EXT_DEV_BUFSIZE.
*/ 
uint8_t phRpc_V_D11_DeviceDaq(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint16_t *rpcStatus, 
                              uint32_t *daqAddress, 
                              uint16_t *daqLength, 
                              uint8_t **daqBuffer);
/// @brief Function pointer for @ref phRpc_V_D11_DeviceDaq
typedef uint8_t (*pphRpc_V_D11_DeviceDaq)(uint8_t*, uint16_t, uint16_t *, uint32_t *, uint16_t *, uint8_t **);
 
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
uint8_t phRpc_D11_GetDevCompatInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                   uint16_t *rpcStatus, 
                                   uint16_t *compatInfo, 
                                   uint8_t *featureCode, 
                                   uint8_t *valLevel, 
                                   uint8_t *majorVersion, 
                                   uint8_t *minorVersion);
/// @brief Function pointer for @ref phRpc_D11_GetDevCompatInfo
typedef uint8_t (*pphRpc_D11_GetDevCompatInfo)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t *, uint8_t *, uint8_t *, uint8_t *);
 
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
uint8_t phRpc_D11_WTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                      uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_D11_WTX
typedef uint8_t (*pphRpc_D11_WTX)(uint8_t*, uint16_t, uint16_t *);
 
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
uint8_t phRpc_D11_GetLastResponse(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_D11_GetLastResponse
typedef uint8_t (*pphRpc_D11_GetLastResponse)(uint8_t*, uint16_t, uint16_t *);
 
/** 
@brief Response: EE Function

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  eeBuf  EEPROM Information Buffer
@param  infoBufLen  Information Buffer Length
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  eeBuf[PH_RPC_CMD_EE_BUFLEN]  infoBufLen[2]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_EE(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                     uint16_t *rpcStatus, 
                     uint8_t **eeBuf, 
                     uint16_t *infoBufLen);
/// @brief Function pointer for @ref phRpc_D11_EE
typedef uint8_t (*pphRpc_D11_EE)(uint8_t*, uint16_t, uint16_t *, uint8_t **, uint16_t *);
 
/** 
@brief Response: EE Function

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  eeBuf  EEPROM Information Buffer
@param  infoBufLen  Information Buffer Length
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  eeBuf[infoBufLen <= PH_RPC_CMD_EE_BUFLEN]  infoBufLen[2]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of eeBuf is variable, depends on infoBufLen and has a maximum length of PH_RPC_CMD_EE_BUFLEN.
*/ 
uint8_t phRpc_V_D11_EE(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                       uint16_t *rpcStatus, 
                       uint8_t **eeBuf, 
                       uint16_t *infoBufLen);
/// @brief Function pointer for @ref phRpc_V_D11_EE
typedef uint8_t (*pphRpc_V_D11_EE)(uint8_t*, uint16_t, uint16_t *, uint8_t **, uint16_t *);
 
/** 
@brief Response to: EECfg

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
uint8_t phRpc_D11_EECfg(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                        uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_D11_EECfg
typedef uint8_t (*pphRpc_D11_EECfg)(uint8_t*, uint16_t, uint16_t *);
 
/** 
@brief Response to Start the Secondary Firmware

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  startStatus  Status of the Start Operation
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  startStatus[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_StartTestSwCt(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint16_t *rpcStatus, 
                                uint8_t *startStatus);
/// @brief Function pointer for @ref phRpc_D11_StartTestSwCt
typedef uint8_t (*pphRpc_D11_StartTestSwCt)(uint8_t*, uint16_t, uint16_t *, uint8_t *);
 
/** 
@brief Response to Stop the Secondary Firmware

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  stopStatus  Status of the Start Operation
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  stopStatus[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_StopTestSwCt(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus, 
                               uint8_t *stopStatus);
/// @brief Function pointer for @ref phRpc_D11_StopTestSwCt
typedef uint8_t (*pphRpc_D11_StopTestSwCt)(uint8_t*, uint16_t, uint16_t *, uint8_t *);
 
/** 
@brief Data Exchange between Secondary Firmware and Host

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  lenFromCt  Receive Length, number of bytes received from the secondary firmware
@param  lenToCt  Transmit Length, number of bytes sent to the secondary firmware
@param  xBuffer  Exchange Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  lenFromCt[2]  lenToCt[2]  xBuffer[PH_RPC_CMD_EXT_DEV_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_DataExchangeTestSwCt(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                       uint16_t *rpcStatus, 
                                       uint16_t *lenFromCt, 
                                       uint16_t *lenToCt, 
                                       uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_D11_DataExchangeTestSwCt
typedef uint8_t (*pphRpc_D11_DataExchangeTestSwCt)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint16_t *, uint8_t **);
 
/** 
@brief Data Exchange between Secondary Firmware and Host

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  lenFromCt  Receive Length, number of bytes received from the secondary firmware
@param  lenToCt  Transmit Length, number of bytes sent to the secondary firmware
@param  xBuffer  Exchange Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  lenFromCt[2]  lenToCt[2]  xBuffer[lenFromCt <= PH_RPC_CMD_EXT_DEV_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of xBuffer is variable, depends on lenFromCt and has a maximum length of PH_RPC_CMD_EXT_DEV_BUFSIZE.
*/ 
uint8_t phRpc_V_D11_DataExchangeTestSwCt(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                         uint16_t *rpcStatus, 
                                         uint16_t *lenFromCt, 
                                         uint16_t *lenToCt, 
                                         uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_V_D11_DataExchangeTestSwCt
typedef uint8_t (*pphRpc_V_D11_DataExchangeTestSwCt)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint16_t *, uint8_t **);
 
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
uint8_t phRpc_D11_DutInit(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                          uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_D11_DutInit
typedef uint8_t (*pphRpc_D11_DutInit)(uint8_t*, uint16_t, uint16_t *);
 
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
uint8_t phRpc_D11_DutGetMode(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint16_t *rpcStatus, 
                             uint32_t *intfMode);
/// @brief Function pointer for @ref phRpc_D11_DutGetMode
typedef uint8_t (*pphRpc_D11_DutGetMode)(uint8_t*, uint16_t, uint16_t *, uint32_t *);
 
/** 
@brief Data Exchange with the DUT - Short Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  rxLength  Receive Length
@param  txLength  Transmit Length
@param  preBuf  Prepend Buffer
@param  xBuffer  Exchange Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  rxLength[2]  txLength[2]  preBuf[PH_RPC_CMD_PREPEND_LEN]  xBuffer[PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_DutRWShort(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint16_t *rpcStatus, 
                             uint16_t *rxLength, 
                             uint16_t *txLength, 
                             uint8_t **preBuf, 
                             uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_D11_DutRWShort
typedef uint8_t (*pphRpc_D11_DutRWShort)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint16_t *, uint8_t **, uint8_t **);
 
/** 
@brief Data Exchange with the DUT - Short Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  rxLength  Receive Length
@param  txLength  Transmit Length
@param  preBuf  Prepend Buffer
@param  xBuffer  Exchange Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  rxLength[2]  txLength[2]  preBuf[PH_RPC_CMD_PREPEND_LEN]  xBuffer[rxLength <= PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of xBuffer is variable, depends on rxLength and has a maximum length of PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT.
*/ 
uint8_t phRpc_V_D11_DutRWShort(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus, 
                               uint16_t *rxLength, 
                               uint16_t *txLength, 
                               uint8_t **preBuf, 
                               uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_V_D11_DutRWShort
typedef uint8_t (*pphRpc_V_D11_DutRWShort)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint16_t *, uint8_t **, uint8_t **);
 
/** 
@brief Data Exchange with the DUT - Long Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  rxLength  Receive Length
@param  txLength  Transmit Length
@param  preBuf  Prepend Buffer
@param  xBuffer  Exchange Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  rxLength[2]  txLength[2]  preBuf[PH_RPC_CMD_PREPEND_LEN]  xBuffer[PH_RPC_CMD_EXT_DEV_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_DutRWLong(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                            uint16_t *rpcStatus, 
                            uint16_t *rxLength, 
                            uint16_t *txLength, 
                            uint8_t **preBuf, 
                            uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_D11_DutRWLong
typedef uint8_t (*pphRpc_D11_DutRWLong)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint16_t *, uint8_t **, uint8_t **);
 
/** 
@brief Data Exchange with the DUT - Long Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  rxLength  Receive Length
@param  txLength  Transmit Length
@param  preBuf  Prepend Buffer
@param  xBuffer  Exchange Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  rxLength[2]  txLength[2]  preBuf[PH_RPC_CMD_PREPEND_LEN]  xBuffer[rxLength <= PH_RPC_CMD_EXT_DEV_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of xBuffer is variable, depends on rxLength and has a maximum length of PH_RPC_CMD_EXT_DEV_BUFSIZE.
*/ 
uint8_t phRpc_V_D11_DutRWLong(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint16_t *rpcStatus, 
                              uint16_t *rxLength, 
                              uint16_t *txLength, 
                              uint8_t **preBuf, 
                              uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_V_D11_DutRWLong
typedef uint8_t (*pphRpc_V_D11_DutRWLong)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint16_t *, uint8_t **, uint8_t **);
 
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
uint8_t phRpc_D11_DevIoCtrl(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                            uint16_t *rpcStatus, 
                            uint32_t *ioctlOpt);
/// @brief Function pointer for @ref phRpc_D11_DevIoCtrl
typedef uint8_t (*pphRpc_D11_DevIoCtrl)(uint8_t*, uint16_t, uint16_t *, uint32_t *);
 
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
uint8_t phRpc_D11_DevIoLineCtrl(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint16_t *rpcStatus, 
                                uint32_t *ioLineCtlOpt);
/// @brief Function pointer for @ref phRpc_D11_DevIoLineCtrl
typedef uint8_t (*pphRpc_D11_DevIoLineCtrl)(uint8_t*, uint16_t, uint16_t *, uint32_t *);
 
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
uint8_t phRpc_D11_AdcGetValue(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint16_t *rpcStatus, 
                              int32_t *daqVal);
/// @brief Function pointer for @ref phRpc_D11_AdcGetValue
typedef uint8_t (*pphRpc_D11_AdcGetValue)(uint8_t*, uint16_t, uint16_t *, int32_t *);
 
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
uint8_t phRpc_D11_DacSetValue(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_D11_DacSetValue
typedef uint8_t (*pphRpc_D11_DacSetValue)(uint8_t*, uint16_t, uint16_t *);
 
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
uint8_t phRpc_D11_DacSetWave(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_D11_DacSetWave
typedef uint8_t (*pphRpc_D11_DacSetWave)(uint8_t*, uint16_t, uint16_t *);
 
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
uint8_t phRpc_D11_DaqGetVRef(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint16_t *rpcStatus, 
                             uint32_t *vrefVal);
/// @brief Function pointer for @ref phRpc_D11_DaqGetVRef
typedef uint8_t (*pphRpc_D11_DaqGetVRef)(uint8_t*, uint16_t, uint16_t *, uint32_t *);
 
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
uint8_t phRpc_D11_DaqSetVRef(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_D11_DaqSetVRef
typedef uint8_t (*pphRpc_D11_DaqSetVRef)(uint8_t*, uint16_t, uint16_t *);
 
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
uint8_t phRpc_D11_DaqSetGain(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_D11_DaqSetGain
typedef uint8_t (*pphRpc_D11_DaqSetGain)(uint8_t*, uint16_t, uint16_t *);
 
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
uint8_t phRpc_D11_DaqGetGain(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint16_t *rpcStatus, 
                             int32_t *gainVal);
/// @brief Function pointer for @ref phRpc_D11_DaqGetGain
typedef uint8_t (*pphRpc_D11_DaqGetGain)(uint8_t*, uint16_t, uint16_t *, int32_t *);
 
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
uint8_t phRpc_D11_DacGetFrequency(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint16_t *rpcStatus, 
                                  uint32_t *actualF);
/// @brief Function pointer for @ref phRpc_D11_DacGetFrequency
typedef uint8_t (*pphRpc_D11_DacGetFrequency)(uint8_t*, uint16_t, uint16_t *, uint32_t *);
 
/** 
@brief Communication Check - Short Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  xLength  Length
@param  xBuffer  Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  xLength[2]  xBuffer[PH_RPC_CMD_COMMCHECK_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_DeviceCommCheck(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint16_t *rpcStatus, 
                                  uint16_t *xLength, 
                                  uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_D11_DeviceCommCheck
typedef uint8_t (*pphRpc_D11_DeviceCommCheck)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t **);
 
/** 
@brief Communication Check - Short Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  xLength  Length
@param  xBuffer  Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  xLength[2]  xBuffer[xLength <= PH_RPC_CMD_COMMCHECK_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of xBuffer is variable, depends on xLength and has a maximum length of PH_RPC_CMD_COMMCHECK_BUFLEN.
*/ 
uint8_t phRpc_V_D11_DeviceCommCheck(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                    uint16_t *rpcStatus, 
                                    uint16_t *xLength, 
                                    uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_V_D11_DeviceCommCheck
typedef uint8_t (*pphRpc_V_D11_DeviceCommCheck)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t **);
 
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
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  xLength[2]  xBuffer[PH_RPC_CMD_COMMCHECK_L_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_DeviceCommCheckL(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                   uint16_t *rpcStatus, 
                                   uint16_t *xLength, 
                                   uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_D11_DeviceCommCheckL
typedef uint8_t (*pphRpc_D11_DeviceCommCheckL)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t **);
 
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
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  xLength[2]  xBuffer[xLength <= PH_RPC_CMD_COMMCHECK_L_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of xBuffer is variable, depends on xLength and has a maximum length of PH_RPC_CMD_COMMCHECK_L_BUFLEN.
*/ 
uint8_t phRpc_V_D11_DeviceCommCheckL(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                     uint16_t *rpcStatus, 
                                     uint16_t *xLength, 
                                     uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_V_D11_DeviceCommCheckL
typedef uint8_t (*pphRpc_V_D11_DeviceCommCheckL)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t **);
 
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
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  xLength[2]  xBuffer[PH_RPC_CMD_COMMCHECK_L_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                     uint16_t *rpcStatus, 
                                     uint16_t *xLength, 
                                     uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_D11_DeviceCommCheckWTX
typedef uint8_t (*pphRpc_D11_DeviceCommCheckWTX)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t **);
 
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
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  xLength[2]  xBuffer[xLength <= PH_RPC_CMD_COMMCHECK_L_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of xBuffer is variable, depends on xLength and has a maximum length of PH_RPC_CMD_COMMCHECK_L_BUFLEN.
*/ 
uint8_t phRpc_V_D11_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                       uint16_t *rpcStatus, 
                                       uint16_t *xLength, 
                                       uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_V_D11_DeviceCommCheckWTX
typedef uint8_t (*pphRpc_V_D11_DeviceCommCheckWTX)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t **);
 
/** 
@brief Test Function 1

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  a1  Test Argument 1
@param  a2  Test Argument 2
@param  a3  Test Argument 3
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  a1[1]  a2[2]  a3[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_D_TEST1(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                          uint16_t *rpcStatus, 
                          uint8_t *a1, 
                          uint16_t *a2, 
                          uint32_t *a3);
/// @brief Function pointer for @ref phRpc_D11_D_TEST1
typedef uint8_t (*pphRpc_D11_D_TEST1)(uint8_t*, uint16_t, uint16_t *, uint8_t *, uint16_t *, uint32_t *);
 
/** 
@brief Test Function 2

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  rpcStatus  Status
@param  a1  Test Argument 1
@param  b1_len  Length
@param  b1  Buffer
@param  a3  Test Argument 3
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  rpcStatus[2]  a1[1]  b1_len[2]  b1[2]  a3[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_D_TEST2(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                          uint16_t *rpcStatus, 
                          uint8_t *a1, 
                          uint16_t *b1_len, 
                          uint8_t **b1, 
                          uint32_t *a3);
/// @brief Function pointer for @ref phRpc_D11_D_TEST2
typedef uint8_t (*pphRpc_D11_D_TEST2)(uint8_t*, uint16_t, uint16_t *, uint8_t *, uint16_t *, uint8_t **, uint32_t *);
 
/** 
@brief Test Function 3

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
uint8_t phRpc_D11_D_TEST3(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                          uint16_t *rpcStatus);
/// @brief Function pointer for @ref phRpc_D11_D_TEST3
typedef uint8_t (*pphRpc_D11_D_TEST3)(uint8_t*, uint16_t, uint16_t *);
 
/** 
@brief Test Function 4

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  a1  Test Argument 1
@param  b1_len  Length of buffer 1
@param  b2_len  Length of buffer 2
@param  b1  Buffer 1
@param  a3  Test Argument 3
@param  b2  Buffer 2
@param  a4  Test Argument 4
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  a1[1]  b1_len[2]  b2_len[2]  b1[16]  a3[4]  b2[16]  a4[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_D11_D_TEST4(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                          uint8_t *a1, 
                          uint16_t *b1_len, 
                          uint16_t *b2_len, 
                          uint8_t **b1, 
                          uint32_t *a3, 
                          uint8_t **b2, 
                          uint32_t *a4);
/// @brief Function pointer for @ref phRpc_D11_D_TEST4
typedef uint8_t (*pphRpc_D11_D_TEST4)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint16_t *, uint8_t **, uint32_t *, uint8_t **, uint32_t *);
 
/** 
@brief Test Function 4

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  a1  Test Argument 1
@param  b1_len  Length of buffer 1
@param  b2_len  Length of buffer 2
@param  b1  Buffer 1
@param  a3  Test Argument 3
@param  b2  Buffer 2
@param  a4  Test Argument 4
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  a1[1]  b1_len[2]  b2_len[2]  b1[b1_len <= 16]  a3[4]  b2[b2_len <= 16]  a4[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of b1 is variable, depends on b1_len and has a maximum length of 16.
      @li The length of b2 is variable, depends on b2_len and has a maximum length of 16.
*/ 
uint8_t phRpc_V_D11_D_TEST4(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                            uint8_t *a1, 
                            uint16_t *b1_len, 
                            uint16_t *b2_len, 
                            uint8_t **b1, 
                            uint32_t *a3, 
                            uint8_t **b2, 
                            uint32_t *a4);
/// @brief Function pointer for @ref phRpc_V_D11_D_TEST4
typedef uint8_t (*pphRpc_V_D11_D_TEST4)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint16_t *, uint8_t **, uint32_t *, uint8_t **, uint32_t *);
 
/** @} */ // grp_rpcf_ll_d2h_r
 

#endif // Guard
