//
// AUTO-GENERATED: DO NOT EDIT. 
//
 

// _________________________________________________________________________________________________
 
#ifndef __APPLE__ 
# define RPC_WEAK_DEFAULT_HANDLER
#endif 
 
#include <stdint.h>
#include <string.h>
#include "phRpc_DeviceSerialiser_2.h"
#include "phRpc_Cmd_2.h"
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
uint8_t phRpc_2_D_SetSeqNum(uint8_t *rpcBuf, uint8_t seqNum)
{
    rpcBuf[SQNR_POS] = seqNum;
    return 0;
}

/// @brief Set the number of bytes
void phRpc_2_D_SetNumBytes(uint8_t *rpcBuf, uint16_t newRpcBufLen)
{
    rpcBuf[LEN_INFO_POS    ] = (uint8_t)newRpcBufLen;
    rpcBuf[LEN_INFO_POS + 1] = (uint8_t)(newRpcBufLen >> 8);
}

/// @brief Set the CH2 ID bit
void phRpc_2_D_SetCh2Id(uint8_t *rpcBuf)
{
    rpcBuf[CH2_ID_POS] |= CH2_ID_BIT_MASK;
}


// _________________________________________________________________________________________________
 
uint8_t phRpc_2_D00_SetCommParam(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_2_D00_GetDeviceInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_2_CMD_DEVINFO_BUFLEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != infoBuf)
        {
            rpc_sd_tmp_len_070972 = (infoBufLen < PH_RPC_2_CMD_DEVINFO_BUFLEN) ? infoBufLen : PH_RPC_2_CMD_DEVINFO_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), infoBuf, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_2_CMD_DEVINFO_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_V_D00_GetDeviceInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
            rpc_sd_tmp_len_070972 = (infoBufLen < PH_RPC_2_CMD_DEVINFO_BUFLEN) ? infoBufLen : PH_RPC_2_CMD_DEVINFO_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), infoBuf, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (infoBufLen < PH_RPC_2_CMD_DEVINFO_BUFLEN) ? infoBufLen : PH_RPC_2_CMD_DEVINFO_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D00_DeviceDaq(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_2_CMD_USER_BUFSIZE) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != daqBuffer)
        {
            *daqBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_2_CMD_USER_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_V_D00_DeviceDaq(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
        rpc_sd_index_070972 += (daqLength < PH_RPC_2_CMD_USER_BUFSIZE) ? daqLength : PH_RPC_2_CMD_USER_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D00_GetDevCompatInfo(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_2_D00_WTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_2_D00_GetLastResponse(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_2_D00_DutInit(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_2_D00_DutGetMode(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_2_D00_DutRWLong(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint16_t rpcStatus, 
                              uint32_t rwFlags, 
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

    // Flags that control the function behaviour
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rwFlags      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rwFlags >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(rwFlags >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(rwFlags >> 24);
        rpc_sd_index_070972 += 4;
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
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_2_CMD_PREPEND_LEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != preBuf)
        {
            *preBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_2_CMD_PREPEND_LEN;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_2_CMD_USER_BUFSIZE) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_2_CMD_USER_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_V_D00_DutRWLong(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                uint16_t rpcStatus, 
                                uint32_t rwFlags, 
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

    // Flags that control the function behaviour
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(rwFlags      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(rwFlags >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(rwFlags >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(rwFlags >> 24);
        rpc_sd_index_070972 += 4;
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
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_2_CMD_PREPEND_LEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        if (NULL != preBuf)
        {
            *preBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        (void)rpc_sd_tmp_len_070972;
        // Compact RPC enabled but not effective due to Buffer with fixed size. Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_2_CMD_PREPEND_LEN;
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
        rpc_sd_index_070972 += (rxLength < PH_RPC_2_CMD_USER_BUFSIZE) ? rxLength : PH_RPC_2_CMD_USER_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D00_DevIoCtrl(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                              uint16_t rpcStatus, 
                              uint32_t ioctlOpt)
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
 
uint8_t phRpc_2_D00_DevIoLineCtrl(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                  uint16_t rpcStatus, 
                                  uint32_t ioLineCtlOpt)
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
 
uint8_t phRpc_2_D00_GetTransferLog(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                   uint16_t rpcStatus, 
                                   uint8_t numTransfers, 
                                   uint32_t transferData, 
                                   uint16_t transferLen)
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

    // Number of transfers
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(numTransfers      );
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transfer data
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(transferData      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(transferData >>  8);
        rpcBuf[rpc_sd_index_070972 + 2] = (uint8_t)(transferData >> 16);
        rpcBuf[rpc_sd_index_070972 + 3] = (uint8_t)(transferData >> 24);
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transfer length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (*rpcBufLen)))
    {
        rpcBuf[rpc_sd_index_070972 + 0] = (uint8_t)(transferLen      );
        rpcBuf[rpc_sd_index_070972 + 1] = (uint8_t)(transferLen >>  8);
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D00_AdcGetValue(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_2_D00_DacSetValue(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_2_D00_DacSetWave(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_2_D00_DaqGetVRef(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_2_D00_DaqSetVRef(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_2_D00_DaqSetGain(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_2_D00_DaqGetGain(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_2_D00_DacGetFrequency(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
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
 
uint8_t phRpc_2_D00_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                       uint16_t rpcStatus, 
                                       uint16_t xLength, 
                                       uint8_t *xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 240;
 
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
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN) <= (*rpcBufLen)))
    {
        uint16_t rpc_sd_tmp_len_070972;
        // Buffer will be copied:
        if (NULL != xBuffer)
        {
            rpc_sd_tmp_len_070972 = (xLength < PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN) ? xLength : PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_V_D00_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t *rpcBufLen, 
                                         uint16_t rpcStatus, 
                                         uint16_t xLength, 
                                         uint8_t *xBuffer)
{
    uint8_t rpc_sd_ret_070972 = 0;
    volatile /* easier to debug */ uint16_t rpc_sd_index_070972 = INFO_START_POS;
    uint8_t rpc_sd_fnc_070972 = 240;
 
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
            rpc_sd_tmp_len_070972 = (xLength < PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN) ? xLength : PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN;
            memcpy(&(rpcBuf[rpc_sd_index_070972]), xBuffer, rpc_sd_tmp_len_070972);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (xLength < PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN) ? xLength : PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    rpcBuf[0] = (uint8_t)rpc_sd_index_070972;
    rpcBuf[1] = (uint8_t)(rpc_sd_index_070972 >> 8);
    *rpcBufLen = rpc_sd_index_070972;
    return rpc_sd_ret_070972;
}
 
