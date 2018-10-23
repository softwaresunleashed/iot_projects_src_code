//
// AUTO-GENERATED: DO NOT EDIT. 
//
 

// _________________________________________________________________________________________________
 
#ifndef __APPLE__ 
# define RPC_WEAK_DEFAULT_HANDLER
#endif 
 
#include <stdint.h>
#include <string.h>
#include "phRpc_DeviceDeSerialiser.h"
#include "phRpc_Cmd.h"
#define LEN_INFO_SIZE      2 //
#define SQNR_INFO_SIZE     1 //
#define LEN_INFO_POS       0 //
#define CH2_ID_BIT_MASK    0x80 // MSB
#define CH2_ID_POS         1 // Length information high byte
#define SQNR_POS           (LEN_INFO_POS  + LEN_INFO_SIZE)  //
#define INFO_START_POS     (LEN_INFO_SIZE + SQNR_INFO_SIZE) //
#define FID_POS            INFO_START_POS //


// _________________________________________________________________________________________________
 
/// @brief Get the number of bytes
uint16_t phRpc_D_GetNumBytes(uint8_t *rpcBuf)
{
    uint16_t len;
    uint8_t lsb = rpcBuf[LEN_INFO_POS    ];
    uint8_t msb = rpcBuf[LEN_INFO_POS + 1];
    msb &= ~(CH2_ID_BIT_MASK);
    len = lsb + (uint16_t)256 * msb;
    if (0 == len) { len = PH_RPC_CMD_RESET_FRAME_LEN; }
    return len;
}

/// @brief Function ID Getter
uint16_t phRpc_D_GetFid(uint8_t *rpcBuf)
{
    uint16_t rpc_sd_fid_070972 = rpcBuf[FID_POS];
    return rpc_sd_fid_070972;
}

/// @brief Sequence Number Getter
uint8_t phRpc_D_GetSeqNum(uint8_t *rpcBuf)
{
    uint8_t sqnr = rpcBuf[SQNR_POS];
    return sqnr;
}

/// @brief Check the CH2 ID bit
uint8_t phRpc_D_IsCh2Id(uint8_t *rpcBuf)
{
    uint8_t is_ch2 = rpcBuf[CH2_ID_POS] & CH2_ID_BIT_MASK;
    return (is_ch2 > 0) ? 1u : 0;
}

/// @brief Clear the CH2 ID bit
void phRpc_D_ClearCh2Id(uint8_t *rpcBuf)
{
    rpcBuf[CH2_ID_POS] &= ~(CH2_ID_BIT_MASK);
}

/// @brief RPC Dispatcher/Entry Handler
uint8_t phRpc_D_Dispatch(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen)
{
    uint8_t rpc_sd_ret_070972 = 0;
    uint8_t rpc_sd_fid_070972 = phRpc_D_GetFid(rxBuf);
    switch (rpc_sd_fid_070972)
    {
        case phRpc_D_FID_SetCommParam:
            rpc_sd_ret_070972 = phRpc_D_Handler_SetCommParam(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_GetDeviceInfo:
            rpc_sd_ret_070972 = phRpc_D_Handler_GetDeviceInfo(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_CtrlDeviceDiag:
            rpc_sd_ret_070972 = phRpc_D_Handler_CtrlDeviceDiag(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_SetDeviceMode:
            rpc_sd_ret_070972 = phRpc_D_Handler_SetDeviceMode(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_GetDeviceCtInfo:
            rpc_sd_ret_070972 = phRpc_D_Handler_GetDeviceCtInfo(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DeviceDaq:
            rpc_sd_ret_070972 = phRpc_D_Handler_DeviceDaq(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_GetDevCompatInfo:
            rpc_sd_ret_070972 = phRpc_D_Handler_GetDevCompatInfo(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_WTX:
            rpc_sd_ret_070972 = phRpc_D_Handler_WTX(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_GetLastResponse:
            rpc_sd_ret_070972 = phRpc_D_Handler_GetLastResponse(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_EE:
            rpc_sd_ret_070972 = phRpc_D_Handler_EE(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_EECfg:
            rpc_sd_ret_070972 = phRpc_D_Handler_EECfg(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_StartTestSwCt:
            rpc_sd_ret_070972 = phRpc_D_Handler_StartTestSwCt(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_StopTestSwCt:
            rpc_sd_ret_070972 = phRpc_D_Handler_StopTestSwCt(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DataExchangeTestSwCt:
            rpc_sd_ret_070972 = phRpc_D_Handler_DataExchangeTestSwCt(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DutInit:
            rpc_sd_ret_070972 = phRpc_D_Handler_DutInit(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DutGetMode:
            rpc_sd_ret_070972 = phRpc_D_Handler_DutGetMode(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DutRWShort:
            rpc_sd_ret_070972 = phRpc_D_Handler_DutRWShort(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DutRWLong:
            rpc_sd_ret_070972 = phRpc_D_Handler_DutRWLong(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DevIoCtrl:
            rpc_sd_ret_070972 = phRpc_D_Handler_DevIoCtrl(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DevIoLineCtrl:
            rpc_sd_ret_070972 = phRpc_D_Handler_DevIoLineCtrl(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_AdcGetValue:
            rpc_sd_ret_070972 = phRpc_D_Handler_AdcGetValue(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DacSetValue:
            rpc_sd_ret_070972 = phRpc_D_Handler_DacSetValue(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DacSetWave:
            rpc_sd_ret_070972 = phRpc_D_Handler_DacSetWave(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DaqGetVRef:
            rpc_sd_ret_070972 = phRpc_D_Handler_DaqGetVRef(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DaqSetVRef:
            rpc_sd_ret_070972 = phRpc_D_Handler_DaqSetVRef(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DaqSetGain:
            rpc_sd_ret_070972 = phRpc_D_Handler_DaqSetGain(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DaqGetGain:
            rpc_sd_ret_070972 = phRpc_D_Handler_DaqGetGain(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DacGetFrequency:
            rpc_sd_ret_070972 = phRpc_D_Handler_DacGetFrequency(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DeviceCommCheck:
            rpc_sd_ret_070972 = phRpc_D_Handler_DeviceCommCheck(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DeviceCommCheckL:
            rpc_sd_ret_070972 = phRpc_D_Handler_DeviceCommCheckL(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_DeviceCommCheckWTX:
            rpc_sd_ret_070972 = phRpc_D_Handler_DeviceCommCheckWTX(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_H_TEST1:
            rpc_sd_ret_070972 = phRpc_D_Handler_H_TEST1(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_H_TEST2:
            rpc_sd_ret_070972 = phRpc_D_Handler_H_TEST2(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_H_TEST3:
            rpc_sd_ret_070972 = phRpc_D_Handler_H_TEST3(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        case phRpc_D_FID_H_TEST4:
            rpc_sd_ret_070972 = phRpc_D_Handler_H_TEST4(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
        default:
            rpc_sd_ret_070972 = phRpc_D_Handler_NotImplemented(rpcCtx, rxBuf, rxBufLen, txBuf, txBufLen);
            break;
    }
    rpc_sd_ret_070972 = phRpc_D_Handler_DispatchCompletion(rpcCtx, rpc_sd_ret_070972);
    return rpc_sd_ret_070972;
}
 
/// @brief Default Function Handler
uint8_t phRpc_D_Handler_NotImplemented(void *rpcCtx, uint8_t *rxBuf, uint16_t rxBufLen, uint8_t *txBuf, uint16_t *txBufLen)
{
    (void)rpcCtx; (void)rxBuf; (void)rxBufLen; (void)txBuf; (void)txBufLen;
    return 1u;
}

// _________________________________________________________________________________________________
 
uint8_t phRpc_H11_SetCommParam(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint32_t *commSettings, 
                               uint16_t *msTimeout)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (1 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Communication Settings
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *commSettings = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Host time-out value in [ms]
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *msTimeout = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_GetDeviceInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint8_t *infoType)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (2 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Type of information to get
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *infoType = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_CtrlDeviceDiag(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                 uint8_t *diagJob, 
                                 uint16_t *infoBufLen, 
                                 uint8_t **infoBuf)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (3 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Type of diagnostic Job
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *diagJob = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_CTRLDIAG_BUFLEN) ? rpc_sd_tmp_070972 : PH_RPC_CMD_CTRLDIAG_BUFLEN;
        *infoBufLen = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Diagnostic Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_CTRLDIAG_BUFLEN) <= (rpcBufLen)))
    {
        if (NULL != infoBuf)
        {
            *infoBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_CTRLDIAG_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H11_CtrlDeviceDiag(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                   uint8_t *diagJob, 
                                   uint16_t *infoBufLen, 
                                   uint8_t **infoBuf)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (3 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Type of diagnostic Job
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *diagJob = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_CTRLDIAG_BUFLEN) ? rpc_sd_tmp_070972 : PH_RPC_CMD_CTRLDIAG_BUFLEN;
        *infoBufLen = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Diagnostic Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + *infoBufLen) <= (rpcBufLen)))
    {
        if (NULL != infoBuf)
        {
            *infoBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (*infoBufLen < PH_RPC_CMD_CTRLDIAG_BUFLEN) ? *infoBufLen : PH_RPC_CMD_CTRLDIAG_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_SetDeviceMode(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint8_t *devMode)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (4 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Operating mode
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *devMode = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_GetDeviceCtInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint8_t *infoType)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (5 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Type of information to get
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *infoType = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DeviceDaq(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                            uint32_t *daqAddress, 
                            uint16_t *daqSetLength, 
                            uint16_t *daqGetLength, 
                            uint8_t **daqBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (12 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // DAQ start address
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *daqAddress = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ SET length in bytes
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_BUFSIZE;
        *daqSetLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ GET length in bytes
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_BUFSIZE;
        *daqGetLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EXT_DEV_BUFSIZE) <= (rpcBufLen)))
    {
        if (NULL != daqBuffer)
        {
            *daqBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H11_DeviceDaq(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint32_t *daqAddress, 
                              uint16_t *daqSetLength, 
                              uint16_t *daqGetLength, 
                              uint8_t **daqBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (12 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // DAQ start address
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *daqAddress = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ SET length in bytes
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_BUFSIZE;
        *daqSetLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ GET length in bytes
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_BUFSIZE;
        *daqGetLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + *daqSetLength) <= (rpcBufLen)))
    {
        if (NULL != daqBuffer)
        {
            *daqBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (*daqSetLength < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? *daqSetLength : PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_GetDevCompatInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                   uint8_t *infoType)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (13 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Type of information to get
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *infoType = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_WTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                      uint8_t *cancelReq)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (14 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Cancel Request
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *cancelReq = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_GetLastResponse(uint8_t *rpcBuf, uint16_t rpcBufLen)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (15 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_EE(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                     uint8_t *eeFn, 
                     uint16_t *eeAddr, 
                     uint16_t *eeLength, 
                     uint8_t **preEEBuf, 
                     uint8_t **eeBuf)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (16 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // EEPROM Function
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *eeFn = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // EEPROM Address
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *eeAddr = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EE_BUFLEN) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EE_BUFLEN;
        *eeLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Prepend Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EE_PREPEND) <= (rpcBufLen)))
    {
        if (NULL != preEEBuf)
        {
            *preEEBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EE_PREPEND;
    } else { rpc_sd_ret_070972 = 1u; }

    // EE Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EE_BUFLEN) <= (rpcBufLen)))
    {
        if (NULL != eeBuf)
        {
            *eeBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EE_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H11_EE(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                       uint8_t *eeFn, 
                       uint16_t *eeAddr, 
                       uint16_t *eeLength, 
                       uint8_t **preEEBuf, 
                       uint8_t **eeBuf)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (16 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // EEPROM Function
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *eeFn = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // EEPROM Address
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *eeAddr = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EE_BUFLEN) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EE_BUFLEN;
        *eeLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Prepend Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EE_PREPEND) <= (rpcBufLen)))
    {
        if (NULL != preEEBuf)
        {
            *preEEBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC enabled but not effective due to Buffer with fixed size. Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EE_PREPEND;
    } else { rpc_sd_ret_070972 = 1u; }

    // EE Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + *eeLength) <= (rpcBufLen)))
    {
        if (NULL != eeBuf)
        {
            *eeBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (*eeLength < PH_RPC_CMD_EE_BUFLEN) ? *eeLength : PH_RPC_CMD_EE_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_EECfg(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                        uint8_t *eeCtlFn)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (17 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // EE Configuration Control Function
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *eeCtlFn = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_StartTestSwCt(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint32_t *optStartParam)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (18 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Optional Parameter
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *optStartParam = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_StopTestSwCt(uint8_t *rpcBuf, uint16_t rpcBufLen)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (19 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DataExchangeTestSwCt(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                       uint16_t *lenFromCt, 
                                       uint16_t *lenToCt, 
                                       uint8_t **xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (20 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Maximum Receive Length, maximum number of bytes to be received from secondary firmware
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_BUFSIZE;
        *lenFromCt = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length, number of bytes to be sent to the secondary firmware
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_BUFSIZE;
        *lenToCt = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EXT_DEV_BUFSIZE) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H11_DataExchangeTestSwCt(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                         uint16_t *lenFromCt, 
                                         uint16_t *lenToCt, 
                                         uint8_t **xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (20 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Maximum Receive Length, maximum number of bytes to be received from secondary firmware
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_BUFSIZE;
        *lenFromCt = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length, number of bytes to be sent to the secondary firmware
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_BUFSIZE;
        *lenToCt = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + *lenToCt) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (*lenToCt < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? *lenToCt : PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DutInit(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                          uint8_t *hiFn, 
                          uint8_t *hiAddr, 
                          uint32_t *hiSpeed, 
                          uint8_t *hiClkPol, 
                          uint8_t *hiClkPha)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (64 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Function/Interface to activate
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *hiFn = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Interface address (only valid for addressable interface)
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *hiAddr = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Interface speed
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *hiSpeed = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // SPI Clock Polarity
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *hiClkPol = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // SPI Clock Phase
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *hiClkPha = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DutGetMode(uint8_t *rpcBuf, uint16_t rpcBufLen)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (65 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DutRWShort(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint8_t *cmdRW, 
                             uint16_t *rxLength, 
                             uint16_t *txLength, 
                             uint8_t **preBuf, 
                             uint8_t **xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (66 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Read/Write
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *cmdRW = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Receive Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT;
        *rxLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT;
        *txLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Prepend Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_PREPEND_LEN) <= (rpcBufLen)))
    {
        if (NULL != preBuf)
        {
            *preBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_PREPEND_LEN;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H11_DutRWShort(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint8_t *cmdRW, 
                               uint16_t *rxLength, 
                               uint16_t *txLength, 
                               uint8_t **preBuf, 
                               uint8_t **xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (66 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Read/Write
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *cmdRW = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Receive Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT;
        *rxLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT;
        *txLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Prepend Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_PREPEND_LEN) <= (rpcBufLen)))
    {
        if (NULL != preBuf)
        {
            *preBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC enabled but not effective due to Buffer with fixed size. Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_PREPEND_LEN;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + *txLength) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (*txLength < PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT) ? *txLength : PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DutRWLong(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                            uint8_t *cmdRW, 
                            uint16_t *rxLength, 
                            uint16_t *txLength, 
                            uint8_t **preBuf, 
                            uint8_t **xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (67 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Read/Write
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *cmdRW = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Receive Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_BUFSIZE;
        *rxLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_BUFSIZE;
        *txLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Prepend Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_PREPEND_LEN) <= (rpcBufLen)))
    {
        if (NULL != preBuf)
        {
            *preBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_PREPEND_LEN;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EXT_DEV_BUFSIZE) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H11_DutRWLong(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint8_t *cmdRW, 
                              uint16_t *rxLength, 
                              uint16_t *txLength, 
                              uint8_t **preBuf, 
                              uint8_t **xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (67 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Read/Write
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *cmdRW = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Receive Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_BUFSIZE;
        *rxLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_CMD_EXT_DEV_BUFSIZE;
        *txLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Prepend Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_PREPEND_LEN) <= (rpcBufLen)))
    {
        if (NULL != preBuf)
        {
            *preBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC enabled but not effective due to Buffer with fixed size. Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_PREPEND_LEN;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + *txLength) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (*txLength < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? *txLength : PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DevIoCtrl(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                            uint8_t *ioctlCodeMj, 
                            uint8_t *ioctlCodeMn, 
                            uint32_t *ioctlOpt)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (68 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Major Code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *ioctlCodeMj = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Minor Code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *ioctlCodeMn = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Optional Parameter
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *ioctlOpt = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DevIoLineCtrl(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint8_t *ioLineCtlItem, 
                                uint8_t *ioLineCtlAction, 
                                uint32_t *ioctlOpt)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (69 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // What to control
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *ioLineCtlItem = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Control Action
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *ioLineCtlAction = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Optional Parameter
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *ioctlOpt = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_AdcGetValue(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint8_t *channelID)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (70 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Channel to query
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *channelID = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DacSetValue(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint8_t *channelID, 
                              int32_t *newValue)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (71 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Channel to control
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *channelID = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // New value to set
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *newValue = (int32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DacSetWave(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint8_t *channelID, 
                             uint8_t *waveType, 
                             uint32_t *waveFrequency, 
                             int32_t *waveAmplitude, 
                             int32_t *waveOffset)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (72 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Channel to control
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *channelID = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Wave Type
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *waveType = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Wave Frequency
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *waveFrequency = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Wave Amplitude
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *waveAmplitude = (int32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Wave Offset
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *waveOffset = (int32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DaqGetVRef(uint8_t *rpcBuf, uint16_t rpcBufLen)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (73 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DaqSetVRef(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint32_t *vrefVal)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (74 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // New Reference Voltage Value
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *vrefVal = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DaqSetGain(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint8_t *hwType, 
                             uint8_t *channelID, 
                             int32_t *gainVal)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (75 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // ADC or DAC
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *hwType = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Channel to control
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *channelID = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // New Gain Value
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *gainVal = (int32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DaqGetGain(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                             uint8_t *hwType, 
                             uint8_t *channelID)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (76 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // ADC or DAC
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *hwType = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Channel to query
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *channelID = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DacGetFrequency(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint8_t *channelID)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (77 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Channel to query
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *channelID = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DeviceCommCheck(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint8_t *msWait, 
                                  uint16_t *xLength, 
                                  uint8_t **xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (241 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Waiting time in [ms]
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *msWait = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_COMMCHECK_BUFLEN) ? rpc_sd_tmp_070972 : PH_RPC_CMD_COMMCHECK_BUFLEN;
        *xLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_COMMCHECK_BUFLEN) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_COMMCHECK_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H11_DeviceCommCheck(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                    uint8_t *msWait, 
                                    uint16_t *xLength, 
                                    uint8_t **xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (241 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Waiting time in [ms]
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *msWait = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_COMMCHECK_BUFLEN) ? rpc_sd_tmp_070972 : PH_RPC_CMD_COMMCHECK_BUFLEN;
        *xLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + *xLength) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (*xLength < PH_RPC_CMD_COMMCHECK_BUFLEN) ? *xLength : PH_RPC_CMD_COMMCHECK_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DeviceCommCheckL(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                   uint8_t *msWait, 
                                   uint16_t *xLength, 
                                   uint8_t **xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (242 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Waiting time in [ms]
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *msWait = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_COMMCHECK_L_BUFLEN) ? rpc_sd_tmp_070972 : PH_RPC_CMD_COMMCHECK_L_BUFLEN;
        *xLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_COMMCHECK_L_BUFLEN) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_COMMCHECK_L_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H11_DeviceCommCheckL(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                     uint8_t *msWait, 
                                     uint16_t *xLength, 
                                     uint8_t **xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (242 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Waiting time in [ms]
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *msWait = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_COMMCHECK_L_BUFLEN) ? rpc_sd_tmp_070972 : PH_RPC_CMD_COMMCHECK_L_BUFLEN;
        *xLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + *xLength) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (*xLength < PH_RPC_CMD_COMMCHECK_L_BUFLEN) ? *xLength : PH_RPC_CMD_COMMCHECK_L_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                     uint16_t *msWait, 
                                     uint16_t *xLength, 
                                     uint8_t **xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (243 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Waiting time in [ms]
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *msWait = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_COMMCHECK_L_BUFLEN) ? rpc_sd_tmp_070972 : PH_RPC_CMD_COMMCHECK_L_BUFLEN;
        *xLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_COMMCHECK_L_BUFLEN) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_COMMCHECK_L_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H11_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                       uint16_t *msWait, 
                                       uint16_t *xLength, 
                                       uint8_t **xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (243 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Waiting time in [ms]
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *msWait = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_CMD_COMMCHECK_L_BUFLEN) ? rpc_sd_tmp_070972 : PH_RPC_CMD_COMMCHECK_L_BUFLEN;
        *xLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + *xLength) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (*xLength < PH_RPC_CMD_COMMCHECK_L_BUFLEN) ? *xLength : PH_RPC_CMD_COMMCHECK_L_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_H_TEST1(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                          uint8_t *a1, 
                          uint16_t *a2, 
                          uint32_t *a3)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (255 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Test Argument 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *a1 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 2
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *a2 = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 3
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *a3 = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_H_TEST2(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                          uint8_t *a1, 
                          uint16_t *b1_len, 
                          uint8_t **b1, 
                          uint32_t *a3)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (254 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Test Argument 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *a1 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < 2) ? rpc_sd_tmp_070972 : 2;
        *b1_len = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        if (NULL != b1)
        {
            *b1 = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 3
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *a3 = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_H_TEST3(uint8_t *rpcBuf, uint16_t rpcBufLen)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (253 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H11_H_TEST4(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                          uint8_t *a1, 
                          uint16_t *b1_len, 
                          uint16_t *b2_len, 
                          uint8_t **b1, 
                          uint32_t *a3, 
                          uint8_t **b2, 
                          uint32_t *a4)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (252 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Test Argument 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *a1 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length of buffer 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < 16) ? rpc_sd_tmp_070972 : 16;
        *b1_len = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length of buffer 2
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < 16) ? rpc_sd_tmp_070972 : 16;
        *b2_len = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 16) <= (rpcBufLen)))
    {
        if (NULL != b1)
        {
            *b1 = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += 16;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 3
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *a3 = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer 2
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 16) <= (rpcBufLen)))
    {
        if (NULL != b2)
        {
            *b2 = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += 16;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 4
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *a4 = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H11_H_TEST4(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                            uint8_t *a1, 
                            uint16_t *b1_len, 
                            uint16_t *b2_len, 
                            uint8_t **b1, 
                            uint32_t *a3, 
                            uint8_t **b2, 
                            uint32_t *a4)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 0;
 
    // De-Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_fnc_070972 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Check Function Code
    if (252 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Test Argument 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *a1 = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length of buffer 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < 16) ? rpc_sd_tmp_070972 : 16;
        *b1_len = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length of buffer 2
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < 16) ? rpc_sd_tmp_070972 : 16;
        *b2_len = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + *b1_len) <= (rpcBufLen)))
    {
        if (NULL != b1)
        {
            *b1 = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (*b1_len < 16) ? *b1_len : 16;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 3
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *a3 = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer 2
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + *b2_len) <= (rpcBufLen)))
    {
        if (NULL != b2)
        {
            *b2 = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (*b2_len < 16) ? *b2_len : 16;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 4
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *a4 = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
