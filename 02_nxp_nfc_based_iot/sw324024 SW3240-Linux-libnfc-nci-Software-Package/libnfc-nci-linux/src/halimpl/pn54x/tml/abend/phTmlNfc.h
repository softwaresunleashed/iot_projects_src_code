/*
*                     Copyright ©, NXP Semiconductors
*
*                       ©NXP Semiconductors N.V.2009
*         All rights are reserved. Reproduction in whole or in part is
*        prohibited without the written consent of the copyright owner.
*    NXP reserves the right to make changes without notice at any time.
*   NXP makes no warranty, expressed, implied or statutory, including but
*   not limited to any implied warranty of merchantability or fitness for any
*  particular purpose, or that the use will not infringe any third party patent,
*   copyright or trademark. NXP must not be liable for any loss or damage
*                            arising from its use.
*
*/

/**
* \file : phTmlNfc.h
*
* \Abstract:
*
*  Transport Mapping Layer header files containing APIs related to Initializing, reading
*  and writing data into the files provided by the driver interface.
*
* \Environment:
*
*   user mode only
*
* \Revision History:
* 
* \note API listed here encompasses Transport Mapping Layer interfaces required to be mapped
* to different Interfaces and Platforms.
*/

#ifndef PHTMLNFC_H
#define PHTMLNFC_H

/* \addtogroup grp_tml_nfc
 * @{
 */

/*
************************* Include Files ****************************************
*/
#include <phNfcCommon.h>
//PA
#include <pthread.h>
/*
****************************** Macro Definitions ******************************
*/

/** \addtogroup grp_tml_rw
 * @{
 */

/**
 * Message posted by Reader thread upon
 * completion of requested operation */
#define PH_TMLNFC_READ_MESSAGE              (0xAA)

/**
 * Message posted by Writer thread upon
 * completion of requested operation */
#define PH_TMLNFC_WRITE_MESSAGE             (0x55)

/** @} */

/** \internal
 * Value indicates to reset device.*/
#define PH_TMLNFC_RESETDEVICE               (0x00008001)

/** 
* Tml write and read buffer size */ 
#define PHTMLNFC_MAX_TXRX_BUFFER_SIZE            (260U)
/** 
 * Max user Tx buffer size */ 
#define PHTMLNFC_MAX_TX_USER_BUFF_SIZE          (PHTMLNFC_MAX_TXRX_BUFFER_SIZE)

/** 
* Tml write and read buffer size */ 
#define PHTMLNFC_MAX_TXRX_BUFFER_SIZE            (260U)   

/** 
 * Tml read buffer size */ 
#define PHTMLNFC_READ_BUFFER_SIZE               (PHTMLNFC_MAX_TXRX_BUFFER_SIZE) 

/** 
 * Tml write buffer size */ 
#define PHTMLNFC_WRITE_BUFFER_SIZE              PHTMLNFC_MAX_TXRX_BUFFER_SIZE


/* TODO: Need to remove, used in DTA code*/
#define LENGTH_COMPORTSTR       128

#define PIN_STABILIZATION_DELAY             (50)

#define PHTMLNFC_MAXTIME_RETRANSMIT         (500U)           /**<  Duration of Timer to wait after sending an Nci packet */

#define PHTMLNFC_MAXTIMEOUT_THREADSCREATE   (2000U)          /**<  Duration of Timer to wait after sending an Nci packet */

#define PH_TMLNFC_RESET_VALUE               (0x00)           /**<  Value to reset variables of TML  */

#define PH_TMLNFC_VALUE_ONE                 (0x01)           /**<  Indicates a Initial or offset value */

#define PH_TMLNFC_DEFAULT_RETRYCOUNT        (0x03)           /**<  Default value of Retry Count */

/**<  Flag attributes required during Clearing of serial port */
//#define PHTMLNFC_PURGE_FLAGS                (PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR)

/* See: NFCC3022: Defer VEN Reset if there is any IO activity pending */
#define PHTMLNFC_DEFER_VEN_RESET            (1)
/**
 * Transaction (Tx/Rx) completion information structure of TML
 *
 * This structure holds the completion callback information of the
 * transaction passed from the TML layer to the Upper layer
 * along with the completion callback.
 *
 * The value of field <code>wStatus</code> can be interpreted as:
 *
 *     - #NFCSTATUS_SUCCESS                    Transaction performed successfully.
 *     - #NFCSTATUS_FAILED                     Failed to wait on Read/Write operation.
 *     - #NFCSTATUS_INSUFFICIENT_STORAGE       Not enough memory to store data in case of read.
 *     - #NFCSTATUS_BOARD_COMMUNICATION_ERROR  Failure to Read/Write from the file or timeout.
 */
typedef struct phTmlNfc_TransactInfo
{
    NFCSTATUS           wStatus;    /**< Status of the Transaction Completion*/
    uint8_t            *pBuff;      /**< Response Data of the Transaction*/
    uint16_t            wLength;    /**< Data size of the Transaction*/
	/*CG*/
    void               *message;    /**< Hold message pool object */
    uint32_t 		   messageType;
	/*End CG*/
}phTmlNfc_TransactInfo_t;           /**< Instance of Transaction structure */

/**
 * Enum definition contains  supported ioctl control codes.
 *
 * \sa phTmlNfc_IoCtl
 */
typedef enum
{
    phTmlNfc_e_Invalid      = 0,                        /** \internal */
    phTmlNfc_e_ResetDevice  = PH_TMLNFC_RESETDEVICE,    /**< Reset the device */
    phTmlNfc_e_EnableDownloadMode,                      /**< Do the hardware setting to enter into download mode */
    phTmlNfc_e_EnableNormalMode,                        /**< Hardware setting for normal mode of operation */
    phTmlNfc_e_PowerOff,                                /**< Do hardware setting to Power Off the chip */
    phTmlNfc_e_PowerOn                                  /**< Do hardware setting to Power On the chip */
} phTmlNfc_ControlCode_t ;                              /**< Control code for IOCTL call */

/** @} */


/** \addtogroup grp_tml_cfg
 * @{
 */

/**
 * TML Configuration exposed to upper layer.
 */
typedef struct phTmlNfc_Config
{
    /** Portname connected to PN547
     *
     * Platform specific canonical device name to which PN547 is connected.
     *
     * e.g. On Linux based systems this would be <code>/dev/pn547</code> */
    int8_t         *pDevName;
    /** Callback Thread ID
     *
     * This is the thread ID on which the Reader & Writer thread posts message. */
    uintptr_t        dwGetMsgThreadId;
    /** Communication speed between DH and PN547
     *
     * This is the baudrate of the bus for communication between DH and PN547 */
    uint32_t        dwBaudRate;
} phTmlNfc_Config_t,*pphTmlNfc_Config_t;    /**< pointer to ref \ref phTmlNfc_Config_t */



typedef enum
{
    I2C_FRAGMENATATION_DISABLED,     /*i2c fragmentation_disabled           */
    I2C_FRAGMENTATION_ENABLED      /*i2c_fragmentation_enabled          */
} phTmlNfc_i2cfragmentation_t;

/**
 * TML Deferred callback interface structure invoked by Upper layer
 *
 * This could be used for read/write operations
 *
 * \param[in] dwMsgPostedThread Message source identifier
 * \param[in] pParams Parameters for the deferred call processing */
typedef  void (*pphTmlNfc_DeferFuncPointer_t) (uint32_t dwMsgPostedThread,void *pParams);

/**
 * Tml Deferred Callback structure used to invoke Upper layer Callback function.
 */
typedef struct
{
    pphTmlNfc_DeferFuncPointer_t    pDef_call; /**<Deferred callback function to be invoked */
    /** Source identifier
     *
     * Identifier of the source which posted the message. */
    uint32_t                        dwMsgPostedThread;
    /** Actual Message
     *
     * This is passed as a parameter passed to the deferred callback function pDef_call. */
    void                           *pParams;
} phTmlNfc_DeferMsg_t;                      /**< DeferMsg structure passed to User Thread */


/*
 * TML transreceive completion callback to Upper Layer
 *
 * \param[in] pContext Context provided by upper layer
 * \param[in] pInfo Transaction info. See \ref phTmlNfc_TransactInfo
 */
typedef void (*pphTmlNfc_TransactCompletionCb_t) (void *pContext,
						    phTmlNfc_TransactInfo_t *pInfo);

typedef enum phPinType
{
    PIN_TYPE_GPIO4  = 0x00,
    PIN_TYPE_VEN   = 0x01
} phPinType_t;

typedef enum phPinStatus
{
    PIN_STATUS_LOW  = 0x00,
    PIN_STATUS_HIGH   = 0x01
} phPinStatus_t;


/**
 *
 * This API allows to Initialize the TML layer and the Hardware interface.
 * This function configures the given Hardware Interface and
 * sends the HANDLE to the caller.
 *
 * \param[in]       pConfig    TML configuration details as provided
 *                             by the upper layer.
 *
 * \retval #NFCSTATUS_SUCCESS                    Initialization happened successfully.
 * \retval #NFCSTATUS_INVALID_PARAMETER          At least one parameter of the function
 *                                              is invalid.
 * \retval #NFCSTATUS_FAILED                     Initialization failed(example.unable to
 *                                              open HW Interface).
 * \retval #NFCSTATUS_INVALID_DEVICE             The device has not been opened or
 *                                              has been disconnected.
 */
NFCSTATUS phTmlNfc_Init( pphTmlNfc_Config_t pConfig);

/**
 *
 * This API allows to DeInitialize the TML layer and the HardWare interface.

 * \retval #NFCSTATUS_SUCCESS            TML Configuration Released successfully.
 * \retval #NFCSTATUS_INVALID_PARAMETER  At least one parameter of the function is invalid.
 * \retval #NFCSTATUS_FAILED             Deinitialization failed(example: Unable to close interface).
 *
 */
NFCSTATUS phTmlNfc_Shutdown();

/**
 *
 * Allows to write a data block to HardWare Interface.
 *
 * This asynchronous function writes the given block of data to the driver.
 * This interface enables writer thread in case there is no write requests pending and returns
 * successfully once writer thread completes write operation. It notifies upper layer using callback
 * mechanism.
 *
 * \param[in]  pContext             Context provided by the upper layer.
 * \param[in]  pBuffer              data to be sent
 * \param[in]  wLength              The length of data buffer
 * \param[in]  pTmlWriteComplete    Pointer to the function to be invoked on completion
 *                                  of Write Operation.
 *
 * \retval #NFCSTATUS_PENDING If the command is yet to be process
 * \retval #NFCSTATUS_INVALID_PARAMETER At least one parameter of the function is invalid.
 * \retval #NFCSTATUS_BUSY A Write request is already in progress.
 *
 * \note
 *   -# It is important to post a message with id #PH_TMLNFC_WRITE_MESSAGE to IntegrationThread after a data has been writtern to the PN547.
 *   -# If CRC needs to be computed, then input buffer should be capable to store two more bytes apart from length of packet.
 *
 *
 */
NFCSTATUS phTmlNfc_Write(   uint8_t *pBuffer, uint16_t wLength ,
			    pphTmlNfc_TransactCompletionCb_t pTmlWriteComplete,  void *pContext);

/**
 *
 * Allows to Read data block from HW Interface.
 *
 * This asynchronous function reads the data from the driver in which length
 * to be read and the buffer are sent by upper layer. This interface enables
 * reader thread in case there is no read requests pending and returns sucessfully.
 * Once read operation is complete, it notifies  to upper layer through callback
 * mechanism
 *
 * \param[in]  pContext             Context provided by the upper layer.
 * \param[in,out]  pBuffer          Location to send read data to the upper layer via the callback
 * \param[in]  wLength              The length of pBuffer given by the upper layer
 * \param[in]  pTmlReadComplete     Pointer to the function to be invoked on completion
 *                                  of Read operation.
 *
 * \retval #NFCSTATUS_PENDING               If the command is yet to be processed.
 * \retval #NFCSTATUS_INVALID_PARAMETER     At least one parameter of the function
 *                                          is invalid.
 * \retval #NFCSTATUS_BUSY                  A Read request is already in progress.
 *
 * \note
 *    -# It is important to post a message with id #PH_TMLNFC_READ_MESSAGE to IntegrationThread after a data has been read from the PN547
 *    -# Reader thread notifies upper layer callback by posting message on the caller's message queue
 *    -# pBuffer would be over-written as part of the call back.  When this function returns pBuffer still has no data
 *
 */
NFCSTATUS phTmlNfc_Read(    uint8_t *pBuffer, uint16_t wLength,
			    pphTmlNfc_TransactCompletionCb_t pTmlReadComplete,  void *pContext);


/**
 *
 * Aborts the pending write request (if any)
 *
 * \retval #NFCSTATUS_SUCCESS                Ongoing Write operation Aborted.
 * \retval #NFCSTATUS_INVALID_PARAMETER      At least one parameter of the function
 *                                          is invalid.
 * \retval #NFCSTATUS_NOT_INITIALISED        TML layer is not initialized.
 * \retval #NFCSTATUS_BOARD_COMMUNICATION_ERROR  Unable to Cancel Write operation.
 *
 */
NFCSTATUS phTmlNfc_WriteAbort();

/**
 *
 * Aborts the pending read request (if any)
 *
 * \retval #NFCSTATUS_SUCCESS               Ongoing Read operation Aborted.
 * \retval #NFCSTATUS_INVALID_PARAMETER     At least one parameter of the function
 *                                          is invalid.
 * \retval #NFCSTATUS_NOT_INITIALISED TML layer is not initialized.
 * \retval #NFCSTATUS_BOARD_COMMUNICATION_ERROR Unable to Cancel Read operation.
 *
 */
NFCSTATUS phTmlNfc_ReadAbort();


/**
 *
 * This API allows to reset the device.
 *
 * This function resets the device when insisted by the upper layer.
 * \note This function shall also be used for other operations which is under discussion.
 *
 * \param[in]       eControlCode   Control code for a specific operation. (See \ref phTmlNfc_ControlCode_t )
 *
 * \retval #NFCSTATUS_SUCCESS       Ioctl Cmd completed successfully.
 * \retval #NFCSTATUS_FAILED        Ioctl Cmd.request failed
 *
 */
NFCSTATUS phTmlNfc_IoCtl(phTmlNfc_ControlCode_t eControlCode);

/** @} */

/** \addtogroup grp_tml_rtx
 * @{ */

/**
 * Eanable / Disable Re-Transmission of Packets
 *
 * \sa phTmlNfc_ConfigNciPktReTx
 */
typedef enum
{
    phTmlNfc_e_EnableRetrans    = 0x00, /**<Enable retransmission of Nci packet */
    phTmlNfc_e_DisableRetrans   = 0x01  /**<Disable retransmission of Nci packet */
} phTmlNfc_ConfigRetrans_t ;            /**< Configuration for Retransmission */

/**
**Structure containing details related to read and write operations.
*
*/
typedef struct phTmlNfc_ReadWriteInfo
{
    uint8_t                              bEnable;           /**<This flag shal decide whether to perform Write/Read operaiton */
    uint8_t                              bThreadBusy;       /**<Flag to indicate thread is busy on respective operation */
    pphTmlNfc_TransactCompletionCb_t     pThread_Callback;  /** Transaction completion Callback function */
    void                                *pContext;          /**<Context passed while invocation of operation */
    uint8_t                             *pBuffer;           /**<Buffer passed while invocation of operation */
    uint16_t                             wLength;           /**<Length of data read/written */
    NFCSTATUS                            wWorkStatus;       /**<Status of the transaction performed */
}phTmlNfc_ReadWriteInfo_t;

/**
*
* This function Clears all Handles opened during TML Initialization.
*
* \param[in] None.
*
* \retval None.
*
*/
static void phNfcTml_CleanUp();

/**
*
* This function is invoked by upper layer thread upon successful read
or write operation
*
* \param[in] dwMsgPostedThread     Thread ID which posted message.
* \param[in] pParams               Parameter passed to the function.
*
* \retval none
*
*/
static void phNfcTml_DeferredCb (/*uint32_t dwMsgPostedThread,*/ void  *pParams);

/**
*
* This function posts message on upper layer thread upon successful read
*        or write operation
*
* \param[in] dwThreadId    Thread ID which is posting message.
* \param[in] ptWorkerMsg   Pointer to Message to be posted.
*
* \retval none
*
*/
void phTmlNfc_DeferredCall(uint32_t dwThreadId,phLibNfc_Message_t * /*phOsalNfc_Message_t **/ptWorkerMsg);

/**
*
* This function writes the requested data onto the lower layer driver.
*
* \param[in] pParam    Parameter to the Writer thread function.
* \retval none
*
*/
void *phNfcTml_TmlThread(void* pContext);

/**
*
* This function retransmits Nci packet if Retry Count has reached its limit.
*
* Parameters used are -
*
* dwTimerId -> Timer used to retransmit nci packet
* pContext -> Pointer to context
*/
static void NfcCommon_ReTxTimerCb(uint32_t dwTimerId,void *pContext);

//PA: compilator warning
#if PA
/**
*
* This function is used to start Timer once Nci packet is sent
*
* No parameters are passed to this function* 
*
* \retval NFCSTATUS
*
*/
static NFCSTATUS phNfcTml_InitiateTimer();
#endif /*PA*/

/**
* This function is used to Enable / Disable Re-Transmission of NCI Packets
*
* Parameters used are -
*
*  eConfig -> Configuration for Retransmission
*  bRetryCount -> Retry count
*  
* \retval NoOfBytesRead
*
*/
static void phNfcTml_ConfigNciPktReTx( phTmlNfc_ConfigRetrans_t eConfig,
					     uint8_t bRetryCount);

/**
**Base Context Structure containing members required for entire session.
*
*/
/* TODO: Refactoring not complete*/
/* TODO : file name is not changed to comman since this header included in LibNfc source to be reworked */
typedef struct phTmlNfc_Context
{
    void                       *hThread;                /**< Handle to the thread which handles write and read operations */
    uint8_t                     bThreadDone;            /**< Flag to decide whether to run or abort the thread */
    phTmlNfc_ConfigRetrans_t    eConfig;                /**< Retransmission of Nci Packet during timeout */
    uint8_t                     bRetryCount;            /**< Number of times retransmission shall happen */
    uint32_t                    dwTimerId;              /**< Timer used to retransmit nci packet */
    phTmlNfc_ReadWriteInfo_t    tReadInfo;              /**< Pointer to Reader Thread Structure */
    phTmlNfc_ReadWriteInfo_t    tWriteInfo;             /**< Pointer to Writer Thread Structure */
    void*                      pDevHandle;             /**< Pointer to Device Handle */
    uintptr_t                    dwCallbackThreadId;     /**< Thread ID to which message to be posted */
    uint8_t                     bEnableCrc;             /**< Flag to validate/not CRC for input buffer */
    uint8_t                     uiLpcI2cAddress;
#if PHTMLNFC_DEFER_VEN_RESET
    bool_t                      bVENResetRequested;     /**< Do a VEN Reset */
    bool_t                      bVENOffRequested;       /**< Turn Off VEN */
    bool_t                      bVENOnRequested;        /**< Turn On VEN */
    void*                     hResetVENEvent;
#endif
    uint8_t                     wFlag;
    uint8_t                     bCurrentRetryCount;
    phTmlNfc_Config_t           tTmlNfcConfig;

    void*                     hReadWriteEvent;
    void*                      hThreadEvent;
    pthread_t                   twWriteReadWorker;
	/*AL*/
    void*                     csTmlAccessLock;
	/*End AL*/

    phTmlNfc_TransactInfo_t tWriteTransactionInfo ;     /**< Transaction info buffer to be passed to Callback Thread */
    phTmlNfc_DeferMsg_t     tWriteDeferredInfo ;        /**< Structure containing Tml callback function and parameters to be invoked
							  by the callback thread */
    phTmlNfc_TransactInfo_t tReadTransactionInfo;       /**< Transaction info buffer to be passed to Callback Thread */
    phTmlNfc_DeferMsg_t     tReadDeferredInfo;          /**< Structure containing Tml callback function and parameters to be invoked
							  by the callback thread */
    phTmlNfc_ControlCode_t      tTmlCntrlCode;              /**< Control code to pass TML Thread **/

}phTmlNfc_Context_t;

/**
*
* This function creates the worker thread for TML read and write.
*
* \param[in] Tml Context.
*
* \retval NFCSTATUS_SUCCESS    Threads Initialized successfully.
* \retval NFCSTATUS_FAILED     Initialization failed due to system error.
*
*/
NFCSTATUS
phNfcTml_CreateWorkerThread(
				  phTmlNfc_Context_t  *pphTmlNfc_Context
				  );

/**
*
* This Internal function does NCI reset, power ON and OFF.
*
* \param[in] Tml Context.
*
* \retval NFCSTATUS_SUCCESS    Threads Initialized successfully.
* \retval NFCSTATUS_FAILED     Initialization failed due to system error.
*
*/
NFCSTATUS
phNfcTmlCommon_NfcControllerOperations(
				       phTmlNfc_Context_t  *pphTmlNfc_Context
				       );


/**
*
* This function must be called when LibNfc is initialized.
* It let the TML implementation to execute post initialization jobs. 
* This function doesn't need to return a value.
*
* \param[in] Tml Context.
*
*/
void
phNfcTmlCommon_NotifyInitComplete(
				  phTmlNfc_Context_t  *pphTmlNfc_Context,
				  NFCSTATUS status
				 );

/**
* This API can be called by High Layers to do an IOCTL custom
*
* \param[in] pphTmlNfc_Context : This  can be place holder for TML context in DevContext
*                                  can contain  Interface specific information.
* \param[in] ioctlCode           : IOCTL custom code
* \param[in] bufferIn            : input buffer for specific data
* \param[in] bufferInSize        : input buffer size
* \param[out] bufferOut          : output buffer for specific data
* \param[out] bufferOutSize      : output buffer size
*
* Returns:
* \retval #SUCCESS:        Returns NFCSTATUS_SUCCESS in case of success.
* \retval #FAILURE:        Returns valid Error codes in case of failures
*
**/
NFCSTATUS
phNfcTmlCommon_IoCtlCustom(phTmlNfc_Context_t* pphTmlNfc_Context, uint32_t ioctlCode, uint8_t* bufferIn, uint32_t bufferInSize, uint8_t* bufferOut, uint32_t* bufferOutSize);

/**
*
* This function cancels all pending IO.
*
* \param[in] Tml Context.
*
* \retval NFCSTATUS.
*
*/
static NFCSTATUS phNfcTml_CancelIo(void* pContext);

void phTmlNfc_set_fragmentation_enabled(phTmlNfc_i2cfragmentation_t enable);
phTmlNfc_i2cfragmentation_t phTmlNfc_get_fragmentation_enabled();

#endif /*  PHTMLNFC_H  */
