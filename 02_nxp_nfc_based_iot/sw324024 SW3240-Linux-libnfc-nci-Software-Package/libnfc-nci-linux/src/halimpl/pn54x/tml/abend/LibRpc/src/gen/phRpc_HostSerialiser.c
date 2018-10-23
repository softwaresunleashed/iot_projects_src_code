//
// AUTO-GENERATED: DO NOT EDIT. 
//
 

// _________________________________________________________________________________________________
 
#ifndef __APPLE__ 
# define RPC_WEAK_DEFAULT_HANDLER
#endif 
 
#include <stdint.h>
#include <string.h>
#include "phRpc_HostSerialiser.h"
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
 
/// @brief Sequence Number Setter
uint8_t phRpc_H_SetSeqNum(uint8_t *rpcBuf, uint8_t seqNum)
{
    rpcBuf[SQNR_POS] = seqNum;
    return 0;
}

/// @brief Set the number of bytes
void phRpc_H_SetNumBytes(uint8_t *rpcBuf, uint16_t newRpcBufLen)
{
    rpcBuf[LEN_INFO_POS    ] = (uint8_t)newRpcBufLen;
    rpcBuf[LEN_INFO_POS + 1] = (uint8_t)(newRpcBufLen >> 8);
}

/// @brief Set the CH2 ID bit
void phRpc_H_SetCh2Id(uint8_t *rpcBuf)
{
    rpcBuf[CH2_ID_POS] |= CH2_ID_BIT_MASK;
}


// _________________________________________________________________________________________________
 
uint8_t phRpc_H00_SetCommParam(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                               uint32_t commSettings, 
                               uint16_t msTimeout)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 1;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Communication Settings
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(commSettings      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(commSettings >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(commSettings >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(commSettings >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Host time-out value in [ms]
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(msTimeout      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(msTimeout >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_GetDeviceInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint8_t infoType)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 2;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Type of information to get
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoType      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_CtrlDeviceDiag(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                 uint8_t diagJob, 
                                 uint16_t infoBufLen, 
                                 uint8_t **infoBuf)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 3;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Type of diagnostic Job
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(diagJob      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoBufLen      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(infoBufLen >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Diagnostic Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_CTRLDIAG_BUFLEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != infoBuf)
        {
            *infoBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_CTRLDIAG_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H00_CtrlDeviceDiag(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                   uint8_t diagJob, 
                                   uint16_t infoBufLen, 
                                   uint8_t **infoBuf)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 3;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Type of diagnostic Job
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(diagJob      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoBufLen      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(infoBufLen >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Diagnostic Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + infoBufLen) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != infoBuf)
        {
            *infoBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (infoBufLen < PH_RPC_CMD_CTRLDIAG_BUFLEN) ? infoBufLen : PH_RPC_CMD_CTRLDIAG_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_SetDeviceMode(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint8_t devMode)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 4;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Operating mode
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(devMode      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_GetDeviceCtInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint8_t infoType)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 5;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Type of information to get
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoType      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DeviceDaq(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint32_t daqAddress, 
                            uint16_t daqSetLength, 
                            uint16_t daqGetLength, 
                            uint8_t *daqBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 12;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ start address
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(daqAddress      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(daqAddress >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(daqAddress >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(daqAddress >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ SET length in bytes
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(daqSetLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(daqSetLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ GET length in bytes
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(daqGetLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(daqGetLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EXT_DEV_BUFSIZE) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != daqBuffer)
        {
            rpc_sd_tmp_len_070972 = (daqSetLength < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? daqSetLength : PH_RPC_CMD_EXT_DEV_BUFSIZE;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), daqBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H00_DeviceDaq(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint32_t daqAddress, 
                              uint16_t daqSetLength, 
                              uint16_t daqGetLength, 
                              uint8_t *daqBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 12;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ start address
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(daqAddress      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(daqAddress >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(daqAddress >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(daqAddress >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ SET length in bytes
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(daqSetLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(daqSetLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ GET length in bytes
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(daqGetLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(daqGetLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + daqSetLength) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != daqBuffer)
        {
            rpc_sd_tmp_len_070972 = (daqSetLength < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? daqSetLength : PH_RPC_CMD_EXT_DEV_BUFSIZE;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), daqBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (daqSetLength < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? daqSetLength : PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_GetDevCompatInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                   uint8_t infoType)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 13;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Type of information to get
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoType      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_WTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                      uint8_t cancelReq)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 14;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Cancel Request
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(cancelReq      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_GetLastResponse(uint8_t *rpcBuf, uint16_t *rpcBufLen)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 15;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_EE(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                     uint8_t eeFn, 
                     uint16_t eeAddr, 
                     uint16_t eeLength, 
                     uint8_t **preEEBuf, 
                     uint8_t *eeBuf)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 16;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // EEPROM Function
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(eeFn      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // EEPROM Address
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(eeAddr      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(eeAddr >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(eeLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(eeLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Prepend Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EE_PREPEND) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != preEEBuf)
        {
            *preEEBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EE_PREPEND;
    } else { rpc_sd_ret_070972 = 1u; }

    // EE Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EE_BUFLEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != eeBuf)
        {
            rpc_sd_tmp_len_070972 = (eeLength < PH_RPC_CMD_EE_BUFLEN) ? eeLength : PH_RPC_CMD_EE_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), eeBuf, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EE_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H00_EE(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                       uint8_t eeFn, 
                       uint16_t eeAddr, 
                       uint16_t eeLength, 
                       uint8_t **preEEBuf, 
                       uint8_t *eeBuf)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 16;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // EEPROM Function
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(eeFn      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // EEPROM Address
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(eeAddr      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(eeAddr >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(eeLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(eeLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Prepend Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EE_PREPEND) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != preEEBuf)
        {
            *preEEBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Compact RPC enabled but not effective due to Buffer with fixed size. Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EE_PREPEND;
    } else { rpc_sd_ret_070972 = 1u; }

    // EE Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + eeLength) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != eeBuf)
        {
            rpc_sd_tmp_len_070972 = (eeLength < PH_RPC_CMD_EE_BUFLEN) ? eeLength : PH_RPC_CMD_EE_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), eeBuf, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (eeLength < PH_RPC_CMD_EE_BUFLEN) ? eeLength : PH_RPC_CMD_EE_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_EECfg(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                        uint8_t eeCtlFn)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 17;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // EE Configuration Control Function
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(eeCtlFn      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_StartTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint32_t optStartParam)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 18;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Optional Parameter
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(optStartParam      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(optStartParam >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(optStartParam >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(optStartParam >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_StopTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 19;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DataExchangeTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                       uint16_t lenFromCt, 
                                       uint16_t lenToCt, 
                                       uint8_t *xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 20;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Maximum Receive Length, maximum number of bytes to be received from secondary firmware
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(lenFromCt      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(lenFromCt >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length, number of bytes to be sent to the secondary firmware
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(lenToCt      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(lenToCt >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EXT_DEV_BUFSIZE) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != xBuffer)
        {
            rpc_sd_tmp_len_070972 = (lenToCt < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? lenToCt : PH_RPC_CMD_EXT_DEV_BUFSIZE;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H00_DataExchangeTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                         uint16_t lenFromCt, 
                                         uint16_t lenToCt, 
                                         uint8_t *xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 20;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Maximum Receive Length, maximum number of bytes to be received from secondary firmware
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(lenFromCt      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(lenFromCt >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length, number of bytes to be sent to the secondary firmware
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(lenToCt      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(lenToCt >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + lenToCt) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != xBuffer)
        {
            rpc_sd_tmp_len_070972 = (lenToCt < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? lenToCt : PH_RPC_CMD_EXT_DEV_BUFSIZE;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (lenToCt < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? lenToCt : PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DutInit(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint8_t hiFn, 
                          uint8_t hiAddr, 
                          uint32_t hiSpeed, 
                          uint8_t hiClkPol, 
                          uint8_t hiClkPha)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 64;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Function/Interface to activate
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(hiFn      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Interface address (only valid for addressable interface)
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(hiAddr      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Interface speed
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(hiSpeed      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(hiSpeed >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(hiSpeed >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(hiSpeed >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // SPI Clock Polarity
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(hiClkPol      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // SPI Clock Phase
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(hiClkPha      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DutGetMode(uint8_t *rpcBuf, uint16_t *rpcBufLen)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 65;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DutRWShort(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint8_t cmdRW, 
                             uint16_t rxLength, 
                             uint16_t txLength, 
                             uint8_t **preBuf, 
                             uint8_t *xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 66;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Read/Write
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(cmdRW      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Receive Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rxLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rxLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(txLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(txLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Prepend Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_PREPEND_LEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != preBuf)
        {
            *preBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_PREPEND_LEN;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != xBuffer)
        {
            rpc_sd_tmp_len_070972 = (txLength < PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT) ? txLength : PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H00_DutRWShort(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                               uint8_t cmdRW, 
                               uint16_t rxLength, 
                               uint16_t txLength, 
                               uint8_t **preBuf, 
                               uint8_t *xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 66;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Read/Write
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(cmdRW      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Receive Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rxLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rxLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(txLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(txLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Prepend Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_PREPEND_LEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != preBuf)
        {
            *preBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Compact RPC enabled but not effective due to Buffer with fixed size. Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_PREPEND_LEN;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + txLength) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != xBuffer)
        {
            rpc_sd_tmp_len_070972 = (txLength < PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT) ? txLength : PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (txLength < PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT) ? txLength : PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DutRWLong(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint8_t cmdRW, 
                            uint16_t rxLength, 
                            uint16_t txLength, 
                            uint8_t **preBuf, 
                            uint8_t *xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 67;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Read/Write
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(cmdRW      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Receive Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rxLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rxLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(txLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(txLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Prepend Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_PREPEND_LEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != preBuf)
        {
            *preBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_PREPEND_LEN;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EXT_DEV_BUFSIZE) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != xBuffer)
        {
            rpc_sd_tmp_len_070972 = (txLength < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? txLength : PH_RPC_CMD_EXT_DEV_BUFSIZE;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H00_DutRWLong(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint8_t cmdRW, 
                              uint16_t rxLength, 
                              uint16_t txLength, 
                              uint8_t **preBuf, 
                              uint8_t *xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 67;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Read/Write
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(cmdRW      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Receive Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rxLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rxLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(txLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(txLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Prepend Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_PREPEND_LEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != preBuf)
        {
            *preBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Compact RPC enabled but not effective due to Buffer with fixed size. Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_PREPEND_LEN;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + txLength) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != xBuffer)
        {
            rpc_sd_tmp_len_070972 = (txLength < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? txLength : PH_RPC_CMD_EXT_DEV_BUFSIZE;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (txLength < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? txLength : PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DevIoCtrl(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint8_t ioctlCodeMj, 
                            uint8_t ioctlCodeMn, 
                            uint32_t ioctlOpt)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 68;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Major Code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(ioctlCodeMj      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Minor Code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(ioctlCodeMn      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Optional Parameter
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(ioctlOpt      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(ioctlOpt >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(ioctlOpt >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(ioctlOpt >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DevIoLineCtrl(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint8_t ioLineCtlItem, 
                                uint8_t ioLineCtlAction, 
                                uint32_t ioctlOpt)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 69;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // What to control
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(ioLineCtlItem      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Control Action
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(ioLineCtlAction      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Optional Parameter
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(ioctlOpt      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(ioctlOpt >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(ioctlOpt >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(ioctlOpt >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_AdcGetValue(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint8_t channelID)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 70;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Channel to query
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(channelID      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DacSetValue(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint8_t channelID, 
                              int32_t newValue)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 71;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Channel to control
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(channelID      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // New value to set
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(newValue      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(newValue >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(newValue >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(newValue >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DacSetWave(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint8_t channelID, 
                             uint8_t waveType, 
                             uint32_t waveFrequency, 
                             int32_t waveAmplitude, 
                             int32_t waveOffset)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 72;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Channel to control
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(channelID      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Wave Type
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(waveType      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Wave Frequency
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(waveFrequency      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(waveFrequency >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(waveFrequency >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(waveFrequency >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Wave Amplitude
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(waveAmplitude      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(waveAmplitude >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(waveAmplitude >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(waveAmplitude >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Wave Offset
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(waveOffset      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(waveOffset >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(waveOffset >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(waveOffset >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DaqGetVRef(uint8_t *rpcBuf, uint16_t *rpcBufLen)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 73;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DaqSetVRef(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint32_t vrefVal)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 74;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // New Reference Voltage Value
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(vrefVal      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(vrefVal >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(vrefVal >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(vrefVal >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DaqSetGain(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint8_t hwType, 
                             uint8_t channelID, 
                             int32_t gainVal)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 75;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // ADC or DAC
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(hwType      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Channel to control
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(channelID      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // New Gain Value
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(gainVal      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(gainVal >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(gainVal >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(gainVal >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DaqGetGain(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint8_t hwType, 
                             uint8_t channelID)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 76;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // ADC or DAC
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(hwType      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Channel to query
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(channelID      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DacGetFrequency(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint8_t channelID)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 77;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Channel to query
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(channelID      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DeviceCommCheck(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint8_t msWait, 
                                  uint16_t xLength, 
                                  uint8_t *xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 241;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Waiting time in [ms]
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(msWait      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(xLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(xLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_COMMCHECK_BUFLEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != xBuffer)
        {
            rpc_sd_tmp_len_070972 = (xLength < PH_RPC_CMD_COMMCHECK_BUFLEN) ? xLength : PH_RPC_CMD_COMMCHECK_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_COMMCHECK_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H00_DeviceCommCheck(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                    uint8_t msWait, 
                                    uint16_t xLength, 
                                    uint8_t *xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 241;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Waiting time in [ms]
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(msWait      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(xLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(xLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + xLength) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != xBuffer)
        {
            rpc_sd_tmp_len_070972 = (xLength < PH_RPC_CMD_COMMCHECK_BUFLEN) ? xLength : PH_RPC_CMD_COMMCHECK_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (xLength < PH_RPC_CMD_COMMCHECK_BUFLEN) ? xLength : PH_RPC_CMD_COMMCHECK_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DeviceCommCheckL(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                   uint8_t msWait, 
                                   uint16_t xLength, 
                                   uint8_t *xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 242;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Waiting time in [ms]
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(msWait      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(xLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(xLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_COMMCHECK_L_BUFLEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != xBuffer)
        {
            rpc_sd_tmp_len_070972 = (xLength < PH_RPC_CMD_COMMCHECK_L_BUFLEN) ? xLength : PH_RPC_CMD_COMMCHECK_L_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_COMMCHECK_L_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H00_DeviceCommCheckL(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                     uint8_t msWait, 
                                     uint16_t xLength, 
                                     uint8_t *xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 242;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Waiting time in [ms]
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(msWait      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(xLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(xLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + xLength) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != xBuffer)
        {
            rpc_sd_tmp_len_070972 = (xLength < PH_RPC_CMD_COMMCHECK_L_BUFLEN) ? xLength : PH_RPC_CMD_COMMCHECK_L_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (xLength < PH_RPC_CMD_COMMCHECK_L_BUFLEN) ? xLength : PH_RPC_CMD_COMMCHECK_L_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                     uint16_t msWait, 
                                     uint16_t xLength, 
                                     uint8_t *xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 243;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Waiting time in [ms]
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(msWait      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(msWait >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(xLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(xLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_COMMCHECK_L_BUFLEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != xBuffer)
        {
            rpc_sd_tmp_len_070972 = (xLength < PH_RPC_CMD_COMMCHECK_L_BUFLEN) ? xLength : PH_RPC_CMD_COMMCHECK_L_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_COMMCHECK_L_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H00_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                       uint16_t msWait, 
                                       uint16_t xLength, 
                                       uint8_t *xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 243;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Waiting time in [ms]
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(msWait      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(msWait >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(xLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(xLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + xLength) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != xBuffer)
        {
            rpc_sd_tmp_len_070972 = (xLength < PH_RPC_CMD_COMMCHECK_L_BUFLEN) ? xLength : PH_RPC_CMD_COMMCHECK_L_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (xLength < PH_RPC_CMD_COMMCHECK_L_BUFLEN) ? xLength : PH_RPC_CMD_COMMCHECK_L_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_H_TEST1(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint8_t a1, 
                          uint16_t a2, 
                          uint32_t a3)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 255;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(a1      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 2
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(a2      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(a2 >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 3
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(a3      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(a3 >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(a3 >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(a3 >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_H_TEST2(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint8_t a1, 
                          uint16_t b1_len, 
                          uint8_t *b1, 
                          uint32_t a3)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 254;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(a1      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(b1_len      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(b1_len >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != b1)
        {
            rpc_sd_tmp_len_070972 = (b1_len < 2) ? b1_len : 2;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), b1, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 3
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(a3      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(a3 >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(a3 >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(a3 >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_H_TEST3(uint8_t *rpcBuf, uint16_t *rpcBufLen)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 253;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_H00_H_TEST4(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint8_t a1, 
                          uint16_t b1_len, 
                          uint16_t b2_len, 
                          uint8_t *b1, 
                          uint32_t a3, 
                          uint8_t *b2, 
                          uint32_t a4)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 252;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(a1      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length of buffer 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(b1_len      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(b1_len >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length of buffer 2
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(b2_len      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(b2_len >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 16) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != b1)
        {
            rpc_sd_tmp_len_070972 = (b1_len < 16) ? b1_len : 16;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), b1, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += 16;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 3
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(a3      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(a3 >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(a3 >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(a3 >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer 2
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 16) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != b2)
        {
            rpc_sd_tmp_len_070972 = (b2_len < 16) ? b2_len : 16;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), b2, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += 16;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 4
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(a4      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(a4 >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(a4 >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(a4 >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_H00_H_TEST4(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint8_t a1, 
                            uint16_t b1_len, 
                            uint16_t b2_len, 
                            uint8_t *b1, 
                            uint32_t a3, 
                            uint8_t *b2, 
                            uint32_t a4)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 252;
 
    // Serialise: 
    // Function code
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpc_sd_fnc_070972      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(a1      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length of buffer 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(b1_len      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(b1_len >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length of buffer 2
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(b2_len      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(b2_len >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer 1
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + b1_len) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != b1)
        {
            rpc_sd_tmp_len_070972 = (b1_len < 16) ? b1_len : 16;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), b1, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (b1_len < 16) ? b1_len : 16;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 3
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(a3      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(a3 >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(a3 >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(a3 >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer 2
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + b2_len) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != b2)
        {
            rpc_sd_tmp_len_070972 = (b2_len < 16) ? b2_len : 16;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), b2, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (b2_len < 16) ? b2_len : 16;
    } else { rpc_sd_ret_070972 = 1u; }

    // Test Argument 4
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(a4      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(a4 >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(a4 >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(a4 >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
