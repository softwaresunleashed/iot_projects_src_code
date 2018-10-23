/*
*                    Copyright (c), NXP Semiconductors
*
*                       (C)NXP Electronics N.V. 2012
*
*         All rights are reserved. Reproduction in whole or in part is
*        prohibited without the written consent of the copyright owner.
*    NXP reserves the right to make changes without notice at any time.
*   NXP makes no warranty, expressed, implied or statutory, including but
*   not limited to any implied warranty of merchantability or fitness for any
*  particular purpose, or that the use will not infringe any third party patent,
*   copyright or trademark. NXP must not be liable for any loss or damage
*                            arising from its use.
*
*
*/

/**
*
* \file  phTmlNfcAbFpga_Abend.cpp
*
* Project:  PN547 Middleware
*
* $Date$
* $Author$
* $Revision$
*
*/

#ifdef PHFL_TML_ABEND

#define  _CRT_SECURE_NO_WARNINGS 1

//JF 05/12/2012
#define ABEND_CONSOLE_TRACES 0
#include "phTmlNfc_Abend.hpp"
#include "phPN547Dl_Common.h"
#include "phTmlNfc_APIWrapper.h"

#define VERBOSE_TAG "tml"
#include "core/Verbose.h"

extern "C"
{

#include <unistd.h>
#include "phNfcStatus.h"
//#include <phLog_Tml.h>
//#include <phLog_TmlH.h>
   //JF 04/09/2013 Add to customize the eSE type trough the file PN547.ini
   //#include "phLibNfc_FeatureConfiguration.h"

   //JF 20/06/2013 Cutomizable by the PN547.ini file
   extern bool_t gflagRfFieldNtf;
   extern bool_t gflagFwAutoUpdate;
   extern bool_t gflagEseUsed;
   extern bool_t gflagEmvcoProfile;
   extern uint8_t gu8_PnLink;
   //EndJF
}
#if ABEND_CONSOLE_TRACES
static void phTmlNfc_AbendDisplayPacket(uint32_t wSize, uint8_t *Data);
#endif

ARMBoardLibIntf *ab = NULL;
void * abendHandle = NULL;
//static void * pTxRxSem;

void * pTxRxMutex;

//ARMBoardLibIntf *ab = NULL;
//void * abendHandle = NULL;

#define USE_TIMEOUT 1



#define ABEND_DEVTYPE_I2C           (0x00)
#define ABEND_DEVTYPE_SPI           (0x01)
#define ABEND_DEVTYPE_HSU           (0x02)
#define ABEND_DEVTYPE_INVALID       (0xFF)

#define ABEND_DEV_TIMEOUT           (20)

/**
* Default value of Retry Count */
#define PH_TMLNFC_ABEND_RETRYCOUNT        (0x10)

static uint8_t phTmlNfc_GetDevType(int8_t *pDevName);

#if 0//ABEND_CONSOLE_TRACES
//PA: to be able to compile without the rest of the libnfc
#define PH_LOG_TML_CRIT_U32MSG(...) printf(__VA_ARGS__)
#define PH_LOG_TML_CRIT_STR(x)  printf("%s",x)
#define PH_LOG_TML_CRIT_X32MSG(...) printf(__VA_ARGS__)
#define PH_LOG_TML_FUNC_ENTRY() printf("--> %s\n",__FUNCTION__)
#define PH_LOG_TML_FUNC_EXIT() printf("<-- %s\n",__FUNCTION__)
#define PH_LOG_TMLH_INFO_HEXDATA(...)  printf(__VA_ARGS__)
#define PH_LOG_TML_CRIT_X32(x) printf("%X\n",x)
#define PH_LOG_TML_INFO_STR(...) printf("%s\n",x)
#else
#define PH_LOG_TML_CRIT_U32MSG(...)
#define PH_LOG_TML_CRIT_STR(x)
#define PH_LOG_TML_CRIT_X32MSG(...)
#define PH_LOG_TML_FUNC_ENTRY()
#define PH_LOG_TML_FUNC_EXIT()
#define PH_LOG_TMLH_INFO_HEXDATA(...)
#define PH_LOG_TML_CRIT_X32(x)
#define PH_LOG_TML_INFO_STR(...)
#endif


#define INVALID_HANDLE_VALUE NULL
//End PA

#define PRINT_AND_EXIT_IF_RET_NOT_ZERO  \
    if ( ret != 0 ) { \
	PH_LOG_TML_CRIT_U32MSG("Line = %d\n", __LINE__); \    
	PH_LOG_TML_CRIT_U32MSG("Failure from ABEND = %d. ", ret); \
	PH_LOG_TML_CRIT_STR("You may have to manually reset the ARM board\n"); \
	return ret; \
    }

static uint8_t abendLogFParam[100] = {0};

void abendLogF(void* context, wchar_t* logData) {
    wprintf(L":AB: %s\n",logData);
    UNUSED(context);
}

static uint8_t phTmlNfc_AbendOpenBoardConnection() {
    uint8_t ret = 0;
    wchar_t* ttyACM[] = {L"/dev/ttyACM0",L"/dev/ttyACM1",L"/dev/ttyACM2"};

    PH_LOG_TML_FUNC_ENTRY();
    for(uint8_t i = 0 ; i< 3 ; i++)
    {
	ret = ab->Open(&abendHandle, ttyACM[i],sizeof(ttyACM[i])/sizeof(wchar_t));
	if(ret == 0)
	{
		//Device found, continue...
		PH_LOG_TML_INFO_STR("device found on: %s\n",ttyACM[i]);
		break;
	}
    }

    if(ret != 0)
    {
	printf("ERROR: No device found on /dev/ttyACMx %d\n", ret);
	perror("open failed\n");
    }

    PRINT_AND_EXIT_IF_RET_NOT_ZERO

    /* ret += ab->SetLogF(abendHandle, abendLogF, abendLogFParam); */

    if ( ret == 0 )
	ret += phTmlNfc_AbendResetPN547();
    PH_LOG_TML_FUNC_EXIT();
    return ret;
}

static uint8_t phTmlNfc_AbendResetAndInitArmBoard() {
    uint8_t ret = 0;
    PH_LOG_TML_FUNC_ENTRY();
    PH_LOG_TML_CRIT_STR("Auto: Re-setting the ARM board");

    ret = ab->SetDeviceMode(abendHandle, PH_RPC_CMD_CTRLDEVMODE_RESETCHECK);
    if ( ret != 0 )
	PH_LOG_TML_CRIT_X32MSG("ARM Board Reboot: RESETCHECK status",ret);

    ret = ab->SetDeviceMode(abendHandle, PH_RPC_CMD_CTRLDEVMODE_RESETCHECK_REBOOT);

    if ( ret == 0 ) {
	PH_LOG_TML_CRIT_STR("Auto: Closing the ARM Board connection");
	ret = ab->Close(&abendHandle);
	PH_LOG_TML_CRIT_STR("Auto: Re-initializing the connection to ARM board. Delay 10 Seconds");
	usleep(200 * 1000); /* usleep for some time. before we restart talking to the board. */
	ret += phTmlNfc_AbendOpenBoardConnection();
	if ( ret == 0)
	    PH_LOG_TML_CRIT_STR("Auto: Successfully recovered ABEND.");
    } else {
	phRpc_Status_t * pabError = NULL;
	ab->GetLastABError(abendHandle, &pabError);
	if ( pabError != NULL ) {
	    PH_LOG_TML_CRIT_X32MSG("ARM Board Reboot: RESETCHECK_REBOOT status",ret);
	    PH_LOG_TML_CRIT_X32MSG("GetLastABError",pabError->CommStatusM);
	    PH_LOG_TML_CRIT_STR("Auto: Re-initializing the connection to ARM board. Delay 10 Seconds");
	}
	usleep(200 * 1000); /* usleep for some time. before we restart talking to the board. */
    }

    PH_LOG_TML_FUNC_EXIT();
    return ret;
}

static void setTimeout() {

    /* Reducing WTX for Abend using phRpc_H_SetTimeout */
    ab->SetTimeout(abendHandle, ABEND_DEV_TIMEOUT);

    /* Sunc btw host USB and LCP ARM board */
    ab->SetCommParam(abendHandle);
}

static uint8_t initializeAbend(int8_t * pDevName) {
    uint8_t ret = 0;
    uint8_t bDevType = 0;
    uint32_t dwI2cAddr = PH_RPC_IOCTL_OPT_DEV_I2C_SET_ADDRSEL_00;
    uint32_t ControlOpt = 0;
    uint32_t dwSpiSpeed = 6400000;
    uint8_t bActualDevType = 0;
    uint32_t dwTimeout = PH_RPC_IOCTL_OPT_EINT_TIMEOUT_INFINITE;
    phRpc_Status_t * pabError = NULL;
    bool_t fDutModeCorrect = TRUE;
    uint32_t u32HostInfoNum = 0;
    uint8_t * pu8HostInfoBuf = NULL;
    uint8_t u8u8HostInfoBufLen = 0;

    PH_LOG_TML_FUNC_ENTRY();
   //JF
   // Add section to allows to choose the link used and the address
   FILE *fp = NULL;
   // Remark : on the demoboard, if the resistor R49 and R58 are present, the I�C address is drive by the LPC
#warning "PA: the I2C address is set by default to 0x28"
   uint8_t I2CAddr = 0x28; // Default address
   char buff[255]= {0};
   
    ret += phTmlNfc_AbendOpenBoardConnection();

    if ( ret != 0 ) {
	/* Could not open the connection, so now re-boot the ARM Board itself. */
	ret = phTmlNfc_AbendResetAndInitArmBoard();
    }
    if ( ret != 0 )

    {
	/* Could not open yet. So now Unload the DLL and try again.*/
	PH_LOG_TML_CRIT_STR("Second re-try to recover ABEND");
	ret = ab->Close(&abendHandle);
	ab->DlUnload();
	usleep(1 * 1000);
	delete ab;
	ab = new ARMBoardLibIntf();
	ab->DlLoad();
//#if PA
	ret += phTmlNfc_AbendOpenBoardConnection();
//#endif
	if ( ret != 0 ) {
	    ret = phTmlNfc_AbendResetAndInitArmBoard();
	}
	if ( ret != 0 ) {
	    PH_LOG_TML_CRIT_STR("Second re-try failed. Kindly reset the ARM Board.");
	}
	PRINT_AND_EXIT_IF_RET_NOT_ZERO
    }

    ret += ab->GetHostInfo(abendHandle,PH_RPC_CMD_HOSTINFO_PCLIB_SWID,
	&u32HostInfoNum,&pu8HostInfoBuf,&u8u8HostInfoBufLen);
    if ( ret == 0 && u8u8HostInfoBufLen > 0 ) {
	PH_LOG_TML_CRIT_STR(pu8HostInfoBuf);
    }

    ret += ab->GetDeviceInfo(abendHandle,PH_RPC_CMD_DEVINFO_SWID,
	&u32HostInfoNum,&pu8HostInfoBuf,&u8u8HostInfoBufLen);
    if ( ret == 0 && u8u8HostInfoBufLen > 0 ) {
	PH_LOG_TML_CRIT_STR(pu8HostInfoBuf);
    }

    /* Get the device type has has to be opened */
    bDevType = phTmlNfc_GetDevType(pDevName);
    switch(bDevType)
    {
    case ABEND_DEVTYPE_I2C:
	/* Opening and initializing I2C */
      //JF 19/08/2013 To be accessible from UI
      //ret += ab->DutInit(abendHandle, PH_RPC_CMD_DEV_ENABLE_I2C, 40, 400000, 0, 0); PRINT_AND_EXIT_IF_RET_NOT_ZERO;
      ret += ab->DutInit(abendHandle, PH_RPC_CMD_DEV_ENABLE_I2C, I2CAddr, 400000, 0, 0); PRINT_AND_EXIT_IF_RET_NOT_ZERO;
      //EndJF
      ret += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_I2C_SET_ADDRSEL, PH_RPC_IOCTL_MN_VOID, &dwI2cAddr); PRINT_AND_EXIT_IF_RET_NOT_ZERO;
	bActualDevType = PH_RPC_CMD_DEV_ENABLE_I2C;
	break;
    case ABEND_DEVTYPE_SPI:
	/* Opening and initializing SPI */
	ret += ab->DutInit(abendHandle,
			   PH_RPC_CMD_DEV_ENABLE_SPI,
			   0,
			   dwSpiSpeed,
			   PH_RPC_CMD_DEV_SPI_CPOL_L,
			   PH_RPC_CMD_DEV_SPI_CPHA_1ST); PRINT_AND_EXIT_IF_RET_NOT_ZERO

	/* Disable Auto NSS */
	ret += ab->DutDevIoCtl(abendHandle,PH_RPC_IOCTL_MJ_DEV_SPI_AUTONSS,PH_RPC_IOCTL_MN_DISABLE, &ControlOpt); PRINT_AND_EXIT_IF_RET_NOT_ZERO
	bActualDevType = PH_RPC_CMD_DEV_ENABLE_SPI;
	break;
    case ABEND_DEVTYPE_HSU:
	ControlOpt = PH_RPC_IOCTL_OPT_NOT_APPLICABLE;
	/* Opening and initializing HSUART */
	ret += ab->DutInit(abendHandle,
			   PH_RPC_CMD_DEV_ENABLE_HSU,
			   0,
			   115200,
			   0,
			   0); PRINT_AND_EXIT_IF_RET_NOT_ZERO

	ControlOpt = PH_RPC_IOCTL_OPT_DEV_SET_DLLMODE_NCI;
	/* Set mode to NCI */
	ret += ab->DutDevIoCtl(abendHandle,
			       PH_RPC_IOCTL_MJ_DEV_SET_DLLMODE,
			       PH_RPC_IOCTL_MN_VOID,
			       &ControlOpt); PRINT_AND_EXIT_IF_RET_NOT_ZERO


	ControlOpt = PH_RPC_IOCTL_OPT_NOT_APPLICABLE;
	/* Deactivate SPI RAW mode */
	ret += ab->DutDevIoCtl(abendHandle,
			       PH_RPC_IOCTL_MJ_DEV_I2C_SPI_RAWMODE,
			       PH_RPC_IOCTL_MN_DISABLE,
			       &ControlOpt); PRINT_AND_EXIT_IF_RET_NOT_ZERO

	ControlOpt = PH_RPC_IOCTL_OPT_NOT_APPLICABLE;
	/* Enable CRC */
	ret += ab->DutDevIoCtl(abendHandle,
			       PH_RPC_IOCTL_MJ_DEV_CRC_ENABLE,
			       PH_RPC_IOCTL_MN_DISABLE,
			       &ControlOpt); PRINT_AND_EXIT_IF_RET_NOT_ZERO

	ControlOpt = PH_RPC_IOCTL_OPT_NOT_APPLICABLE;
	/* SOF TX disbale */
	ret += ab->DutDevIoCtl(abendHandle,
			       PH_RPC_IOCTL_MJ_DEV_TX_SOF_ENABLE,
			       PH_RPC_IOCTL_MN_DISABLE,
			       &ControlOpt); PRINT_AND_EXIT_IF_RET_NOT_ZERO

	ControlOpt = PH_RPC_IOCTL_OPT_NOT_APPLICABLE;
	/* SOF RX disbale */
	ret += ab->DutDevIoCtl(abendHandle,
			       PH_RPC_IOCTL_MJ_DEV_RX_SOF_ENABLE,
			       PH_RPC_IOCTL_MN_DISABLE,
			       &ControlOpt); PRINT_AND_EXIT_IF_RET_NOT_ZERO

	ControlOpt = PH_RPC_IOCTL_OPT_NOT_APPLICABLE;
	/* enable RTS/CTSe (activate hardware control flow) */
	ret += ab->DutDevIoCtl(abendHandle,
			       PH_RPC_IOCTL_MJ_DEV_HW_CTL_FLOW,
			       PH_RPC_IOCTL_MN_ENABLE,
			       &ControlOpt); PRINT_AND_EXIT_IF_RET_NOT_ZERO

	ControlOpt = PH_RPC_IOCTL_OPT_NOT_APPLICABLE;
	/* HSUART full duplex mode */
	ret += ab->DutDevIoCtl(abendHandle,
			       PH_RPC_IOCTL_MJ_DEV_FULL_DUPLEX_ENABLE,
			       PH_RPC_IOCTL_MN_DISABLE,
			       &ControlOpt); PRINT_AND_EXIT_IF_RET_NOT_ZERO

	ControlOpt = PH_RPC_IOCTL_OPT_NOT_APPLICABLE;
	/* EINT_SENSE DISABLE */
	ret += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_EINT_SENSE_ENABLE, PH_RPC_IOCTL_MN_DISABLE, &ControlOpt);
	PRINT_AND_EXIT_IF_RET_NOT_ZERO;

	bActualDevType = PH_RPC_CMD_DEV_ENABLE_HSU;
	break;
    default :
	/* Invalid device type */
	ret = 1; PRINT_AND_EXIT_IF_RET_NOT_ZERO
	break;
    }

    ControlOpt = PH_RPC_IOCTL_OPT_NOT_APPLICABLE;
    ret += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_I2C_SPI_RAWMODE, PH_RPC_IOCTL_MN_DISABLE, NULL); PRINT_AND_EXIT_IF_RET_NOT_ZERO

#if 1       // LPCBOARD_DELIVERY_20120312_X and later needs EINT disabled.
    ret += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_EINT_SENSE_ENABLE, PH_RPC_IOCTL_MN_DISABLE, NULL);
    PRINT_AND_EXIT_IF_RET_NOT_ZERO;
#else       // else older release.
    ret += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_EINT_SENSE_ENABLE, PH_RPC_IOCTL_MN_ENABLE, NULL);
#endif
    //phRpc_H_DevIoCtl(void *hdl, uint8_t ctrlMj, uint8_t ctrlMn, uint32_t *ctrlOpt);
    ret += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_FORCE_READ_ON_EXT_TIMEOUT, PH_RPC_IOCTL_MN_DISABLE, NULL); PRINT_AND_EXIT_IF_RET_NOT_ZERO
    ab->GetLastABError(abendHandle, &pabError);

    ControlOpt = PH_RPC_IOCTL_OPT_EINT_SENSE_LEVEL_H;
    ret += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_SET_EINT_SENSE, PH_RPC_IOCTL_MN_VOID, &ControlOpt); PRINT_AND_EXIT_IF_RET_NOT_ZERO

    ControlOpt = PH_RPC_IOCTL_OPT_DEV_SET_DLLMODE_NONE;
    ret += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_SET_DLLMODE, PH_RPC_IOCTL_MN_VOID, &ControlOpt); PRINT_AND_EXIT_IF_RET_NOT_ZERO
    ab->GetLastABError(abendHandle, &pabError);

    ControlOpt = PH_RPC_IOCTL_OPT_NOT_APPLICABLE;
    ret += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_CRC_ENABLE, PH_RPC_IOCTL_MN_DISABLE, NULL); PRINT_AND_EXIT_IF_RET_NOT_ZERO


    ControlOpt = PH_RPC_IOCTL_OPT_DEV_SET_DLLMODE_NCI;
    //ControlOpt = PH_RPC_IOCTL_OPT_DEV_SET_DLLMODE_NONE;
    ret += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_SET_DLLMODE, PH_RPC_IOCTL_MN_VOID, &ControlOpt); PRINT_AND_EXIT_IF_RET_NOT_ZERO

    ab->GetLastABError(abendHandle, &pabError);
    ret += ab->DutDevIoLineCtl(abendHandle, PH_RPC_IO_LINE_CTL_DWL_REQ, PH_RPC_IO_LINE_CTL_ACT_OFF, NULL); PRINT_AND_EXIT_IF_RET_NOT_ZERO
    ab->GetLastABError(abendHandle, &pabError);
    //        ret += ab->DutDevIoLineCtl(abendHandle, PH_RPC_IO_LINE_CTL_CLK_REQ, PH_RPC_IO_LINE_CTL_ACT_OFF, NULL); PRINT_AND_EXIT_IF_RET_NOT_ZERO

    ab->GetLastABError(abendHandle, &pabError);


    ret += ab->DutDevIoLineCtl(abendHandle, PH_RPC_IO_LINE_CTL_VEN, PH_RPC_IO_LINE_CTL_ACT_OFF, NULL); PRINT_AND_EXIT_IF_RET_NOT_ZERO
    usleep(100);
    //       ret += ab->DutDevIoLineCtl(abendHandle, PH_RPC_IO_LINE_CTL_CLK_REQ, PH_RPC_IO_LINE_CTL_ACT_ON, NULL); PRINT_AND_EXIT_IF_RET_NOT_ZERO
    usleep(100);
    ret += ab->DutDevIoLineCtl(abendHandle, PH_RPC_IO_LINE_CTL_VEN, PH_RPC_IO_LINE_CTL_ACT_ON, NULL); PRINT_AND_EXIT_IF_RET_NOT_ZERO
    usleep(100);

    ab->GetLastABError(abendHandle, &pabError);

    uint32_t dutMode = 0;
    ret += ab->DutGetMode(abendHandle, &dutMode); PRINT_AND_EXIT_IF_RET_NOT_ZERO

    if (bActualDevType != ((dutMode & PH_PN547DL_MODE_MASK)
	>> PH_PN547DL_MODE_SHIFT))
	fDutModeCorrect = false;
    if (PH_RPC_IOCTL_OPT_DEV_SET_DLLMODE_NCI != ((dutMode
	& PH_PN547DL_DLLMODE_MASK) >> PH_PN547DL_DLLMODE_SHIFT))
	fDutModeCorrect = false;
    //TODO: More comparisions

    if (!fDutModeCorrect)
    {
	PH_LOG_TML_CRIT_STR("Could not enable I2C on ARM Board\n");
	(void) ab->Close(&abendHandle);
	abendHandle = NULL;
	ret++;
    }

    if (ret == 0 ){
	uint32_t irqSenseTimeout = 20;  // just get blocked for very small time to sense irq.
	uint16_t irqStatus;
	// set the time out to irqSenseTimeout=20ms.
	// if we get "0002" --> we are using firmware with the feature of
	//                      PH_RPC_IOCTL_MJ_DEV_SET_EINT_TIMEOUT
	// if we get "000F9" --> we are using DORETHEA or older ABEND Firmware.
	ret += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_SET_EINT_TIMEOUT, PH_RPC_IOCTL_MN_VOID, &irqSenseTimeout);
	irqStatus = phTmlNfc_AbendWaitForIRQ();

	// if we get that IRQ is not yet implemented
	if ((irqStatus & 0xFF) == PH_RPC_STATUS_E_INVALID_REQ) {
	    ret += 1; //increment error counter. We are on wrong ABEND Version.
	}
	// else nothing to do. even if we get timeout.
    }
    // we are re-setting the interrupt wait timeout.
    ret += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_SET_EINT_TIMEOUT, PH_RPC_IOCTL_MN_VOID, &dwTimeout);

    setTimeout();

    return ret;
}

void *phTmlNfc_AbendOpen(int8_t *pDevName)
{
    uint8_t ret = 0;

    if(NULL != pDevName)
    {
	ab = new ARMBoardLibIntf();
	ab->DlLoad();

	if (ab->IsValid())
	{
	    ret = initializeAbend(pDevName);

	    if (ret == 0)
	    {
		//phOsalNfc_CreateSemaphore(&pTxRxSem, 0, 1);
	    }
	    else
	    {
		PH_LOG_TML_CRIT_STR("Some operation failed for abend. RET != 0\n");
		(void) ab->Close(&abendHandle);
		abendHandle = NULL;
	    }
	}
	if (abendHandle == NULL)
	    // this is how the upper layer understands that there was a failure.
	    abendHandle = INVALID_HANDLE_VALUE;
    }
    else
    {
	abendHandle = INVALID_HANDLE_VALUE;
    }
    //PA: Warning on cast printf("abdendHandle = %d\n", (int)abendHandle);
    
  //   printf("abdendHandle = %p\n", abendHandle);
    return abendHandle;
}

//PA
static uint8_t canceledIO = FALSE;

uint16_t phTmlNfc_AbendCancelIo(void)
{
    uint8_t ret = 0;

#if 0 //ABEND_CONSOLE_TRACES
    char szprintBuffer[1000];
    sprintf(szprintBuffer,"%s\n", __FUNCTION__); phOsalNfc_DbgString(szprintBuffer);
#endif
    ret = ab->CancelIo(abendHandle);
#if 0 //ABEND_CONSOLE_TRACES
    sprintf(szprintBuffer,"%s ret=%d\n", __FUNCTION__, ret);
    phOsalNfc_DbgString(szprintBuffer);
#endif

    canceledIO = TRUE;

    return ret;
}


int phTmlNfc_AbendTx(uint8_t *pBuff, uint16_t buffLen,
			   uint16_t *pBytesWritten)
{
    uint8_t ret = 0;
    uint8_t abendTxLastError = 0;
    uint8_t bRetryCount = 0;
    uint16_t Len = buffLen;
    uint8_t ** pTxBuff;
    uint8_t *pTxTempBuff = pBuff;
    phRpc_Status_t * pabError = NULL;

#if ABEND_CONSOLE_TRACES
    char szprintBuffer[1000];
#endif
    PH_LOG_TML_FUNC_ENTRY();
    //  usleep(100);
#if ABEND_CONSOLE_TRACES
    PH_LOG_TMLH_INFO_HEXDATA("TX",pBuff,buffLen);
    sprintf(szprintBuffer,"%s %d\n", __FUNCTION__, Len); phOsalNfc_DbgString(szprintBuffer);
    sprintf(szprintBuffer,"DutTx(Len=%d)\n",Len); phOsalNfc_DbgString(szprintBuffer);
    phTmlNfc_AbendDisplayPacket(Len, pBuff);
#endif

    canceledIO = FALSE;//PA: reset canceled IO

    do
    {
	abendTxLastError = 0;
	pTxTempBuff = pBuff;
	pTxBuff = &pTxTempBuff;
	Len = buffLen;

#define ENABLE_RX_TX_TRACES 0
#if ENABLE_RX_TX_TRACES
	printf("Tx --> ");
	for (int i=0; i < Len; i++) {
		printf("%02X ", *(pBuff+i));
	}
	printf("\n");
#endif

	ret = ab->DutTx(abendHandle, pTxBuff, &Len);
	ab->GetLastABError(abendHandle, &pabError);
	abendTxLastError = PH_RPC_GET_STATUS(pabError);

#if ABEND_CONSOLE_TRACES
	sprintf(szprintBuffer,"%s Len=%d ret=%d\n", __FUNCTION__, Len, ret);phOsalNfc_DbgString(szprintBuffer);
	sprintf(szprintBuffer,"TX PH_RPC_GET_STATUS(pabError)=%02X\n", abendTxLastError);phOsalNfc_DbgString(szprintBuffer);
#endif

	if ( abendTxLastError != 0 ) {
	    PH_LOG_TML_CRIT_X32(abendTxLastError);
	    bRetryCount++;
	    usleep(1000);
	}
    } 	while( (   (abendTxLastError == PH_RPC_STATUS_W_LESS_DATA)
		||	(abendTxLastError == PH_RPC_STATUS_E_FRAMING)	)
		&&	(bRetryCount < PH_TMLNFC_ABEND_RETRYCOUNT) );

#if ABEND_CONSOLE_TRACES
    printf("--------------------\n");
    printf("%s: bRetryCount = %d\n", __FUNCTION__, bRetryCount);
    printf("--------------------\n");
#endif

    if (ret != 0)
	Len = 0;
    if (Len == 0 && ret == 0) //successful Tx
	Len = buffLen;
    *pBytesWritten = Len;
    PH_LOG_TML_FUNC_EXIT();
    //return (int) Len;
    //CB
    return ret; //NFCSTATUS_SUCCESS
}

#define MINVAL(X,Y) (X) < (Y) ? (X) : (Y)

/* return 0, if successful,
* else send the abend API ret val in upper 8 bits, and lasterror in lower 8 bits.
*/
uint16_t phTmlNfc_AbendWaitForIRQ() {
    uint16_t ret = 0;
    phRpc_Status_t * pabError = NULL;
    uint8_t lastError = 0;
#if ABEND_CONSOLE_TRACES
    char szprintBuffer[1000];

    sprintf(szprintBuffer,"WaitForIRQ..");phOsalNfc_DbgString(szprintBuffer);
#endif
    PH_LOG_TML_FUNC_ENTRY();
    ret = ab->DutDevIoCtl(abendHandle,
	PH_RPC_IOCTL_MJ_DEV_WAIT_IRQ,
	PH_RPC_IOCTL_MN_VOID,
	NULL);
    ab->GetLastABError(abendHandle, &pabError);
    lastError = PH_RPC_GET_STATUS(pabError);

    if (lastError == PH_RPC_STATUS_E_INVALID_REQ) {
	/* FIXME: Remove this warning at later point of time */
	printf("###################################################################\n");
	printf("!ERROR! Please upgrade to Latest release of ABEND Firmware.\n");
	printf("Press any key to continue...");
	getchar();
    }

#if ABEND_CONSOLE_TRACES
    sprintf(szprintBuffer,"..ret=%d,lastError=0x%02X\n",ret,lastError);phOsalNfc_DbgString(szprintBuffer);
#endif
    PH_LOG_TML_FUNC_EXIT();
    return (ret <<8 | lastError);
}

int phTmlNfc_AbendRx(uint8_t *pBuff, uint16_t buffLen,
			   uint16_t *pBytesRead)
{
    uint8_t ret = 0;
    uint8_t abendRxLastError =0;
    uint8_t * outBuff;
    uint16_t Len = 300;//buffLen;
    uint8_t retryCounter = 0;
    uint16_t waitForIrqStatus = 0;

#if ABEND_CONSOLE_TRACES
    char szprintBuffer[1000];

    //  sprintf(szprintBuffer,"%s-Enter\n", __FUNCTION__);phOsalNfc_DbgString(szprintBuffer);
#endif

    PH_LOG_TML_FUNC_ENTRY();

    /*Alow write to finish if requested to write*/
    memset(pBuff, ~0, buffLen);

#if ABEND_CONSOLE_TRACES
    sprintf(szprintBuffer,"DutRx(RxLen=%d)\n",buffLen);phOsalNfc_DbgString(szprintBuffer);
#endif


    waitForIrqStatus = phTmlNfc_AbendWaitForIRQ();

    if(waitForIrqStatus == 0)
    {

retry:
		ret = ab->DutRx(abendHandle, &outBuff, &Len);

		phRpc_Status_t * pabError = NULL;
		ab->GetLastABError(abendHandle, &pabError);
		abendRxLastError = PH_RPC_GET_STATUS(pabError);

#if ABEND_CONSOLE_TRACES
		if ( abendRxLastError != 0) {
			PH_LOG_TML_CRIT_X32(abendRxLastError);
		}
		else
		{
			PH_LOG_TMLH_INFO_HEXDATA("RX",outBuff,Len);
		}

		sprintf(szprintBuffer,"%s Len=%d ret=%d\n", __FUNCTION__, Len, ret);phOsalNfc_DbgString(szprintBuffer);
		sprintf(szprintBuffer,"RX PH_RPC_GET_STATUS(pabError)=%02X\n", abendRxLastError);phOsalNfc_DbgString(szprintBuffer);
#endif

		if (ret == 0 && Len < 261) //magic 100. NCI would never send this long buffer.
		{
			if(abendRxLastError == PH_RPC_STATUS_OK && Len != 0)
			{
				memcpy(pBuff, outBuff, MINVAL(Len,buffLen));

#if ABEND_CONSOLE_TRACES
				phTmlNfc_AbendDisplayPacket(MINVAL(Len,buffLen), pBuff);
#endif
			}
			else
			{

#if ABEND_CONSOLE_TRACES
				sprintf(szprintBuffer,"RX Retry=PH_RPC_GET_STATUS(pabError)=%02X\n", abendRxLastError);phOsalNfc_DbgString(szprintBuffer);
#endif
				//PA: Add retry mechanism
				retryCounter++;

				Len = 300; //Not null value is required by libAbend to retry
				if(canceledIO != TRUE)
				{
					usleep(5000);
					goto retry;
				}
				else
				{
#if ABEND_CONSOLE_TRACES
					sprintf(szprintBuffer,"%s: canceled",__FUNCTION__);phOsalNfc_DbgString(szprintBuffer);
#endif
					Len = 0;
					canceledIO = FALSE;
					ret = 0x96; //Aborted by upper layer
				}
			}
		}
		else
		{
#if ABEND_CONSOLE_TRACES
			//error here.
			sprintf(szprintBuffer,"%s: ret = %d retry",__FUNCTION__, ret);phOsalNfc_DbgString(szprintBuffer);
#endif
			Len = 0;
			//PA: Add retry mechanism
			retryCounter++;
			if(retryCounter < 100 && canceledIO != TRUE)
			{
				usleep(10000);
				Len = 300; //Not null value is required by libAbend to retry
				goto retry;
			}
			else if(canceledIO == TRUE)
			{
#if ABEND_CONSOLE_TRACES
				sprintf(szprintBuffer,"%s: canceled",__FUNCTION__);phOsalNfc_DbgString(szprintBuffer);
#endif
				canceledIO = FALSE;
				ret = 0x96; //Aborted in upper layer
			}
			else
			{
#if ABEND_CONSOLE_TRACES
				sprintf(szprintBuffer,"%s: retry > 100 --> return failed",__FUNCTION__);phOsalNfc_DbgString(szprintBuffer);
#endif
			}
		}

    }
    else
    {
#if ABEND_CONSOLE_TRACES
	printf("Wait for IRQ error %d\n",waitForIrqStatus);
#endif
	ret = 0x01; //--> raised an error
	Len = 0;
    }

    if (Len != 0)
    {
		*pBytesRead = Len;
#if ENABLE_RX_TX_TRACES
		printf("Rx <-- ");
		for (int i=0; i < Len; i++) {
			printf("%02X ", *(pBuff+i));
		}
		printf("\n");
#endif

    }

    PH_LOG_TML_FUNC_EXIT();
    //CB return (int) Len;
    return ret;
}

void phTmlNfc_AbendClose()
{
    uint8_t retVal = 0;
    PH_LOG_TML_FUNC_ENTRY();
    if (ab != NULL && abendHandle != NULL )
    {
	retVal = ab->Close(&abendHandle);
	delete ab;
	ab = NULL;
    }
    PH_LOG_TML_FUNC_EXIT();
}

NFCSTATUS phTmlNfc_AbendEnterDnldMode(void)
{
    NFCSTATUS wStatus = NFCSTATUS_SUCCESS;
    uint8_t retVal = 0;
    phRpc_Status_t * pabError = NULL;
    uint32_t ControlOpt = PH_RPC_IOCTL_OPT_DEV_SET_DLLMODE_DNLD;
    PH_LOG_TML_FUNC_EXIT();
    if (ab != NULL && abendHandle != NULL )
    {
	retVal += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_SET_DLLMODE, PH_RPC_IOCTL_MN_VOID, &ControlOpt);
	ab->GetLastABError(abendHandle, &pabError);

	//retVal += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_CRC_ENABLE, PH_RPC_IOCTL_MN_DISABLE, NULL);
	//ab->GetLastABError(abendHandle, &pabError);

	if (retVal > 0)
	{
	    PH_LOG_TML_CRIT_STR("No connection to ARMboard!\n");
	    wStatus = NFCSTATUS_FAILED;
	}
	else
	{
	    retVal += ab->DutDevIoLineCtl(abendHandle, PH_RPC_IO_LINE_CTL_DWL_REQ, PH_RPC_IO_LINE_CTL_ACT_ON, NULL);
	    ab->GetLastABError(abendHandle, &pabError);

	    retVal += ab->DutDevIoLineCtl(abendHandle, PH_RPC_IO_LINE_CTL_CLK_REQ, PH_RPC_IO_LINE_CTL_ACT_ON, NULL);
	    ab->GetLastABError(abendHandle, &pabError);
/*
	    uint32_t dutMode = 0;
	    retVal += ab->DutGetMode(abendHandle, &dutMode);

	    if (PH_RPC_IOCTL_OPT_DEV_SET_DLLMODE_DNLD != ((dutMode
		& PH_PN547DL_DLLMODE_MASK) >> PH_PN547DL_DLLMODE_SHIFT))
	    {
		phOsalNfc_DbgString("Enable Download mode Failed on ARM Board\n");
		wStatus = NFCSTATUS_FAILED;
	    }
*/
	    phTmlNfc_AbendResetPN547();
	}
    }
    PH_LOG_TML_FUNC_EXIT();
    return wStatus;
}

NFCSTATUS phTmlNfc_AbendEnterNormalMode(void)
{
    NFCSTATUS wStatus = NFCSTATUS_SUCCESS;
    uint8_t retVal = 0;
    phRpc_Status_t * pabError = NULL;
    uint32_t ControlOpt = PH_RPC_IOCTL_OPT_DEV_SET_DLLMODE_NCI;
    PH_LOG_TML_FUNC_ENTRY();
    if (ab != NULL && abendHandle != NULL )
    {
	retVal += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_SET_DLLMODE, PH_RPC_IOCTL_MN_VOID, &ControlOpt);
	ab->GetLastABError(abendHandle, &pabError);

	retVal += ab->DutDevIoCtl(abendHandle, PH_RPC_IOCTL_MJ_DEV_CRC_ENABLE, PH_RPC_IOCTL_MN_DISABLE, NULL);
	ab->GetLastABError(abendHandle, &pabError);

	if (retVal > 0)
	{
	    PH_LOG_TML_CRIT_STR("No connection to ARMboard!\n");
	}
	else
	{
	    retVal += ab->DutDevIoLineCtl(abendHandle, PH_RPC_IO_LINE_CTL_DWL_REQ, PH_RPC_IO_LINE_CTL_ACT_OFF, NULL);
	    ab->GetLastABError(abendHandle, &pabError);

	    retVal += ab->DutDevIoLineCtl(abendHandle, PH_RPC_IO_LINE_CTL_CLK_REQ, PH_RPC_IO_LINE_CTL_ACT_OFF, NULL);
	    ab->GetLastABError(abendHandle, &pabError);

	    /*
	    uint32_t dutMode = 0;
	    retVal += ab->DutGetMode(abendHandle, &dutMode);

	    if (PH_RPC_IOCTL_OPT_DEV_SET_DLLMODE_NONE != ((dutMode
		& PH_PN547DL_DLLMODE_MASK) >> PH_PN547DL_DLLMODE_SHIFT))
	    {
		phOsalNfc_DbgString("Enable Normal mode Failed on ARM Board\n");
		wStatus = NFCSTATUS_FAILED;
	    }*/

	    phTmlNfc_AbendResetPN547();
	}
    }
    PH_LOG_TML_FUNC_EXIT();
    return wStatus;
}

uint8_t phTmlNfc_AbendResetPN547(void)
{
    uint8_t ret = 0;
    phRpc_Status_t * pabError = NULL;
    PH_LOG_TML_FUNC_ENTRY();
    if (ab != NULL && abendHandle != NULL )
    {
	//Reset PN547
	PH_LOG_TML_INFO_STR("Resetting PN547 via VEN");
	/*when fw update is interrupted and next fw update is tried then this
	function is getting failed. with 50ms delay, next fw update happens successfully*/
	usleep(50);
	ret += ab->DutDevIoLineCtl(abendHandle, PH_RPC_IO_LINE_CTL_VEN, PH_RPC_IO_LINE_CTL_ACT_OFF, NULL);
	PRINT_AND_EXIT_IF_RET_NOT_ZERO
	usleep(100);

	ret += ab->DutDevIoLineCtl(abendHandle, PH_RPC_IO_LINE_CTL_VEN, PH_RPC_IO_LINE_CTL_ACT_ON, NULL);
	PRINT_AND_EXIT_IF_RET_NOT_ZERO
	usleep(100);

	ab->GetLastABError(abendHandle, &pabError);
    }
    PH_LOG_TML_FUNC_EXIT();
    return ret;
}

uint8_t phTmlNfc_AbendPowerOffPN547(void)
{
    uint8_t ret = 0;
    phRpc_Status_t * pabError = NULL;
    PH_LOG_TML_FUNC_ENTRY();
    if (ab != NULL && abendHandle != NULL )
    {
	//Turn Off PN547
	PH_LOG_TML_INFO_STR("Turning PN547 Off via VEN");
	ret += ab->DutDevIoLineCtl(abendHandle, PH_RPC_IO_LINE_CTL_VEN, PH_RPC_IO_LINE_CTL_ACT_LOW, NULL);
	PRINT_AND_EXIT_IF_RET_NOT_ZERO
	usleep(100);

	ab->GetLastABError(abendHandle, &pabError);
    }
    PH_LOG_TML_FUNC_EXIT();
    return ret;
}

uint8_t phTmlNfc_AbendPowerOnPN547(void)
{
    uint8_t ret = 0;
    phRpc_Status_t * pabError = NULL;
    PH_LOG_TML_FUNC_ENTRY();
    if (ab != NULL && abendHandle != NULL )
    {
	//Turn On PN547
	PH_LOG_TML_INFO_STR("Turning PN547 On via VEN");
	ret += ab->DutDevIoLineCtl(abendHandle, PH_RPC_IO_LINE_CTL_VEN, PH_RPC_IO_LINE_CTL_ACT_HIGH, NULL);
	PRINT_AND_EXIT_IF_RET_NOT_ZERO
	usleep(100);

	ab->GetLastABError(abendHandle, &pabError);
    }
    PH_LOG_TML_FUNC_EXIT();
    return ret;
}

static uint8_t phTmlNfc_GetDevType(int8_t *pDevName)
{
    uint8_t bDevType = ABEND_DEVTYPE_INVALID;

    /* Input parameter NULL check is not required as it is being performed in the calling function */
    if(!memcmp(pDevName,"I2C",3))
    {
	bDevType = (uint8_t )ABEND_DEVTYPE_I2C;
    }
    else if(!memcmp(pDevName,"SPI",3))
    {
	bDevType = (uint8_t )ABEND_DEVTYPE_SPI;
    }
    else if(!memcmp(pDevName,"HSU",3))
    {
	bDevType = (uint8_t )ABEND_DEVTYPE_HSU;
    }
    else
    {
	/* Return invalid device type */
    }
    return bDevType;
}

#if ABEND_CONSOLE_TRACES
static void phTmlNfc_AbendDisplayPacket(uint32_t wSize, uint8_t *Data)
{
    //usleep(100);
    phOsalNfc_DbgPrintData(Data, wSize);
    phOsalNfc_DbgString("\n");
    return;
}
#endif

#if defined(ABEND_TRACE_ENABLED) && ABEND_TRACE_ENABLED == 1
void ARMBoardLibIntf::DumpBufferToFile(const  uint8_t * const  buff, const uint16_t len) {
    int printLen = 0;
#   if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
    if ( len > PRINT_IN_ONE_LINE )
	fprintf(fpDumpTextLogs,"BUFF:\n");
    else
	fprintf(fpDumpTextLogs,"BUFF:");
#   endif
    for (printLen = 0 ; printLen < len; printLen++) {
#   if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
	fprintf(fpDumpTextLogs," %02X",buff[printLen]);
#   endif
	if (this->fpDumpCSVLogs != NULL)
	    fprintf(this->fpDumpCSVLogs,"%02X ",buff[printLen]);
#   if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
	if ( ((printLen+1) % PRINT_IN_ONE_LINE) == 0)
	    fprintf(fpDumpTextLogs,"\n");
#   endif
    }
#   if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
    fprintf(fpDumpTextLogs,"\n");
    fflush(this->fpDumpTextLogs);
#   endif
    if (this->fpDumpCSVLogs != NULL)
	fprintf(this->fpDumpCSVLogs,CSV_SEPARATOR);
}

#endif /* ABEND_TRACE_ENABLED */

#endif /* PHFL_TML_ABEND */
