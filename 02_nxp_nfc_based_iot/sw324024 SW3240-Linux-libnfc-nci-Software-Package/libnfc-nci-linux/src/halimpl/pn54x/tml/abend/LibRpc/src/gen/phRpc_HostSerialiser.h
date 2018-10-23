//
// AUTO-GENERATED: DO NOT EDIT. 
//
 

// _________________________________________________________________________________________________
 
#ifndef phRpc00HD_h
#define phRpc00HD_h

#include <stdint.h>
#include <string.h>

/** 
 * @addtogroup grp_rpcf_ll_h2d_l
 * @{ 
 */ 
 

// _________________________________________________________________________________________________
 
/// @brief Sequence Number Setter
uint8_t phRpc_H_SetSeqNum(uint8_t *rpcBuf, uint8_t seqNum);

/// @brief Set the number of bytes
void phRpc_H_SetNumBytes(uint8_t *rpcBuf, uint16_t newRpcBufLen);

/// @brief Set the CH2 ID bit
void phRpc_H_SetCh2Id(uint8_t *rpcBuf);


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
uint8_t phRpc_H00_SetCommParam(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                               uint32_t commSettings, 
                               uint16_t msTimeout);
/// @brief Function pointer for @ref phRpc_H00_SetCommParam
typedef uint8_t (*pphRpc_H00_SetCommParam)(uint8_t*, uint16_t*, uint32_t , uint16_t );
 
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
uint8_t phRpc_H00_GetDeviceInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint8_t infoType);
/// @brief Function pointer for @ref phRpc_H00_GetDeviceInfo
typedef uint8_t (*pphRpc_H00_GetDeviceInfo)(uint8_t*, uint16_t*, uint8_t );
 
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
uint8_t phRpc_H00_CtrlDeviceDiag(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                 uint8_t diagJob, 
                                 uint16_t infoBufLen, 
                                 uint8_t **infoBuf);
/// @brief Function pointer for @ref phRpc_H00_CtrlDeviceDiag
typedef uint8_t (*pphRpc_H00_CtrlDeviceDiag)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint8_t **);
 
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
uint8_t phRpc_V_H00_CtrlDeviceDiag(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                   uint8_t diagJob, 
                                   uint16_t infoBufLen, 
                                   uint8_t **infoBuf);
/// @brief Function pointer for @ref phRpc_V_H00_CtrlDeviceDiag
typedef uint8_t (*pphRpc_V_H00_CtrlDeviceDiag)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint8_t **);
 
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
uint8_t phRpc_H00_SetDeviceMode(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint8_t devMode);
/// @brief Function pointer for @ref phRpc_H00_SetDeviceMode
typedef uint8_t (*pphRpc_H00_SetDeviceMode)(uint8_t*, uint16_t*, uint8_t );
 
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
uint8_t phRpc_H00_GetDeviceCtInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint8_t infoType);
/// @brief Function pointer for @ref phRpc_H00_GetDeviceCtInfo
typedef uint8_t (*pphRpc_H00_GetDeviceCtInfo)(uint8_t*, uint16_t*, uint8_t );
 
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
uint8_t phRpc_H00_DeviceDaq(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint32_t daqAddress, 
                            uint16_t daqSetLength, 
                            uint16_t daqGetLength, 
                            uint8_t *daqBuffer);
/// @brief Function pointer for @ref phRpc_H00_DeviceDaq
typedef uint8_t (*pphRpc_H00_DeviceDaq)(uint8_t*, uint16_t*, uint32_t , uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_V_H00_DeviceDaq(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint32_t daqAddress, 
                              uint16_t daqSetLength, 
                              uint16_t daqGetLength, 
                              uint8_t *daqBuffer);
/// @brief Function pointer for @ref phRpc_V_H00_DeviceDaq
typedef uint8_t (*pphRpc_V_H00_DeviceDaq)(uint8_t*, uint16_t*, uint32_t , uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_H00_GetDevCompatInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                   uint8_t infoType);
/// @brief Function pointer for @ref phRpc_H00_GetDevCompatInfo
typedef uint8_t (*pphRpc_H00_GetDevCompatInfo)(uint8_t*, uint16_t*, uint8_t );
 
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
uint8_t phRpc_H00_WTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                      uint8_t cancelReq);
/// @brief Function pointer for @ref phRpc_H00_WTX
typedef uint8_t (*pphRpc_H00_WTX)(uint8_t*, uint16_t*, uint8_t );
 
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
uint8_t phRpc_H00_GetLastResponse(uint8_t *rpcBuf, uint16_t *rpcBufLen);
/// @brief Function pointer for @ref phRpc_H00_GetLastResponse
typedef uint8_t (*pphRpc_H00_GetLastResponse)(uint8_t*, uint16_t*);
 
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
uint8_t phRpc_H00_EE(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                     uint8_t eeFn, 
                     uint16_t eeAddr, 
                     uint16_t eeLength, 
                     uint8_t **preEEBuf, 
                     uint8_t *eeBuf);
/// @brief Function pointer for @ref phRpc_H00_EE
typedef uint8_t (*pphRpc_H00_EE)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint16_t , uint8_t **, uint8_t *);
 
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
uint8_t phRpc_V_H00_EE(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                       uint8_t eeFn, 
                       uint16_t eeAddr, 
                       uint16_t eeLength, 
                       uint8_t **preEEBuf, 
                       uint8_t *eeBuf);
/// @brief Function pointer for @ref phRpc_V_H00_EE
typedef uint8_t (*pphRpc_V_H00_EE)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint16_t , uint8_t **, uint8_t *);
 
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
uint8_t phRpc_H00_EECfg(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                        uint8_t eeCtlFn);
/// @brief Function pointer for @ref phRpc_H00_EECfg
typedef uint8_t (*pphRpc_H00_EECfg)(uint8_t*, uint16_t*, uint8_t );
 
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
uint8_t phRpc_H00_StartTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint32_t optStartParam);
/// @brief Function pointer for @ref phRpc_H00_StartTestSwCt
typedef uint8_t (*pphRpc_H00_StartTestSwCt)(uint8_t*, uint16_t*, uint32_t );
 
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
uint8_t phRpc_H00_StopTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen);
/// @brief Function pointer for @ref phRpc_H00_StopTestSwCt
typedef uint8_t (*pphRpc_H00_StopTestSwCt)(uint8_t*, uint16_t*);
 
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
uint8_t phRpc_H00_DataExchangeTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                       uint16_t lenFromCt, 
                                       uint16_t lenToCt, 
                                       uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_H00_DataExchangeTestSwCt
typedef uint8_t (*pphRpc_H00_DataExchangeTestSwCt)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_V_H00_DataExchangeTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                         uint16_t lenFromCt, 
                                         uint16_t lenToCt, 
                                         uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_V_H00_DataExchangeTestSwCt
typedef uint8_t (*pphRpc_V_H00_DataExchangeTestSwCt)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_H00_DutInit(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint8_t hiFn, 
                          uint8_t hiAddr, 
                          uint32_t hiSpeed, 
                          uint8_t hiClkPol, 
                          uint8_t hiClkPha);
/// @brief Function pointer for @ref phRpc_H00_DutInit
typedef uint8_t (*pphRpc_H00_DutInit)(uint8_t*, uint16_t*, uint8_t , uint8_t , uint32_t , uint8_t , uint8_t );
 
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
uint8_t phRpc_H00_DutGetMode(uint8_t *rpcBuf, uint16_t *rpcBufLen);
/// @brief Function pointer for @ref phRpc_H00_DutGetMode
typedef uint8_t (*pphRpc_H00_DutGetMode)(uint8_t*, uint16_t*);
 
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
uint8_t phRpc_H00_DutRWShort(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint8_t cmdRW, 
                             uint16_t rxLength, 
                             uint16_t txLength, 
                             uint8_t **preBuf, 
                             uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_H00_DutRWShort
typedef uint8_t (*pphRpc_H00_DutRWShort)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint16_t , uint8_t **, uint8_t *);
 
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
uint8_t phRpc_V_H00_DutRWShort(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                               uint8_t cmdRW, 
                               uint16_t rxLength, 
                               uint16_t txLength, 
                               uint8_t **preBuf, 
                               uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_V_H00_DutRWShort
typedef uint8_t (*pphRpc_V_H00_DutRWShort)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint16_t , uint8_t **, uint8_t *);
 
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
uint8_t phRpc_H00_DutRWLong(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint8_t cmdRW, 
                            uint16_t rxLength, 
                            uint16_t txLength, 
                            uint8_t **preBuf, 
                            uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_H00_DutRWLong
typedef uint8_t (*pphRpc_H00_DutRWLong)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint16_t , uint8_t **, uint8_t *);
 
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
uint8_t phRpc_V_H00_DutRWLong(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint8_t cmdRW, 
                              uint16_t rxLength, 
                              uint16_t txLength, 
                              uint8_t **preBuf, 
                              uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_V_H00_DutRWLong
typedef uint8_t (*pphRpc_V_H00_DutRWLong)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint16_t , uint8_t **, uint8_t *);
 
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
uint8_t phRpc_H00_DevIoCtrl(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint8_t ioctlCodeMj, 
                            uint8_t ioctlCodeMn, 
                            uint32_t ioctlOpt);
/// @brief Function pointer for @ref phRpc_H00_DevIoCtrl
typedef uint8_t (*pphRpc_H00_DevIoCtrl)(uint8_t*, uint16_t*, uint8_t , uint8_t , uint32_t );
 
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
uint8_t phRpc_H00_DevIoLineCtrl(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint8_t ioLineCtlItem, 
                                uint8_t ioLineCtlAction, 
                                uint32_t ioctlOpt);
/// @brief Function pointer for @ref phRpc_H00_DevIoLineCtrl
typedef uint8_t (*pphRpc_H00_DevIoLineCtrl)(uint8_t*, uint16_t*, uint8_t , uint8_t , uint32_t );
 
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
uint8_t phRpc_H00_AdcGetValue(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint8_t channelID);
/// @brief Function pointer for @ref phRpc_H00_AdcGetValue
typedef uint8_t (*pphRpc_H00_AdcGetValue)(uint8_t*, uint16_t*, uint8_t );
 
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
uint8_t phRpc_H00_DacSetValue(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint8_t channelID, 
                              int32_t newValue);
/// @brief Function pointer for @ref phRpc_H00_DacSetValue
typedef uint8_t (*pphRpc_H00_DacSetValue)(uint8_t*, uint16_t*, uint8_t , int32_t );
 
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
uint8_t phRpc_H00_DacSetWave(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint8_t channelID, 
                             uint8_t waveType, 
                             uint32_t waveFrequency, 
                             int32_t waveAmplitude, 
                             int32_t waveOffset);
/// @brief Function pointer for @ref phRpc_H00_DacSetWave
typedef uint8_t (*pphRpc_H00_DacSetWave)(uint8_t*, uint16_t*, uint8_t , uint8_t , uint32_t , int32_t , int32_t );
 
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
uint8_t phRpc_H00_DaqGetVRef(uint8_t *rpcBuf, uint16_t *rpcBufLen);
/// @brief Function pointer for @ref phRpc_H00_DaqGetVRef
typedef uint8_t (*pphRpc_H00_DaqGetVRef)(uint8_t*, uint16_t*);
 
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
uint8_t phRpc_H00_DaqSetVRef(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint32_t vrefVal);
/// @brief Function pointer for @ref phRpc_H00_DaqSetVRef
typedef uint8_t (*pphRpc_H00_DaqSetVRef)(uint8_t*, uint16_t*, uint32_t );
 
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
uint8_t phRpc_H00_DaqSetGain(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint8_t hwType, 
                             uint8_t channelID, 
                             int32_t gainVal);
/// @brief Function pointer for @ref phRpc_H00_DaqSetGain
typedef uint8_t (*pphRpc_H00_DaqSetGain)(uint8_t*, uint16_t*, uint8_t , uint8_t , int32_t );
 
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
uint8_t phRpc_H00_DaqGetGain(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint8_t hwType, 
                             uint8_t channelID);
/// @brief Function pointer for @ref phRpc_H00_DaqGetGain
typedef uint8_t (*pphRpc_H00_DaqGetGain)(uint8_t*, uint16_t*, uint8_t , uint8_t );
 
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
uint8_t phRpc_H00_DacGetFrequency(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint8_t channelID);
/// @brief Function pointer for @ref phRpc_H00_DacGetFrequency
typedef uint8_t (*pphRpc_H00_DacGetFrequency)(uint8_t*, uint16_t*, uint8_t );
 
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
uint8_t phRpc_H00_DeviceCommCheck(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint8_t msWait, 
                                  uint16_t xLength, 
                                  uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_H00_DeviceCommCheck
typedef uint8_t (*pphRpc_H00_DeviceCommCheck)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_V_H00_DeviceCommCheck(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                    uint8_t msWait, 
                                    uint16_t xLength, 
                                    uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_V_H00_DeviceCommCheck
typedef uint8_t (*pphRpc_V_H00_DeviceCommCheck)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_H00_DeviceCommCheckL(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                   uint8_t msWait, 
                                   uint16_t xLength, 
                                   uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_H00_DeviceCommCheckL
typedef uint8_t (*pphRpc_H00_DeviceCommCheckL)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_V_H00_DeviceCommCheckL(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                     uint8_t msWait, 
                                     uint16_t xLength, 
                                     uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_V_H00_DeviceCommCheckL
typedef uint8_t (*pphRpc_V_H00_DeviceCommCheckL)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_H00_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                     uint16_t msWait, 
                                     uint16_t xLength, 
                                     uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_H00_DeviceCommCheckWTX
typedef uint8_t (*pphRpc_H00_DeviceCommCheckWTX)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_V_H00_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                       uint16_t msWait, 
                                       uint16_t xLength, 
                                       uint8_t *xBuffer);
/// @brief Function pointer for @ref phRpc_V_H00_DeviceCommCheckWTX
typedef uint8_t (*pphRpc_V_H00_DeviceCommCheckWTX)(uint8_t*, uint16_t*, uint16_t , uint16_t , uint8_t *);
 
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
uint8_t phRpc_H00_H_TEST1(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint8_t a1, 
                          uint16_t a2, 
                          uint32_t a3);
/// @brief Function pointer for @ref phRpc_H00_H_TEST1
typedef uint8_t (*pphRpc_H00_H_TEST1)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint32_t );
 
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
uint8_t phRpc_H00_H_TEST2(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint8_t a1, 
                          uint16_t b1_len, 
                          uint8_t *b1, 
                          uint32_t a3);
/// @brief Function pointer for @ref phRpc_H00_H_TEST2
typedef uint8_t (*pphRpc_H00_H_TEST2)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint8_t *, uint32_t );
 
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
uint8_t phRpc_H00_H_TEST3(uint8_t *rpcBuf, uint16_t *rpcBufLen);
/// @brief Function pointer for @ref phRpc_H00_H_TEST3
typedef uint8_t (*pphRpc_H00_H_TEST3)(uint8_t*, uint16_t*);
 
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
uint8_t phRpc_H00_H_TEST4(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint8_t a1, 
                          uint16_t b1_len, 
                          uint16_t b2_len, 
                          uint8_t *b1, 
                          uint32_t a3, 
                          uint8_t *b2, 
                          uint32_t a4);
/// @brief Function pointer for @ref phRpc_H00_H_TEST4
typedef uint8_t (*pphRpc_H00_H_TEST4)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint16_t , uint8_t *, uint32_t , uint8_t *, uint32_t );
 
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
uint8_t phRpc_V_H00_H_TEST4(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint8_t a1, 
                            uint16_t b1_len, 
                            uint16_t b2_len, 
                            uint8_t *b1, 
                            uint32_t a3, 
                            uint8_t *b2, 
                            uint32_t a4);
/// @brief Function pointer for @ref phRpc_V_H00_H_TEST4
typedef uint8_t (*pphRpc_V_H00_H_TEST4)(uint8_t*, uint16_t*, uint8_t , uint16_t , uint16_t , uint8_t *, uint32_t , uint8_t *, uint32_t );
 
/** @} */ // grp_rpcf_ll_h2d_l
 

#endif // Guard
