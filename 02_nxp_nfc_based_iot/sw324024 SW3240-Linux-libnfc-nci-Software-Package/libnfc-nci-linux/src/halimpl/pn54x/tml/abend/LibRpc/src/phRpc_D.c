/*
*                  Copyright (c), NXP Semiconductors
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* Project: RPC Device Library / ARM-Board for PN547 V&V.
* $Author: atp01705 $
* $Revision: 29472 $
* $Date: 2014-09-09 09:25:58 +0200 (mar., 09 sept. 2014) $
*
*/

// ________________________________________________________________________________________________
//
// Includes and Definitions
// ________________________________________________________________________________________________

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "phRpc_D.h"

// ________________________________________________________________________________________________
//
// Comp-Specific
// ________________________________________________________________________________________________

// States
#define PH_RPC_D_IDLE              0    // No request is being processed, device is ready
#define PH_RPC_D_RX_ONGOING        1    // Receiving is ongoing
#define PH_RPC_D_DISPATCH          2    // Incoming request is being dispatched
#define PH_RPC_D_DISPATCH_WAIT     3    // Incoming request is being processed, wait for completion
#define PH_RPC_D_TX                4    // Initiating of TX
#define PH_RPC_D_TX_WAIT           5    // Check whether TX has finished

// Debug Settings
#define PH_RPC_D_DBG_NORM_OP   0x00u    // Normal operation. Init value
#define PH_RPC_D_DBG_DISP_OFF  0x01u    // Disable the dispatcher
#define PH_RPC_D_DBG_COMP_OFF  0x02u    // Disable the component: No RX, no dispatch, state machine OFF

// Constants
#define PH_RPC_D_MIN_RX_LEN        2    // First 2 char are length info
#define PH_RPC_D_TIME_SINCE_TX_MIN 1000 // µs

// Helpers, Delegate Abbreviations
#define PH_RPC_D_TIME_UNIT_MS2US(_to) (_to * 1000)   // Convert ms into µs
#define PH_RPC_D_HOOK(_actionType) if(NULL!=rpcCx->Delegates->Hook){rpcCx->Delegates->Hook(rpcCx->UserData,_actionType);}

// Helper Functions
void     phRpc_D_HandleTx(phRpc_D_t *rpcCx);
uint8_t  phRpc_D_IsWtxInterval(phRpc_D_t *rpcCx);
void     phRpc_D_ResetWtxTimeout(phRpc_D_t *rpcCx);
void     phRpc_D_BuildWtx(phRpc_D_t *rpcCx, uint16_t *wtxLen);
uint8_t  phRpc_D_IsWtx(phRpc_D_t *rpcCx, uint8_t fId, uint8_t *cancelRequest);
void     phRpc_D_TxReset(phRpc_D_t *rpcCx);
void     phRpc_D_RxReset(phRpc_D_t *rpcCx);
void     phRpc_D_ErrorReset(phRpc_D_t *rpcCx);
void     phRpc_D_RcReset(phRpc_D_t *rpcCx);
uint16_t phRpc_D_SetTransmitSize(phRpc_D_t *rpcCx, uint8_t *txBuf, uint16_t txSize);
uint8_t  phRpc_D_CheckRcResetS(phRpc_D_t *rpcCx);
uint8_t  phRpc_D_CheckRcReset(phRpc_D_t *rpcCx, uint8_t *outBuf, uint16_t outLen);
// ISR Context
inline uint16_t phRpc_D_GetTargetLength(phRpc_D_t *rpcCx);
inline uint16_t phRpc_D_GetMinLength(phRpc_D_t *rpcCx);

// ________________________________________________________________________________________________
//
// RPC Device Functions
// ________________________________________________________________________________________________

uint8_t phRpc_D_Init(phRpc_D_t                 *rpcCx,
                     phRpc_D_Delegates_t       *delegateFunctions,
                     void                      *userData,
                     uint32_t                   trxTimeoutMicrosec,
                     uint32_t                   intervalMicrosec,
                     uint8_t                   *inBuf,
                     uint16_t                   inBufSize,
                     uint8_t                   *outBuf,
                     uint16_t                   outBufSize)
{
    uint8_t ret = 1u;

    if ((NULL != rpcCx) && (NULL != delegateFunctions) &&
        (NULL != inBuf) && (NULL != outBuf) && (0 != inBufSize) && (0 != outBufSize))
    {
        // Zero out struct:
        memset(rpcCx, 0, sizeof (phRpc_D_t));

        // Buffers
        rpcCx->InBufWtx         = inBuf;        // InBuf is derived from total InBuf
        rpcCx->OutBuf           = outBuf;       // Out Buffer (data coming from PC)
        rpcCx->InBufWtxSize     = inBufSize;    // InBuf is derived from total InBuf
        rpcCx->OutBufSize       = outBufSize;   // Out Buffer (data coming from PC)

        // Delegate data:
        rpcCx->UserData         = userData;

        // Set Delegates
        rpcCx->Delegates        = delegateFunctions;

        // Reset Protocol:
        ret = phRpc_D_Reset(rpcCx);

        // Apply Cfg:
        rpcCx->TRxTimeout       = trxTimeoutMicrosec;
        rpcCx->IntervalMicrosec = intervalMicrosec;
        rpcCx->HostTimeout      = PH_RPC_D_TIME_UNIT_MS2US(PH_RPC_D_DEFAULT_HOST_TIMEOUT);

        // Defaults:
        rpcCx->NumBytesToSendMul= PH_RPC_D_MIN_COMM_BUFSIZE_DEFAULT_MUL;
        rpcCx->PadPlus1         = 0;
        rpcCx->PadMul           = 1;

        ret = 0;
    } else { }

    return ret;
}

uint8_t phRpc_D_Reset(phRpc_D_t *rpcCx)
{
    uint8_t ret = 1u;

    if (NULL != rpcCx)
    {
        // Log
        PH_RPC_D_HOOK(PH_RPC_D_HOOKF_RESET);
        // Include special members:
        phRpc_D_TxReset(rpcCx);
        phRpc_D_RxReset(rpcCx);
        // More members: Reset them, but do not reset configuration data.
        rpcCx->DebugInformation.RecentFid           = 0;
        rpcCx->HostSequenceNumber                   = 0;
        rpcCx->PrevInLen                            = 0;
        rpcCx->DebugInformation.CommCheckResDelay   = 0;
        rpcCx->HostTimeoutCount                     = 0;
        phRpc_D_ResetWtxTimeout(rpcCx);
        rpcCx->DispatchTimer                        = 0;
        rpcCx->DeferInLen                           = PH_RPC_D_TOTAL_BUFSIZE(rpcCx);
        // Debug
        rpcCx->DebugInformation.DbgNumRequest       = 0;
        rpcCx->DebugInformation.DbgNumResponse      = 0;

        ret = 0;
    } else { }

    return ret;
}

void phRpc_D_TxReset(phRpc_D_t *rpcCx)
{
    PH_RPC_D_HOOK(PH_RPC_D_HOOKF_RESET_LITTLE);

    // In Buffer (starts after the WTX buffer):
    rpcCx->InBuf                = &(rpcCx->InBufWtx[PH_RPC_D_COMM_WTXBUFSIZE]);
    rpcCx->InLen                = PH_RPC_D_TOTAL_BUFSIZE(rpcCx);
    // State, status, flags
    rpcCx->TxState              = PH_RPC_D_IDLE;
    rpcCx->EpStatus             = PH_RPC_D_STATUS_OK;
    rpcCx->InWtx                = 0;
    // Transmit Specific:
    rpcCx->NumSent              = 0;
    rpcCx->TxTimer              = 0;
    rpcCx->TxComplete           = 0;
}

void phRpc_D_RxReset(phRpc_D_t *rpcCx)
{
    PH_RPC_D_HOOK(PH_RPC_D_HOOKF_RESET_LITTLE);

    rpcCx->RxState          = PH_RPC_D_IDLE;
    rpcCx->TargetRxLength   = PH_RPC_D_MIN_RX_LEN;
    rpcCx->RxTimer          = 0;
    rpcCx->OutLen           = 0;
}

uint8_t phRpc_D_SetComOptions(phRpc_D_t *rpcCx, uint32_t comParam, uint16_t msTimeout)
{
    uint8_t ret = 1u;

    if (NULL != rpcCx)
    {
        // Padding requested by host?
        if (PH_RPC_CMD_PAD_PLUS_1 == (comParam & PH_RPC_CMD_PAD_PLUS_1))
        {
            rpcCx->PadPlus1 = 1u;
        } else
        {
            rpcCx->PadPlus1 = 0;
        }
        // Variable-length RPC enabled?
        if (PH_RPC_CMD_VARIABLE_LEN_RPCBUF == (comParam & PH_RPC_CMD_VARIABLE_LEN_RPCBUF))
        {
            rpcCx->VarLenRpcEnable = 1u;
        } else
        {
            rpcCx->VarLenRpcEnable = 0;
        }
        rpcCx->PadMul = (uint8_t)((comParam & PH_RPC_CMD_PAD_MUL_MASK) >> PH_RPC_CMD_PAD_MUL_SHIFT);
        rpcCx->PadMul = (rpcCx->PadMul < PH_RPC_CMD_PAD_MUL_MAX) ? rpcCx->PadMul : PH_RPC_CMD_PAD_MUL_MAX;
        rpcCx->PadMul = (0 == rpcCx->PadMul) ? 1u : rpcCx->PadMul;

        // Host Time-out:
        rpcCx->HostTimeout = PH_RPC_D_TIME_UNIT_MS2US(msTimeout);
        rpcCx->HostTimeout = (rpcCx->HostTimeout < PH_RPC_D_MIN_HOST_TIMEOUT_MICROSEC) ? PH_RPC_D_MIN_HOST_TIMEOUT_MICROSEC : rpcCx->HostTimeout;
        ret = 0;
    } else { }

    return ret;
}

uint8_t phRpc_D_Main(phRpc_D_t *rpcCx)
{
    uint8_t  ret                    = 1u;
    uint8_t  fid;
    uint8_t  cancel_req             = 0;

    if ((NULL != rpcCx) && (NULL != rpcCx->Delegates->Defer) && (NULL != rpcCx->Delegates->Cancel) && (NULL != rpcCx->Delegates->Tx))
    {
        // Enter Main:
        PH_RPC_D_HOOK(PH_RPC_D_HOOKF_ENTERMAIN);

        // RX States:
        switch (rpcCx->RxState)
        {
            default:
            // Should not happen. Reset to reasonable values.
            phRpc_D_ErrorReset(rpcCx);
            case PH_RPC_D_IDLE:
                break;

            case PH_RPC_D_RX_ONGOING:
                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_ENTER_RX_ONGOING);
                rpcCx->RxTimer += rpcCx->IntervalMicrosec;
                if (rpcCx->RxTimer > rpcCx->TRxTimeout)
                {
                    // Stop the reception/reset as there was a time-out condition.
                    phRpc_D_ErrorReset(rpcCx);
                } else { }
                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_LEAVE_RX_ONGOING);
                break;

            case PH_RPC_D_DISPATCH:
                // Reset the timers:
                rpcCx->HostTimeoutCount = 0;
                rpcCx->DispatchTimer = 0;
                // Basic action
                if (PH_RPC_D_IDLE == rpcCx->TxState)
                {
                    PH_RPC_D_HOOK(PH_RPC_D_HOOKF_ENTER_DISPATCH);
                    if (0 != phRpc_D_CheckRcResetS(rpcCx))
                    {
                        // We have received a RC reset request!
                    } else
                    {
                        // Go ahead with dispatching the new request.
                        // Check the sequence whether we are in order:
                        rpcCx->HostSequenceNumber = rpcCx->Delegates->GetSeqNum(rpcCx->OutBuf);
                        // Determine what to do:
                        fid = rpcCx->Delegates->GetFid(rpcCx->OutBuf);
                        rpcCx->DebugInformation.RecentFid = fid;

                        if (0 != phRpc_D_IsWtx(rpcCx, fid, &cancel_req))
                        {
                            PH_RPC_D_HOOK(PH_RPC_D_HOOKF_WTX_CONF);
                            // Incoming WTX confirmation:
                            // We were in Dispatch Wait when we requested more time, go there again.
                            // Also, move the In Buffer to the "real start" location as the deferred
                            // task could complete any time.
                            rpcCx->InBuf = &(rpcCx->InBufWtx[PH_RPC_D_COMM_WTXBUFSIZE]);
                            rpcCx->RxState = PH_RPC_D_DISPATCH_WAIT;
                            if (0 != cancel_req)
                            {
                                // The WTX confirmation from the PC comprises a CANCEL Request.
                                (void)rpcCx->Delegates->Cancel(rpcCx, rpcCx->UserData);
                            } else
                            {
                                // No action as we continue to 'Wtx.
                            }
                        } else
                        {
                            // Define next state:
                            rpcCx->RxState = PH_RPC_D_DISPATCH_WAIT;
                            // Start over with WTX interval
                            phRpc_D_ResetWtxTimeout(rpcCx);
                            // Dispatch
                            rpcCx->DeferInLen = PH_RPC_D_TOTAL_BUFSIZE(rpcCx); // Full buffer size, but w/o guard
                            // Call Type: There are direct and deferred calls:
                            if ((fid >= PH_RPC_D_RANGE_DIRECT_LOW) && (fid <= PH_RPC_D_RANGE_DIRECT_HIGH)) // first part is always true as PH_RPC_D_RANGE_DIRECT_LOW == 0
                            {
                                // Direct call in context of USB task:
                                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_PRE_DIRECT_CALL);
                                ret = phRpc_D_Entry(rpcCx, rpcCx->UserData, rpcCx->OutBuf, rpcCx->OutLen, rpcCx->InBuf, &rpcCx->DeferInLen);
                                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_POST_DIRECT_CALL);
                            } else
                            {
                                // Deferred call in context of async task:
                                // Deferring of the call is last action here.
                                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_PRE_DEFER_CALL);
                                ret = rpcCx->Delegates->Defer(rpcCx, rpcCx->UserData, rpcCx->OutBuf, rpcCx->OutLen, rpcCx->InBuf, &rpcCx->DeferInLen);
                                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_POST_DEFER_CALL);
                            }
                        }
                    }
                    PH_RPC_D_HOOK(PH_RPC_D_HOOKF_LEAVE_DISPATCH);
                } else
                {
                    // Stay here because the last transmission has not yet completed
                }
                break;

            case PH_RPC_D_DISPATCH_WAIT:
                // Time out on Host I/O (USB)?
                rpcCx->HostTimeoutCount += rpcCx->IntervalMicrosec;
                // Time out on Dispatch?
                rpcCx->DispatchTimer += rpcCx->IntervalMicrosec;

                // Call hook after value update
                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_ENTER_DISPATCH_WAIT);

                if (0 != rpcCx->DispatchDone)
                {
                    // Yes -- we have a dispatch completion. Finished waiting here:
                    rpcCx->DispatchDone = 0;
                    rpcCx->NumSent = 0;
                    rpcCx->InLen = (rpcCx->DeferInLen > PH_RPC_D_USER_BUFSIZE(rpcCx)) ? PH_RPC_D_USER_BUFSIZE(rpcCx) : rpcCx->DeferInLen;
                    rpcCx->InWtx = 0u;
                    rpcCx->TxState = PH_RPC_D_TX;
                    phRpc_D_RxReset(rpcCx); // Ready to receive next command from host
                    // Set the exchange buffer (WTX buffer is before, so we shift start by offset)
                    rpcCx->InBuf = &(rpcCx->InBufWtx[PH_RPC_D_COMM_WTXBUFSIZE]);
                    PH_RPC_D_HOOK(PH_RPC_D_HOOKF_DISPATCH_COMPLETION);
                } else
                {
                    // No dispatch completion: Handle host timeout, if needed:
                    if (0 != phRpc_D_IsWtxInterval(rpcCx))
                    {
                        PH_RPC_D_HOOK(PH_RPC_D_HOOKF_WTX_REQ);
                        // Send a WTX: Set the input buffer to the WTX location and set flag:
                        rpcCx->InBuf = &(rpcCx->InBufWtx[0]);
                        rpcCx->InWtx = 1u;
                        phRpc_D_BuildWtx(rpcCx, &(rpcCx->InLen));
                        rpcCx->NumSent = 0;
                        rpcCx->TxState = PH_RPC_D_TX;
                        phRpc_D_RxReset(rpcCx); // Ready to receive WTX conf from host
                    } else { /* No action, host will not time out but just wait for I/O completion */ }
                }

                if (PH_RPC_D_TX == rpcCx->TxState)
                {
                    // We go transmit now:
                    // Determine how much has to be sent (pad to block size, etc.):
                    rpcCx->InLen = phRpc_D_SetTransmitSize(rpcCx, rpcCx->InBuf, rpcCx->InLen);
                    // Update the number of bytes in the RPC header:
                    rpcCx->Delegates->SetNumBytes(rpcCx->InBuf, rpcCx->InLen);
                    // Remember in case the host asks to repeat last TX:
                    rpcCx->PrevInLen = rpcCx->InLen;
                    // Debug
                    rpcCx->DebugInformation.RecentFid = rpcCx->Delegates->GetFid(rpcCx->InBuf);
                }

                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_LEAVE_DISPATCH_WAIT);
                break;
        }

        // TX States:
        switch (rpcCx->TxState)
        {
            default:
            // Should not happen. Reset to reasonable values.
            phRpc_D_ErrorReset(rpcCx);
            case PH_RPC_D_IDLE:
                break;

            case PH_RPC_D_TX:
                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_ENTER_TX);

                if (0 == rpcCx->DebugInformation.CommCheckResDelay) // Debug: Can delay the response
                {
                    switch (rpcCx->EpStatus)
                    {
                        default:
                        case PH_RPC_D_STATUS_OK:
                            // No special action
                            break;

                        case PH_RPC_D_STATUS_ERROR:
                            // No special action
                            break;

                        case PH_RPC_D_STATUS_REPEAT:
                            // Prepare last content to be sent:
                            rpcCx->InLen = rpcCx->PrevInLen;
                            break;
                    }

                    // Sequence Number:
                    rpcCx->Delegates->SetSeqNum(rpcCx->InBuf, rpcCx->HostSequenceNumber);
                    // Transmit
                    phRpc_D_HandleTx(rpcCx);
                } else
                {
                    rpcCx->DebugInformation.CommCheckResDelay = (rpcCx->DebugInformation.CommCheckResDelay >= rpcCx->IntervalMicrosec) ?
                        (rpcCx->DebugInformation.CommCheckResDelay - rpcCx->IntervalMicrosec) : 0;
                }
                // Debug
                rpcCx->DebugInformation.DbgNumSent = rpcCx->NumSent;

                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_LEAVE_TX);
                break;

            case PH_RPC_D_TX_WAIT:
                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_ENTER_TX_WAIT);
                // Usually the TX completion callback is issued while waiting here, but in case the
                // TX completion is too late or not issued at all we check for timeout.
                if (0 == rpcCx->TxComplete)
                {
                    if (rpcCx->NumSent < rpcCx->InLen)
                    {
                        // Repeat TX until done
                        rpcCx->TxState = PH_RPC_D_TX;
                    } else
                    {
                        // Stay here; State will be reset.
                    }
                    // TX timeout check
                    rpcCx->TxTimer += rpcCx->IntervalMicrosec;
                    if (rpcCx->TxTimer > rpcCx->TRxTimeout)
                    {
                        // Done or TX impossible or error: Finish.
                        phRpc_D_ErrorReset(rpcCx);
                    } else { /* not done */ }
                } else
                {
                    phRpc_D_TxReset(rpcCx);
                }
                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_LEAVE_TX_WAIT);
                break;
        }
        ret = 0;
        // Leave Main:
        PH_RPC_D_HOOK(PH_RPC_D_HOOKF_LEAVEMAIN);
    } else { /* Invalid Param or component OFF */ }

    return ret;
}

// Caution: We may be in ISR context here.
uint8_t phRpc_D_Receive(phRpc_D_t *rpcCx, uint8_t *buf, size_t bufLen, uint8_t callerComp)
{
    uint8_t     ret = 0;
    size_t      num_bytes_to_copy;
    size_t      num_bytes_free;

    if (NULL != rpcCx)
    {
        // Determine CALL source
        rpcCx->RecentCaller = callerComp;
        switch (rpcCx->RxState)
        {
            case PH_RPC_D_IDLE:
                rpcCx->TargetRxLength = 0;
            case PH_RPC_D_RX_ONGOING:
                num_bytes_free = (PH_RPC_D_TOTAL_BUFSIZE(rpcCx) > rpcCx->OutLen) ? (PH_RPC_D_TOTAL_BUFSIZE(rpcCx) - rpcCx->OutLen) : 0;
                num_bytes_to_copy = (num_bytes_free > bufLen) ? bufLen : num_bytes_free;
                if (num_bytes_free > 0)
                {
                    rpcCx->RxState = PH_RPC_D_RX_ONGOING;

                    memcpy(&(rpcCx->OutBuf[rpcCx->OutLen]), buf, num_bytes_to_copy);
                    rpcCx->OutLen += num_bytes_to_copy;

                    // Determine frame length:
                    if ((rpcCx->OutLen >= phRpc_D_GetMinLength(rpcCx)) && (0 == rpcCx->TargetRxLength))
                    {
                        // Get the expected number of bytes:
                        rpcCx->TargetRxLength = phRpc_D_GetTargetLength(rpcCx);
                        // Check whether we receive anything that could make sense to us
                        // and doesn't overflow the buffer
                        if ((rpcCx->TargetRxLength > phRpc_D_GetMinLength(rpcCx)) && (rpcCx->TargetRxLength <= PH_RPC_D_TOTAL_BUFSIZE(rpcCx)))
                        {
                            // OK, go ahead
                        } else
                        {
                            // Error: Non-plausible data
                            phRpc_D_ErrorReset(rpcCx);
                            ret = 1u;
                        }
                    } else { }

                    // Time to dispatch?
                    if ((0 != rpcCx->TargetRxLength) && (rpcCx->OutLen >= rpcCx->TargetRxLength))
                    {
                        // Yes:
                        rpcCx->DebugInformation.RX_LastData = *((uint32_t*)((void*)rpcCx->OutBuf));
                        rpcCx->DebugInformation.DbgNumRequest++;
                        rpcCx->RxState = PH_RPC_D_DISPATCH;
                    } else
                    {
                        // Not yet, just accumulate the next bytes (above) and say OK.
                        ret = 0;
                    }
                    // Resetting of receive timer (trx-timer) is not required here.
                } else
                {
                    // Overflow, reset
                    phRpc_D_ErrorReset(rpcCx);
                    ret = 1u;
                }
                break;

            case PH_RPC_D_DISPATCH:
            case PH_RPC_D_DISPATCH_WAIT:
                // Received and currently processing.
                // Sense for RC Reset packet
                (void)phRpc_D_CheckRcReset(rpcCx, buf, bufLen);
                break;
            default:
                // Wait for completion of the ongoing operation, do not accumulate any new input.
                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_RX_DISCARD);
                rpcCx->DebugInformation.RX_LastDataDiscarded = *((uint32_t*)((void*)buf));
                rpcCx->DebugInformation.RX_Discarded++;
                rpcCx->DebugInformation.RX_Discard_RxState = rpcCx->RxState;
                rpcCx->DebugInformation.RX_Discard_TxState = rpcCx->TxState;
                break;
        }
    } else
    {
        // Invalid arg:
        ret = 1u;
    }

    return ret;
}

uint8_t phRpc_D_GetVarRpcEnableState(phRpc_D_t *rpcCx)
{
    uint8_t enable_state = 0;

    if (NULL != rpcCx)
    {
        enable_state = (0 != rpcCx->VarLenRpcEnable) ? 1u : 0;
    }

    return enable_state;
}

uint8_t phRpc_D_SetResWaitingTimeOnce(phRpc_D_t *rpcCx, uint8_t msWait)
{
    uint8_t ret = 1u;

    if (NULL != rpcCx)
    {
        rpcCx->DebugInformation.CommCheckResDelay = PH_RPC_D_TIME_UNIT_MS2US(msWait);
        ret                        = 0;
    } else { /* Param */ }

    return ret;
}

uint8_t phRpc_D_DispatchCompletion(phRpc_D_t *rpcCx, uint8_t status)
{
    uint8_t ret = 1u;

    if (NULL != rpcCx)
    {
        rpcCx->EpStatus     = status;
        rpcCx->DispatchDone = 1u;
        ret                 = 0;
    } else { /* Param */ }

    return ret;
}

uint8_t phRpc_D_TXCompletion(phRpc_D_t *rpcCx, uint8_t txStatus, uint16_t numSent)
{
    uint8_t ret = 1u;

    if (NULL != rpcCx)
    {
        if (rpcCx->NumSent < rpcCx->InLen)
        {
            // We have not yet sent all: Re-enter TX state:
            rpcCx->TxComplete = 0;
            // Hook/Debug
            if (PH_RPC_D_TXCOMPLETION_OK == txStatus)
            {
                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_TXCOMPLETION_PARTIAL);
            } else
            {
                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_TXCOMPLETION_PARTIAL_ERR);
            }
        } else
        {
            // Complete!
            rpcCx->TxComplete = 1u;
            // Hook/Debug
            if (PH_RPC_D_TXCOMPLETION_OK == txStatus)
            {
                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_TXCOMPLETION);
            } else
            {
                PH_RPC_D_HOOK(PH_RPC_D_HOOKF_TXCOMPLETION_ERR);
            }
        }
        ret = 0;
    } else { /* Param */ }

    (void)numSent;
    return ret;
}

uint8_t phRpc_D_Entry(phRpc_D_t *rpcCx, void *userData, uint8_t *rpcRxBuf, uint16_t rpcRxBufLen, uint8_t *rpcTxBuf, uint16_t *rpcTxBufLen)
{
    return rpcCx->Delegates->Dispatch(userData, rpcRxBuf, rpcRxBufLen, rpcTxBuf, rpcTxBufLen);
}

uint8_t phRpc_D_SetTxPacketSizeMul(phRpc_D_t *rpcCx, uint8_t sizeMul)
{
    uint8_t     ret = 0;
    uint8_t     max = PH_RPC_D_TOTAL_BUFSIZE(rpcCx) / PH_RPC_D_MIN_COMM_BUFSIZE;

    if (NULL != rpcCx)
    {
        if ((sizeMul > 0) && (sizeMul < max))
        {
            rpcCx->NumBytesToSendMul = sizeMul;
        } else
        {
            rpcCx->NumBytesToSendMul = 1u;
        }
    } else
    {
        ret = 1u;
    }

    return ret;
}

// ________________________________________________________________________________________________
//
// HELPERS
// ________________________________________________________________________________________________

void phRpc_D_HandleTx(phRpc_D_t *rpcCx)
{
    uint16_t num_bytes_to_send;

    // Length / Overrun check
    if (rpcCx->InLen > rpcCx->NumSent)
    {
        uint16_t prev_num_sent;

        rpcCx->DebugInformation.DbgNumResponse++;
        num_bytes_to_send = rpcCx->InLen - rpcCx->NumSent;
        // Send:
        rpcCx->TxTimer = 0;
        rpcCx->TxState = PH_RPC_D_TX_WAIT;
        PH_RPC_D_HOOK(PH_RPC_D_HOOKF_TX);
        // All to send is also being sent if the function succeeds:
        prev_num_sent = rpcCx->NumSent;
        rpcCx->NumSent += num_bytes_to_send; // Add before TX to avoid race condition with TX completion.
        // Don't use the value provided by the function to increase sent byte count
        (void)rpcCx->Delegates->Tx(rpcCx, rpcCx->UserData, &(rpcCx->InBuf[prev_num_sent]), num_bytes_to_send);
        // Switch buffer back (as switched anyway in WTX reception above)
        rpcCx->InBuf = &(rpcCx->InBufWtx[PH_RPC_D_COMM_WTXBUFSIZE]);
    } else if (rpcCx->InLen == rpcCx->NumSent)
    {
        // Done (should not come here as this is handled in TX WAIT):
        rpcCx->DebugInformation.TX_0++;
        phRpc_D_TxReset(rpcCx);
    } else
    {
        // Error: Should not get there as the TX completion should have been issued before!
        rpcCx->DebugInformation.TX_Ovr++;
        phRpc_D_ErrorReset(rpcCx);
    }
}

uint8_t phRpc_D_IsWtxInterval(phRpc_D_t *rpcCx)
{
    uint8_t is_interval = 0;

    if (rpcCx->HostTimeoutCount > rpcCx->WtxTimeout)
    {
        uint32_t toc = (rpcCx->HostTimeout / 2u) + 1u;
        uint32_t max_wtx_span_us = PH_RPC_D_TIME_UNIT_MS2US(PH_RPC_D_COMM_MAX_WTXTIMESPAN_MS);

        toc = (toc > max_wtx_span_us) ? max_wtx_span_us : toc;
        rpcCx->WtxTimeout *= 5;
        rpcCx->WtxTimeout /= 4;
        rpcCx->WtxTimeout = (rpcCx->WtxTimeout > toc) ? toc : rpcCx->WtxTimeout;

        is_interval = 1u;
        rpcCx->HostTimeoutCount = 0;
    } else
    {
        // Not yet sending WTX
    }

    return is_interval;
}

void phRpc_D_ResetWtxTimeout(phRpc_D_t *rpcCx)
{
    rpcCx->WtxTimeout = PH_RPC_D_MIN_HOST_TIMEOUT_MICROSEC / 2; // WTX performs progressive wait time increase: Start with low value.
}

void phRpc_D_ErrorReset(phRpc_D_t *rpcCx)
{
    PH_RPC_D_HOOK(PH_RPC_D_HOOKF_RESET_ERROR);
    (void)rpcCx->Delegates->ResetP(rpcCx, rpcCx->UserData);
    (void)phRpc_D_Reset(rpcCx);
}

void phRpc_D_RcReset(phRpc_D_t *rpcCx)
{
    (void)rpcCx->Delegates->Cancel(rpcCx, rpcCx->UserData);
    (void)rpcCx->Delegates->ResetP(rpcCx, rpcCx->UserData);
    memset(rpcCx->InBufWtx, 0, rpcCx->InBufWtxSize); // Zero the entire InBuf (In is host view)
    (void)phRpc_D_Reset(rpcCx);
    rpcCx->DeferInLen = PH_RPC_D_COMM_RCRESETBUFSIZE;
    rpcCx->DispatchDone = 1u;
    rpcCx->DebugInformation.DbgNumRequest++; // As we clear the count during reset
    rpcCx->RxState = PH_RPC_D_DISPATCH_WAIT; // Use the processing path from end of dispatch onwards
}

void phRpc_D_BuildWtx(phRpc_D_t *rpcCx, uint16_t *wtxLen)
{
    uint16_t    status  = PH_RPC_STATUS_OK;
    *wtxLen  = PH_RPC_D_COMM_WTXBUFSIZE;
    (void)rpcCx->Delegates->BuildWtx(rpcCx->InBufWtx, wtxLen, status);
}

uint8_t phRpc_D_IsWtx(phRpc_D_t *rpcCx, uint8_t fId, uint8_t *cancelRequest)
{
    uint8_t     is_wtx = 0;

    if (NULL != rpcCx)
    {
        uint8_t ret = rpcCx->Delegates->ReceiveWtx(rpcCx->OutBuf, rpcCx->OutLen, cancelRequest);
        if (0 == ret)
        {
            // IS WTX
            is_wtx = 1u;
            // OK, set cancel request flag:
            *cancelRequest = (0 != *cancelRequest) ? 1u : 0; // Limit range
        } else
        {
            // Something went wrong with the de-serialisation
            *cancelRequest = 0;
        }
    } else
    {
        is_wtx = 0;
    }

    (void)fId;

    return is_wtx;
}

uint16_t phRpc_D_SetTransmitSize(phRpc_D_t *rpcCx, uint8_t *txBuf, uint16_t txSize)
{
    uint16_t min_tx_size;
    uint16_t prev_tx_size;
    uint16_t i;

    // Pad to 64 byte (USB bulk size) multiples
    min_tx_size = PH_RPC_D_MIN_COMM_BUFSIZE * rpcCx->PadMul;
    prev_tx_size = txSize;
    txSize += (min_tx_size - (txSize % min_tx_size));

    // Pad one extra byte if needed:
    if (0 != rpcCx->PadPlus1)
    {
        txSize++;
    }

    // Fill extra space with dummy character (if in "normal" and not in WTX mode)
    if (&(rpcCx->InBufWtx[PH_RPC_D_COMM_WTXBUFSIZE]) == txBuf)
    {
        // "Normal" mode, pad all buffer
        for (i = prev_tx_size; i < txSize; i++)
        {
            txBuf[i] = 0xFFu;
        }
    } else
    {
        // WTX mode, pad only what is dedicated to WTX
        for (i = prev_tx_size; i < PH_RPC_D_COMM_WTXBUFSIZE; i++)
        {
            txBuf[i] = 0xFFu;
        }
    }

    return txSize;
}

uint8_t phRpc_D_CheckRcResetS(phRpc_D_t *rpcCx)
{
    uint16_t out_len = rpcCx->OutLen;
    uint8_t *out_buf = rpcCx->OutBuf;
    return phRpc_D_CheckRcReset(rpcCx, out_buf, out_len);
}

uint8_t phRpc_D_CheckRcReset(phRpc_D_t *rpcCx, uint8_t *outBuf, uint16_t outLen)
{
    const uint8_t  rcreset_buffer[PH_RPC_CMD_RESET_FRAME_LEN] = PH_RPC_CMD_RESET_FRAME;
    uint8_t ret = 0;

    if (PH_RPC_CMD_RESET_FRAME_LEN == outLen)
    {
        if (0 == memcmp(rcreset_buffer, outBuf, PH_RPC_CMD_RESET_FRAME_LEN))
        {
            phRpc_D_RcReset(rpcCx);
            ret = 1u;
        } else
        {
            // Anything else with same length
        }
    } else
    {
        // Anything else
    }

    return ret;
}

inline uint16_t phRpc_D_GetTargetLength(phRpc_D_t *rpcCx)
{
    uint16_t target_length;

    if (PH_RPC_D_CALL_SOURCE_SERIAL == rpcCx->RecentCaller)
    {
        // Could differ in future implementation, thus clumsy like this..
        target_length = rpcCx->Delegates->GetNumBytes(rpcCx->OutBuf);
    } else
    {
        target_length = rpcCx->Delegates->GetNumBytes(rpcCx->OutBuf);
    }

    return target_length;
}

inline uint16_t phRpc_D_GetMinLength(phRpc_D_t *rpcCx)
{
    uint16_t min_len = PH_RPC_D_MIN_RX_LEN;

    if (PH_RPC_D_CALL_SOURCE_SERIAL == rpcCx->RecentCaller)
    {
        // Could differ in future implementation, thus clumsy like this..
        min_len = PH_RPC_D_MIN_RX_LEN;
    } else
    {
        min_len = PH_RPC_D_MIN_RX_LEN;
    }

    return min_len;
}
