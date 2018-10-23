#ifndef ARMBOARD_LIB_INTF
#define ARMBOARD_LIB_INTF

#include "phNfcTypes.h"
#include "LibIntf.hpp"
#include "phRpc_H.h"
#include <sstream>
#include <stdio.h>

//PA
#include "phRpc_Status.h"

typedef enum AbendOperation {
    AbendOperation_Rx = 2,
    AbendOperation_Tx = 3,
    AbendOperation_Last
} AbendOperation_t;

class ARMBoardLibIntf : public LibIntf
{
    public:

    ARMBoardLibIntf() : LibIntf(),
                        // Members
                        Open(NULL),
                        OpenL(NULL),
                        OpenLH(NULL),
                        OpenLHF(NULL),
                        Close(NULL),
                        SetTimeout(NULL),
                        GetCompatibilityInfo(NULL),
                        GetLastABError(NULL),
                        GetErrorText(NULL),
                        GetHostErrorText(NULL),
                        GetHostCtxText(NULL),
                        GetBuffers(NULL),
                        SetLogF(NULL),
                        SetHookF(NULL),
                        HostIoCtl(NULL),
                        GetHostInfo(NULL),
                        CancelIo(NULL),
                        SetLockD(NULL),

                        Raw(NULL),

                        SetCommParam(NULL),
                        GetDeviceInfo(NULL),
                        CtrlDeviceDiag(NULL),
                        SetDeviceMode(NULL),
                        GetDeviceCtInfo(NULL),

                        EE(NULL),
                        EECfg(NULL),

                        StartTestSW(NULL),
                        StopTestSW(NULL),
                        DataExchangeTestSW(NULL),

                        DutInit(NULL),
                        DutGetMode(NULL),
#if defined(ABEND_TRACE_ENABLED) && ABEND_TRACE_ENABLED == 1
                        DutRx_Real(NULL),
                        DutTx_Real(NULL),
                        DutDevIoCtl_Real(NULL),
#else
                        DutRx(NULL),
                        DutTx(NULL),
                        DutDevIoCtl(NULL),
#endif
                        DutDevIoLineCtl(NULL),
                        DutSetMinMode(NULL),

                        CommCheck(NULL),
                        CommCheckLong(NULL),
                        CommCheckWtx(NULL)
    {
#     if defined PH_RPC_H_PLAT_WINDOWS
#     if defined PH_RPC_H_PLAT_WINDOWS_64
        this->LibName = (wchar_t*)L"ARMBoard_x64.dll";
#     else
        this->LibName = (wchar_t*)L"ARMBoard.dll";
#     endif
#     elif defined PH_RPC_H_PLAT_MACOS
        this->LibName = (wchar_t*)L"ARMBoard.dylib";   // Executable Prefix, Executable Extension
#     elif defined PH_RPC_H_PLAT_IOS
        this->LibName = (wchar_t*)L"iOS-Library.a";     // unused - will use RTLD_DEFAULT as LibHandle
#       warning iOS lib
#     elif defined PH_RPC_H_PLAT_LINUX
        this->LibName = (wchar_t*)L"libARMBoard.so";
#     else
#       error No Platform Definition
#     endif
    }

    ARMBoardLibIntf(wchar_t *libName) : LibIntf(),
                                        // Members
                                        Open(NULL),
                                        OpenL(NULL),
                                        OpenLH(NULL),
                                        OpenLHF(NULL),
                                        Close(NULL),
                                        SetTimeout(NULL),
                                        GetCompatibilityInfo(NULL),
                                        GetLastABError(NULL),
                                        GetErrorText(NULL),
                                        GetHostErrorText(NULL),
                                        GetHostCtxText(NULL),
                                        GetBuffers(NULL),
                                        SetLogF(NULL),
                                        SetHookF(NULL),
                                        HostIoCtl(NULL),
                                        GetHostInfo(NULL),
                                        CancelIo(NULL),
                                        SetLockD(NULL),

                                        Raw(NULL),

                                        SetCommParam(NULL),
                                        GetDeviceInfo(NULL),
                                        CtrlDeviceDiag(NULL),
                                        SetDeviceMode(NULL),
                                        GetDeviceCtInfo(NULL),

                                        EE(NULL),
                                        EECfg(NULL),

                                        StartTestSW(NULL),
                                        StopTestSW(NULL),
                                        DataExchangeTestSW(NULL),

                                        DutInit(NULL),
                                        DutGetMode(NULL),
#if defined(ABEND_TRACE_ENABLED) && ABEND_TRACE_ENABLED == 1
                                        DutRx_Real(NULL),
                                        DutTx_Real(NULL),
                                        DutDevIoCtl_Real(NULL),
#else
                                        DutRx(NULL),
                                        DutTx(NULL),
                                        DutDevIoCtl(NULL),
#endif
                                        DutDevIoLineCtl(NULL),
                                        DutSetMinMode(NULL),

                                        CommCheck(NULL),
                                        CommCheckLong(NULL),
                                        CommCheckWtx(NULL)
    {
        this->SetLibName(libName);
    }

    virtual ~ARMBoardLibIntf()
    {
        this->DlUnload();
    }

    // Substitute Functions
    static phRpc_H_Return_t Gci(void *h, uint8_t *info)
    {
        if (NULL != info)
        {
            *info = PH_RPC_H_COMPAT_ERROR;
        }
        (void)h;
        return PH_RPC_H_STATUS_OK;
    }

    static phRpc_H_Return_t Sld(void *h, pphRpc_H_LockD_t lockD, void *userData)
    {
        (void)h;
        (void)lockD;
        (void)userData;
        return PH_RPC_H_STATUS_OK;
    }

    // Function Pointers to the individual library members: These "Pseudo-Members" can be called by
    // the application code.
    pphRpc_H_Open_t                 Open;
    pphRpc_H_OpenL_t                OpenL;
    pphRpc_H_OpenLH_t               OpenLH;
    pphRpc_H_OpenLHF_t              OpenLHF;
    pphRpc_H_Close_t                Close;
    pphRpc_H_SetTimeout_t           SetTimeout;
    pphRpc_H_GetCompatibilityInfo_t GetCompatibilityInfo;

#if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
    pphRpc_H_GetLastError_t         GetLastABError_Real;

    uint8_t GetLastABError(void *hdl, phRpc_Status_t **lastError) {
        uint8_t retVal = 0;
        phRpc_Status_t * pLastError;
        retVal = this->GetLastABError_Real(hdl,lastError);
        pLastError = * lastError;
        if ( pLastError == NULL )
            fprintf(this->fpDumpTextLogs,"GetLastError: pLastError=NULL. retVal=0x%02X\n",retVal);
        else
            fprintf(this->fpDumpTextLogs,"GetLastError: CommStatusM=0x%02X\n",pLastError->CommStatusM);
        return retVal;
    }
#else
    pphRpc_H_GetLastError_t         GetLastABError;
#endif
    pphRpc_H_GetErrorText_t         GetErrorText;
    pphRpc_H_GetHostErrorText_t     GetHostErrorText;
    pphRpc_H_GetHostCtxText_t       GetHostCtxText;
    pphRpc_H_GetBuffers_t           GetBuffers;
    pphRpc_H_SetLogF_t              SetLogF;
    pphRpc_H_SetHookF_t             SetHookF;
    pphRpc_H_HostIoCtl_t            HostIoCtl;
    pphRpc_H_GetHostInfo_t          GetHostInfo;
#if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
    pphRpc_H_CancelIo_t             CancelIo_Real;

    uint8_t CancelIo(void *hdl) {
        uint8_t retVal = 0;
        fprintf(this->fpDumpTextLogs,"CancelIo:(Call)\n");
        retVal = this->CancelIo_Real(hdl);
        fprintf(this->fpDumpTextLogs,"CancelIo:(Ret) retVal=0x%02X\n",retVal);
        return retVal;
    }
#else
    pphRpc_H_CancelIo_t             CancelIo;
#endif

    pphRpc_H_SetLockD_t             SetLockD;
    pphRpc_H_Raw_t                  Raw;

    pphRpc_H_SetCommParam_t         SetCommParam;
    pphRpc_H_GetDeviceInfo_t        GetDeviceInfo;
    pphRpc_H_CtrlDeviceDiag_t       CtrlDeviceDiag;
    pphRpc_H_SetDeviceMode_t        SetDeviceMode;
    pphRpc_H_GetDeviceCtInfo_t      GetDeviceCtInfo;

    pphRpc_H_EE_t                   EE;
    pphRpc_H_EECfg_t                EECfg;

    pphRpc_H_StartTestSw_t          StartTestSW;
    pphRpc_H_StopTestSw_t           StopTestSW;
    pphRpc_H_DataExchangeTestSw_t   DataExchangeTestSW;

    pphRpc_H_DutInit_t              DutInit;
    pphRpc_H_DutGetMode_t           DutGetMode;
#if defined(ABEND_TRACE_ENABLED) && ABEND_TRACE_ENABLED == 1
    pphRpc_H_DutRx_t                DutRx_Real;
    pphRpc_H_DutTx_t                DutTx_Real;
    void DumpBufferToFile(const  uint8_t * const  buff, const uint16_t len);

    uint8_t DutRx(void *hdl, uint8_t **rxBuf, uint16_t *rxBufLen) {
        uint8_t retVal = 0;
#if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
        fprintf(this->fpDumpTextLogs,"DutRx:(Call)   rxBufLen=%03d\n",*rxBufLen);
#endif
        retVal = this->DutRx_Real(hdl,rxBuf,rxBufLen);
#if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
        fprintf(this->fpDumpTextLogs,"DutRx:(Ret)    rxBufLen=%03d   retVal=0x%02X   ",*rxBufLen,retVal);
#endif
        if (this->fpDumpCSVLogs != NULL)
#if ABEND_TRACE_ENABLED_WITH_TIMESTAMP
            this->writeTimeStampToCsvFile(AbendOperation_Rx);
#endif
        fprintf(this->fpDumpCSVLogs,"RX" CSV_SEPARATOR "%d" CSV_SEPARATOR ,*rxBufLen);

        if (*rxBufLen != 0 && retVal == 0) {
            this->DumpBufferToFile(*rxBuf,*rxBufLen);
        } else {
#if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
            fprintf(this->fpDumpTextLogs,"\n");
#endif
            if (this->fpDumpCSVLogs != NULL)
                fprintf(this->fpDumpCSVLogs, CSV_SEPARATOR );
        }
        if (this->fpDumpCSVLogs != NULL) {
            fprintf(this->fpDumpCSVLogs,"0x%02X\n",retVal);
            fflush(this->fpDumpCSVLogs);
        }
#if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
        fflush(this->fpDumpTextLogs);
#endif
        return retVal;
    }
    void writeTimeStampToCsvFile(AbendOperation_t eCurrentOperation) {
        time_t rawtime;
        /*FIXME: Make this snippet portable VS2005/2008/MINGW */
    #if _MSC_VER > 1000
        struct tm   sTimeinfo;
    #endif
        struct tm * ptimeinfo = NULL;
        char buffer [120];
        (void)time ( &rawtime );

    #if _MSC_VER > 1000
        localtime_s(&sTimeinfo, &rawtime );
        ptimeinfo = &sTimeinfo;
    #else
        ptimeinfo = localtime(&rawtime );
    #endif
        strftime (buffer,120,"%Y%m%d-%H%M%S",ptimeinfo);
        fprintf(this->fpDumpCSVLogs, "%s" CSV_SEPARATOR, buffer );
    #if ABEND_TRACE_ENABLED_WITH_GetTickCount
        if ( AbendOperation_Rx == this->eLastAbendOperation &&
            AbendOperation_Tx == eCurrentOperation) {
            DWORD currentTickCount = GetTickCount();
            fprintf(this->fpDumpCSVLogs, "%ld" CSV_SEPARATOR "%ld" CSV_SEPARATOR, currentTickCount, currentTickCount - this->dwLastTickCount );
            this->dwLastTickCount = currentTickCount;
        }
        else
        {
            this->dwLastTickCount = GetTickCount();
            fprintf(this->fpDumpCSVLogs, "%ld" CSV_SEPARATOR "0" CSV_SEPARATOR, this->dwLastTickCount );
        }
        this->eLastAbendOperation = eCurrentOperation;
        this->dwLastTickCount = GetTickCount();
    #else
        UNUSED(eCurrentOperation);
    #endif
    }

    uint8_t DutTx(void *hdl, uint8_t **txBuf, uint16_t *txBufLen) {
        uint8_t retVal = 0;
#if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
        fprintf(this->fpDumpTextLogs,"DutTx:(Call)   txBufLen=%3d                 ",*txBufLen);
#endif
        if (this->fpDumpCSVLogs != NULL) {
#if ABEND_TRACE_ENABLED_WITH_TIMESTAMP
            this->writeTimeStampToCsvFile(AbendOperation_Tx);
#endif
            fprintf(this->fpDumpCSVLogs,"TX" CSV_SEPARATOR "%d" CSV_SEPARATOR ,*txBufLen);
        }
        this->DumpBufferToFile(*txBuf,*txBufLen);
        retVal = this->DutTx_Real(hdl,txBuf,txBufLen);
#if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
        fprintf(this->fpDumpTextLogs,"DutTx:(Ret)    txBufLen=%3d   retVal=0x%02X\n",*txBufLen,retVal);
#endif
        if (this->fpDumpCSVLogs != NULL)
            fprintf(this->fpDumpCSVLogs,"0x%02X\n",retVal);
        return retVal;
    }
#else
    pphRpc_H_DutRx_t                DutRx;
    pphRpc_H_DutTx_t                DutTx;
#endif
    pphRpc_H_DutTRx_t               DutTRx;
#if defined(ABEND_TRACE_ENABLED) && ABEND_TRACE_ENABLED == 1
    pphRpc_H_DevIoCtl_t             DutDevIoCtl_Real;

    uint8_t DutDevIoCtl(void *hdl, uint8_t ctrlMj, uint8_t ctrlMn, uint32_t *ctrlOpt) {
        uint8_t retVal = 0;
        retVal = this->DutDevIoCtl_Real(hdl,ctrlMj,ctrlMn,ctrlOpt);
#if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
        if (ctrlOpt == NULL)
            fprintf(this->fpDumpTextLogs,"IoCtl:(Ret)   ctrlMj=0x%02X    ctrlMn=0x%02X    ctrlOpt=%s    retVal=0x%02X\n",ctrlMj,ctrlMn, "NULL",retVal);
        else
            fprintf(this->fpDumpTextLogs,"IoCtl:(Ret)   ctrlMj=0x%02X    ctrlMn=0x%02X    ctrlOpt=0x%08X    retVal=0x%02X\n",ctrlMj,ctrlMn, *ctrlOpt,retVal);
#endif
        return retVal;
    }
#else
    pphRpc_H_DevIoCtl_t             DutDevIoCtl;
#endif
    pphRpc_H_DevIoLineCtl_t         DutDevIoLineCtl;
    pphRpc_H_DutSetMinIOMode_t      DutSetMinMode;

    pphRpc_H_DeviceCommCheck_t      CommCheck;
    pphRpc_H_DeviceCommCheckLong_t  CommCheckLong;
    pphRpc_H_DeviceCommCheckWtx_t   CommCheckWtx;

    protected:

    #if ABEND_TRACE_ENABLED_WITH_GetTickCount
        AbendOperation_t        eLastAbendOperation;
        DWORD                   dwLastTickCount;
    #endif



    void LoadAllSymAddresses()
    {
        this->Open                  = (pphRpc_H_Open_t)                 this->GetSymAddress((wchar_t*)L"phRpc_H_Open");
        this->OpenL                 = (pphRpc_H_OpenL_t)                this->GetSymAddress((wchar_t*)L"phRpc_H_OpenL");
        this->OpenLH                = (pphRpc_H_OpenLH_t)               this->GetSymAddress((wchar_t*)L"phRpc_H_OpenLH");
        this->OpenLHF               = (pphRpc_H_OpenLHF_t)              this->GetSymAddress((wchar_t*)L"phRpc_H_OpenLHF");
        this->Close                 = (pphRpc_H_Close_t)                this->GetSymAddress((wchar_t*)L"phRpc_H_Close");
        this->SetTimeout            = (pphRpc_H_SetTimeout_t)           this->GetSymAddress((wchar_t*)L"phRpc_H_SetTimeout");
        this->GetCompatibilityInfo  = (pphRpc_H_GetCompatibilityInfo_t) this->GetSymAddress((wchar_t*)L"phRpc_H_GetCompatibilityInfo",  (void*)&ARMBoardLibIntf::Gci);
#if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
        this->GetLastABError_Real   = (pphRpc_H_GetLastError_t)         this->GetSymAddress((wchar_t*)L"phRpc_H_GetLastError");
#else
        this->GetLastABError        = (pphRpc_H_GetLastError_t)         this->GetSymAddress((wchar_t*)L"phRpc_H_GetLastError");
#endif
        this->GetErrorText          = (pphRpc_H_GetErrorText_t)         this->GetSymAddress((wchar_t*)L"phRpc_H_GetErrorText");
        this->GetHostErrorText      = (pphRpc_H_GetHostErrorText_t)     this->GetSymAddress((wchar_t*)L"phRpc_H_GetHostErrorText");
        this->GetHostCtxText        = (pphRpc_H_GetHostCtxText_t)       this->GetSymAddress((wchar_t*)L"phRpc_H_GetHostCtxText");
        this->GetBuffers            = (pphRpc_H_GetBuffers_t)           this->GetSymAddress((wchar_t*)L"phRpc_H_GetBuffers");
        this->SetLogF               = (pphRpc_H_SetLogF_t)              this->GetSymAddress((wchar_t*)L"phRpc_H_SetLogF");
        this->SetHookF              = (pphRpc_H_SetHookF_t)             this->GetSymAddress((wchar_t*)L"phRpc_H_SetHookF");
        this->HostIoCtl             = (pphRpc_H_HostIoCtl_t)            this->GetSymAddress((wchar_t*)L"phRpc_H_HostIoCtl");
        this->GetHostInfo           = (pphRpc_H_GetHostInfo_t)          this->GetSymAddress((wchar_t*)L"phRpc_H_GetHostInfo");
#if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
        this->CancelIo_Real              = (pphRpc_H_CancelIo_t)             this->GetSymAddress((wchar_t*)L"phRpc_H_CancelIo");
#else
        this->CancelIo              = (pphRpc_H_CancelIo_t)             this->GetSymAddress((wchar_t*)L"phRpc_H_CancelIo");
#endif
        this->SetLockD              = (pphRpc_H_SetLockD_t)             this->GetSymAddress((wchar_t*)L"phRpc_H_SetLockD",              (void*)&ARMBoardLibIntf::Sld);
        this->Raw                   = (pphRpc_H_Raw_t)                  this->GetSymAddress((wchar_t*)L"phRpc_H_Raw");

        this->SetCommParam          = (pphRpc_H_SetCommParam_t)         this->GetSymAddress((wchar_t*)L"phRpc_H_SetCommParam");
        this->GetDeviceInfo         = (pphRpc_H_GetDeviceInfo_t)        this->GetSymAddress((wchar_t*)L"phRpc_H_GetDeviceInfo");
        this->CtrlDeviceDiag        = (pphRpc_H_CtrlDeviceDiag_t)       this->GetSymAddress((wchar_t*)L"phRpc_H_CtrlDeviceDiag");
        this->SetDeviceMode         = (pphRpc_H_SetDeviceMode_t)        this->GetSymAddress((wchar_t*)L"phRpc_H_SetDeviceMode");
        this->GetDeviceCtInfo       = (pphRpc_H_GetDeviceCtInfo_t)      this->GetSymAddress((wchar_t*)L"phRpc_H_GetDeviceCtInfo");

        this->EE                    = (pphRpc_H_EE_t)                   this->GetSymAddress((wchar_t*)L"phRpc_H_EE");
        this->EECfg                 = (pphRpc_H_EECfg_t)                this->GetSymAddress((wchar_t*)L"phRpc_H_EECfg");

        this->StartTestSW           = (pphRpc_H_StartTestSw_t)          this->GetSymAddress((wchar_t*)L"phRpc_H_StartTestSw");
        this->StopTestSW            = (pphRpc_H_StopTestSw_t)           this->GetSymAddress((wchar_t*)L"phRpc_H_StopTestSw");
        this->DataExchangeTestSW    = (pphRpc_H_DataExchangeTestSw_t)   this->GetSymAddress((wchar_t*)L"phRpc_H_DataExchangeTestSw");

        this->DutInit               = (pphRpc_H_DutInit_t)              this->GetSymAddress((wchar_t*)L"phRpc_H_DutInit");
        this->DutGetMode            = (pphRpc_H_DutGetMode_t)           this->GetSymAddress((wchar_t*)L"phRpc_H_DutGetMode");
#if defined(ABEND_TRACE_ENABLED) && ABEND_TRACE_ENABLED == 1
        this->DutRx_Real                 = (pphRpc_H_DutRx_t)                this->GetSymAddress((wchar_t*)L"phRpc_H_DutRx");
        this->DutTx_Real                 = (pphRpc_H_DutTx_t)                this->GetSymAddress((wchar_t*)L"phRpc_H_DutTx");
#else
        this->DutRx                 = (pphRpc_H_DutRx_t)                this->GetSymAddress((wchar_t*)L"phRpc_H_DutRx");
        this->DutTx                 = (pphRpc_H_DutTx_t)                this->GetSymAddress((wchar_t*)L"phRpc_H_DutTx");
#endif
        this->DutTRx                = (pphRpc_H_DutTRx_t)               this->GetSymAddress((wchar_t*)L"phRpc_H_DutTRx");
#if defined(ABEND_TRACE_ENABLED) && ABEND_TRACE_ENABLED == 1
        this->DutDevIoCtl_Real           = (pphRpc_H_DevIoCtl_t)             this->GetSymAddress((wchar_t*)L"phRpc_H_DevIoCtl");
#else
        this->DutDevIoCtl           = (pphRpc_H_DevIoCtl_t)             this->GetSymAddress((wchar_t*)L"phRpc_H_DevIoCtl");
#endif
        this->DutDevIoLineCtl       = (pphRpc_H_DevIoLineCtl_t)         this->GetSymAddress((wchar_t*)L"phRpc_H_DevIoLineCtl");
        this->DutSetMinMode         = (pphRpc_H_DutSetMinIOMode_t)      this->GetSymAddress((wchar_t*)L"phRpc_H_DutSetMinIOMode");

        this->CommCheck             = (pphRpc_H_DeviceCommCheck_t)      this->GetSymAddress((wchar_t*)L"phRpc_H_DeviceCommCheck");
        this->CommCheckLong         = (pphRpc_H_DeviceCommCheckLong_t)  this->GetSymAddress((wchar_t*)L"phRpc_H_DeviceCommCheckLong");
        this->CommCheckWtx          = (pphRpc_H_DeviceCommCheckWtx_t)   this->GetSymAddress((wchar_t*)L"phRpc_H_DeviceCommCheckWTX");
    }
};

#endif // Guard
