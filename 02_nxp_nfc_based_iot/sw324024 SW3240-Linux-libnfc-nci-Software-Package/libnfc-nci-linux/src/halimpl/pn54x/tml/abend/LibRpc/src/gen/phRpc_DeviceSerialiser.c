//
// AUTO-GENERATED: DO NOT EDIT. 
//
 

// _________________________________________________________________________________________________
 
#ifndef __APPLE__ 
# define RPC_WEAK_DEFAULT_HANDLER
#endif 
 
#include <stdint.h>
#include <string.h>
#include "phRpc_DeviceSerialiser.h"
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
uint8_t phRpc_D_SetSeqNum(uint8_t *rpcBuf, uint8_t seqNum)
{
    rpcBuf[SQNR_POS] = seqNum;
    return 0;
}

/// @brief Set the number of bytes
void phRpc_D_SetNumBytes(uint8_t *rpcBuf, uint16_t newRpcBufLen)
{
    rpcBuf[LEN_INFO_POS    ] = (uint8_t)newRpcBufLen;
    rpcBuf[LEN_INFO_POS + 1] = (uint8_t)(newRpcBufLen >> 8);
}

/// @brief Set the CH2 ID bit
void phRpc_D_SetCh2Id(uint8_t *rpcBuf)
{
    rpcBuf[CH2_ID_POS] |= CH2_ID_BIT_MASK;
}


// _________________________________________________________________________________________________
 
uint8_t phRpc_D00_SetCommParam(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                               uint16_t rpcStatus)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_GetDeviceInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint16_t rpcStatus, 
                                uint32_t infoNum, 
                                uint16_t infoBufLen, 
                                uint8_t *infoBuf)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Numerical information
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoNum      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(infoNum >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(infoNum >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(infoNum >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoBufLen      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(infoBufLen >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_DEVINFO_BUFLEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != infoBuf)
        {
            rpc_sd_tmp_len_070972 = (infoBufLen < PH_RPC_CMD_DEVINFO_BUFLEN) ? infoBufLen : PH_RPC_CMD_DEVINFO_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), infoBuf, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_DEVINFO_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_D00_GetDeviceInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint16_t rpcStatus, 
                                  uint32_t infoNum, 
                                  uint16_t infoBufLen, 
                                  uint8_t *infoBuf)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Numerical information
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoNum      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(infoNum >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(infoNum >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(infoNum >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoBufLen      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(infoBufLen >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + infoBufLen) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != infoBuf)
        {
            rpc_sd_tmp_len_070972 = (infoBufLen < PH_RPC_CMD_DEVINFO_BUFLEN) ? infoBufLen : PH_RPC_CMD_DEVINFO_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), infoBuf, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (infoBufLen < PH_RPC_CMD_DEVINFO_BUFLEN) ? infoBufLen : PH_RPC_CMD_DEVINFO_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_CtrlDeviceDiag(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                 uint16_t rpcStatus, 
                                 uint16_t infoBufLen, 
                                 uint8_t *infoBuf)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer
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
        // Buffer will be copied:
        if (NULL != infoBuf)
        {
            rpc_sd_tmp_len_070972 = (infoBufLen < PH_RPC_CMD_CTRLDIAG_BUFLEN) ? infoBufLen : PH_RPC_CMD_CTRLDIAG_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), infoBuf, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_CTRLDIAG_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_D00_CtrlDeviceDiag(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                   uint16_t rpcStatus, 
                                   uint16_t infoBufLen, 
                                   uint8_t *infoBuf)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer
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
        // Buffer will be copied:
        if (NULL != infoBuf)
        {
            rpc_sd_tmp_len_070972 = (infoBufLen < PH_RPC_CMD_CTRLDIAG_BUFLEN) ? infoBufLen : PH_RPC_CMD_CTRLDIAG_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), infoBuf, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (infoBufLen < PH_RPC_CMD_CTRLDIAG_BUFLEN) ? infoBufLen : PH_RPC_CMD_CTRLDIAG_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_SetDeviceMode(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint16_t rpcStatus)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_GetDeviceCtInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint16_t rpcStatus, 
                                  uint32_t infoNum, 
                                  uint16_t infoBufLen, 
                                  uint8_t *infoBuf)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Numerical information
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoNum      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(infoNum >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(infoNum >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(infoNum >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoBufLen      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(infoBufLen >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_DEVINFO_BUFLEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != infoBuf)
        {
            rpc_sd_tmp_len_070972 = (infoBufLen < PH_RPC_CMD_DEVINFO_BUFLEN) ? infoBufLen : PH_RPC_CMD_DEVINFO_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), infoBuf, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_DEVINFO_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_D00_GetDeviceCtInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                    uint16_t rpcStatus, 
                                    uint32_t infoNum, 
                                    uint16_t infoBufLen, 
                                    uint8_t *infoBuf)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Numerical information
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoNum      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(infoNum >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(infoNum >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(infoNum >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoBufLen      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(infoBufLen >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + infoBufLen) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != infoBuf)
        {
            rpc_sd_tmp_len_070972 = (infoBufLen < PH_RPC_CMD_DEVINFO_BUFLEN) ? infoBufLen : PH_RPC_CMD_DEVINFO_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), infoBuf, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (infoBufLen < PH_RPC_CMD_DEVINFO_BUFLEN) ? infoBufLen : PH_RPC_CMD_DEVINFO_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_DeviceDaq(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint16_t rpcStatus, 
                            uint32_t daqAddress, 
                            uint16_t daqLength, 
                            uint8_t **daqBuffer)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
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

    // DAQ length in bytes
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(daqLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(daqLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EXT_DEV_BUFSIZE) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != daqBuffer)
        {
            *daqBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_D00_DeviceDaq(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint16_t rpcStatus, 
                              uint32_t daqAddress, 
                              uint16_t daqLength, 
                              uint8_t **daqBuffer)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
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

    // DAQ length in bytes
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(daqLength      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(daqLength >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + daqLength) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != daqBuffer)
        {
            *daqBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (daqLength < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? daqLength : PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_GetDevCompatInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                   uint16_t rpcStatus, 
                                   uint16_t compatInfo, 
                                   uint8_t featureCode, 
                                   uint8_t valLevel, 
                                   uint8_t majorVersion, 
                                   uint8_t minorVersion)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Compatibility Information
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(compatInfo      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(compatInfo >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // FeatureCode
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(featureCode      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Validation Level
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(valLevel      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Major Version
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(majorVersion      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Minor Version
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(minorVersion      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_WTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                      uint16_t rpcStatus)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_GetLastResponse(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint16_t rpcStatus)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_EE(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                     uint16_t rpcStatus, 
                     uint8_t *eeBuf, 
                     uint16_t infoBufLen)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // EEPROM Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_CMD_EE_BUFLEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != eeBuf)
        {
            rpc_sd_tmp_len_070972 = (infoBufLen < PH_RPC_CMD_EE_BUFLEN) ? infoBufLen : PH_RPC_CMD_EE_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), eeBuf, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EE_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoBufLen      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(infoBufLen >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_D00_EE(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                       uint16_t rpcStatus, 
                       uint8_t *eeBuf, 
                       uint16_t infoBufLen)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // EEPROM Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + infoBufLen) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != eeBuf)
        {
            rpc_sd_tmp_len_070972 = (infoBufLen < PH_RPC_CMD_EE_BUFLEN) ? infoBufLen : PH_RPC_CMD_EE_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), eeBuf, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (infoBufLen < PH_RPC_CMD_EE_BUFLEN) ? infoBufLen : PH_RPC_CMD_EE_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(infoBufLen      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(infoBufLen >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_EECfg(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                        uint16_t rpcStatus)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_StartTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint16_t rpcStatus, 
                                uint8_t startStatus)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Status of the Start Operation
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(startStatus      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_StopTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                               uint16_t rpcStatus, 
                               uint8_t stopStatus)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Status of the Start Operation
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(stopStatus      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_DataExchangeTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                       uint16_t rpcStatus, 
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Receive Length, number of bytes received from the secondary firmware
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(lenFromCt      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(lenFromCt >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length, number of bytes sent to the secondary firmware
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
            rpc_sd_tmp_len_070972 = (lenFromCt < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? lenFromCt : PH_RPC_CMD_EXT_DEV_BUFSIZE;
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
 
uint8_t phRpc_V_D00_DataExchangeTestSwCt(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                         uint16_t rpcStatus, 
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Receive Length, number of bytes received from the secondary firmware
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(lenFromCt      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(lenFromCt >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length, number of bytes sent to the secondary firmware
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(lenToCt      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(lenToCt >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + lenFromCt) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != xBuffer)
        {
            rpc_sd_tmp_len_070972 = (lenFromCt < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? lenFromCt : PH_RPC_CMD_EXT_DEV_BUFSIZE;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (lenFromCt < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? lenFromCt : PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_DutInit(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint16_t rpcStatus)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_DutGetMode(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint16_t rpcStatus, 
                             uint32_t intfMode)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Interface Mode
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(intfMode      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(intfMode >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(intfMode >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(intfMode >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_DutRWShort(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint16_t rpcStatus, 
                             uint16_t rxLength, 
                             uint16_t txLength, 
                             uint8_t **preBuf, 
                             uint8_t **xBuffer)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
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
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_D00_DutRWShort(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                               uint16_t rpcStatus, 
                               uint16_t rxLength, 
                               uint16_t txLength, 
                               uint8_t **preBuf, 
                               uint8_t **xBuffer)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
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
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + rxLength) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (rxLength < PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT) ? rxLength : PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_DutRWLong(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint16_t rpcStatus, 
                            uint16_t rxLength, 
                            uint16_t txLength, 
                            uint8_t **preBuf, 
                            uint8_t **xBuffer)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
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
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_V_D00_DutRWLong(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint16_t rpcStatus, 
                              uint16_t rxLength, 
                              uint16_t txLength, 
                              uint8_t **preBuf, 
                              uint8_t **xBuffer)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
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
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + rxLength) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (rxLength < PH_RPC_CMD_EXT_DEV_BUFSIZE) ? rxLength : PH_RPC_CMD_EXT_DEV_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_DevIoCtrl(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                            uint16_t rpcStatus, 
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
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
 
uint8_t phRpc_D00_DevIoLineCtrl(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint16_t rpcStatus, 
                                uint32_t ioLineCtlOpt)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Optional Parameter
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(ioLineCtlOpt      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(ioLineCtlOpt >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(ioLineCtlOpt >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(ioLineCtlOpt >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_AdcGetValue(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint16_t rpcStatus, 
                              int32_t daqVal)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Acquired Value
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(daqVal      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(daqVal >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(daqVal >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(daqVal >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_DacSetValue(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint16_t rpcStatus)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_DacSetWave(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint16_t rpcStatus)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_DaqGetVRef(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint16_t rpcStatus, 
                             uint32_t vrefVal)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Reference Voltage Value
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
 
uint8_t phRpc_D00_DaqSetVRef(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint16_t rpcStatus)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_DaqSetGain(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint16_t rpcStatus)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_DaqGetGain(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                             uint16_t rpcStatus, 
                             int32_t gainVal)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Gain Value
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
 
uint8_t phRpc_D00_DacGetFrequency(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint16_t rpcStatus, 
                                  uint32_t actualF)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Frequency
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(actualF      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(actualF >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(actualF >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(actualF >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_DeviceCommCheck(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint16_t rpcStatus, 
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
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
 
uint8_t phRpc_V_D00_DeviceCommCheck(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                    uint16_t rpcStatus, 
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
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
 
uint8_t phRpc_D00_DeviceCommCheckL(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                   uint16_t rpcStatus, 
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
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
 
uint8_t phRpc_V_D00_DeviceCommCheckL(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                     uint16_t rpcStatus, 
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
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
 
uint8_t phRpc_D00_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                     uint16_t rpcStatus, 
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
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
 
uint8_t phRpc_V_D00_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                       uint16_t rpcStatus, 
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
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
 
uint8_t phRpc_D00_D_TEST1(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint16_t rpcStatus, 
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
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
 
uint8_t phRpc_D00_D_TEST2(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint16_t rpcStatus, 
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
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
 
uint8_t phRpc_D00_D_TEST3(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                          uint16_t rpcStatus)
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

    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rpcStatus      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rpcStatus >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_D00_D_TEST4(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_V_D00_D_TEST4(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
