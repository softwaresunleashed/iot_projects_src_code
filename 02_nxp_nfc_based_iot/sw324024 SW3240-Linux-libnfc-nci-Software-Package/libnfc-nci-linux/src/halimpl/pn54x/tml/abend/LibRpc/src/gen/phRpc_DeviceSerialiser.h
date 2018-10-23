//
// AUTO-GENERATED: DO NOT EDIT. 
//
 

// _________________________________________________________________________________________________
 
#ifndef phRpc00DH_h
#define phRpc00DH_h

#include <stdint.h>
#include <string.h>

/** 
 * @addtogroup grp_rpcf_ll_d2h_l
 * @{ 
 */ 
 

// _________________________________________________________________________________________________
 
/// @brief Sequence Number Setter
uint8_t phRpc_D_SetSeqNum(uint8_t *rpcBuf, uint8_t seqNum);

/// @brief Set the number of bytes
void phRpc_D_SetNumBytes(uint8_t *rpcBuf, uint16_t newRpcBufLen);

/// @brief Set the CH2 ID bit
void phRpc_D_SetCh2Id(uint8_t *rpcBuf);


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
uint8_t phRpc_D00_SetCommParam(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                               uint16_t rpcStatus);
/// @brief Function pointer for @ref phRpc_D00_SetCommParam
typedef uint8_t (*pphRpc_D00_SetCommParam)(uint8_t*, uint16_t*, uint16_t );
 
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
uint8_t phRpc_D00_GetDeviceInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint16_t rpcStatus, 
                                uint32_t infoNum, 
                                uint16_t infoBufLen, 
                                uint8_t *infoBuf);
/// @brief Function pointer for @ref phRpc_D00_GetDeviceInfo
typedef uint8_t (*pphRpc_D00_GetDeviceInfo)(uint8_t*, uint16_t*, uint16_t , uint32_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_V_D00_GetDeviceInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint16_t rpcStatus, 
                                  uint32_t infoNum, 
                                  uint16_t infoBufLen, 
                                  uint8_t *infoBuf);
/// @brief Function pointer for @ref phRpc_V_D00_GetDeviceInfo
typedef uint8_t (*pphRpc_V_D00_GetDeviceInfo)(uint8_t*, uint16_t*, uint16_t , uint32_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_D00_CtrlDeviceDiag(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                 uint16_t rpcStatus, 
                                 uint16_t infoBufLen, 
                                 uint8_t *infoBuf);
/// @brief Function pointer for @ref phRpc_D00_CtrlDeviceDiag
typedef uint8_t (*pphRpc_D00_CtrlDeviceDiag)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_V_D00_CtrlDeviceDiag(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                   uint16_t rpcStatus, 
                                   uint16_t infoBufLen, 
                                   uint8_t *infoBuf);
/// @brief Function pointer for @ref phRpc_V_D00_CtrlDeviceDiag
typedef uint8_t (*pphRpc_V_D00_CtrlDeviceDiag)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_D00_SetDeviceMode(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint16_t rpcStatus);
/// @brief Function pointer for @ref phRpc_D00_SetDeviceMode
typedef uint8_t (*pphRpc_D00_SetDeviceMode)(uint8_t*, uint16_t*, uint16_t );
 
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
uint8_t phRpc_D00_GetDeviceCtInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint16_t rpcStatus, 
                                  uint32_t infoNum, 
                                  uint16_t infoBufLen, 
                                  uint8_t *infoBuf);
/// @brief Function pointer for @ref phRpc_D00_GetDeviceCtInfo
typedef uint8_t (*pphRpc_D00_GetDeviceCtInfo)(uint8_t*, uint16_t*, uint16_t , uint32_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_V_D00_GetDeviceCtInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                    uint16_t rpcStatus, 
                                    uint32_t infoNum, 
                                    uint16_t infoBufLen, 
                                    uint8_t *infoBuf);
/// @brief Function pointer for @ref phRpc_V_D00_GetDeviceCtInfo
typedef uint8_t (*pphRpc_V_D00_GetDeviceCtInfo)(uint8_t*, uint16_t*, uint16_t , uint32_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_D00_DeviceDaq(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint16_t rpcStatus, 
                            uint32_t daqAddress, 
                            uint16_t daqLength, 
                            uint8_t **daqBuffer);
/// @brief Function pointer for @ref phRpc_D00_DeviceDaq
typedef uint8_t (*pphRpc_D00_DeviceDaq)(uint8_t*, uint16_t*, uint16_t , uint32_t , uint16_t , uint8_t **);
 
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
uint8_t phRpc_V_D00_DeviceDaq(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint16_t rpcStatus, 
                              uint32_t daqAddress, 
                              uint16_t daqLength, 
                              uint8_t **daqBuffer);
/// @brief Function pointer for @ref phRpc_V_D00_DeviceDaq
typedef uint8_t (*pphRpc_V_D00_DeviceDaq)(uint8_t*, uint16_t*, uint16_t , uint32_t , uint16_t , uint8_t **);
 
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
uint8_t phRpc_D00_GetDevCompatInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                   uint16_t rpcStatus, 
                                   uint16_t compatInfo, 
                                   uint8_t featureCode, 
                                   uint8_t valLevel, 
                                   uint8_t majorVersion, 
                                   uint8_t minorVersion);
/// @brief Function pointer for @ref phRpc_D00_GetDevCompatInfo
typedef uint8_t (*pphRpc_D00_GetDevCompatInfo)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint8_t , uint8_t , uint8_t , uint8_t );
 
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
uint8_t phRpc_D00_WTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                      uint16_t rpcStatus);
/// @brief Function pointer for @ref phRpc_D00_WTX
typedef uint8_t (*pphRpc_D00_WTX)(uint8_t*, uint16_t*, uint16_t );
 
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
uint8_t phRpc_D00_GetLastResponse(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint16_t rpcStatus);
/// @brief Function pointer for @ref phRpc_D00_GetLastResponse
typedef uint8_t (*pphRpc_D00_GetLastResponse)(uint8_t*, uint16_t*, uint16_t );
 
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
uint8_t phRpc_D00_EE(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                     uint16_t rpcStatus, 
                     uint8_t *eeBuf, 
                     uint16_t infoBufLen);
/// @brief Function pointer for @ref phRpc_D00_EE
typedef uint8_t (*pphRpc_D00_EE)(uint8_t*, uint16_t*, uint16_t , uint8_t *, uint16_t );
 
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
uint8_t phRpc_V_D00_EE(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                       uint16_t rpcStatus, 
                       uint8_t *eeBuf, 
                       uint16_t infoBufLen);
/// @brief Function pointer for @ref phRpc_V_D00_EE
typedef uint8_t (*pphRpc_V_D00_EE)(uint8_t*, uint16_t*, uint16_t , uint8_t *, uint16_t );
 
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
uint8_t phRpc_D00_EECfg(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                        uint16_t rpcStatus);
/// @brief Function pointer for @ref phRpc_D00_EECfg
typedef uint8_t (*pphRpc_D00_EECfg)(uint8_t*, uint16_t*, uint16_t );
 
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
uint8_t phRpc_D00_StartTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint16_t rpcStatus, 
                                uint8_t startStatus);
/// @brief Function pointer for @ref phRpc_D00_StartTestSwCt
typedef uint8_t (*pphRpc_D00_StartTestSwCt)(uint8_t*, uint16_t*, uint16_t , uint8_t );
 
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
uint8_t phRpc_D00_StopTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                               uint16_t rpcStatus, 
                               uint8_t stopStatus);
/// @brief Function pointer for @ref phRpc_D00_StopTestSwCt
typedef uint8_t (*pphRpc_D00_StopTestSwCt)(uint8_t*, uint16_t*, uint16_t , uint8_t );
 
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
uint8_t phRpc_D00_DataExchangeTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                       uint16_t rpcStatus, 
                                       uint16_t lenFromCt, 
                                       uint16_t lenToCt, 
                                       uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_D00_DataExchangeTestSwCt
typedef uint8_t (*pphRpc_D00_DataExchangeTestSwCt)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_V_D00_DataExchangeTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                         uint16_t rpcStatus, 
                                         uint16_t lenFromCt, 
                                         uint16_t lenToCt, 
                                         uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_V_D00_DataExchangeTestSwCt
typedef uint8_t (*pphRpc_V_D00_DataExchangeTestSwCt)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_D00_DutInit(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint16_t rpcStatus);
/// @brief Function pointer for @ref phRpc_D00_DutInit
typedef uint8_t (*pphRpc_D00_DutInit)(uint8_t*, uint16_t*, uint16_t );
 
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
uint8_t phRpc_D00_DutGetMode(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint16_t rpcStatus, 
                             uint32_t intfMode);
/// @brief Function pointer for @ref phRpc_D00_DutGetMode
typedef uint8_t (*pphRpc_D00_DutGetMode)(uint8_t*, uint16_t*, uint16_t , uint32_t );
 
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
uint8_t phRpc_D00_DutRWShort(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint16_t rpcStatus, 
                             uint16_t rxLength, 
                             uint16_t txLength, 
                             uint8_t **preBuf, 
                             uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_D00_DutRWShort
typedef uint8_t (*pphRpc_D00_DutRWShort)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint16_t , uint8_t **, uint8_t **);
 
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
uint8_t phRpc_V_D00_DutRWShort(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                               uint16_t rpcStatus, 
                               uint16_t rxLength, 
                               uint16_t txLength, 
                               uint8_t **preBuf, 
                               uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_V_D00_DutRWShort
typedef uint8_t (*pphRpc_V_D00_DutRWShort)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint16_t , uint8_t **, uint8_t **);
 
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
uint8_t phRpc_D00_DutRWLong(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint16_t rpcStatus, 
                            uint16_t rxLength, 
                            uint16_t txLength, 
                            uint8_t **preBuf, 
                            uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_D00_DutRWLong
typedef uint8_t (*pphRpc_D00_DutRWLong)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint16_t , uint8_t **, uint8_t **);
 
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
uint8_t phRpc_V_D00_DutRWLong(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint16_t rpcStatus, 
                              uint16_t rxLength, 
                              uint16_t txLength, 
                              uint8_t **preBuf, 
                              uint8_t **xBuffer);
/// @brief Function pointer for @ref phRpc_V_D00_DutRWLong
typedef uint8_t (*pphRpc_V_D00_DutRWLong)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint16_t , uint8_t **, uint8_t **);
 
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
uint8_t phRpc_D00_DevIoCtrl(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint16_t rpcStatus, 
                            uint32_t ioctlOpt);
/// @brief Function pointer for @ref phRpc_D00_DevIoCtrl
typedef uint8_t (*pphRpc_D00_DevIoCtrl)(uint8_t*, uint16_t*, uint16_t , uint32_t );
 
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
uint8_t phRpc_D00_DevIoLineCtrl(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint16_t rpcStatus, 
                                uint32_t ioLineCtlOpt);
/// @brief Function pointer for @ref phRpc_D00_DevIoLineCtrl
typedef uint8_t (*pphRpc_D00_DevIoLineCtrl)(uint8_t*, uint16_t*, uint16_t , uint32_t );
 
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
uint8_t phRpc_D00_AdcGetValue(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint16_t rpcStatus, 
                              int32_t daqVal);
/// @brief Function pointer for @ref phRpc_D00_AdcGetValue
typedef uint8_t (*pphRpc_D00_AdcGetValue)(uint8_t*, uint16_t*, uint16_t , int32_t );
 
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
uint8_t phRpc_D00_DacSetValue(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint16_t rpcStatus);
/// @brief Function pointer for @ref phRpc_D00_DacSetValue
typedef uint8_t (*pphRpc_D00_DacSetValue)(uint8_t*, uint16_t*, uint16_t );
 
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
uint8_t phRpc_D00_DacSetWave(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint16_t rpcStatus);
/// @brief Function pointer for @ref phRpc_D00_DacSetWave
typedef uint8_t (*pphRpc_D00_DacSetWave)(uint8_t*, uint16_t*, uint16_t );
 
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
uint8_t phRpc_D00_DaqGetVRef(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint16_t rpcStatus, 
                             uint32_t vrefVal);
/// @brief Function pointer for @ref phRpc_D00_DaqGetVRef
typedef uint8_t (*pphRpc_D00_DaqGetVRef)(uint8_t*, uint16_t*, uint16_t , uint32_t );
 
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
uint8_t phRpc_D00_DaqSetVRef(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint16_t rpcStatus);
/// @brief Function pointer for @ref phRpc_D00_DaqSetVRef
typedef uint8_t (*pphRpc_D00_DaqSetVRef)(uint8_t*, uint16_t*, uint16_t );
 
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
uint8_t phRpc_D00_DaqSetGain(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint16_t rpcStatus);
/// @brief Function pointer for @ref phRpc_D00_DaqSetGain
typedef uint8_t (*pphRpc_D00_DaqSetGain)(uint8_t*, uint16_t*, uint16_t );
 
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
uint8_t phRpc_D00_DaqGetGain(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint16_t rpcStatus, 
                             int32_t gainVal);
/// @brief Function pointer for @ref phRpc_D00_DaqGetGain
typedef uint8_t (*pphRpc_D00_DaqGetGain)(uint8_t*, uint16_t*, uint16_t , int32_t );
 
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
uint8_t phRpc_D00_DacGetFrequency(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint16_t rpcStatus, 
                                  uint32_t actualF);
/// @brief Function pointer for @ref phRpc_D00_DacGetFrequency
typedef uint8_t (*pphRpc_D00_DacGetFrequency)(uint8_t*, uint16_t*, uint16_t , uint32_t );
 
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
uint8_t phRpc_D00_DeviceCommCheck(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint16_t rpcStatus, 
                                  uint16_t xLength, 
                                  uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_D00_DeviceCommCheck
typedef uint8_t (*pphRpc_D00_DeviceCommCheck)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_V_D00_DeviceCommCheck(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                    uint16_t rpcStatus, 
                                    uint16_t xLength, 
                                    uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_V_D00_DeviceCommCheck
typedef uint8_t (*pphRpc_V_D00_DeviceCommCheck)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_D00_DeviceCommCheckL(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                   uint16_t rpcStatus, 
                                   uint16_t xLength, 
                                   uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_D00_DeviceCommCheckL
typedef uint8_t (*pphRpc_D00_DeviceCommCheckL)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_V_D00_DeviceCommCheckL(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                     uint16_t rpcStatus, 
                                     uint16_t xLength, 
                                     uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_V_D00_DeviceCommCheckL
typedef uint8_t (*pphRpc_V_D00_DeviceCommCheckL)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_D00_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                     uint16_t rpcStatus, 
                                     uint16_t xLength, 
                                     uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_D00_DeviceCommCheckWTX
typedef uint8_t (*pphRpc_D00_DeviceCommCheckWTX)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_V_D00_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                       uint16_t rpcStatus, 
                                       uint16_t xLength, 
                                       uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_V_D00_DeviceCommCheckWTX
typedef uint8_t (*pphRpc_V_D00_DeviceCommCheckWTX)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_D00_D_TEST1(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint16_t rpcStatus, 
                          uint8_t a1, 
                          uint16_t a2, 
                          uint32_t a3);
/// @brief Function pointer for @ref phRpc_D00_D_TEST1
typedef uint8_t (*pphRpc_D00_D_TEST1)(uint8_t*, uint16_t*, uint16_t , uint8_t , uint16_t , uint32_t );
 
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
uint8_t phRpc_D00_D_TEST2(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint16_t rpcStatus, 
                          uint8_t a1, 
                          uint16_t b1_len, 
                          uint8_t *b1, 
                          uint32_t a3);
/// @brief Function pointer for @ref phRpc_D00_D_TEST2
typedef uint8_t (*pphRpc_D00_D_TEST2)(uint8_t*, uint16_t*, uint16_t , uint8_t , uint16_t , uint8_t *, uint32_t );
 
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
uint8_t phRpc_D00_D_TEST3(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint16_t rpcStatus);
/// @brief Function pointer for @ref phRpc_D00_D_TEST3
typedef uint8_t (*pphRpc_D00_D_TEST3)(uint8_t*, uint16_t*, uint16_t );
 
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
uint8_t phRpc_D00_D_TEST4(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint8_t a1, 
                          uint16_t b1_len, 
                          uint16_t b2_len, 
                          uint8_t *b1, 
                          uint32_t a3, 
                          uint8_t *b2, 
                          uint32_t a4);
/// @brief Function pointer for @ref phRpc_D00_D_TEST4
typedef uint8_t (*pphRpc_D00_D_TEST4)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint16_t , uint8_t *, uint32_t , uint8_t *, uint32_t );
 
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
uint8_t phRpc_V_D00_D_TEST4(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint8_t a1, 
                            uint16_t b1_len, 
                            uint16_t b2_len, 
                            uint8_t *b1, 
                            uint32_t a3, 
                            uint8_t *b2, 
                            uint32_t a4);
/// @brief Function pointer for @ref phRpc_V_D00_D_TEST4
typedef uint8_t (*pphRpc_V_D00_D_TEST4)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint16_t , uint8_t *, uint32_t , uint8_t *, uint32_t );
 
/** @} */ // grp_rpcf_ll_d2h_l
 

#endif // Guard
