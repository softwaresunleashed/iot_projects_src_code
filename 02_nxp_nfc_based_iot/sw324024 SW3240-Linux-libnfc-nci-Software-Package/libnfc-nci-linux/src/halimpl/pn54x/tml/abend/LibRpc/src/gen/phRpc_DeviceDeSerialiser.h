//
// AUTO-GENERATED: DO NOT EDIT. 
//
 

// _________________________________________________________________________________________________
 
#ifndef phRpc11HD_h
#define phRpc11HD_h

#include <stdint.h>
#include <string.h>

/** 
 * @addtogroup grp_rpcf_ll_h2d_r
 * @{ 
 */ 
 
/// @brief Function ID Enumeration 
typedef enum
{
    phRpc_D_FID_SetCommParam = 1, ///< Apply communication Parameters
    phRpc_D_FID_GetDeviceInfo = 2, ///< Get Device Information
    phRpc_D_FID_CtrlDeviceDiag = 3, ///< Control Diagnostics
    phRpc_D_FID_SetDeviceMode = 4, ///< Re-Initialise device and put it into specified operating mode
    phRpc_D_FID_GetDeviceCtInfo = 5, ///< Get Device Secondary Firmware Information
    phRpc_D_FID_DeviceDaq = 12, ///< Device DAQ
    phRpc_D_FID_GetDevCompatInfo = 13, ///< Get Device Compatibility Information
    phRpc_D_FID_WTX = 14, ///< Waiting Time Extension and Cancel handling
    phRpc_D_FID_GetLastResponse = 15, ///< Get Last Response
    phRpc_D_FID_EE = 16, ///< EEPROM Command
    phRpc_D_FID_EECfg = 17, ///< EE Configuration Control
    phRpc_D_FID_StartTestSwCt = 18, ///< Start the Secondary Firmware
    phRpc_D_FID_StopTestSwCt = 19, ///< Stop the Secondary Firmware
    phRpc_D_FID_DataExchangeTestSwCt = 20, ///< Data Exchange with the Secondary Firmware
    phRpc_D_FID_DutInit = 64, ///< INIT Interface to DUT
    phRpc_D_FID_DutGetMode = 65, ///< Get DUT Interface mode
    phRpc_D_FID_DutRWShort = 66, ///< Data Exchange with the DUT - Short Buffer
    phRpc_D_FID_DutRWLong = 67, ///< Data Exchange with the DUT - Long Buffer
    phRpc_D_FID_DevIoCtrl = 68, ///< Device I/O Control
    phRpc_D_FID_DevIoLineCtrl = 69, ///< Device I/O Line Control
    phRpc_D_FID_AdcGetValue = 70, ///< Get Acquired Value
    phRpc_D_FID_DacSetValue = 71, ///< Set Value
    phRpc_D_FID_DacSetWave = 72, ///< Set Wave
    phRpc_D_FID_DaqGetVRef = 73, ///< Get the Reference Voltage
    phRpc_D_FID_DaqSetVRef = 74, ///< Set the Reference Voltage
    phRpc_D_FID_DaqSetGain = 75, ///< Set the Gain of a Channel
    phRpc_D_FID_DaqGetGain = 76, ///< Get the Gain of a Channel
    phRpc_D_FID_DacGetFrequency = 77, ///< Get the Frequency of a Channel
    phRpc_D_FID_DeviceCommCheck = 241, ///< Communication Check - Short Buffer
    phRpc_D_FID_DeviceCommCheckL = 242, ///< Communication Check - Long Buffer
    phRpc_D_FID_DeviceCommCheckWTX = 243, ///< Communication Check - Using WTX
    phRpc_D_FID_H_TEST1 = 255, ///< Test Function 1
    phRpc_D_FID_H_TEST2 = 254, ///< Test Function 2
    phRpc_D_FID_H_TEST3 = 253, ///< Test Function 3
    phRpc_D_FID_H_TEST4 = 252, ///< Test Function 4
    phRpc_D_FID_Max
} phRpc_D_FID_t;

// _________________________________________________________________________________________________
 
/// @brief Completion Handler
uint8_t phRpc_D_Handler_DispatchCompletion(void *rpcCtx, uint8_t dispatchResult);

/// @brief Get the number of bytes
uint16_t phRpc_D_GetNumBytes(uint8_t *rpcBuf);

/// @brief Function ID Getter
uint16_t phRpc_D_GetFid(uint8_t *rpcBuf);

/// @brief Sequence Number Getter
uint8_t phRpc_D_GetSeqNum(uint8_t *rpcBuf);

/// @brief Check the CH2 ID bit
uint8_t phRpc_D_IsCh2Id(uint8_t *rpcBuf);

/// @brief Clear the CH2 ID bit
void phRpc_D_ClearCh2Id(uint8_t *rpcBuf);

/// @brief RPC Dispatcher/Entry Handler
uint8_t phRpc_D_Dispatch(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 

// _________________________________________________________________________________________________
 
/// \brief Remote handler for function NotImplemented
uint8_t phRpc_D_Handler_NotImplemented(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function SetCommParam
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_SetCommParam(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function GetDeviceInfo
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_GetDeviceInfo(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function CtrlDeviceDiag
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_CtrlDeviceDiag(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function SetDeviceMode
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_SetDeviceMode(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function GetDeviceCtInfo
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_GetDeviceCtInfo(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DeviceDaq
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DeviceDaq(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function GetDevCompatInfo
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_GetDevCompatInfo(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function WTX
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_WTX(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function GetLastResponse
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_GetLastResponse(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function EE
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_EE(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function EECfg
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_EECfg(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function StartTestSwCt
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_StartTestSwCt(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function StopTestSwCt
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_StopTestSwCt(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DataExchangeTestSwCt
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DataExchangeTestSwCt(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DutInit
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DutInit(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DutGetMode
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DutGetMode(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DutRWShort
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DutRWShort(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DutRWLong
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DutRWLong(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DevIoCtrl
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DevIoCtrl(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DevIoLineCtrl
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DevIoLineCtrl(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function AdcGetValue
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_AdcGetValue(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DacSetValue
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DacSetValue(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DacSetWave
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DacSetWave(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DaqGetVRef
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DaqGetVRef(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DaqSetVRef
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DaqSetVRef(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DaqSetGain
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DaqSetGain(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DaqGetGain
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DaqGetGain(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DacGetFrequency
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DacGetFrequency(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DeviceCommCheck
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DeviceCommCheck(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DeviceCommCheckL
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DeviceCommCheckL(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function DeviceCommCheckWTX
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_DeviceCommCheckWTX(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function H_TEST1
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_H_TEST1(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function H_TEST2
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_H_TEST2(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function H_TEST3
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_H_TEST3(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 
/// \brief Remote handler for function H_TEST4
#ifdef RPC_WEAK_DEFAULT_HANDLER
 __attribute__ ((weak, alias ("phRpc_D_Handler_NotImplemented")))
#endif
uint8_t phRpc_D_Handler_H_TEST4(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen);
 

// _________________________________________________________________________________________________
 
/** 
@brief Apply communication Parameters

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  commSettings  Communication Settings
@param  msTimeout  Host time-out value in [ms]
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  commSettings[4]  msTimeout[2]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_SetCommParam(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint32_t *commSettings, 
                               uint16_t *msTimeout);
/// @brief Function pointer for @ref phRpc_H11_SetCommParam
typedef uint8_t (*pphRpc_H11_SetCommParam)(uint8_t*, uint16_t, uint32_t *, uint16_t *);
 
/** 
@brief Get Device Information

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  infoType  Type of information to get
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  infoType[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_GetDeviceInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint8_t *infoType);
/// @brief Function pointer for @ref phRpc_H11_GetDeviceInfo
typedef uint8_t (*pphRpc_H11_GetDeviceInfo)(uint8_t*, uint16_t, uint8_t *);
 
/** 
@brief Control Diagnostics

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  diagJob  Type of diagnostic Job
@param  infoBufLen  Information Buffer Length
@param  infoBuf  Diagnostic Information Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  diagJob[1]  infoBufLen[2]  infoBuf[PH_RPC_CMD_CTRLDIAG_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_CtrlDeviceDiag(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                 uint8_t *diagJob, 
                                 uint16_t *infoBufLen, 
                                 uint8_t **infoBuf);
/// @brief Function pointer for @ref phRpc_H11_CtrlDeviceDiag
typedef uint8_t (*pphRpc_H11_CtrlDeviceDiag)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint8_t **);
 
/** 
@brief Control Diagnostics

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  diagJob  Type of diagnostic Job
@param  infoBufLen  Information Buffer Length
@param  infoBuf  Diagnostic Information Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  diagJob[1]  infoBufLen[2]  infoBuf[infoBufLen <= PH_RPC_CMD_CTRLDIAG_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of infoBuf is variable, depends on infoBufLen and has a maximum length of PH_RPC_CMD_CTRLDIAG_BUFLEN.
*/ 
uint8_t phRpc_V_H11_CtrlDeviceDiag(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                   uint8_t *diagJob, 
                                   uint16_t *infoBufLen, 
                                   uint8_t **infoBuf);
/// @brief Function pointer for @ref phRpc_V_H11_CtrlDeviceDiag
typedef uint8_t (*pphRpc_V_H11_CtrlDeviceDiag)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint8_t **);
 
/** 
@brief Re-Initialise device and put it into specified operating mode

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  devMode  Operating mode
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  devMode[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_SetDeviceMode(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint8_t *devMode);
/// @brief Function pointer for @ref phRpc_H11_SetDeviceMode
typedef uint8_t (*pphRpc_H11_SetDeviceMode)(uint8_t*, uint16_t, uint8_t *);
 
/** 
@brief Get Device Secondary Firmware Information

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  infoType  Type of information to get
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  infoType[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_GetDeviceCtInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint8_t *infoType);
/// @brief Function pointer for @ref phRpc_H11_GetDeviceCtInfo
typedef uint8_t (*pphRpc_H11_GetDeviceCtInfo)(uint8_t*, uint16_t, uint8_t *);
 
/** 
@brief Device DAQ

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  daqAddress  DAQ start address
@param  daqSetLength  DAQ SET length in bytes
@param  daqGetLength  DAQ GET length in bytes
@param  daqBuffer  DAQ Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  daqAddress[4]  daqSetLength[2]  daqGetLength[2]  daqBuffer[PH_RPC_CMD_EXT_DEV_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DeviceDaq(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                            uint32_t *daqAddress, 
                            uint16_t *daqSetLength, 
                            uint16_t *daqGetLength, 
                            uint8_t **daqBuffer);
/// @brief Function pointer for @ref phRpc_H11_DeviceDaq
typedef uint8_t (*pphRpc_H11_DeviceDaq)(uint8_t*, uint16_t, uint32_t *, uint16_t *, uint16_t *, uint8_t **);
 
/** 
@brief Device DAQ

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  daqAddress  DAQ start address
@param  daqSetLength  DAQ SET length in bytes
@param  daqGetLength  DAQ GET length in bytes
@param  daqBuffer  DAQ Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  daqAddress[4]  daqSetLength[2]  daqGetLength[2]  daqBuffer[daqSetLength <= PH_RPC_CMD_EXT_DEV_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of daqBuffer is variable, depends on daqSetLength and has a maximum length of PH_RPC_CMD_EXT_DEV_BUFSIZE.
*/ 
uint8_t phRpc_V_H11_DeviceDaq(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint32_t *daqAddress, 
                              uint16_t *daqSetLength, 
                              uint16_t *daqGetLength, 
                              uint8_t **daqBuffer);
/// @brief Function pointer for @ref phRpc_V_H11_DeviceDaq
typedef uint8_t (*pphRpc_V_H11_DeviceDaq)(uint8_t*, uint16_t, uint32_t *, uint16_t *, uint16_t *, uint8_t **);
 
/** 
@brief Get Device Compatibility Information

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  infoType  Type of information to get
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  infoType[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_GetDevCompatInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                   uint8_t *infoType);
/// @brief Function pointer for @ref phRpc_H11_GetDevCompatInfo
typedef uint8_t (*pphRpc_H11_GetDevCompatInfo)(uint8_t*, uint16_t, uint8_t *);
 
/** 
@brief Waiting Time Extension and Cancel handling

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  cancelReq  Cancel Request
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  cancelReq[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_WTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                      uint8_t *cancelReq);
/// @brief Function pointer for @ref phRpc_H11_WTX
typedef uint8_t (*pphRpc_H11_WTX)(uint8_t*, uint16_t, uint8_t *);
 
/** 
@brief Get Last Response

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_GetLastResponse(uint8_t *rpcBuf, uint16_t rpcBufLen);
/// @brief Function pointer for @ref phRpc_H11_GetLastResponse
typedef uint8_t (*pphRpc_H11_GetLastResponse)(uint8_t*, uint16_t);
 
/** 
@brief EEPROM Command

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  eeFn  EEPROM Function
@param  eeAddr  EEPROM Address
@param  eeLength  Buffer Length
@param  preEEBuf  Prepend Buffer
@param  eeBuf  EE Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  eeFn[1]  eeAddr[2]  eeLength[2]  preEEBuf[PH_RPC_CMD_EE_PREPEND]  eeBuf[PH_RPC_CMD_EE_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_EE(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                     uint8_t *eeFn, 
                     uint16_t *eeAddr, 
                     uint16_t *eeLength, 
                     uint8_t **preEEBuf, 
                     uint8_t **eeBuf);
/// @brief Function pointer for @ref phRpc_H11_EE
typedef uint8_t (*pphRpc_H11_EE)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint16_t *, uint8_t **, uint8_t **);
 
/** 
@brief EEPROM Command

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  eeFn  EEPROM Function
@param  eeAddr  EEPROM Address
@param  eeLength  Buffer Length
@param  preEEBuf  Prepend Buffer
@param  eeBuf  EE Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  eeFn[1]  eeAddr[2]  eeLength[2]  preEEBuf[PH_RPC_CMD_EE_PREPEND]  eeBuf[eeLength <= PH_RPC_CMD_EE_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of eeBuf is variable, depends on eeLength and has a maximum length of PH_RPC_CMD_EE_BUFLEN.
*/ 
uint8_t phRpc_V_H11_EE(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                       uint8_t *eeFn, 
                       uint16_t *eeAddr, 
                       uint16_t *eeLength, 
                       uint8_t **preEEBuf, 
                       uint8_t **eeBuf);
/// @brief Function pointer for @ref phRpc_V_H11_EE
typedef uint8_t (*pphRpc_V_H11_EE)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint16_t *, uint8_t **, uint8_t **);
 
/** 
@brief EE Configuration Control

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  eeCtlFn  EE Configuration Control Function
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  eeCtlFn[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_EECfg(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                        uint8_t *eeCtlFn);
/// @brief Function pointer for @ref phRpc_H11_EECfg
typedef uint8_t (*pphRpc_H11_EECfg)(uint8_t*, uint16_t, uint8_t *);
 
/** 
@brief Start the Secondary Firmware

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  optStartParam  Optional Parameter
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  optStartParam[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_StartTestSwCt(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint32_t *optStartParam);
/// @brief Function pointer for @ref phRpc_H11_StartTestSwCt
typedef uint8_t (*pphRpc_H11_StartTestSwCt)(uint8_t*, uint16_t, uint32_t *);
 
/** 
@brief Stop the Secondary Firmware

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_StopTestSwCt(uint8_t *rpcBuf, uint16_t rpcBufLen);
/// @brief Function pointer for @ref phRpc_H11_StopTestSwCt
typedef uint8_t (*pphRpc_H11_StopTestSwCt)(uint8_t*, uint16_t);
 
/** 
@brief Data Exchange with the Secondary Firmware

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  lenFromCt  Maximum Receive Length, maximum number of bytes to be received from secondary firmware
@param  lenToCt  Transmit Length, number of bytes to be sent to the secondary firmware
@param  xBuffer  Exchange Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  lenFromCt[2]  lenToCt[2]  xBuffer[PH_RPC_CMD_EXT_DEV_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DataExchangeTestSwCt(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                       uint16_t *lenFromCt, 
                                       uint16_t *lenToCt, 
                                       uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_H11_DataExchangeTestSwCt
typedef uint8_t (*pphRpc_H11_DataExchangeTestSwCt)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t **);
 
/** 
@brief Data Exchange with the Secondary Firmware

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  lenFromCt  Maximum Receive Length, maximum number of bytes to be received from secondary firmware
@param  lenToCt  Transmit Length, number of bytes to be sent to the secondary firmware
@param  xBuffer  Exchange Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  lenFromCt[2]  lenToCt[2]  xBuffer[lenToCt <= PH_RPC_CMD_EXT_DEV_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of xBuffer is variable, depends on lenToCt and has a maximum length of PH_RPC_CMD_EXT_DEV_BUFSIZE.
*/ 
uint8_t phRpc_V_H11_DataExchangeTestSwCt(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                         uint16_t *lenFromCt, 
                                         uint16_t *lenToCt, 
                                         uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_V_H11_DataExchangeTestSwCt
typedef uint8_t (*pphRpc_V_H11_DataExchangeTestSwCt)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t **);
 
/** 
@brief INIT Interface to DUT

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  hiFn  Function/Interface to activate
@param  hiAddr  Interface address (only valid for addressable interface)
@param  hiSpeed  Interface speed
@param  hiClkPol  SPI Clock Polarity
@param  hiClkPha  SPI Clock Phase
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  hiFn[1]  hiAddr[1]  hiSpeed[4]  hiClkPol[1]  hiClkPha[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DutInit(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                          uint8_t *hiFn, 
                          uint8_t *hiAddr, 
                          uint32_t *hiSpeed, 
                          uint8_t *hiClkPol, 
                          uint8_t *hiClkPha);
/// @brief Function pointer for @ref phRpc_H11_DutInit
typedef uint8_t (*pphRpc_H11_DutInit)(uint8_t*, uint16_t, uint8_t *, uint8_t *, uint32_t *, uint8_t *, uint8_t *);
 
/** 
@brief Get DUT Interface mode

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DutGetMode(uint8_t *rpcBuf, uint16_t rpcBufLen);
/// @brief Function pointer for @ref phRpc_H11_DutGetMode
typedef uint8_t (*pphRpc_H11_DutGetMode)(uint8_t*, uint16_t);
 
/** 
@brief Data Exchange with the DUT - Short Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  cmdRW  Read/Write
@param  rxLength  Receive Length
@param  txLength  Transmit Length
@param  preBuf  Prepend Buffer
@param  xBuffer  Exchange Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  cmdRW[1]  rxLength[2]  txLength[2]  preBuf[PH_RPC_CMD_PREPEND_LEN]  xBuffer[PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DutRWShort(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint8_t *cmdRW, 
                             uint16_t *rxLength, 
                             uint16_t *txLength, 
                             uint8_t **preBuf, 
                             uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_H11_DutRWShort
typedef uint8_t (*pphRpc_H11_DutRWShort)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint16_t *, uint8_t **, uint8_t **);
 
/** 
@brief Data Exchange with the DUT - Short Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  cmdRW  Read/Write
@param  rxLength  Receive Length
@param  txLength  Transmit Length
@param  preBuf  Prepend Buffer
@param  xBuffer  Exchange Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  cmdRW[1]  rxLength[2]  txLength[2]  preBuf[PH_RPC_CMD_PREPEND_LEN]  xBuffer[txLength <= PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of xBuffer is variable, depends on txLength and has a maximum length of PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT.
*/ 
uint8_t phRpc_V_H11_DutRWShort(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint8_t *cmdRW, 
                               uint16_t *rxLength, 
                               uint16_t *txLength, 
                               uint8_t **preBuf, 
                               uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_V_H11_DutRWShort
typedef uint8_t (*pphRpc_V_H11_DutRWShort)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint16_t *, uint8_t **, uint8_t **);
 
/** 
@brief Data Exchange with the DUT - Long Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  cmdRW  Read/Write
@param  rxLength  Receive Length
@param  txLength  Transmit Length
@param  preBuf  Prepend Buffer
@param  xBuffer  Exchange Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  cmdRW[1]  rxLength[2]  txLength[2]  preBuf[PH_RPC_CMD_PREPEND_LEN]  xBuffer[PH_RPC_CMD_EXT_DEV_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DutRWLong(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                            uint8_t *cmdRW, 
                            uint16_t *rxLength, 
                            uint16_t *txLength, 
                            uint8_t **preBuf, 
                            uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_H11_DutRWLong
typedef uint8_t (*pphRpc_H11_DutRWLong)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint16_t *, uint8_t **, uint8_t **);
 
/** 
@brief Data Exchange with the DUT - Long Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  cmdRW  Read/Write
@param  rxLength  Receive Length
@param  txLength  Transmit Length
@param  preBuf  Prepend Buffer
@param  xBuffer  Exchange Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  cmdRW[1]  rxLength[2]  txLength[2]  preBuf[PH_RPC_CMD_PREPEND_LEN]  xBuffer[txLength <= PH_RPC_CMD_EXT_DEV_BUFSIZE]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of xBuffer is variable, depends on txLength and has a maximum length of PH_RPC_CMD_EXT_DEV_BUFSIZE.
*/ 
uint8_t phRpc_V_H11_DutRWLong(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint8_t *cmdRW, 
                              uint16_t *rxLength, 
                              uint16_t *txLength, 
                              uint8_t **preBuf, 
                              uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_V_H11_DutRWLong
typedef uint8_t (*pphRpc_V_H11_DutRWLong)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint16_t *, uint8_t **, uint8_t **);
 
/** 
@brief Device I/O Control

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  ioctlCodeMj  Major Code
@param  ioctlCodeMn  Minor Code
@param  ioctlOpt  Optional Parameter
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  ioctlCodeMj[1]  ioctlCodeMn[1]  ioctlOpt[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DevIoCtrl(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                            uint8_t *ioctlCodeMj, 
                            uint8_t *ioctlCodeMn, 
                            uint32_t *ioctlOpt);
/// @brief Function pointer for @ref phRpc_H11_DevIoCtrl
typedef uint8_t (*pphRpc_H11_DevIoCtrl)(uint8_t*, uint16_t, uint8_t *, uint8_t *, uint32_t *);
 
/** 
@brief Device I/O Line Control

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  ioLineCtlItem  What to control
@param  ioLineCtlAction  Control Action
@param  ioctlOpt  Optional Parameter
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  ioLineCtlItem[1]  ioLineCtlAction[1]  ioctlOpt[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DevIoLineCtrl(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint8_t *ioLineCtlItem, 
                                uint8_t *ioLineCtlAction, 
                                uint32_t *ioctlOpt);
/// @brief Function pointer for @ref phRpc_H11_DevIoLineCtrl
typedef uint8_t (*pphRpc_H11_DevIoLineCtrl)(uint8_t*, uint16_t, uint8_t *, uint8_t *, uint32_t *);
 
/** 
@brief Get Acquired Value

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  channelID  Channel to query
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  channelID[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_AdcGetValue(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint8_t *channelID);
/// @brief Function pointer for @ref phRpc_H11_AdcGetValue
typedef uint8_t (*pphRpc_H11_AdcGetValue)(uint8_t*, uint16_t, uint8_t *);
 
/** 
@brief Set Value

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  channelID  Channel to control
@param  newValue  New value to set
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  channelID[1]  newValue[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DacSetValue(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint8_t *channelID, 
                              int32_t *newValue);
/// @brief Function pointer for @ref phRpc_H11_DacSetValue
typedef uint8_t (*pphRpc_H11_DacSetValue)(uint8_t*, uint16_t, uint8_t *, int32_t *);
 
/** 
@brief Set Wave

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  channelID  Channel to control
@param  waveType  Wave Type
@param  waveFrequency  Wave Frequency
@param  waveAmplitude  Wave Amplitude
@param  waveOffset  Wave Offset
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  channelID[1]  waveType[1]  waveFrequency[4]  waveAmplitude[4]  waveOffset[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DacSetWave(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint8_t *channelID, 
                             uint8_t *waveType, 
                             uint32_t *waveFrequency, 
                             int32_t *waveAmplitude, 
                             int32_t *waveOffset);
/// @brief Function pointer for @ref phRpc_H11_DacSetWave
typedef uint8_t (*pphRpc_H11_DacSetWave)(uint8_t*, uint16_t, uint8_t *, uint8_t *, uint32_t *, int32_t *, int32_t *);
 
/** 
@brief Get the Reference Voltage

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DaqGetVRef(uint8_t *rpcBuf, uint16_t rpcBufLen);
/// @brief Function pointer for @ref phRpc_H11_DaqGetVRef
typedef uint8_t (*pphRpc_H11_DaqGetVRef)(uint8_t*, uint16_t);
 
/** 
@brief Set the Reference Voltage

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  vrefVal  New Reference Voltage Value
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  vrefVal[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DaqSetVRef(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint32_t *vrefVal);
/// @brief Function pointer for @ref phRpc_H11_DaqSetVRef
typedef uint8_t (*pphRpc_H11_DaqSetVRef)(uint8_t*, uint16_t, uint32_t *);
 
/** 
@brief Set the Gain of a Channel

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  hwType  ADC or DAC
@param  channelID  Channel to control
@param  gainVal  New Gain Value
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  hwType[1]  channelID[1]  gainVal[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DaqSetGain(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint8_t *hwType, 
                             uint8_t *channelID, 
                             int32_t *gainVal);
/// @brief Function pointer for @ref phRpc_H11_DaqSetGain
typedef uint8_t (*pphRpc_H11_DaqSetGain)(uint8_t*, uint16_t, uint8_t *, uint8_t *, int32_t *);
 
/** 
@brief Get the Gain of a Channel

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  hwType  ADC or DAC
@param  channelID  Channel to query
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  hwType[1]  channelID[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DaqGetGain(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint8_t *hwType, 
                             uint8_t *channelID);
/// @brief Function pointer for @ref phRpc_H11_DaqGetGain
typedef uint8_t (*pphRpc_H11_DaqGetGain)(uint8_t*, uint16_t, uint8_t *, uint8_t *);
 
/** 
@brief Get the Frequency of a Channel

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  channelID  Channel to query
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  channelID[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DacGetFrequency(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint8_t *channelID);
/// @brief Function pointer for @ref phRpc_H11_DacGetFrequency
typedef uint8_t (*pphRpc_H11_DacGetFrequency)(uint8_t*, uint16_t, uint8_t *);
 
/** 
@brief Communication Check - Short Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  msWait  Waiting time in [ms]
@param  xLength  Length
@param  xBuffer  Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  msWait[1]  xLength[2]  xBuffer[PH_RPC_CMD_COMMCHECK_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DeviceCommCheck(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint8_t *msWait, 
                                  uint16_t *xLength, 
                                  uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_H11_DeviceCommCheck
typedef uint8_t (*pphRpc_H11_DeviceCommCheck)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint8_t **);
 
/** 
@brief Communication Check - Short Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  msWait  Waiting time in [ms]
@param  xLength  Length
@param  xBuffer  Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  msWait[1]  xLength[2]  xBuffer[xLength <= PH_RPC_CMD_COMMCHECK_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of xBuffer is variable, depends on xLength and has a maximum length of PH_RPC_CMD_COMMCHECK_BUFLEN.
*/ 
uint8_t phRpc_V_H11_DeviceCommCheck(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                    uint8_t *msWait, 
                                    uint16_t *xLength, 
                                    uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_V_H11_DeviceCommCheck
typedef uint8_t (*pphRpc_V_H11_DeviceCommCheck)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint8_t **);
 
/** 
@brief Communication Check - Long Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  msWait  Waiting time in [ms]
@param  xLength  Length
@param  xBuffer  Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  msWait[1]  xLength[2]  xBuffer[PH_RPC_CMD_COMMCHECK_L_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DeviceCommCheckL(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                   uint8_t *msWait, 
                                   uint16_t *xLength, 
                                   uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_H11_DeviceCommCheckL
typedef uint8_t (*pphRpc_H11_DeviceCommCheckL)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint8_t **);
 
/** 
@brief Communication Check - Long Buffer

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  msWait  Waiting time in [ms]
@param  xLength  Length
@param  xBuffer  Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  msWait[1]  xLength[2]  xBuffer[xLength <= PH_RPC_CMD_COMMCHECK_L_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of xBuffer is variable, depends on xLength and has a maximum length of PH_RPC_CMD_COMMCHECK_L_BUFLEN.
*/ 
uint8_t phRpc_V_H11_DeviceCommCheckL(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                     uint8_t *msWait, 
                                     uint16_t *xLength, 
                                     uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_V_H11_DeviceCommCheckL
typedef uint8_t (*pphRpc_V_H11_DeviceCommCheckL)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint8_t **);
 
/** 
@brief Communication Check - Using WTX

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  msWait  Waiting time in [ms]
@param  xLength  Length
@param  xBuffer  Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  msWait[2]  xLength[2]  xBuffer[PH_RPC_CMD_COMMCHECK_L_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                     uint16_t *msWait, 
                                     uint16_t *xLength, 
                                     uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_H11_DeviceCommCheckWTX
typedef uint8_t (*pphRpc_H11_DeviceCommCheckWTX)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t **);
 
/** 
@brief Communication Check - Using WTX

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  msWait  Waiting time in [ms]
@param  xLength  Length
@param  xBuffer  Buffer
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  msWait[2]  xLength[2]  xBuffer[xLength <= PH_RPC_CMD_COMMCHECK_L_BUFLEN]  
@endverbatim 
Data format: The LSB is at lower buffer position.
@note This function uses variable-length serialisation.
      @li The length of xBuffer is variable, depends on xLength and has a maximum length of PH_RPC_CMD_COMMCHECK_L_BUFLEN.
*/ 
uint8_t phRpc_V_H11_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                       uint16_t *msWait, 
                                       uint16_t *xLength, 
                                       uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_V_H11_DeviceCommCheckWTX
typedef uint8_t (*pphRpc_V_H11_DeviceCommCheckWTX)(uint8_t*, uint16_t, uint16_t *, uint16_t *, uint8_t **);
 
/** 
@brief Test Function 1

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  a1  Test Argument 1
@param  a2  Test Argument 2
@param  a3  Test Argument 3
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  a1[1]  a2[2]  a3[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_H_TEST1(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                          uint8_t *a1, 
                          uint16_t *a2, 
                          uint32_t *a3);
/// @brief Function pointer for @ref phRpc_H11_H_TEST1
typedef uint8_t (*pphRpc_H11_H_TEST1)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint32_t *);
 
/** 
@brief Test Function 2

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@param  a1  Test Argument 1
@param  b1_len  Length
@param  b1  Buffer
@param  a3  Test Argument 3
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  a1[1]  b1_len[2]  b1[2]  a3[4]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_H_TEST2(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                          uint8_t *a1, 
                          uint16_t *b1_len, 
                          uint8_t **b1, 
                          uint32_t *a3);
/// @brief Function pointer for @ref phRpc_H11_H_TEST2
typedef uint8_t (*pphRpc_H11_H_TEST2)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint8_t **, uint32_t *);
 
/** 
@brief Test Function 3

@param  rpcBuf  Serialisation Buffer
@param  rpcBufLen  Serialisation Buffer Length
@retval  0 Success
@retval  1 Error
@par Transfer Format 
@verbatim 
Length[2]  SqNr[1]  FnId[1]  
@endverbatim 
Data format: The LSB is at lower buffer position.
*/ 
uint8_t phRpc_H11_H_TEST3(uint8_t *rpcBuf, uint16_t rpcBufLen);
/// @brief Function pointer for @ref phRpc_H11_H_TEST3
typedef uint8_t (*pphRpc_H11_H_TEST3)(uint8_t*, uint16_t);
 
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
uint8_t phRpc_H11_H_TEST4(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                          uint8_t *a1, 
                          uint16_t *b1_len, 
                          uint16_t *b2_len, 
                          uint8_t **b1, 
                          uint32_t *a3, 
                          uint8_t **b2, 
                          uint32_t *a4);
/// @brief Function pointer for @ref phRpc_H11_H_TEST4
typedef uint8_t (*pphRpc_H11_H_TEST4)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint16_t *, uint8_t **, uint32_t *, uint8_t **, uint32_t *);
 
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
uint8_t phRpc_V_H11_H_TEST4(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                            uint8_t *a1, 
                            uint16_t *b1_len, 
                            uint16_t *b2_len, 
                            uint8_t **b1, 
                            uint32_t *a3, 
                            uint8_t **b2, 
                            uint32_t *a4);
/// @brief Function pointer for @ref phRpc_V_H11_H_TEST4
typedef uint8_t (*pphRpc_V_H11_H_TEST4)(uint8_t*, uint16_t, uint8_t *, uint16_t *, uint16_t *, uint8_t **, uint32_t *, uint8_t **, uint32_t *);
 
/** @} */ // grp_rpcf_ll_h2d_r
 

#endif // Guard
