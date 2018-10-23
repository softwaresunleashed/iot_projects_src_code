//
// AUTO-GENERATED: DO NOT EDIT. 
//
 

// _________________________________________________________________________________________________
 
#ifndef __APPLE__ 
# define RPC_WEAK_DEFAULT_HANDLER
#endif 
 
#include <stdint.h>
#include <string.h>
#include "phRpc_HostDeSerialiser_2.h"
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
 
/// @brief Get the number of bytes
uint16_t phRpc_2_H_GetNumBytes(uint8_t *rpcBuf)
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
uint16_t phRpc_2_H_GetFid(uint8_t *rpcBuf)
{
    uint16_t rpc_sd_fid_070972 = rpcBuf[FID_POS];
    return rpc_sd_fid_070972;
}

/// @brief Sequence Number Getter
uint8_t phRpc_2_H_GetSeqNum(uint8_t *rpcBuf)
{
    uint8_t sqnr = rpcBuf[SQNR_POS];
    return sqnr;
}

/// @brief Check the CH2 ID bit
uint8_t phRpc_2_H_IsCh2Id(uint8_t *rpcBuf)
{
    uint8_t is_ch2 = rpcBuf[CH2_ID_POS] & CH2_ID_BIT_MASK;
    return (is_ch2 > 0) ? 1u : 0;
}

/// @brief Clear the CH2 ID bit
void phRpc_2_H_ClearCh2Id(uint8_t *rpcBuf)
{
    rpcBuf[CH2_ID_POS] &= ~(CH2_ID_BIT_MASK);
}

/// @brief RPC Dispatcher/Entry Handler

// _________________________________________________________________________________________________
 
uint8_t phRpc_2_D11_SetCommParam(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                 uint16_t *rpcStatus)
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_GetDeviceInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint16_t *rpcStatus, 
                                  uint32_t *infoNum, 
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
    if (2 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Numerical information
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *infoNum = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_2_CMD_DEVINFO_BUFLEN) ? rpc_sd_tmp_070972 : PH_RPC_2_CMD_DEVINFO_BUFLEN;
        *infoBufLen = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_2_CMD_DEVINFO_BUFLEN) <= (rpcBufLen)))
    {
        if (NULL != infoBuf)
        {
            *infoBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_2_CMD_DEVINFO_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_V_D11_GetDeviceInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                    uint16_t *rpcStatus, 
                                    uint32_t *infoNum, 
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
    if (2 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Numerical information
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *infoNum = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_2_CMD_DEVINFO_BUFLEN) ? rpc_sd_tmp_070972 : PH_RPC_2_CMD_DEVINFO_BUFLEN;
        *infoBufLen = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Information Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + *infoBufLen) <= (rpcBufLen)))
    {
        if (NULL != infoBuf)
        {
            *infoBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (*infoBufLen < PH_RPC_2_CMD_DEVINFO_BUFLEN) ? *infoBufLen : PH_RPC_2_CMD_DEVINFO_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_DeviceDaq(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint16_t *rpcStatus, 
                              uint32_t *daqAddress, 
                              uint16_t *daqLength, 
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

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

    // DAQ length in bytes
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_2_CMD_USER_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_2_CMD_USER_BUFSIZE;
        *daqLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_2_CMD_USER_BUFSIZE) <= (rpcBufLen)))
    {
        if (NULL != daqBuffer)
        {
            *daqBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_2_CMD_USER_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_V_D11_DeviceDaq(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint16_t *rpcStatus, 
                                uint32_t *daqAddress, 
                                uint16_t *daqLength, 
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

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

    // DAQ length in bytes
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_2_CMD_USER_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_2_CMD_USER_BUFSIZE;
        *daqLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // DAQ Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + *daqLength) <= (rpcBufLen)))
    {
        if (NULL != daqBuffer)
        {
            *daqBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (*daqLength < PH_RPC_2_CMD_USER_BUFSIZE) ? *daqLength : PH_RPC_2_CMD_USER_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_GetDevCompatInfo(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                     uint16_t *rpcStatus, 
                                     uint16_t *compatInfo, 
                                     uint8_t *featureCode, 
                                     uint8_t *valLevel, 
                                     uint8_t *majorVersion, 
                                     uint8_t *minorVersion)
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Compatibility Information
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *compatInfo = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // FeatureCode
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *featureCode = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Validation Level
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *valLevel = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Major Version
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *majorVersion = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Minor Version
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *minorVersion = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_WTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                        uint16_t *rpcStatus)
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_GetLastResponse(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                    uint16_t *rpcStatus)
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_DutInit(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                            uint16_t *rpcStatus)
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_DutGetMode(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus, 
                               uint32_t *intfMode)
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Interface Mode
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *intfMode = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_DutRWLong(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint16_t *rpcStatus, 
                              uint32_t *rwFlags, 
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Flags that control the function behaviour
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *rwFlags = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Receive Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_2_CMD_USER_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_2_CMD_USER_BUFSIZE;
        *rxLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_2_CMD_USER_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_2_CMD_USER_BUFSIZE;
        *txLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Prepend Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_2_CMD_PREPEND_LEN) <= (rpcBufLen)))
    {
        if (NULL != preBuf)
        {
            *preBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_2_CMD_PREPEND_LEN;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_2_CMD_USER_BUFSIZE) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_2_CMD_USER_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_V_D11_DutRWLong(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint16_t *rpcStatus, 
                                uint32_t *rwFlags, 
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Flags that control the function behaviour
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *rwFlags = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Receive Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_2_CMD_USER_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_2_CMD_USER_BUFSIZE;
        *rxLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transmit Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_2_CMD_USER_BUFSIZE) ? rpc_sd_tmp_070972 : PH_RPC_2_CMD_USER_BUFSIZE;
        *txLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Prepend Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_2_CMD_PREPEND_LEN) <= (rpcBufLen)))
    {
        if (NULL != preBuf)
        {
            *preBuf = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC enabled but not effective due to Buffer with fixed size. Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_2_CMD_PREPEND_LEN;
    } else { rpc_sd_ret_070972 = 1u; }

    // Exchange Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + *rxLength) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Compact RPC: Buffer with no fixed size. Add individual size to spacing:
        rpc_sd_index_070972 += (*rxLength < PH_RPC_2_CMD_USER_BUFSIZE) ? *rxLength : PH_RPC_2_CMD_USER_BUFSIZE;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_DevIoCtrl(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                              uint16_t *rpcStatus, 
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
    if (67 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
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
 
uint8_t phRpc_2_D11_DevIoLineCtrl(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                  uint16_t *rpcStatus, 
                                  uint32_t *ioLineCtlOpt)
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Optional Parameter
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *ioLineCtlOpt = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_GetTransferLog(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                   uint16_t *rpcStatus, 
                                   uint8_t *numTransfers, 
                                   uint32_t *transferData, 
                                   uint16_t *transferLen)
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Number of transfers
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 1) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        *numTransfers = (uint8_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 1;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transfer data
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *transferData = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

    // Transfer length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *transferLen = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_AdcGetValue(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint16_t *rpcStatus, 
                                int32_t *daqVal)
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Acquired Value
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *daqVal = (int32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_DacSetValue(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                uint16_t *rpcStatus)
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_DacSetWave(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus)
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_DaqGetVRef(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus, 
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
    if (73 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Reference Voltage Value
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
 
uint8_t phRpc_2_D11_DaqSetVRef(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus)
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_DaqSetGain(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus)
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_DaqGetGain(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                               uint16_t *rpcStatus, 
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
    if (76 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Gain Value
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
 
uint8_t phRpc_2_D11_DacGetFrequency(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                    uint16_t *rpcStatus, 
                                    uint32_t *actualF)
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
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Frequency
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 4) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 2])) << 16);
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 3])) << 24);
        *actualF = (uint32_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 4;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_D11_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                       uint16_t *rpcStatus, 
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
    if (240 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN) ? rpc_sd_tmp_070972 : PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN;
        *xLength = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Buffer
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN) <= (rpcBufLen)))
    {
        if (NULL != xBuffer)
        {
            *xBuffer = &(rpcBuf[rpc_sd_index_070972]);
        } else { /* NULL means that this is just a spacer. */ }
        // Buffer has fixed size (and compact RPC disabled). Add constant size to spacing:
        rpc_sd_index_070972 += PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
uint8_t phRpc_2_V_D11_DeviceCommCheckWTX(uint8_t *rpcBuf, uint16_t rpcBufLen, 
                                         uint16_t *rpcStatus, 
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
    if (240 != rpc_sd_fnc_070972)
    {
        rpc_sd_ret_070972 = 1u;
    } else { }
 
    // Status
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        *rpcStatus = (uint16_t)rpc_sd_tmp_070972;
        rpc_sd_index_070972 += 2;
    } else { rpc_sd_ret_070972 = 1u; }

    // Length
    if ((0 == rpc_sd_ret_070972) && ((rpc_sd_index_070972 + 2) <= (rpcBufLen)))
    {
        uint32_t rpc_sd_tmp_070972 = 0;
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 0]))      );
        rpc_sd_tmp_070972 |= (((uint32_t)(rpcBuf[rpc_sd_index_070972 + 1])) <<  8);
        rpc_sd_tmp_070972 = (rpc_sd_tmp_070972 < PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN) ? rpc_sd_tmp_070972 : PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN;
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
        rpc_sd_index_070972 += (*xLength < PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN) ? *xLength : PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN;
    } else { rpc_sd_ret_070972 = 1u; }

 
    return rpc_sd_ret_070972;
}
 
