/*
*                  Copyright (c), NXP Semiconductors
*
*                     (C)NXP Semiconductors
*        All rights are reserved. Reproduction in whole or in part is
*       prohibited without the written consent of the copyright owner.
*   NXP reserves the right to make changes without notice at any time.
*  NXP makes no warranty, expressed, implied or statutory, including but
*  not limited to any implied warranty of merchantability or fitness for any
* particular purpose, or that the use will not infringe any third party patent,
*  copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* Project: RPC Device Library / ARM-Board for PN547 V&V.
* $Author: atp01705 $
* $Revision: 29472 $
* $Date: 2014-09-09 09:25:58 +0200 (mar., 09 sept. 2014) $
*
* Created: Feb. 2011 by Gerald Kersch-Koncar
*
*/

#ifndef PHRPC_D_H //
#define PHRPC_D_H //

// ________________________________________________________________________________________________
//
// Includes
// ________________________________________________________________________________________________

#include <stdint.h>
#include <stdlib.h>

#include "phRpc_Cmd_2.h"
#include "phRpc_Status.h"

// ________________________________________________________________________________________________
//
// Public Definitions
// ________________________________________________________________________________________________

/**
 * \addtogroup grp_rpc_dev
 * \brief RPC Device Functionality.
 *
 * The component implements the RPC protocol state machine on device side. It comprises the interface
 * to the USB, a protocol state machine, and interfaces to the RPC endpoints and the DPC component.
 *
 * @{
 */

/// Minimum host timeout in microseconds
#define PH_RPC_D_MIN_HOST_TIMEOUT_MICROSEC   ((uint32_t)PH_RPC_CMD_MIN_HOST_TIMEOUT_MILLISECONDS * 1000u)

// Where the entry call came from
#define PH_RPC_D_CALL_SOURCE_USB                  ((uint8_t)0)  ///< The request came from the USB
#define PH_RPC_D_CALL_SOURCE_SERIAL               ((uint8_t)1)  ///< The request came from the serial port

// RPC Function Classification
#define PH_RPC_D_RANGE_DIRECT_LOW              ((uint8_t)0x01)  ///< Direct calls (in context of USB task), lower limit
#define PH_RPC_D_RANGE_DIRECT_HIGH             ((uint8_t)0x0F)  ///< Direct calls (in context of USB task), upper limit
#define PH_RPC_D_RANGE_DEFER_F_LOW             ((uint8_t)0x10)  ///< Deferred Calls, device functions, lower limit
#define PH_RPC_D_RANGE_DEFER_F_HIGH            ((uint8_t)0xEF)  ///< Deferred Calls, device functions, upper limit
#define PH_RPC_D_RANGE_DEFER_CHK_LOW           ((uint8_t)0xF0)  ///< Deferred Calls, device self-check, lower limit
#define PH_RPC_D_RANGE_DEFER_CHK_HIGH          ((uint8_t)0xF9)  ///< Deferred Calls, device self-check, upper limit
#define PH_RPC_D_RANGE_UTST_LOW                ((uint8_t)0xFA)  ///< Unit Test - Do not use
#define PH_RPC_D_RANGE_UTST_HIGH               ((uint8_t)0xFF)  ///< Unit Test - Do not use

// Return codes
#define PH_RPC_D_STATUS_OK                        ((uint8_t)0)  ///< Status OK
#define PH_RPC_D_STATUS_ERROR                     ((uint8_t)1)  ///< An error has occurred
#define PH_RPC_D_STATUS_REPEAT                    ((uint8_t)2)  ///< Repeat request due to error or time-out

// TX completion codes
#define PH_RPC_D_TXCOMPLETION_OK                  ((uint8_t)0)  ///< TX completed successfully
#define PH_RPC_D_TXCOMPLETION_ERR                 ((uint8_t)1u) ///< TX encountered an error

// Direct, transparent communication mode for serial host interface
#define PH_RPC_D_SERIAL_DIRECT_NONE               ((uint8_t)0)  ///< Serial is not transparent and uses RPC protocol
#define PH_RPC_D_SERIAL_DIRECT_DNLD               ((uint8_t)1)  ///< Serial is transparent and uses Download Mode protocol
#define PH_RPC_D_SERIAL_DIRECT_NCI                ((uint8_t)2)  ///< Serial is transparent and uses NCI protocol
#define PH_RPC_D_SERIAL_DIRECT_NUM_MODES          ((uint8_t)3)  ///< Number of modes
// Direct, transparent communication command
#define PH_RPC_D_SERIAL_DIRECT_SEND               ((uint8_t)0)  ///< Send data
#define PH_RPC_D_SERIAL_DIRECT_RECEIVE            ((uint8_t)1)  ///< Request Receive and get data
#define PH_RPC_D_SERIAL_DIRECT_CMD_STATUS_POS     ((uint8_t)0)  ///< Position of the first command
#define PH_RPC_D_SERIAL_DIRECT_MIN_LENGTH_NCI     ((uint8_t)3)  ///< Length info in 3rd byte
#define PH_RPC_D_SERIAL_DIRECT_MIN_LENGTH_DNLD    ((uint8_t)2)  ///< Length info in first 2 bytes
#define PH_RPC_D_SERIAL_DIRECT_LENPOS_NCI         ((uint8_t)3)  ///< Length is at buffer[3]
#define PH_RPC_D_SERIAL_DIRECT_LENPOS_DNLD        ((uint8_t)1)  ///< Length is at buffer[1] and [2]

// ________________________________________________________________________________________________
//
// INTERNAL Definitions
// ________________________________________________________________________________________________

#define PH_RPC_D_DEFAULT_HOST_TIMEOUT         ((uint16_t)500u)  ///< \internal Default Timeout
#define PH_RPC_D_COMM_MAX_WTXTIMESPAN_MS      ((uint16_t)250u)  ///< \internal Default Timeout

// Hook Functions
#define PH_RPC_D_HOOKF_LEAVEMAIN                ((uint8_t)0x00) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_ENTERMAIN                ((uint8_t)0x01) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_PRE_DEFER_CALL           ((uint8_t)0x02) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_POST_DEFER_CALL          ((uint8_t)0x03) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_PRE_DIRECT_CALL          ((uint8_t)0x04) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_POST_DIRECT_CALL         ((uint8_t)0x05) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_ENTER_DISPATCH           ((uint8_t)0x06) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_LEAVE_DISPATCH           ((uint8_t)0x07) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_ENTER_DISPATCH_WAIT      ((uint8_t)0x08) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_LEAVE_DISPATCH_WAIT      ((uint8_t)0x09) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_ENTER_TX                 ((uint8_t)0x0A) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_LEAVE_TX                 ((uint8_t)0x0B) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_ENTER_TX_WAIT            ((uint8_t)0x0C) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_LEAVE_TX_WAIT            ((uint8_t)0x0D) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_ENTER_RX_ONGOING         ((uint8_t)0x0E) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_LEAVE_RX_ONGOING         ((uint8_t)0x0F) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_WTX_REQ                  ((uint8_t)0x10) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_WTX_CONF                 ((uint8_t)0x11) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_RESET                    ((uint8_t)0x12) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_RESET_LITTLE             ((uint8_t)0x13) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_RESET_ERROR              ((uint8_t)0x14) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_TXCOMPLETION             ((uint8_t)0x15) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_TXERROR                  ((uint8_t)0x16) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_RX_DISCARD               ((uint8_t)0x17) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_DISPATCH_COMPLETION      ((uint8_t)0x18) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_TX                       ((uint8_t)0x19) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_TXCOMPLETION_ERR         ((uint8_t)0x2A) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_TXCOMPLETION_PARTIAL     ((uint8_t)0x2B) ///< \internal Debug Hook
#define PH_RPC_D_HOOKF_TXCOMPLETION_PARTIAL_ERR ((uint8_t)0x2C) ///< \internal Debug Hook

// ________________________________________________________________________________________________
//
// BUFFER SIZES
// ________________________________________________________________________________________________

#define PH_RPC_D_COMM_WTXBUFSIZE                16u                                                         ///< \internal WTX Communication Buffer to prepend to IN BUF
#define PH_RPC_D_MIN_COMM_BUFSIZE               PH_RPC_H_MINDEVBUFLEN                                       ///< \internal Bulk I/O buffer size
#define PH_RPC_D_MIN_COMM_BUFSIZE_DEFAULT_MUL   PH_RPC_IOCTL_OPT_DEV_SETTRSZMUL_DEFAULT                     ///< \internal Bulk I/O buffer size default multiplier
#define PH_RPC_D_TOTAL_BUFSIZE(rpc__ctx)        (rpc__ctx->OutBufSize - 1u)                                 ///< \internal Total Buffer - guard bytes
#define PH_RPC_D_USER_BUFSIZE(rpc__ctx)         (PH_RPC_D_TOTAL_BUFSIZE(rpc__ctx) - 1u)                     ///< \internal Payload buffer max. fill

/// \brief provide the buffer size in OUT direction
#define PH_RPC_D_OUT_BUFSIZE(com__size) (com__size + 1u) // size + padding + guard bytes
/// \brief provide the buffer size in IN direction
#define PH_RPC_D_IN_BUFSIZE(com__size)  (PH_RPC_D_OUT_BUFSIZE(com__size) + PH_RPC_D_COMM_WTXBUFSIZE) // + wtx buf


#define PH_RPC_D_COMM_RCRESETBUFSIZE            16u                                                         ///< \internal RC Reset buffer default size


// ________________________________________________________________________________________________
//
// DELEGATES
// ________________________________________________________________________________________________

/**
 * \brief Defer a RPC Call
 *
 * Delegate to defer a RPC action from the fast USB task to a worker task. The function returns
 * immediately, leaving the processing up to the worker thread.
 *
 * \par Parameters
 * - Pointer to the component instance of type \ref phRpc_D_t.
 * - Pointer to user data stored within the instance of the RPC structure \ref phRpc_D_t and set by \ref phRpc_D_Init.
 * - Pointer to the request data
 * - Number of bytes in the request
 * - Pointer to a buffer that will receive the response
 * - Pointer to a location that holds the available number of bytes in the response buffer. When the
 *   deferred call completes, its implementation sets the value to the actual number of bytes returned.
 * .
 *
 * \par Return Values
 * - When the call succeeds, \b 0 is returned.
 * - The underlying function returns \b 1 on error.
 *
 */
typedef uint8_t (*pphRpc_D_Defer_t) (void*, void*, uint8_t*, uint16_t, uint8_t*, uint16_t*);

/**
 * \brief Cancel a deferred RPC Call
 *
 * Delegate to cancel a deferred RPC action. The function returns immediately, not waiting for the
 * worker task to actually cancel the ongoing action.
 *
 * \par Parameter
 * - Pointer to user data stored within the instance of the RPC structure \ref phRpc_D_t and set by \ref phRpc_D_Init.
 * .
 *
 * \par Return Values
 * - When the call succeeds, \b 0 is returned.
 * - The underlying function returns \b 1 on error.
 *
 */
typedef uint8_t (*pphRpc_D_Cancel_t) (void*, void*);

/**
 * \brief Delegate to Put Data into the TX FIFO.
 *
 * Delegate used to send back data. The interface to the USB, in direction to the host (IN) is fed
 * with data via this interface.
 *
 * \par Parameters
 * - Pointer to user data stored within the instance of the RPC structure \ref phRpc_D_t and set by \ref phRpc_D_Init.
 * - Pointer to the response data
 * - Number of bytes in the response
 * .
 *
 * \par Return
 * The actual number of bytes sent is returned by the underlying implementation.
 *
 */
typedef uint16_t (*pphRpc_D_Tx_t) (void*, void*, uint8_t*, uint16_t);

/**
 * \brief Reset the protocol
 *
 * Delegate to reset the communication protocol. The RPC component requests protocol reset
 * if an error condition has been detected.
 *
 * \par Parameter
 * - Pointer to user data stored within the instance of the RPC structure \ref phRpc_D_t and set by \ref phRpc_D_Init.
 * .
 *
 * \par Return Values
 * - When the call succeeds, \b 0 is returned.
 * - The underlying function returns \b 1 on error.
 *
 */
typedef uint8_t (*pphRpc_D_ResetProtocol_t) (void*, void*);

/**
 * \brief Delegate for Debug Hooks
 * Delegate used to debug the protocol. The hook function can be installed and will provide to its
 * implementation the information about the protocol status.
 *
 * \par Parameters
 * - Pointer to user data stored within the instance of the RPC structure \ref phRpc_D_t and set by \ref phRpc_D_Init.
 * - Identification of the processing stage. Please see the hook function definitions.
 * .
 *
 */
typedef void (*pphRpc_D_Hook_t) (void*, uint8_t);

/**
 * \brief Delegate for Timing
 * Delegate used to measure the time. It must be present and provided to the initialisation function.
 *
 * \par Parameters
 * - Pointer to user data stored within the instance of the RPC structure \ref phRpc_D_t and set by \ref phRpc_D_Init.
 * - Identification of the action performed:
 *   - 0: Start
 *   - 1: Stop
 *   .
 * .
 * - Pointer to a location that will receive the start time or the time difference respectively.
 *
 */
typedef void (*pphRpc_D_MeasTime_t) (void*, uint8_t, uint32_t*);

/**
 * \brief Delegate to build WTX
 *
 * \par Parameters
 * - Serialisation Buffer
 * - Serialisation Buffer Length
 * - Status
 * .
 *
 * \retval  0 Success
 * \retval  1 Error
 *
 */
typedef uint8_t (*pphRpc_D_BuildWtx_t)(uint8_t*, uint16_t*, uint16_t);

/**
 * \brief Delegate: Sequence Number Setter
 *
 * \par Parameters
 * - Serialisation Buffer
 * - Sequence number
 * .
 *
 * \retval  0 Success
 * \retval  1 Error
 *
 */
typedef uint8_t (*pphRpc_D_SetSeqNum_t)(uint8_t*, uint8_t );

/**
 * \brief Delegate to set the number of bytes
 *
 * \par Parameters
 * - Serialisation Buffer
 * - Serialisation Buffer Length
 * .
 *
 */
typedef void (*pphRpc_D_SetNumBytes_t)(uint8_t *, uint16_t);

/**
 * \brief Delegate receiving WTX sent by the host
 *
 * \par Parameters
 * - Serialisation Buffer
 * - Serialisation Buffer Length
 * - Cancel flag
 * .
 *
 * \retval  0 Success
 * \retval  1 Error
 *
 */
typedef uint8_t (*pphRpc_ReceiveWtx_t)(uint8_t*, uint16_t, uint8_t*);

/**
 * \brief Delegate to get the number of bytes encoded into the message header
 *
 * \par Parameters
 * - Serialisation Buffer
 * .
 *
 * \return  Number of bytes comprised in the message
 *
 */
typedef uint16_t (*pphRpc_D_GetNumBytes_t)(uint8_t*);

/**
 * \brief Delegate to get the Function ID encoded into the message header
 *
 * \par Parameters
 * - Serialisation Buffer
 * .
 *
 * \return Function ID, FID
 *
 */
typedef uint16_t (*pphRpc_D_GetFid_t)(uint8_t*);

/**
 * \brief Delegate to get the Sequence Number encoded into the message header
 *
 * \par Parameters
 * - Serialisation Buffer
 * .
 *
 * \return Function ID, FID
 *
 */
typedef uint8_t (*pphRpc_D_GetSeqNum_t)(uint8_t*);

/**
 * \brief Delegate to get the Sequence Number encoded into the message header
 *
 * \par Parameters
 * - RPC component context
 * - RX buffer
 * - Length of the RX buffer
 * - TX buffer
 * - Length of the TX buffer
 * .
 *
 * \return Function ID, FID
 *
 */
typedef uint8_t (*phRpc_D_Dispatch_t)(void*, uint8_t*, uint16_t , uint8_t*, uint16_t*);

// ________________________________________________________________________________________________
//
// TYPES
// ________________________________________________________________________________________________

/**
 * \brief Debug Information
 * \internal
 */
typedef struct phRpc_D_Debug
{
    // Error counters and info
    uint32_t    TX_0;                               // TX state entered with no bytes to send
    uint32_t    TX_Ovr;                             // TX state re-entered in TX length overflow condition
    uint32_t    RX_Discarded;                       // How many RX frames have been discarded
    uint32_t    RX_LastDataDiscarded;               // Start of the buffer that has been discarded last
    uint8_t     RX_Discard_TxState;                 // Last State of the TX RPC when packets were discarded
    uint8_t     RX_Discard_RxState;                 // last State of the RX RPC when packets were discarded
    // Debug
    uint32_t    RX_LastData;                        // Start of the buffer that has been successfully received last
    uint32_t    CommCheckResDelay;                  // Communication check: Response Waiting Time in µs: Delay response
    uint8_t     RecentFid;                          // Most recent Function ID (for both TX and RX)
    uint8_t     DbgNumSent;                         // Number of bytes sent
    uint8_t     DbgNumRequest;                      // How often a command was dispatched
    uint8_t     DbgNumResponse;                     // How often a response was sent
} phRpc_D_Debug_t;

/**
 * \brief RPC Delegate Structure
 *
 * The structure contains pointers to delegate functions.
 *
 */
typedef struct phRpc_D_Delegates
{
    // RPC/DPC Related:
    pphRpc_D_Defer_t            Defer;              // Delegate to defer the RPC
    pphRpc_D_Cancel_t           Cancel;             // Delegate to cancel a deferred RPC
    pphRpc_D_Tx_t               Tx;                 // Delegate to send data
    pphRpc_D_ResetProtocol_t    ResetP;             // Delegate to reset an external protocol component
    pphRpc_D_MeasTime_t         TimingFunction;     // Delegate for the timing function
    pphRpc_D_Hook_t             Hook;               // [Optional] Delegate as Hook on internal events
    // Serialisation and Dispatch Related:
    pphRpc_D_BuildWtx_t         BuildWtx;            // Delegate to build the WTX
    pphRpc_D_SetSeqNum_t        SetSeqNum;          // Delegate to set Sequence Number
    pphRpc_D_SetNumBytes_t      SetNumBytes;        // Delegate to set number of bytes
    pphRpc_ReceiveWtx_t         ReceiveWtx;         // Delegate to receive WTX
    pphRpc_D_GetNumBytes_t      GetNumBytes;        // Delegate to get the number of bytes
    pphRpc_D_GetFid_t           GetFid;             // Delegate to get Function ID
    pphRpc_D_GetSeqNum_t        GetSeqNum;          // Delegate to get Sequence Number
    phRpc_D_Dispatch_t          Dispatch;           // Delegate for direct Dispatch
} phRpc_D_Delegates_t;

/**
 * \brief RPC Component Structure
 *
 * The structure contains all data, buffer state variables and the like for RPC operation.
 * Provided to every RPC function as its first parameter, the need of globals is eliminated.
 *
 */
typedef struct phRpc_D
{
    // Communication related
    uint8_t    *InBufWtx;                           // Total OUTgoing buffer incl. prepended WTX
    uint8_t    *OutBuf;                             // Total INcoming buffer (IN/OUT = Host View)
    uint16_t    InBufWtxSize;                       // Total buffer size, including WTX space
    uint16_t    InBufSize;                          // Partial IN buffer, data frame only (not including WTX buffer which is just before)
    uint16_t    OutBufSize;                         // Total buffer size
    uint8_t    *InBuf;                              // Partial OUTgoing buffer (IN/OUT = Host View) w/o WTX
    uint16_t    OutLen;                             // Number of bytes received (again HOST View..)
    uint16_t    InLen;                              // Number of bytes to send  (..same here and further on)
    uint16_t    PrevInLen;                          // Previous number of bytes to send (repeat handling)
    uint16_t    DeferInLen;                         // Used for dispatcher; Will be copied to InLen before TX
    uint16_t    NumSent;                            // Number of bytes sent
    uint16_t    TargetRxLength;                     // How many bytes to expect
    uint8_t     PadPlus1;                           // Pad 1 beyond a block size
    uint8_t     VarLenRpcEnable;                    // Variable length buffer RPC is enabled
    uint8_t     PadMul;                             // Pad to multiples of a block size
    uint8_t     NumBytesToSendMul;                  // The minimum block size times this value is allowed to be sent at once.
    uint8_t     RecentCaller;                       // Via which interface came the last request?

    // State specific
    uint8_t     TxState;                            // State of the RPC
    uint8_t     RxState;                            // State of the RPC
    uint8_t     DispatchDone;                       // Indicates Dispatch completion
    uint8_t     TxComplete;                         // TX is complete
    uint8_t     HostSequenceNumber;                 // Sequence number that the host uses
    uint8_t     EpStatus;                           // Status of last endpoint action
    uint8_t     InWtx;                              // Currently handling WTX

    // Component Timing
    uint32_t    TRxTimeout;                         // Period in µs that will time the TX/RX state out
    uint32_t    HostTimeout;                        // Time-out of the host in microsec
    uint32_t    DispatchTimer;                      // Timer for dispatched call
    uint32_t    TxTimer;                            // Timer for transmit handling
    uint32_t    RxTimer;                            // Timer for receive handling
    uint32_t    HostTimeoutCount;                   // WTX handling timeout count
    uint32_t    WtxTimeout;                         // WTX timeout counter
    uint32_t    IntervalMicrosec;                   // Cycle time for Main call in microsec

    // Delegates
    phRpc_D_Delegates_t *Delegates;                 // Pointer to the "Delegates" structure instance
    void                *UserData;                  // Pointer that can be set to any user context

    // Debug Variables
    phRpc_D_Debug_t     DebugInformation;           // Debug information and Error counters

    #ifdef TESTSUITE
    void               *TestData;                   // Arbitrary, test-related pointer
    #endif
} phRpc_D_t;


// ________________________________________________________________________________________________
//
// API
// ________________________________________________________________________________________________

/**
 * \brief RPC Device Init Function
 *
 * The RPC component is initialised with this function. No other function of the component must be called
 * before.
 *
 * \param[in] rpcCx                     Pointer to the non-initialised instance of \ref phRpc_D_t.
 * \param[in] delegateFunctions         Pointer to the delegate struct
 * \param[in] userData                  Pointer to the delegate user data. Arbitrary data that the delegates can use.
 * \param[in] trxTimeoutMicrosec        TX/RX timeout in microseconds. When it expires, the protocol resets itself.
 * \param[in] dispatchTimeoutMicrosec   Dispatch/Defer timeout in microseconds. When it expires, the protocol resets itself.
 * \param[in] intervalMicrosec          Interval times (cycle time) for calls to \ref phRpc_D_Main. This value is used for timeout handling.
 * \param[in] inBuf                     Pointer to a sufficiently large IN buffer memory block. Use \ref PH_RPC_D_IN_BUFSIZE to determine its size.
 * \param[in] inBufSize                 Size of the entire USB IN buffer.
 * \param[in] outBuf                    Pointer to a sufficiently large OUT buffer memory block. Use \ref PH_RPC_D_OUT_BUFSIZE to determine its size.
 * \param[in] outBufSize                Size of the entire USB OUT buffer.
 *
 * \retval 0 The call was successful.
 * \retval 1 An error has occurred.
 *
 * \todo Init struct instead of long parameter list?
 *
 */
uint8_t phRpc_D_Init(phRpc_D_t                 *rpcCx,
                     phRpc_D_Delegates_t       *delegateFunctions,
                     void                      *userData,
                     uint32_t                   trxTimeoutMicrosec,
                     uint32_t                   intervalMicrosec,
                     uint8_t                   *inBuf,
                     uint16_t                   inBufSize,
                     uint8_t                   *outBuf,
                     uint16_t                   outBufSize);

/**
 * \brief RPC Protocol Reset Function
 *
 * Reset the RPC protocol.
 *
 * \param[in] rpcCx Pointer to the initialised instance of \ref phRpc_D_t.
 *
 * \retval 0 The call was successful.
 * \retval 1 An error has occurred.
 *
 */
uint8_t phRpc_D_Reset(phRpc_D_t *rpcCx);

/**
 * \brief RPC Communication Options Setter
 *
 * Set the communication options. The host can call this function through RPC when it needs to
 * change or initially set the communication parameters.
 *
 * \param[in] rpcCx     Pointer to the initialised instance of \ref phRpc_D_t.
 * \param[in] comParam  With the LSB set, the host instructs the device to add one byte if the length
 *                      of the response is a multiple of 64. On some hosts such a number cannot be
 *                      cleanly processed, leading to spurious timeout events.
 * \param[in] msTimeout Timeout of the host library. The device must know about timeout conditions
 *                      of the host to handle timeout extension.
 *
 * \retval 0 The call was successful.
 * \retval 1 An error has occurred.
 *
 */
uint8_t phRpc_D_SetComOptions(phRpc_D_t *rpcCx, uint32_t comParam, uint16_t msTimeout);

/**
 * \brief Set the Response Waiting Time \b Once
 *
 * This is a test/debug function. It can be used for a special type of function (Communication Check)
 * to test the host protocol timeout-handling. The parameter for waiting time delays the response for
 * a certain number of milliseconds. The host can access the function via RPC. The setting is valid
 * for the following communication cycle only, after that it is automatically reset.
 *
 * \param[in] rpcCx     Pointer to the initialised instance of \ref phRpc_D_t.
 * \param[in] msWait    Response delay in milliseconds.
 *
 * \retval 0 The call was successful.
 * \retval 1 An error has occurred.
 *
 */
uint8_t phRpc_D_SetResWaitingTimeOnce(phRpc_D_t *rpcCx, uint8_t msWait);

/**
 * \brief RPC Device Receive Function
 *
 * The cummunication stack calls this function in a loop for each byte it receives. The function runs in
 * interrupt context of the communication device. It checks, as being called, how many bytes it shall receive and how
 * many bytes it has already received. When reception completes, the function starts the dispatching
 * part of the RPC component. The function is suitable for character- and block-oriented transfer media.
 *
 * \param[in] rpcCx         Pointer to the initialised instance of \ref phRpc_D_t.
 * \param[in] buf           Buffer (data fragment, frame) provided by the interface.
 * \param[in] bufLen        Buffer length, number of bytes provided.
 * \param[in] callerComp    Who has called this function. See \ref PH_RPC_D_CALL_SOURCE_USB.
 *
 * \retval 0 The call was successful.
 * \retval 1 An error has occurred.
 *
 */
uint8_t phRpc_D_Receive(phRpc_D_t *rpcCx, uint8_t *buf, size_t bufLen, uint8_t callerComp);

/**
 * \brief RPC Complete Dispatcher Call. Used by the endpoint to indicate that data is ready.
 *
 * Endpoint calls are either direct or deferred. The endpoint needs to call this function in order
 * to trigger transmission of the returned data.
 *
 * \param[in] rpcCx     Pointer to the initialised instance of \ref phRpc_D_t.
 * \param[in] status    Completion status: \b 0 means successful, \b 1 means that an error has occurred.
 *
 * \retval 0 The call was successful.
 * \retval 1 An error has occurred.
 *
 * \note When the function is not called by the endpoint, the RPC component times out on Dispatch and
 *       will not transmit any data. Rather, it will reset the component.
 *
 */
uint8_t phRpc_D_DispatchCompletion(phRpc_D_t *rpcCx, uint8_t status);

/**
 * \brief Complete TX. Used by the communication component (USB, Serial) to tell that all data has been sent.
 *
 * When the transmission is over, the call to this function causes the component to accept further requests or
 * to advance the send state to the transmission of another packet, if applicable.
 *
 * \param[in] rpcCx     Pointer to the initialised instance of \ref phRpc_D_t.
 * \param[in] txStatus  TX completion status, see \ref PH_RPC_D_TXCOMPLETION_OK.
 * \param[in] numSent   Number of bytes sent.
 *
 * \retval 0 The call was successful.
 * \retval 1 An error has occurred.
 *
 * \note When the function is not called the component times out on TX and will reset itself.
 *
 */
uint8_t phRpc_D_TXCompletion(phRpc_D_t *rpcCx, uint8_t txStatus, uint16_t numSent);

/**
 * \brief Set Packet Size Multiplier
 *
 * The maximum number of 64 byte packets to send via the communication link. This can be used to
 * reduce the interrupt load and/or bus load. The lower the number, the more discrete transfers
 * will be required per transmission. The advantage of a lower number is that the ISR is blocked for
 * less time.
 *
 * \param[in] rpcCx     Pointer to the initialised instance of \ref phRpc_D_t.
 * \param[in] sizeMul   Size Multiplier.
 *
 * \retval 0 The call was successful.
 * \retval 1 An error has occurred.
 *
 *
 */
uint8_t phRpc_D_SetTxPacketSizeMul(phRpc_D_t *rpcCx, uint8_t sizeMul);

/**
 * \brief RPC Timing Function
 *
 * \param[in] rpcCx     Pointer to the initialised instance of \ref phRpc_D_t.
 *
 */
uint8_t phRpc_D_Main(phRpc_D_t *rpcCx);

/**
 * \brief RPC Getter function for variable-buffer enable state
 *
 * \param[in] rpcCx     Pointer to the initialised instance of \ref phRpc_D_t.
 *
 */
uint8_t phRpc_D_GetVarRpcEnableState(phRpc_D_t *rpcCx);

// ________________________________________________________________________________________________
//
// INTERNAL FUNCTIONS
// ________________________________________________________________________________________________

/**
 * \internal
 * \brief RPC Device Dispatch Entry Point
 *
 * Upon successful reception, this function is called by the protocol. It will call the dispatcher to
 * the device functions.
 *
 *
 * \note: This is no API function of the component. The first parameter is not the component instance,
 *        rather it is the user pointer.
 *
 */
uint8_t phRpc_D_Entry(phRpc_D_t *rpcCx, void *userData, uint8_t *rpcRxBuf, uint16_t rpcRxBufLen, uint8_t *rpcTxBuf, uint16_t *rpcTxBufLen);

/** @} */

#endif // Guard
