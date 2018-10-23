#define IPGW 0
/*
 *                     Copyright ©, NXP Semiconductors
 *
 *                       ©NXP Semiconductors N.V.2013
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
 * \file phNfcTmlCommon.cpp
 */
extern "C"
{
	#include <phNfcStatus.h>
	#include <stdlib.h>
	#include <phOsalNfc_Timer.h>
	#include "phTmlNfc.h"
	#include <unistd.h>
	#include <phDal4Nfc_messageQueueLib.h>
	#include "phNxpNciHal_utils.h"
	#include <phNxpLog.h>
}


phTmlNfc_Context_t *gpphTmlNfc_Context = NULL;      /** Initialize Context structure pointer used to access context structure */

// FIXME : should be integrated in phTmlNfc_Context_t later.
typedef enum _eIOState
{
	IO_STATE_READ_NONE,
	IO_STATE_READ_READING,
	IO_STATE_READ_CANCELING,
	IO_STATE_READ_CANCELED
}eIOReadState;

typedef enum _eIOWriteState
{
	IO_STATE_WRITE_NONE,
	IO_STATE_WRITE_WRITING
}eIOWriteState;

eIOReadState   readState = IO_STATE_READ_NONE;
eIOWriteState  writeState = IO_STATE_WRITE_NONE;


extern phTmlNfc_i2cfragmentation_t fragmentation_enabled = I2C_FRAGMENATATION_DISABLED;

//PA
#define INVALID_HANDLE_VALUE NULL
#include "core/WaiterNotifier.h"
#include "core/Verbose.h"
#include "phTmlNfc_Abend.hpp"
#include "phTmlNfc_APIWrapper.h"


static Locker stateLock;


NFCSTATUS phNfcTml_NfcControllerOperations(phTmlNfc_Context_t *pphTmlNfc_Context);

enum eState
{
	NONE,
	WAITING,
	NOTIFIED
};

eState mystate = NONE;


static phTmlNfc_TransactInfo_t tTransactionInfo; //        = {0};
static phLibNfc_DeferredCall_t tDeferredInfo;
static phLibNfc_Message_t tMsg; //                    = {0};

void phMessagingNfc_Interface_DeferredCall(NFCSTATUS status, uint8_t *buffer, uint16_t size, uint32_t msgType)
{
	/* Fill the Transaction info structure to be passed to Callback Function */
	tTransactionInfo.wStatus = status;
	tTransactionInfo.pBuff = buffer;
	/* Actual number of bytes read is filled in the structure */
	tTransactionInfo.wLength = size;
	//PA: To manage their bullsheet messageType
	tTransactionInfo.messageType = msgType;

	/* Read operation completed successfully. Post a Message onto Callback Thread*/
	/* Prepare the message to be posted on User thread */
	tDeferredInfo.pCallback = &phNfcTml_DeferredCb;
	tDeferredInfo.pParameter = &tTransactionInfo;
	
	tMsg.eMsgType = PH_LIBNFC_DEFERREDCALL_MSG ;
	tMsg.pMsgData = &tDeferredInfo;
	tMsg.Size = sizeof(tDeferredInfo);
	phTmlNfc_DeferredCall(gpphTmlNfc_Context->dwCallbackThreadId, (phLibNfc_Message_t *) &tMsg);

	usleep(0);
}

void phNfcTml_WaitForState(eIOReadState state, uint8_t waitForNone)
{
	uint8_t   waitOnRead = 1;

	while (waitOnRead)
	{
		stateLock.lock();
#ifdef LOGS
		Tools_LOG("%s : state expected : %X ; readState  : %X", __FUNCTION__, state, readState);
#endif

		if ((readState == state) || ((waitForNone == 1) && (readState == IO_STATE_READ_NONE)))
		{
			// Expected readState has been reached.
			waitOnRead = 0;
		}
		stateLock.unlock();

		phTmlNfc_AbendCancelIo();
		if (waitOnRead)
		{
			usleep(100);//SwitchToThread(); // Cause Yield()
		}
	}
}

void phNfcTml_SafeIOCancel()
{
#ifdef LOGS
	Tools_LOG("In %s", __FUNCTION__);
#endif

	stateLock.lock();

#ifdef LOGS
	Tools_LOG("%s : readState(1) 0x%i", __FUNCTION__, readState);
#endif

	if (readState == IO_STATE_READ_NONE)
	{
		// Nothing to cancel.
		stateLock.unlock();
#ifdef LOGS
		Tools_LOG("Out %s", __FUNCTION__);
#endif
		return;
	}
#ifdef LOGS
	Tools_LOG("%s : readState(2) 0x%i", __FUNCTION__, readState);
#endif

	if (readState == IO_STATE_READ_CANCELED)
	{
		stateLock.unlock();
		// We are in canceled state we wait for next Read.
		//phNfcTml_WaitForState(IO_STATE_READ_READING, 1);
#ifdef LOGS
		Tools_LOG("%s : PA do nothing", __FUNCTION__, readState);
#endif
		stateLock.lock();
	}

#ifdef LOGS
	Tools_LOG("%s : readState(3) 0x%i", __FUNCTION__, readState);
#endif
	if (readState == IO_STATE_READ_READING)
	{
		// Reading in progress we cancel it.
		readState = IO_STATE_READ_CANCELING;
		stateLock.unlock();
		// Wait for read to get canceled or read completes.
		phNfcTml_WaitForState(IO_STATE_READ_CANCELED, 1);
		stateLock.lock();
	}

	stateLock.unlock();

#ifdef LOGS
	Tools_LOG("Out %s", __FUNCTION__);
#endif
	// Now we have the guarantee that pending operation is properly canceled
}


NFCSTATUS phTmlNfc_Init(pphTmlNfc_Config_t pConfig)
{
	NFCSTATUS wInitStatus = NFCSTATUS_SUCCESS;

	readState = IO_STATE_READ_NONE;

	int8_t pDevNamelocal[] = "I2C";
	
	/* Check if TML layer is already Initialized */
	if (NULL != gpphTmlNfc_Context)
	{
		/* TML initialization is already completed */
		wInitStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_ALREADY_INITIALISED);
	}
	/* Validate Input parameters */
	else if ((NULL == pConfig) || (PH_TMLNFC_RESET_VALUE == pConfig->dwGetMsgThreadId))
	{
		/*Parameters passed to TML init are wrong */
		wInitStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_INVALID_PARAMETER);
	}
	else
	{
		/* Allocate memory for TML context */
		gpphTmlNfc_Context = (phTmlNfc_Context_t *)malloc(sizeof(phTmlNfc_Context_t));
		if (NULL == gpphTmlNfc_Context)
		{
			wInitStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_FAILED);
		}
		else
		{
			/* Initialise all the internal TML variables */
			memset(gpphTmlNfc_Context,0, sizeof(phTmlNfc_Context_t));
			/* Make sure that the thread runs once it is created */

			gpphTmlNfc_Context->tTmlNfcConfig.pDevName = pDevNamelocal;
			//PA gpphTmlNfc_Context->uiLpcI2cAddress = pDevContext->RegistryConfig.uiLpcI2cAddress;
			/*Copy Tml Context*/
			gpphTmlNfc_Context = (phTmlNfc_Context_t *)gpphTmlNfc_Context;

			gpphTmlNfc_Context->bThreadDone = TRUE;
			//                 gpphTmlNfc_Context->wFlag = FALSE;
			gpphTmlNfc_Context->bCurrentRetryCount = PH_TMLNFC_DEFAULT_RETRYCOUNT;

			/* Open the device file to which data is read/written */
			gpphTmlNfc_Context->pDevHandle = phTmlNfc_AbendOpen(gpphTmlNfc_Context->tTmlNfcConfig.pDevName);

			if(INVALID_HANDLE_VALUE == gpphTmlNfc_Context->pDevHandle || NFCSTATUS_SUCCESS != wInitStatus)
			{
				wInitStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_INVALID_DEVICE);
			}
			else
			{
				gpphTmlNfc_Context->tReadInfo.bEnable = FALSE;
				gpphTmlNfc_Context->tWriteInfo.bEnable = FALSE;
				gpphTmlNfc_Context->tReadInfo.bThreadBusy = FALSE;
				gpphTmlNfc_Context->tWriteInfo.bThreadBusy = FALSE;

				memset(&gpphTmlNfc_Context->tWriteTransactionInfo,0, sizeof(phTmlNfc_TransactInfo_t));
				memset(&gpphTmlNfc_Context->tWriteDeferredInfo,0, sizeof(phTmlNfc_DeferMsg_t));

				memset(&gpphTmlNfc_Context->tReadTransactionInfo,0, sizeof(phTmlNfc_TransactInfo_t));
				memset(&gpphTmlNfc_Context->tReadDeferredInfo,0, sizeof(phTmlNfc_DeferMsg_t));

				gpphTmlNfc_Context->hThreadEvent = new Locker();
				if (NULL == gpphTmlNfc_Context->hThreadEvent)
				{
					wInitStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_FAILED);
				}
				else
				{
					gpphTmlNfc_Context->hReadWriteEvent = new WaiterNotifier();
					if (NULL == gpphTmlNfc_Context->hReadWriteEvent)
					{
						wInitStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_FAILED);
					}
					else
					{
#if PHTMLNFC_DEFER_VEN_RESET
						gpphTmlNfc_Context->hResetVENEvent = new Locker();
						if (NULL == gpphTmlNfc_Context->hResetVENEvent)
						{
							wInitStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_FAILED);
						}
						else
						{
#endif
							/* Initialize the critical section for Read/Write operations*/
							gpphTmlNfc_Context->csTmlAccessLock = new Locker();

							/* Start TML worker thread (to handle write and read operations) */
							wInitStatus = phNfcTml_CreateWorkerThread(gpphTmlNfc_Context);
							if (NFCSTATUS_SUCCESS != wInitStatus)
							{
								wInitStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_FAILED);
							}
							else
							{
								uint16_t	retWait = 0;
								((Locker*)gpphTmlNfc_Context->hThreadEvent)->lock();
								if(mystate == NONE)
								{
									mystate = WAITING;
									((Locker*)gpphTmlNfc_Context->hThreadEvent)->wait(false);
									mystate = NONE;
								}
								else
								{
									mystate = NONE;
								}
								((Locker*)gpphTmlNfc_Context->hThreadEvent)->unlock();

								/* Create Timer used for Retransmission of NCI packets */
								gpphTmlNfc_Context->dwTimerId = phOsalNfc_Timer_Create();
								if (PH_OSALNFC_TIMER_ID_INVALID != gpphTmlNfc_Context->dwTimerId)
								{
									/* Store the Thread Identifier to which Message is to be posted */
									gpphTmlNfc_Context->dwCallbackThreadId = pConfig->dwGetMsgThreadId;
									/* Enable retransmission of Nci packet & set retry count to default */
									gpphTmlNfc_Context->eConfig = phTmlNfc_e_EnableRetrans;
									gpphTmlNfc_Context->bRetryCount = PH_TMLNFC_DEFAULT_RETRYCOUNT;
								}
								else
								{
									wInitStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_FAILED);
								}

							}
#if PHTMLNFC_DEFER_VEN_RESET
						}
#endif
					}
				}
			}
		}
		
		/* Clean up all the TML resources if any error */
		if (NFCSTATUS_SUCCESS != wInitStatus)
		{
			/* Clear all handles and memory locations initialized during init */
			phNfcTml_CleanUp();
		}
		
	}
	
	return wInitStatus;
}

void phNfcTml_ConfigNciPktReTx(phTmlNfc_ConfigRetrans_t eConfiguration,
		uint8_t bRetryCounter)
{
	/* Enable/Disable Retransmission */
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (In)", __FUNCTION__);
	if (NULL == gpphTmlNfc_Context)
	{
		//CB TraceEvents(TRACE_LEVEL_ERROR, FLAG_TML, "(%s) TML COntext is NULL", __FUNCTION__);
	}
	else
	{
		gpphTmlNfc_Context->eConfig = eConfiguration;
		if (phTmlNfc_e_EnableRetrans == eConfiguration)
		{
			/* Check whether Retry counter passed is valid */
			if (0 != bRetryCounter)
			{
				gpphTmlNfc_Context->bRetryCount = bRetryCounter;
			}
			/* Set retry counter to its default value */
			else
			{
				gpphTmlNfc_Context->bRetryCount = PH_TMLNFC_DEFAULT_RETRYCOUNT;
			}
		}
		else
		{
			gpphTmlNfc_Context->bRetryCount = 0;
		}
	}
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (Out)", __FUNCTION__);
}


static void phNfcTml_TmlProcessWrite()
{
	NFCSTATUS  wStatus       = NFCSTATUS_SUCCESS;
	uint16_t   dwNoBytesWrRd = PH_TMLNFC_RESET_VALUE;
#ifdef LOGS
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, "(%s) (WRITE To Be Started)", __FUNCTION__);
#endif

	/* Variable to fetch the actual number of bytes written */
	dwNoBytesWrRd = PH_TMLNFC_RESET_VALUE;
	/* Write the data in the buffer onto the file */
	wStatus = phTmlNfc_AbendTx(gpphTmlNfc_Context->tWriteInfo.pBuffer, gpphTmlNfc_Context->tWriteInfo.wLength, (uint16_t*)&dwNoBytesWrRd);

	if (NFCSTATUS_BUSY == wStatus)
	{
		printf("phTmlNfc_AbendTx return NFCSTATUS_BUSY\n");
	}
	if (NFCSTATUS_ABORTED == wStatus)
	{
		//Do nothing ???
		printf("phTmlNfc_AbendTx return NFCSTATUS_ABORTED\n");
	}
	else if (NFCSTATUS_SUCCESS == wStatus)
	{
		dwNoBytesWrRd = PH_TMLNFC_VALUE_ONE;
		phNxpNciHal_print_packet("SEND", gpphTmlNfc_Context->tWriteInfo.pBuffer,
		gpphTmlNfc_Context->tWriteInfo.wLength);
	}
	else
	{
		wStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_BOARD_COMMUNICATION_ERROR);
	}

	//PA ResetEvent(gpphTmlNfc_Context->hReadWriteEvent);
	/* Acquire lock for the Write operation*/
	((Locker*)gpphTmlNfc_Context->csTmlAccessLock)->lock();
	gpphTmlNfc_Context->tWriteInfo.bEnable = FALSE;
	/* Release lock to proceed with Read operation @ Read API level*/
	((Locker*)gpphTmlNfc_Context->csTmlAccessLock)->unlock();

	stateLock.lock();
	writeState = IO_STATE_WRITE_NONE;
	if (readState == IO_STATE_READ_CANCELED)
	{
#ifdef LOGS
		Tools_LOG("%s : readState 0x%i => IO_STATE_READ_READING", __FUNCTION__, readState);
#endif
		readState = IO_STATE_READ_READING;
	}
	stateLock.unlock();

	/* Check whether Retransmission is started,
	If yes, Send callback is not invoked */
	if (phTmlNfc_e_DisableRetrans == gpphTmlNfc_Context->eConfig)
	{
		phMessagingNfc_Interface_DeferredCall(wStatus, gpphTmlNfc_Context->tWriteInfo.pBuffer, dwNoBytesWrRd , PH_TMLNFC_WRITE_MESSAGE);
	}
	else
	{
		if (gpphTmlNfc_Context->bCurrentRetryCount == gpphTmlNfc_Context->bRetryCount)
		{
#ifdef LOGS
			//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, "(%s) Posting Write Message (%d) sizeof = %d", __FUNCTION__, gpphTmlNfc_Context->tWriteMsg.eMsgType, sizeof(sizeof(gpphTmlNfc_Context->tWriteDeferredInfo)));
#endif
			phMessagingNfc_Interface_DeferredCall(wStatus, gpphTmlNfc_Context->tWriteInfo.pBuffer, dwNoBytesWrRd , PH_TMLNFC_WRITE_MESSAGE);
		}
	}
}

static void phNfcTml_TmlProcessRead()
{
	NFCSTATUS  wStatus       = NFCSTATUS_SUCCESS;
	uint16_t   dwNoBytesWrRd = PH_TMLNFC_RESET_VALUE;

#ifdef LOGS
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, "(%s) (READ To Be Started)", __FUNCTION__);
#endif


	/* Read the data from the file onto the buffer */
	// FIXME : This flag seems useless.
	// ******************** LOCK ***************************
	stateLock.lock();
	if (readState == IO_STATE_READ_READING)
	{
		stateLock.unlock();
		//wStatus = phTmlNfcInterface_Read(gpphTmlNfc_Context,gpphTmlNfc_Context->tReadInfo.pBuffer,gpphTmlNfc_Context->tReadInfo.wLength,(LPDWORD)(uint16_t *)&dwNoBytesWrRd);
		wStatus = phTmlNfc_AbendRx(gpphTmlNfc_Context->tReadInfo.pBuffer, gpphTmlNfc_Context->tReadInfo.wLength, (uint16_t *)&dwNoBytesWrRd);

		stateLock.lock();
	}

	switch(readState)
	{
	case IO_STATE_READ_READING:
	{
		if (NFCSTATUS_SUCCESS == wStatus)
		{
			// Clean up event
			//PA ResetEvent(gpphTmlNfc_Context->hReadWriteEvent);

			/* Acquire Lock for Read Operation */
			((Locker*)gpphTmlNfc_Context->csTmlAccessLock)->lock();
			/* This has to be reset only after a successful read */
			gpphTmlNfc_Context->tReadInfo.bEnable = FALSE;
			/* Update the actual number of bytes read including header */
			gpphTmlNfc_Context->tReadInfo.wLength = (uint16_t)(dwNoBytesWrRd);
			((Locker*)gpphTmlNfc_Context->csTmlAccessLock)->unlock();
			
			phNxpNciHal_print_packet("RECV", gpphTmlNfc_Context->tReadInfo.pBuffer,
                        gpphTmlNfc_Context->tReadInfo.wLength);

			dwNoBytesWrRd = PH_TMLNFC_RESET_VALUE;

			phMessagingNfc_Interface_DeferredCall(wStatus, gpphTmlNfc_Context->tReadInfo.pBuffer, gpphTmlNfc_Context->tReadInfo.wLength, PH_TMLNFC_READ_MESSAGE);

			// The Read operation completes as success update status.
			// Check if we have been canceled in the meanwhile.
#ifdef LOGS
			Tools_LOG("%s : readState 0x%i => IO_STATE_READ_NONE", __FUNCTION__, readState);
#endif

			// Read complete successfully.
			readState = IO_STATE_READ_NONE;
		}
		else if (NFCSTATUS_ABORTED == wStatus)
		{
#ifdef LOGS
			//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, "(%s) read ABORTED", __FUNCTION__);
#endif

			// Check if we have been canceled in the meanwhile
			// NOTE : ERROR and CANCELED behave in the same way.
#ifdef LOGS
			Tools_LOG("%s : readState 0x%i => IO_STATE_READ_CANCELED", __FUNCTION__, readState);
#endif
			readState = IO_STATE_READ_CANCELED;
		}
		else
		{
#ifdef LOGS
			//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, "(%s) read returned (0x%02x)", __FUNCTION__, wStatus);
#endif
			// Check if we have been canceled in the meanwhile
			// NOTE : ERROR and CANCELED behave in the same way.
#ifdef LOGS
			Tools_LOG("%s : readState 0x%i ", __FUNCTION__, readState);
#endif
			
				// FIXME : Should notify LibNfc upperlayers ???
				// NOTE : Notifying upper layers cause read to be rearm in loop ...
				// We simply stop the read.
				readState = IO_STATE_READ_NONE;
		}
		break;
	}

	case IO_STATE_READ_CANCELING:
	{
		// We've been canceled no read.
		wStatus = NFCSTATUS_ABORTED;
#ifdef LOGS
		Tools_LOG("%s : readState 0x%i => IO_STATE_READ_CANCELED", __FUNCTION__, readState);
#endif
		readState = IO_STATE_READ_CANCELED;
		break;
	}

	default:
	{
#ifdef LOGS
		Tools_LOG("%s : Should never happen readState = 0x%X ",__FUNCTION__,readState);
#endif
	}
	}
	// ******************** UNLOCK ***************************
	stateLock.unlock();
}

static uint8_t phNfcTml_TmlProcessNfcControllerOperation(phTmlNfc_Context_t *pphTmlNfc_Context)
{
	uint8_t       bResetVEN = TRUE;
	NFCSTATUS  wStatus   = NFCSTATUS_SUCCESS;
#if PHTMLNFC_DEFER_VEN_RESET
	wStatus = phNfcTml_NfcControllerOperations(gpphTmlNfc_Context);
	if (NFCSTATUS_SUCCESS == wStatus)
	{
		////CB TraceEvents(TRACE_LEVEL_VERBOSE, FLAG_TML, "(%s) phNfcTmlCommon_NfcControllerOperations (SUCCESS)", __FUNCTION__);
	}
	else
	{
		////CB TraceEvents(TRACE_LEVEL_VERBOSE, FLAG_TML, "(%s) phNfcTmlCommon_NfcControllerOperations (FAILED)", __FUNCTION__);
	}
	bResetVEN = ((TRUE == pphTmlNfc_Context->bVENResetRequested) ? FALSE : TRUE);
#endif
	return bResetVEN;
}

void* phNfcTml_TmlThread(void* pContext)
{
	phTmlNfc_Context_t     *pphTmlNfc_Context = (phTmlNfc_Context_t  *)pContext;
	uint8_t                 bResetVEN = TRUE;
	uint8_t                 bRetState = FALSE;


#ifdef LOGS
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (In)", __FUNCTION__);
#endif

	if (NULL == pphTmlNfc_Context)
	{
#ifdef LOGS
		//CB TraceEvents(TRACE_LEVEL_ERROR, FLAG_TML, "(%s) TML Context is NULL", __FUNCTION__);
#endif
		return NULL;
	}

	/* Set the event to inform that Tml thread is started successfully */
	bRetState = TRUE;

	((Locker*)gpphTmlNfc_Context->hThreadEvent)->lock();
	if(mystate == WAITING)
	{
		mystate = NOTIFIED;
		((Locker*)gpphTmlNfc_Context->hThreadEvent)->wakeUp(false);
	}
	else
	{
		mystate = NOTIFIED;
	}
	((Locker*)gpphTmlNfc_Context->hThreadEvent)->unlock();

	/* Writer thread loop shall be running till shutdown is invoked */
	while ((FALSE != bRetState) && (TRUE == gpphTmlNfc_Context->bThreadDone))
	{
		bResetVEN = phNfcTml_TmlProcessNfcControllerOperation(pphTmlNfc_Context);

		/* If Tml write is requested */
		stateLock.lock();

		if ((writeState != IO_STATE_WRITE_NONE) && (TRUE == bResetVEN))
		{
			stateLock.unlock();
			phNfcTml_TmlProcessWrite();
			stateLock.lock();
		}else if ((readState != IO_STATE_READ_NONE) && (readState != IO_STATE_READ_CANCELED) && (TRUE == bResetVEN))
		{
			/* If Tml read is requested */
			stateLock.unlock();
			phNfcTml_TmlProcessRead();
			stateLock.lock();
		}

		if ((writeState == IO_STATE_WRITE_NONE) && (readState == IO_STATE_READ_NONE))
		{
			stateLock.unlock();
			((WaiterNotifier*)gpphTmlNfc_Context->hReadWriteEvent)->wait(true);
		}
		else
		{
			stateLock.unlock();
		}
		usleep(100);
	}/* End of While loop */

	return NULL;

#ifdef LOGS
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (Out)", __FUNCTION__);
#endif
}

static void phNfcTml_CleanUp()
{
	//PA: compilator warning    NFCSTATUS wRetval = NFCSTATUS_SUCCESS;
#ifdef LOGS
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (In)", __FUNCTION__);
#endif
	if (NULL == gpphTmlNfc_Context)
	{
#ifdef LOGS
		//CB TraceEvents(TRACE_LEVEL_ERROR, FLAG_TML, "(%s) TML Context is NULL", __FUNCTION__);
#endif
	}
	else
	{
		if (0 != gpphTmlNfc_Context->dwTimerId)
		{
			phOsalNfc_Timer_Delete(gpphTmlNfc_Context->dwTimerId);
			gpphTmlNfc_Context->dwTimerId = 0;
		}

		/* Delete the critical section*/
		if (NULL != gpphTmlNfc_Context->csTmlAccessLock)
		{
			delete((Locker*)gpphTmlNfc_Context->csTmlAccessLock);
			gpphTmlNfc_Context->csTmlAccessLock = NULL;
		}
				/* Clear All the resources allocated during initialization */
		if (NULL != gpphTmlNfc_Context->hReadWriteEvent)
		{
#ifdef LOGS
			//CB TraceEvents(TRACE_LEVEL_VERBOSE, FLAG_TML, "(%s) Closing hReadWriteEvent", __FUNCTION__);
#endif
			delete((WaiterNotifier*)gpphTmlNfc_Context->hReadWriteEvent);
			gpphTmlNfc_Context->hReadWriteEvent = NULL;
		}

		if (NULL != gpphTmlNfc_Context->hThreadEvent)
		{
#ifdef LOGS
			//CB TraceEvents(TRACE_LEVEL_VERBOSE, FLAG_TML, "(%s) Closing hThreadEvent", __FUNCTION__);
#endif
			delete((Locker*)gpphTmlNfc_Context->hThreadEvent);
			gpphTmlNfc_Context->hThreadEvent = NULL;
		}

#if PHTMLNFC_DEFER_VEN_RESET
		if (NULL != gpphTmlNfc_Context->hResetVENEvent)
		{
#ifdef LOGS
			//CB TraceEvents(TRACE_LEVEL_VERBOSE, FLAG_TML, "(%s) Closing hResetVENEvent", __FUNCTION__);
#endif
			delete((Locker*)gpphTmlNfc_Context->hResetVENEvent);
			gpphTmlNfc_Context->hResetVENEvent = NULL;
		}
#endif

		/* Clear memory allocated for storing Context variables */
		free((void *)gpphTmlNfc_Context);
		/* Set the pointer to NULL to indicate De-Initialization */
		gpphTmlNfc_Context = NULL;
	}
#ifdef LOGS
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (Out)", __FUNCTION__);
#endif
}

NFCSTATUS phTmlNfc_Shutdown()
{
	NFCSTATUS wShutdownStatus = NFCSTATUS_SUCCESS;

	/* Check whether TML is Initialized */
	if (NULL != gpphTmlNfc_Context)
	{

		/* Reset thread variable to terminate the thread */
		gpphTmlNfc_Context->bThreadDone = FALSE;
		gpphTmlNfc_Context->tReadInfo.bEnable = FALSE;
		gpphTmlNfc_Context->tWriteInfo.bEnable = FALSE;

		phNfcTml_SafeIOCancel();

		/* Setting Thread event to proceed further and exit from worker thread*/
		((WaiterNotifier*)gpphTmlNfc_Context->hReadWriteEvent)->notify(true);

		if (0 != gpphTmlNfc_Context->twWriteReadWorker)
		{
#ifdef LOGS
			//CB TraceEvents(TRACE_LEVEL_VERBOSE, FLAG_TML, "(%s) WaitForThreadpoolWorkCallbacks", __FUNCTION__);
#endif
			pthread_join(gpphTmlNfc_Context->twWriteReadWorker, NULL);
			gpphTmlNfc_Context->twWriteReadWorker = 0;
		}
		
		phTmlNfc_AbendResetPN547();
		
		if ((NULL != gpphTmlNfc_Context->pDevHandle) &&	(INVALID_HANDLE_VALUE != gpphTmlNfc_Context->pDevHandle))
		{
			phTmlNfc_AbendClose();
			gpphTmlNfc_Context->pDevHandle = NULL;
		}

		phNfcTml_CleanUp();
		if (gpphTmlNfc_Context != NULL)
		{
			gpphTmlNfc_Context = NULL;
		}
	}
	else
	{
#ifdef LOGS
		//CB TraceEvents(TRACE_LEVEL_ERROR, FLAG_TML, "(%s) TML Context is NULL", __FUNCTION__);
#endif
		wShutdownStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_NOT_INITIALISED);
	}
#ifdef LOGS
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (Out) :: Status 0x%X", __FUNCTION__, wShutdownStatus);
#endif
	return wShutdownStatus;
}

NFCSTATUS phTmlNfc_Write(uint8_t *pBuffer, uint16_t wLength,
		pphTmlNfc_TransactCompletionCb_t pTmlWriteComplete, void *pContext)
{
	NFCSTATUS wWriteStatus;

	if (NULL != gpphTmlNfc_Context)
	{
		if ((NULL != pBuffer) && (PH_TMLNFC_RESET_VALUE != wLength) && (NULL != pTmlWriteComplete))
		{
			if (!gpphTmlNfc_Context->tWriteInfo.bThreadBusy)
			{
				/* Acquire the lock for Write Operation*/
				((Locker*)gpphTmlNfc_Context->csTmlAccessLock)->lock();
				/* Setting the flag marks beginning of a Write Operation */
				gpphTmlNfc_Context->tWriteInfo.bThreadBusy = TRUE;
				/* Copy the buffer, length and Callback function,
				This shall be utilized while invoking the Callback function in thread */
				gpphTmlNfc_Context->tWriteInfo.pBuffer = pBuffer;
				gpphTmlNfc_Context->tWriteInfo.wLength = wLength;
				gpphTmlNfc_Context->tWriteInfo.pThread_Callback = pTmlWriteComplete;
				gpphTmlNfc_Context->tWriteInfo.pContext = pContext;

				/* Set event to invoke Writer Thread */
				gpphTmlNfc_Context->tWriteInfo.bEnable = 1;
				/* Release lock after updating Write events*/
				((Locker*)gpphTmlNfc_Context->csTmlAccessLock)->unlock();

				wWriteStatus = NFCSTATUS_PENDING;
				/* FIXME: If retry is going on. Stop the retry thread/timer */
				if (phTmlNfc_e_EnableRetrans == gpphTmlNfc_Context->eConfig)
				{
					/* Set retry count to default value */
					/* FIXME: If the timer expired there, and meanwhile we have created */
					/*  a new request. The exipred timer will thing that retry is still */
					/*  on going. */
					gpphTmlNfc_Context->bCurrentRetryCount = gpphTmlNfc_Context->bRetryCount;
				}

				/* Just cancel any panding Read or Write Request */
				phNfcTml_SafeIOCancel();

				stateLock.lock();
#ifdef LOGS
				Tools_LOG("%s : writeState 0x%i => IO_STATE_WRITE_WRITING", __FUNCTION__, writeState);
#endif
				writeState = IO_STATE_WRITE_WRITING;
				stateLock.unlock();
#ifdef LOGS
				//CB TraceEvents(TRACE_LEVEL_VERBOSE, FLAG_TML, "(%s) Event Set for Write", __FUNCTION__);
#endif
				((WaiterNotifier*)gpphTmlNfc_Context->hReadWriteEvent)->notify(TRUE);
			}
			else
			{
#ifdef LOGS
				//CB TraceEvents(TRACE_LEVEL_ERROR, FLAG_TML, "(%s) Device busy in Write", __FUNCTION__);
#endif
				wWriteStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_BUSY);
			}
		}
		else
		{
#ifdef LOGS
			//CB TraceEvents(TRACE_LEVEL_ERROR, FLAG_TML, "(%s) Invalid Write parameters", __FUNCTION__);
#endif
			wWriteStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_INVALID_PARAMETER);
		}
		//             gpphTmlNfc_Context->wFlag = TRUE;
	}
	else
	{
#ifdef LOGS
		//CB TraceEvents(TRACE_LEVEL_ERROR, FLAG_TML, "(%s) TML context is NULL", __FUNCTION__);
#endif
		wWriteStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_NOT_INITIALISED);
	}
#ifdef LOGS
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (Out) :: Status 0x%X", __FUNCTION__, wWriteStatus);
#endif
	return wWriteStatus;
}

NFCSTATUS phTmlNfc_Read(uint8_t *pBuffer, uint16_t wLength,
		pphTmlNfc_TransactCompletionCb_t pTmlReadComplete, void *pContext)
{
	NFCSTATUS wReadStatus;
	
	/* Check whether TML is Initialized */
	if (NULL != gpphTmlNfc_Context)
	{
		if ((NULL != pBuffer) && (PH_TMLNFC_RESET_VALUE != wLength) && (NULL != pTmlReadComplete))
		{
			if (!gpphTmlNfc_Context->tReadInfo.bThreadBusy)
			{
				/* Acquire lock For read operation */
				((Locker*)gpphTmlNfc_Context->csTmlAccessLock)->lock();
				/* Setting the flag marks beginning of a Read Operation */
				gpphTmlNfc_Context->tReadInfo.bThreadBusy = TRUE;
				/* Copy the buffer, length and Callback function,
		    This shall be utilized while invoking the Callback function in thread */
				gpphTmlNfc_Context->tReadInfo.pBuffer = pBuffer;
				gpphTmlNfc_Context->tReadInfo.wLength = wLength;
				gpphTmlNfc_Context->tReadInfo.pThread_Callback = pTmlReadComplete;
				gpphTmlNfc_Context->tReadInfo.pContext = pContext;
				wReadStatus = NFCSTATUS_PENDING;

				/* Set event to invoke Reader Thread */
				gpphTmlNfc_Context->tReadInfo.bEnable = TRUE;
				/* Release lock after updating read events */
				((Locker*)gpphTmlNfc_Context->csTmlAccessLock)->unlock();
#ifdef LOGS
				//CB TraceEvents(TRACE_LEVEL_VERBOSE, FLAG_TML, "(%s) Event is Set for Read", __FUNCTION__);
#endif

				phNfcTml_SafeIOCancel();
				// Set status to Read in progress
				stateLock.lock();
#ifdef LOGS
				Tools_LOG("%s : readState 0x%i => IO_STATE_READ_READING", __FUNCTION__, readState);
#endif
				readState = IO_STATE_READ_READING;
				stateLock.unlock();

				((WaiterNotifier*)gpphTmlNfc_Context->hReadWriteEvent)->notify(TRUE);
			}
			else
			{
#ifdef LOGS
				//CB TraceEvents(TRACE_LEVEL_ERROR, FLAG_TML, "(%s) Device busy for Read", __FUNCTION__);
#endif
				wReadStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_BUSY);
			}
		}
		else
		{
#ifdef LOGS
			//CB TraceEvents(TRACE_LEVEL_ERROR, FLAG_TML, "(%s) Invalid parameters for Read", __FUNCTION__);
#endif
			wReadStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_INVALID_PARAMETER);
		}
	}
	else
	{
#ifdef LOGS
		//CB TraceEvents(TRACE_LEVEL_ERROR, FLAG_TML, "(%s) TML context is NULL", __FUNCTION__);
#endif
		wReadStatus = PHNFCSTVAL(CID_NFC_TML, NFCSTATUS_NOT_INITIALISED);
	}
#ifdef LOGS
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (Out) :: Status 0x%X", __FUNCTION__, wReadStatus);
#endif
	return wReadStatus;
}

NFCSTATUS phTmlNfc_ReadAbort()
{
	NFCSTATUS wStatus = NFCSTATUS_INVALID_PARAMETER;

	if (NULL == gpphTmlNfc_Context)
	{
#ifdef LOGS
	    //CB TraceEvents(TRACE_LEVEL_ERROR, FLAG_TML, "(%s) TML Context is NULL", __FUNCTION__);
#endif
	}
	else
	{
		gpphTmlNfc_Context->tReadInfo.bEnable = FALSE;
		/*Reset the flag to accept another Read Request */
		gpphTmlNfc_Context->tReadInfo.bThreadBusy = FALSE;

		phNfcTml_SafeIOCancel();

		wStatus = NFCSTATUS_SUCCESS;
	}

#ifdef LOGS 
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (Out) :: Status 0x%X", __FUNCTION__, wStatus);
#endif
	return wStatus;
}

NFCSTATUS phTmlNfc_WriteAbort()
{
	NFCSTATUS wStatus = NFCSTATUS_INVALID_PARAMETER;
	{
		if (NULL == gpphTmlNfc_Context)
		{
#ifdef LOGS
			Tools_LOG("gpphTmlNfc_Context = NULL");
#endif
		}
		else
		{
			gpphTmlNfc_Context->tWriteInfo.bEnable = FALSE;
			/* Stop if any retransmission is in progress */
			gpphTmlNfc_Context->bCurrentRetryCount = 0;
			/* Reset the flag to accept another Write Request */
			gpphTmlNfc_Context->tWriteInfo.bThreadBusy = FALSE;
			wStatus = NFCSTATUS_SUCCESS;

			stateLock.lock();
#ifdef LOGS
			Tools_LOG("%s : readState 0x%i => IO_STATE_WRITE_NONE", __FUNCTION__, readState);
#endif
			writeState = IO_STATE_WRITE_NONE;
			stateLock.unlock();
		}
	}
#ifdef LOGS
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (Out) :: Status 0x%X", __FUNCTION__, wStatus);
#endif
	return wStatus;
}

NFCSTATUS phTmlNfc_IoCtl(phTmlNfc_ControlCode_t eControlCode)
{
	NFCSTATUS wStatus = NFCSTATUS_SUCCESS;

	if (NULL == gpphTmlNfc_Context)
	{
#ifdef LOGS
		Tools_LOG("gpphTmlNfc_Context = NULL");
#endif
		wStatus = NFCSTATUS_FAILED;
	}
	else
	{
		switch (eControlCode)
		{
		case phTmlNfc_e_ResetDevice:
		{
#if PHTMLNFC_DEFER_VEN_RESET
			gpphTmlNfc_Context->bVENResetRequested = TRUE;
			phNfcTml_SafeIOCancel();
			((WaiterNotifier*)gpphTmlNfc_Context->hReadWriteEvent)->notify(TRUE);
			((Locker*)gpphTmlNfc_Context->hResetVENEvent)->lock();
			((Locker*)gpphTmlNfc_Context->hResetVENEvent)->wait(FALSE);
			((Locker*)gpphTmlNfc_Context->hResetVENEvent)->unlock();
#else
			phTmlNfcInterface_ReSetNfcController(gpphTmlNfc_Context);
#endif
		}
		break;
		case phTmlNfc_e_EnableNormalMode:
		{
			phTmlNfc_AbendEnterNormalMode();
			phTmlNfc_AbendResetPN547();
			phNfcTml_ConfigNciPktReTx(phTmlNfc_e_EnableRetrans, 0);
		}
		break;
		case phTmlNfc_e_EnableDownloadMode:
		{
			/* Just cancel any panding Read or Write Request */
			phNfcTml_SafeIOCancel();
			phNfcTml_ConfigNciPktReTx(phTmlNfc_e_DisableRetrans, 0);
			phTmlNfc_AbendEnterDnldMode();
			phTmlNfc_AbendResetPN547();
		}
		break;
		case phTmlNfc_e_PowerOff:
		{
			/* Just cancel any panding Read or Write Request */
			phNfcTml_SafeIOCancel();
			phTmlNfc_AbendPowerOffPN547();
		}
		break;
		case phTmlNfc_e_PowerOn:
		{
			phTmlNfc_AbendPowerOnPN547();
		}
		break;
		default:
		{
			wStatus = NFCSTATUS_INVALID_PARAMETER;
		}
		break;
		}
	}
	return wStatus;
}

void phTmlNfc_DeferredCall(uint32_t dwThreadId, phLibNfc_Message_t * ptWorkerMsg)
{
	uint8_t bPostStatus = FALSE;

	/* Post message on the user thread to invoke the callback function */
	if (NULL == gpphTmlNfc_Context)
	{
#ifdef LOGS
		Tools_LOG("gpphTmlNfc_Context = NULL");
#endif
	}
	else
	{
		bPostStatus = phDal4Nfc_msgsnd(gpphTmlNfc_Context->dwCallbackThreadId,
			ptWorkerMsg,
			0 //IPC_NOWAIT kind
			);
	}

}

static void phNfcTml_DeferredCb(void  *pParams)
{
	/* Transaction info buffer to be passed to Callback Function */
	phTmlNfc_TransactInfo_t *pTransactionInfo = (phTmlNfc_TransactInfo_t *)pParams;

#ifdef LOGS
	Tools_LOG("%s : pTransactionInfo->pBuff ", __FUNCTION__);


	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (In)", __FUNCTION__);
#endif
	if (NULL == gpphTmlNfc_Context)
	{
#ifdef LOGS
		//CB TraceEvents(TRACE_LEVEL_ERROR, FLAG_TML, "(%s) TML context is NULL", __FUNCTION__);
#endif
	}
	else
	{
		if (PH_TMLNFC_WRITE_MESSAGE == pTransactionInfo->messageType)
		{
#ifdef LOGS
			//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, "(%s) TML context write message", __FUNCTION__);
#endif
			/* Reset the flag to accept another Write Request */
			gpphTmlNfc_Context->tWriteInfo.bThreadBusy = FALSE;
			gpphTmlNfc_Context->tWriteInfo.pThread_Callback(gpphTmlNfc_Context->tWriteInfo.pContext, \
					pTransactionInfo);
		}
		/* Message type can be either Read/Write ONLY */
		else
		{
#ifdef LOGS
			//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, "(%s) TML context read message", __FUNCTION__);
#endif
			/* Reset the flag to accept another Read Request */
			gpphTmlNfc_Context->tReadInfo.bThreadBusy = FALSE;
			gpphTmlNfc_Context->tReadInfo.pThread_Callback(gpphTmlNfc_Context->tReadInfo.pContext, \
					pTransactionInfo);
		}
	}

#ifdef LOGS
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (Out)", __FUNCTION__);
#endif
}

NFCSTATUS
phNfcTml_CreateWorkerThread(
		phTmlNfc_Context_t  *pphTmlNfc_Context
)
{
	NFCSTATUS nfcStatus = NFCSTATUS_SUCCESS;
#ifdef LOGS
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (In)", __FUNCTION__);
#endif
	if (NULL == pphTmlNfc_Context)
	{
#ifdef LOGS
		//CB TraceEvents(TRACE_LEVEL_ERROR, FLAG_TML, "(%s) TML context is NULL", __FUNCTION__);
#endif
		nfcStatus = NFCSTATUS_INVALID_PARAMETER;
	}
	else
	{
		/* Creating the Worker Thread for TML Read/Write operations */

		if (pthread_create(&(pphTmlNfc_Context->twWriteReadWorker), NULL, &phNfcTml_TmlThread, (void *)pphTmlNfc_Context))
		{
			nfcStatus = NFCSTATUS_FAILED;
		}
		if (0 == pphTmlNfc_Context->twWriteReadWorker)
		{
#ifdef LOGS
			//CB TraceEvents(TRACE_LEVEL_ERROR, FLAG_TML, "(%s) CreateThreadpoolWork failed (Error : %d)", __FUNCTION__, GetLastError());
#endif
			nfcStatus = NFCSTATUS_FAILED;
		}
		else
		{
			//PA: Join must be done remove that: pthread_detach(gpphTmlNfc_Context->twWriteReadWorker);
#ifdef LOGS
			//CB TraceEvents(TRACE_LEVEL_VERBOSE, FLAG_TML, "(%s) TCreateThreadpoolWork Success", __FUNCTION__);
#endif
            if(pthread_setname_np((pphTmlNfc_Context->twWriteReadWorker),"TML_WORKER_TSK"))
            {
                NXPLOG_NCIHAL_E("pthread_setname_np failed");
            }
		}
	}
#ifdef LOGS
	//CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (Out) :: Status 0x%X", __FUNCTION__, nfcStatus);
#endif
	return nfcStatus;
}
#if PHTMLNFC_DEFER_VEN_RESET

NFCSTATUS
phNfcTml_NfcControllerOperations(
		phTmlNfc_Context_t  *pphTmlNfc_Context
)
{
	NFCSTATUS nfcStatus = NFCSTATUS_SUCCESS;
	//     //CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (In)", __FUNCTION__);
	if (pphTmlNfc_Context->bVENResetRequested)
	{
		//CB TraceEvents(TRACE_LEVEL_VERBOSE, FLAG_TML, "(%s) Resetting NFC Controller", __FUNCTION__);
		nfcStatus = phTmlNfc_AbendResetPN547();
		((Locker*)pphTmlNfc_Context->hResetVENEvent)->lock();
		((Locker*)pphTmlNfc_Context->hResetVENEvent)->wakeUp(FALSE);
		((Locker*)pphTmlNfc_Context->hResetVENEvent)->unlock();
		pphTmlNfc_Context->bVENResetRequested = FALSE;
	}
	else if (pphTmlNfc_Context->bVENOffRequested)
	{
		//CB TraceEvents(TRACE_LEVEL_VERBOSE, FLAG_TML, "(%s) Turning Off NFC Controller", __FUNCTION__);
		nfcStatus = phTmlNfc_AbendPowerOffPN547();
		((Locker*)pphTmlNfc_Context->hResetVENEvent)->lock();
		((Locker*)pphTmlNfc_Context->hResetVENEvent)->wakeUp(FALSE);
		((Locker*)pphTmlNfc_Context->hResetVENEvent)->unlock();
		pphTmlNfc_Context->bVENOffRequested = FALSE;
	}
	else if (pphTmlNfc_Context->bVENOnRequested)
	{
		//CB TraceEvents(TRACE_LEVEL_VERBOSE, FLAG_TML, "(%s) Turning On NFC Controller", __FUNCTION__);
		nfcStatus = phTmlNfc_AbendPowerOnPN547();
		((Locker*)pphTmlNfc_Context->hResetVENEvent)->lock();
		((Locker*)pphTmlNfc_Context->hResetVENEvent)->wakeUp(FALSE);
		((Locker*)pphTmlNfc_Context->hResetVENEvent)->unlock();
		pphTmlNfc_Context->bVENOnRequested = FALSE;
	}
	else
	{
		//         //CB TraceEvents(TRACE_LEVEL_VERBOSE, FLAG_TML, "(%s) No IOCTL Operation On NFC Controller", __FUNCTION__);
	}
	//     //CB TraceEvents(TRACE_LEVEL_INFORMATION, FLAG_TML, " %s (Out) :: Status 0x%X", __FUNCTION__, nfcStatus);
	return nfcStatus;
}
#endif

void phTmlNfc_set_fragmentation_enabled(phTmlNfc_i2cfragmentation_t result)
{
    fragmentation_enabled = result;
}

phTmlNfc_i2cfragmentation_t phTmlNfc_get_fragmentation_enabled()
{
    return  fragmentation_enabled;
}
