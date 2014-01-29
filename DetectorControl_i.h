

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Jan 29 21:25:42 2014
 */
/* Compiler settings for DetectorControl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DetectorControl_i_h__
#define __DetectorControl_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFrameReadyCallBack_FWD_DEFINED__
#define __IFrameReadyCallBack_FWD_DEFINED__
typedef interface IFrameReadyCallBack IFrameReadyCallBack;
#endif 	/* __IFrameReadyCallBack_FWD_DEFINED__ */


#ifndef __ICommandChannel_FWD_DEFINED__
#define __ICommandChannel_FWD_DEFINED__
typedef interface ICommandChannel ICommandChannel;
#endif 	/* __ICommandChannel_FWD_DEFINED__ */


#ifndef __IScannerImage_FWD_DEFINED__
#define __IScannerImage_FWD_DEFINED__
typedef interface IScannerImage IScannerImage;
#endif 	/* __IScannerImage_FWD_DEFINED__ */


#ifndef __IScannerDisplay_FWD_DEFINED__
#define __IScannerDisplay_FWD_DEFINED__
typedef interface IScannerDisplay IScannerDisplay;
#endif 	/* __IScannerDisplay_FWD_DEFINED__ */


#ifndef __IFrameObject_FWD_DEFINED__
#define __IFrameObject_FWD_DEFINED__
typedef interface IFrameObject IFrameObject;
#endif 	/* __IFrameObject_FWD_DEFINED__ */


#ifndef __IScanner_FWD_DEFINED__
#define __IScanner_FWD_DEFINED__
typedef interface IScanner IScanner;
#endif 	/* __IScanner_FWD_DEFINED__ */


#ifndef __CommandChannel_FWD_DEFINED__
#define __CommandChannel_FWD_DEFINED__

#ifdef __cplusplus
typedef class CommandChannel CommandChannel;
#else
typedef struct CommandChannel CommandChannel;
#endif /* __cplusplus */

#endif 	/* __CommandChannel_FWD_DEFINED__ */


#ifndef ___IScannerImageEvents_FWD_DEFINED__
#define ___IScannerImageEvents_FWD_DEFINED__
typedef interface _IScannerImageEvents _IScannerImageEvents;
#endif 	/* ___IScannerImageEvents_FWD_DEFINED__ */


#ifndef __ScannerImage_FWD_DEFINED__
#define __ScannerImage_FWD_DEFINED__

#ifdef __cplusplus
typedef class ScannerImage ScannerImage;
#else
typedef struct ScannerImage ScannerImage;
#endif /* __cplusplus */

#endif 	/* __ScannerImage_FWD_DEFINED__ */


#ifndef ___IScannerDisplayEvents_FWD_DEFINED__
#define ___IScannerDisplayEvents_FWD_DEFINED__
typedef interface _IScannerDisplayEvents _IScannerDisplayEvents;
#endif 	/* ___IScannerDisplayEvents_FWD_DEFINED__ */


#ifndef __ScannerDisplay_FWD_DEFINED__
#define __ScannerDisplay_FWD_DEFINED__

#ifdef __cplusplus
typedef class ScannerDisplay ScannerDisplay;
#else
typedef struct ScannerDisplay ScannerDisplay;
#endif /* __cplusplus */

#endif 	/* __ScannerDisplay_FWD_DEFINED__ */


#ifndef __FrameObject_FWD_DEFINED__
#define __FrameObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class FrameObject FrameObject;
#else
typedef struct FrameObject FrameObject;
#endif /* __cplusplus */

#endif 	/* __FrameObject_FWD_DEFINED__ */


#ifndef __Scanner_FWD_DEFINED__
#define __Scanner_FWD_DEFINED__

#ifdef __cplusplus
typedef class Scanner Scanner;
#else
typedef struct Scanner Scanner;
#endif /* __cplusplus */

#endif 	/* __Scanner_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IFrameReadyCallBack_INTERFACE_DEFINED__
#define __IFrameReadyCallBack_INTERFACE_DEFINED__

/* interface IFrameReadyCallBack */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IFrameReadyCallBack;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FA6DA72C-D386-4F1A-A288-F7A821A6D13B")
    IFrameReadyCallBack : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FrameReady( 
            /* [in] */ LONG NumLines) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubFrameReady( 
            /* [in] */ LONG NumOfBlockLeft,
            /* [in] */ LONG StartLine,
            /* [in] */ LONG NumLines,
            /* [in] */ LONG bLastBlock) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFrameReadyCallBackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFrameReadyCallBack * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFrameReadyCallBack * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFrameReadyCallBack * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FrameReady )( 
            IFrameReadyCallBack * This,
            /* [in] */ LONG NumLines);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubFrameReady )( 
            IFrameReadyCallBack * This,
            /* [in] */ LONG NumOfBlockLeft,
            /* [in] */ LONG StartLine,
            /* [in] */ LONG NumLines,
            /* [in] */ LONG bLastBlock);
        
        END_INTERFACE
    } IFrameReadyCallBackVtbl;

    interface IFrameReadyCallBack
    {
        CONST_VTBL struct IFrameReadyCallBackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFrameReadyCallBack_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFrameReadyCallBack_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFrameReadyCallBack_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFrameReadyCallBack_FrameReady(This,NumLines)	\
    ( (This)->lpVtbl -> FrameReady(This,NumLines) ) 

#define IFrameReadyCallBack_SubFrameReady(This,NumOfBlockLeft,StartLine,NumLines,bLastBlock)	\
    ( (This)->lpVtbl -> SubFrameReady(This,NumOfBlockLeft,StartLine,NumLines,bLastBlock) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFrameReadyCallBack_INTERFACE_DEFINED__ */


#ifndef __ICommandChannel_INTERFACE_DEFINED__
#define __ICommandChannel_INTERFACE_DEFINED__

/* interface ICommandChannel */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ICommandChannel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F9C9CB4E-7202-4E3F-BFB3-A74BC9DE77C3")
    ICommandChannel : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IPAddress( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IPAddress( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CmdPort( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CmdPort( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ObjectHandle( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsOpened( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LastErrID( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ChannelType( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ChannelType( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CmdTimeOut( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CmdTimeOut( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [retval][out] */ LONG *bOK) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SendCommand( 
            BSTR bstrCmd,
            /* [out] */ BSTR *bstrRTMsg,
            /* [retval][out] */ LONG *bOK) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SendCommandA( 
            /* [in] */ CHAR *Cmd,
            /* [out] */ CHAR *pRT,
            /* [retval][out] */ LONG *bOK) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandChannelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICommandChannel * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICommandChannel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICommandChannel * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IPAddress )( 
            ICommandChannel * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IPAddress )( 
            ICommandChannel * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CmdPort )( 
            ICommandChannel * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CmdPort )( 
            ICommandChannel * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectHandle )( 
            ICommandChannel * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsOpened )( 
            ICommandChannel * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastErrID )( 
            ICommandChannel * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChannelType )( 
            ICommandChannel * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ChannelType )( 
            ICommandChannel * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CmdTimeOut )( 
            ICommandChannel * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CmdTimeOut )( 
            ICommandChannel * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            ICommandChannel * This,
            /* [retval][out] */ LONG *bOK);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            ICommandChannel * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SendCommand )( 
            ICommandChannel * This,
            BSTR bstrCmd,
            /* [out] */ BSTR *bstrRTMsg,
            /* [retval][out] */ LONG *bOK);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SendCommandA )( 
            ICommandChannel * This,
            /* [in] */ CHAR *Cmd,
            /* [out] */ CHAR *pRT,
            /* [retval][out] */ LONG *bOK);
        
        END_INTERFACE
    } ICommandChannelVtbl;

    interface ICommandChannel
    {
        CONST_VTBL struct ICommandChannelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommandChannel_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICommandChannel_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICommandChannel_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICommandChannel_get_IPAddress(This,pVal)	\
    ( (This)->lpVtbl -> get_IPAddress(This,pVal) ) 

#define ICommandChannel_put_IPAddress(This,newVal)	\
    ( (This)->lpVtbl -> put_IPAddress(This,newVal) ) 

#define ICommandChannel_get_CmdPort(This,pVal)	\
    ( (This)->lpVtbl -> get_CmdPort(This,pVal) ) 

#define ICommandChannel_put_CmdPort(This,newVal)	\
    ( (This)->lpVtbl -> put_CmdPort(This,newVal) ) 

#define ICommandChannel_get_ObjectHandle(This,pVal)	\
    ( (This)->lpVtbl -> get_ObjectHandle(This,pVal) ) 

#define ICommandChannel_get_IsOpened(This,pVal)	\
    ( (This)->lpVtbl -> get_IsOpened(This,pVal) ) 

#define ICommandChannel_get_LastErrID(This,pVal)	\
    ( (This)->lpVtbl -> get_LastErrID(This,pVal) ) 

#define ICommandChannel_get_ChannelType(This,pVal)	\
    ( (This)->lpVtbl -> get_ChannelType(This,pVal) ) 

#define ICommandChannel_put_ChannelType(This,newVal)	\
    ( (This)->lpVtbl -> put_ChannelType(This,newVal) ) 

#define ICommandChannel_get_CmdTimeOut(This,pVal)	\
    ( (This)->lpVtbl -> get_CmdTimeOut(This,pVal) ) 

#define ICommandChannel_put_CmdTimeOut(This,newVal)	\
    ( (This)->lpVtbl -> put_CmdTimeOut(This,newVal) ) 

#define ICommandChannel_Open(This,bOK)	\
    ( (This)->lpVtbl -> Open(This,bOK) ) 

#define ICommandChannel_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define ICommandChannel_SendCommand(This,bstrCmd,bstrRTMsg,bOK)	\
    ( (This)->lpVtbl -> SendCommand(This,bstrCmd,bstrRTMsg,bOK) ) 

#define ICommandChannel_SendCommandA(This,Cmd,pRT,bOK)	\
    ( (This)->lpVtbl -> SendCommandA(This,Cmd,pRT,bOK) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICommandChannel_INTERFACE_DEFINED__ */


#ifndef __IScannerImage_INTERFACE_DEFINED__
#define __IScannerImage_INTERFACE_DEFINED__

/* interface IScannerImage */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IScannerImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0852B104-F2F5-485C-A463-38886C8CB4F6")
    IScannerImage : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ImgHeight( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ImgHeight( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ImgWidth( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ImgWidth( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BytesPerPixel( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BytesPerPixel( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ChannelType( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ChannelType( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ImagePort( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ImagePort( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DetectorObject( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DetectorObject( 
            /* [in] */ IUnknown *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsOpened( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LastErrID( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [retval][out] */ LONG *bOK) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Grab( 
            /* [in] */ LONG FrameNum,
            /* [retval][out] */ LONG *bOK) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Snap( 
            /* [in] */ LONG FrameNum,
            /* [retval][out] */ LONG *bOK) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PrintErrMsg( 
            /* [in] */ LONG ErrID,
            /* [out] */ BSTR *ErrMsg) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SubFrameHeight( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SubFrameHeight( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsGrabing( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ImageObject( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BandWidth( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ObjectHandle( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TimeOut( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TimeOut( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ExFrameTrigger( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ExFrameTrigger( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DualScanMode( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DualScanMode( 
            /* [in] */ LONG newVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenMemImage( 
            LONG width,
            LONG height,
            BYTE *data) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Advise( 
            /* [in] */ IFrameReadyCallBack *pCallBack,
            /* [out] */ long *cookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnAdvise( 
            /* [in] */ LONG cookie) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IScannerImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IScannerImage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IScannerImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IScannerImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IScannerImage * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IScannerImage * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IScannerImage * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IScannerImage * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImgHeight )( 
            IScannerImage * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImgHeight )( 
            IScannerImage * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImgWidth )( 
            IScannerImage * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImgWidth )( 
            IScannerImage * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BytesPerPixel )( 
            IScannerImage * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BytesPerPixel )( 
            IScannerImage * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChannelType )( 
            IScannerImage * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ChannelType )( 
            IScannerImage * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImagePort )( 
            IScannerImage * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImagePort )( 
            IScannerImage * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DetectorObject )( 
            IScannerImage * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DetectorObject )( 
            IScannerImage * This,
            /* [in] */ IUnknown *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsOpened )( 
            IScannerImage * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastErrID )( 
            IScannerImage * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IScannerImage * This,
            /* [retval][out] */ LONG *bOK);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IScannerImage * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Grab )( 
            IScannerImage * This,
            /* [in] */ LONG FrameNum,
            /* [retval][out] */ LONG *bOK);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Snap )( 
            IScannerImage * This,
            /* [in] */ LONG FrameNum,
            /* [retval][out] */ LONG *bOK);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PrintErrMsg )( 
            IScannerImage * This,
            /* [in] */ LONG ErrID,
            /* [out] */ BSTR *ErrMsg);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SubFrameHeight )( 
            IScannerImage * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SubFrameHeight )( 
            IScannerImage * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IScannerImage * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsGrabing )( 
            IScannerImage * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageObject )( 
            IScannerImage * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BandWidth )( 
            IScannerImage * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectHandle )( 
            IScannerImage * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimeOut )( 
            IScannerImage * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TimeOut )( 
            IScannerImage * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExFrameTrigger )( 
            IScannerImage * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExFrameTrigger )( 
            IScannerImage * This,
            /* [in] */ LONG newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DualScanMode )( 
            IScannerImage * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DualScanMode )( 
            IScannerImage * This,
            /* [in] */ LONG newVal);
        
        HRESULT ( STDMETHODCALLTYPE *OpenMemImage )( 
            IScannerImage * This,
            LONG width,
            LONG height,
            BYTE *data);
        
        HRESULT ( STDMETHODCALLTYPE *Advise )( 
            IScannerImage * This,
            /* [in] */ IFrameReadyCallBack *pCallBack,
            /* [out] */ long *cookie);
        
        HRESULT ( STDMETHODCALLTYPE *UnAdvise )( 
            IScannerImage * This,
            /* [in] */ LONG cookie);
        
        END_INTERFACE
    } IScannerImageVtbl;

    interface IScannerImage
    {
        CONST_VTBL struct IScannerImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScannerImage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IScannerImage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IScannerImage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IScannerImage_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IScannerImage_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IScannerImage_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IScannerImage_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IScannerImage_get_ImgHeight(This,pVal)	\
    ( (This)->lpVtbl -> get_ImgHeight(This,pVal) ) 

#define IScannerImage_put_ImgHeight(This,newVal)	\
    ( (This)->lpVtbl -> put_ImgHeight(This,newVal) ) 

#define IScannerImage_get_ImgWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_ImgWidth(This,pVal) ) 

#define IScannerImage_put_ImgWidth(This,newVal)	\
    ( (This)->lpVtbl -> put_ImgWidth(This,newVal) ) 

#define IScannerImage_get_BytesPerPixel(This,pVal)	\
    ( (This)->lpVtbl -> get_BytesPerPixel(This,pVal) ) 

#define IScannerImage_put_BytesPerPixel(This,newVal)	\
    ( (This)->lpVtbl -> put_BytesPerPixel(This,newVal) ) 

#define IScannerImage_get_ChannelType(This,pVal)	\
    ( (This)->lpVtbl -> get_ChannelType(This,pVal) ) 

#define IScannerImage_put_ChannelType(This,newVal)	\
    ( (This)->lpVtbl -> put_ChannelType(This,newVal) ) 

#define IScannerImage_get_ImagePort(This,pVal)	\
    ( (This)->lpVtbl -> get_ImagePort(This,pVal) ) 

#define IScannerImage_put_ImagePort(This,newVal)	\
    ( (This)->lpVtbl -> put_ImagePort(This,newVal) ) 

#define IScannerImage_get_DetectorObject(This,pVal)	\
    ( (This)->lpVtbl -> get_DetectorObject(This,pVal) ) 

#define IScannerImage_put_DetectorObject(This,newVal)	\
    ( (This)->lpVtbl -> put_DetectorObject(This,newVal) ) 

#define IScannerImage_get_IsOpened(This,pVal)	\
    ( (This)->lpVtbl -> get_IsOpened(This,pVal) ) 

#define IScannerImage_get_LastErrID(This,pVal)	\
    ( (This)->lpVtbl -> get_LastErrID(This,pVal) ) 

#define IScannerImage_Open(This,bOK)	\
    ( (This)->lpVtbl -> Open(This,bOK) ) 

#define IScannerImage_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define IScannerImage_Grab(This,FrameNum,bOK)	\
    ( (This)->lpVtbl -> Grab(This,FrameNum,bOK) ) 

#define IScannerImage_Snap(This,FrameNum,bOK)	\
    ( (This)->lpVtbl -> Snap(This,FrameNum,bOK) ) 

#define IScannerImage_PrintErrMsg(This,ErrID,ErrMsg)	\
    ( (This)->lpVtbl -> PrintErrMsg(This,ErrID,ErrMsg) ) 

#define IScannerImage_get_SubFrameHeight(This,pVal)	\
    ( (This)->lpVtbl -> get_SubFrameHeight(This,pVal) ) 

#define IScannerImage_put_SubFrameHeight(This,newVal)	\
    ( (This)->lpVtbl -> put_SubFrameHeight(This,newVal) ) 

#define IScannerImage_Stop(This)	\
    ( (This)->lpVtbl -> Stop(This) ) 

#define IScannerImage_get_IsGrabing(This,pVal)	\
    ( (This)->lpVtbl -> get_IsGrabing(This,pVal) ) 

#define IScannerImage_get_ImageObject(This,pVal)	\
    ( (This)->lpVtbl -> get_ImageObject(This,pVal) ) 

#define IScannerImage_get_BandWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_BandWidth(This,pVal) ) 

#define IScannerImage_get_ObjectHandle(This,pVal)	\
    ( (This)->lpVtbl -> get_ObjectHandle(This,pVal) ) 

#define IScannerImage_get_TimeOut(This,pVal)	\
    ( (This)->lpVtbl -> get_TimeOut(This,pVal) ) 

#define IScannerImage_put_TimeOut(This,newVal)	\
    ( (This)->lpVtbl -> put_TimeOut(This,newVal) ) 

#define IScannerImage_get_ExFrameTrigger(This,pVal)	\
    ( (This)->lpVtbl -> get_ExFrameTrigger(This,pVal) ) 

#define IScannerImage_put_ExFrameTrigger(This,newVal)	\
    ( (This)->lpVtbl -> put_ExFrameTrigger(This,newVal) ) 

#define IScannerImage_get_DualScanMode(This,pVal)	\
    ( (This)->lpVtbl -> get_DualScanMode(This,pVal) ) 

#define IScannerImage_put_DualScanMode(This,newVal)	\
    ( (This)->lpVtbl -> put_DualScanMode(This,newVal) ) 

#define IScannerImage_OpenMemImage(This,width,height,data)	\
    ( (This)->lpVtbl -> OpenMemImage(This,width,height,data) ) 

#define IScannerImage_Advise(This,pCallBack,cookie)	\
    ( (This)->lpVtbl -> Advise(This,pCallBack,cookie) ) 

#define IScannerImage_UnAdvise(This,cookie)	\
    ( (This)->lpVtbl -> UnAdvise(This,cookie) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IScannerImage_INTERFACE_DEFINED__ */


#ifndef __IScannerDisplay_INTERFACE_DEFINED__
#define __IScannerDisplay_INTERFACE_DEFINED__

/* interface IScannerDisplay */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IScannerDisplay;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("383027FD-F712-4040-BA21-ACAC15F268A3")
    IScannerDisplay : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImgWidth( 
            /* [retval][out] */ ULONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImgWidth( 
            /* [in] */ ULONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImgHeight( 
            /* [retval][out] */ ULONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImgHeight( 
            /* [in] */ ULONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Gamma( 
            /* [retval][out] */ FLOAT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Gamma( 
            /* [in] */ FLOAT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MapStart( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MapStart( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MapEnd( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MapEnd( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataSource( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DataSource( 
            /* [in] */ IUnknown *newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [retval][out] */ LONG *bOK) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RefreshMode( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RefreshMode( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RefreshRate( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RefreshRate( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImageObject( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayScale( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DisplayScale( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OrgPoint_X( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OrgPoint_X( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OrgPoint_Y( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OrgPoint_Y( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( 
            BSTR FilePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            BSTR FilePath) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ObjectHandle( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RepaintDisplay( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IScannerDisplayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IScannerDisplay * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IScannerDisplay * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IScannerDisplay * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IScannerDisplay * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IScannerDisplay * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IScannerDisplay * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IScannerDisplay * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImgWidth )( 
            IScannerDisplay * This,
            /* [retval][out] */ ULONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImgWidth )( 
            IScannerDisplay * This,
            /* [in] */ ULONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImgHeight )( 
            IScannerDisplay * This,
            /* [retval][out] */ ULONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImgHeight )( 
            IScannerDisplay * This,
            /* [in] */ ULONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Gamma )( 
            IScannerDisplay * This,
            /* [retval][out] */ FLOAT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Gamma )( 
            IScannerDisplay * This,
            /* [in] */ FLOAT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MapStart )( 
            IScannerDisplay * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MapStart )( 
            IScannerDisplay * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MapEnd )( 
            IScannerDisplay * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MapEnd )( 
            IScannerDisplay * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataSource )( 
            IScannerDisplay * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DataSource )( 
            IScannerDisplay * This,
            /* [in] */ IUnknown *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IScannerDisplay * This,
            /* [retval][out] */ LONG *bOK);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IScannerDisplay * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RefreshMode )( 
            IScannerDisplay * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RefreshMode )( 
            IScannerDisplay * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RefreshRate )( 
            IScannerDisplay * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RefreshRate )( 
            IScannerDisplay * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageObject )( 
            IScannerDisplay * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisplayScale )( 
            IScannerDisplay * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DisplayScale )( 
            IScannerDisplay * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IScannerDisplay * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OrgPoint_X )( 
            IScannerDisplay * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OrgPoint_X )( 
            IScannerDisplay * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OrgPoint_Y )( 
            IScannerDisplay * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OrgPoint_Y )( 
            IScannerDisplay * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IScannerDisplay * This,
            BSTR FilePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IScannerDisplay * This,
            BSTR FilePath);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectHandle )( 
            IScannerDisplay * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RepaintDisplay )( 
            IScannerDisplay * This);
        
        END_INTERFACE
    } IScannerDisplayVtbl;

    interface IScannerDisplay
    {
        CONST_VTBL struct IScannerDisplayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScannerDisplay_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IScannerDisplay_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IScannerDisplay_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IScannerDisplay_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IScannerDisplay_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IScannerDisplay_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IScannerDisplay_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IScannerDisplay_get_ImgWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_ImgWidth(This,pVal) ) 

#define IScannerDisplay_put_ImgWidth(This,newVal)	\
    ( (This)->lpVtbl -> put_ImgWidth(This,newVal) ) 

#define IScannerDisplay_get_ImgHeight(This,pVal)	\
    ( (This)->lpVtbl -> get_ImgHeight(This,pVal) ) 

#define IScannerDisplay_put_ImgHeight(This,newVal)	\
    ( (This)->lpVtbl -> put_ImgHeight(This,newVal) ) 

#define IScannerDisplay_get_Gamma(This,pVal)	\
    ( (This)->lpVtbl -> get_Gamma(This,pVal) ) 

#define IScannerDisplay_put_Gamma(This,newVal)	\
    ( (This)->lpVtbl -> put_Gamma(This,newVal) ) 

#define IScannerDisplay_get_MapStart(This,pVal)	\
    ( (This)->lpVtbl -> get_MapStart(This,pVal) ) 

#define IScannerDisplay_put_MapStart(This,newVal)	\
    ( (This)->lpVtbl -> put_MapStart(This,newVal) ) 

#define IScannerDisplay_get_MapEnd(This,pVal)	\
    ( (This)->lpVtbl -> get_MapEnd(This,pVal) ) 

#define IScannerDisplay_put_MapEnd(This,newVal)	\
    ( (This)->lpVtbl -> put_MapEnd(This,newVal) ) 

#define IScannerDisplay_get_DataSource(This,pVal)	\
    ( (This)->lpVtbl -> get_DataSource(This,pVal) ) 

#define IScannerDisplay_put_DataSource(This,newVal)	\
    ( (This)->lpVtbl -> put_DataSource(This,newVal) ) 

#define IScannerDisplay_Open(This,bOK)	\
    ( (This)->lpVtbl -> Open(This,bOK) ) 

#define IScannerDisplay_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define IScannerDisplay_get_RefreshMode(This,pVal)	\
    ( (This)->lpVtbl -> get_RefreshMode(This,pVal) ) 

#define IScannerDisplay_put_RefreshMode(This,newVal)	\
    ( (This)->lpVtbl -> put_RefreshMode(This,newVal) ) 

#define IScannerDisplay_get_RefreshRate(This,pVal)	\
    ( (This)->lpVtbl -> get_RefreshRate(This,pVal) ) 

#define IScannerDisplay_put_RefreshRate(This,newVal)	\
    ( (This)->lpVtbl -> put_RefreshRate(This,newVal) ) 

#define IScannerDisplay_get_ImageObject(This,pVal)	\
    ( (This)->lpVtbl -> get_ImageObject(This,pVal) ) 

#define IScannerDisplay_get_DisplayScale(This,pVal)	\
    ( (This)->lpVtbl -> get_DisplayScale(This,pVal) ) 

#define IScannerDisplay_put_DisplayScale(This,newVal)	\
    ( (This)->lpVtbl -> put_DisplayScale(This,newVal) ) 

#define IScannerDisplay_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IScannerDisplay_get_OrgPoint_X(This,pVal)	\
    ( (This)->lpVtbl -> get_OrgPoint_X(This,pVal) ) 

#define IScannerDisplay_put_OrgPoint_X(This,newVal)	\
    ( (This)->lpVtbl -> put_OrgPoint_X(This,newVal) ) 

#define IScannerDisplay_get_OrgPoint_Y(This,pVal)	\
    ( (This)->lpVtbl -> get_OrgPoint_Y(This,pVal) ) 

#define IScannerDisplay_put_OrgPoint_Y(This,newVal)	\
    ( (This)->lpVtbl -> put_OrgPoint_Y(This,newVal) ) 

#define IScannerDisplay_Load(This,FilePath)	\
    ( (This)->lpVtbl -> Load(This,FilePath) ) 

#define IScannerDisplay_Save(This,FilePath)	\
    ( (This)->lpVtbl -> Save(This,FilePath) ) 

#define IScannerDisplay_get_ObjectHandle(This,pVal)	\
    ( (This)->lpVtbl -> get_ObjectHandle(This,pVal) ) 

#define IScannerDisplay_RepaintDisplay(This)	\
    ( (This)->lpVtbl -> RepaintDisplay(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IScannerDisplay_INTERFACE_DEFINED__ */


#ifndef __IFrameObject_INTERFACE_DEFINED__
#define __IFrameObject_INTERFACE_DEFINED__

/* interface IFrameObject */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IFrameObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5ED30CFC-6EB8-41F3-93B5-BF86191DCA9E")
    IFrameObject : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ImageDataAddress( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ImageDataAddress( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BytesPerPixel( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Pixel( 
            /* [in] */ LONG X,
            /* [in] */ LONG Y,
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Pixel( 
            /* [in] */ LONG X,
            /* [in] */ LONG Y,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ LONG Width,
            /* [in] */ LONG Height,
            /* [in] */ LONG BytesPerPixel) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ImageLineAddress( 
            /* [in] */ LONG LineIndex,
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ColAverage( 
            /* [out] */ LONG *pAvg) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ColMax( 
            /* [out] */ LONG *pMax) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ColMin( 
            /* [out] */ LONG *pMin) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RowMin( 
            /* [out] */ LONG *pMin) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RowMax( 
            /* [out] */ LONG *pMax) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RowAverage( 
            LONG *pAvg) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ColNoise( 
            /* [out] */ FLOAT *pNoise) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RowNoise( 
            /* [out] */ FLOAT *pNoise) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFrameObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFrameObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFrameObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFrameObject * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageDataAddress )( 
            IFrameObject * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImageDataAddress )( 
            IFrameObject * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IFrameObject * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IFrameObject * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BytesPerPixel )( 
            IFrameObject * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Pixel )( 
            IFrameObject * This,
            /* [in] */ LONG X,
            /* [in] */ LONG Y,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Pixel )( 
            IFrameObject * This,
            /* [in] */ LONG X,
            /* [in] */ LONG Y,
            /* [in] */ LONG newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IFrameObject * This,
            /* [in] */ LONG Width,
            /* [in] */ LONG Height,
            /* [in] */ LONG BytesPerPixel);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageLineAddress )( 
            IFrameObject * This,
            /* [in] */ LONG LineIndex,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ColAverage )( 
            IFrameObject * This,
            /* [out] */ LONG *pAvg);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ColMax )( 
            IFrameObject * This,
            /* [out] */ LONG *pMax);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ColMin )( 
            IFrameObject * This,
            /* [out] */ LONG *pMin);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RowMin )( 
            IFrameObject * This,
            /* [out] */ LONG *pMin);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RowMax )( 
            IFrameObject * This,
            /* [out] */ LONG *pMax);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RowAverage )( 
            IFrameObject * This,
            LONG *pAvg);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ColNoise )( 
            IFrameObject * This,
            /* [out] */ FLOAT *pNoise);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RowNoise )( 
            IFrameObject * This,
            /* [out] */ FLOAT *pNoise);
        
        END_INTERFACE
    } IFrameObjectVtbl;

    interface IFrameObject
    {
        CONST_VTBL struct IFrameObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFrameObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFrameObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFrameObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFrameObject_get_ImageDataAddress(This,pVal)	\
    ( (This)->lpVtbl -> get_ImageDataAddress(This,pVal) ) 

#define IFrameObject_put_ImageDataAddress(This,newVal)	\
    ( (This)->lpVtbl -> put_ImageDataAddress(This,newVal) ) 

#define IFrameObject_get_Width(This,pVal)	\
    ( (This)->lpVtbl -> get_Width(This,pVal) ) 

#define IFrameObject_get_Height(This,pVal)	\
    ( (This)->lpVtbl -> get_Height(This,pVal) ) 

#define IFrameObject_get_BytesPerPixel(This,pVal)	\
    ( (This)->lpVtbl -> get_BytesPerPixel(This,pVal) ) 

#define IFrameObject_get_Pixel(This,X,Y,pVal)	\
    ( (This)->lpVtbl -> get_Pixel(This,X,Y,pVal) ) 

#define IFrameObject_put_Pixel(This,X,Y,newVal)	\
    ( (This)->lpVtbl -> put_Pixel(This,X,Y,newVal) ) 

#define IFrameObject_Open(This,Width,Height,BytesPerPixel)	\
    ( (This)->lpVtbl -> Open(This,Width,Height,BytesPerPixel) ) 

#define IFrameObject_get_ImageLineAddress(This,LineIndex,pVal)	\
    ( (This)->lpVtbl -> get_ImageLineAddress(This,LineIndex,pVal) ) 

#define IFrameObject_get_ColAverage(This,pAvg)	\
    ( (This)->lpVtbl -> get_ColAverage(This,pAvg) ) 

#define IFrameObject_get_ColMax(This,pMax)	\
    ( (This)->lpVtbl -> get_ColMax(This,pMax) ) 

#define IFrameObject_get_ColMin(This,pMin)	\
    ( (This)->lpVtbl -> get_ColMin(This,pMin) ) 

#define IFrameObject_get_RowMin(This,pMin)	\
    ( (This)->lpVtbl -> get_RowMin(This,pMin) ) 

#define IFrameObject_get_RowMax(This,pMax)	\
    ( (This)->lpVtbl -> get_RowMax(This,pMax) ) 

#define IFrameObject_get_RowAverage(This,pAvg)	\
    ( (This)->lpVtbl -> get_RowAverage(This,pAvg) ) 

#define IFrameObject_get_ColNoise(This,pNoise)	\
    ( (This)->lpVtbl -> get_ColNoise(This,pNoise) ) 

#define IFrameObject_get_RowNoise(This,pNoise)	\
    ( (This)->lpVtbl -> get_RowNoise(This,pNoise) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFrameObject_INTERFACE_DEFINED__ */


#ifndef __IScanner_INTERFACE_DEFINED__
#define __IScanner_INTERFACE_DEFINED__

/* interface IScanner */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IScanner;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8C36086B-9A03-4202-B3A1-8773A18E95F8")
    IScanner : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DetectorObject( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DetectorObject( 
            /* [in] */ IUnknown *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OffBoardCalibration( 
            /* [in] */ LONG CalibrationType,
            /* [in] */ IUnknown *pImgObject,
            /* [in] */ LONG StartPixel,
            /* [in] */ LONG EndPixel,
            /* [in] */ LONG TargetValue) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Gain( 
            /* [in] */ LONG Index,
            /* [retval][out] */ FLOAT *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Gain( 
            /* [in] */ LONG Index,
            /* [in] */ FLOAT newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Offset( 
            /* [in] */ LONG Index,
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Offset( 
            /* [in] */ LONG Index,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CorrectionGain( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CorrectionGain( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CorrectionOffset( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CorrectionOffset( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CorrectionBaseline( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CorrectionBaseline( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Baseline( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Baseline( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IntegrationTime( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IntegrationTime( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AverageFilter( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AverageFilter( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DataPattern( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DataPattern( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FrameTrigger( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_FrameTrigger( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LineTrigger( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LineTrigger( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ LONG Mode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SaveOffset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SaveGain( 
            /* [in] */ LONG Index) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadOffset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadGain( 
            /* [in] */ LONG Index) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OutputBits( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OutputBits( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SendExFrameTrigger( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FrameOut( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_FrameOut( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ImageOutputType( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ImageOutputType( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SensitivityLevel( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SensitivityLevel( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SumLines( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SumLines( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteDataPattern( 
            /* [in] */ LONG Base,
            /* [in] */ LONG Step) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsOpened( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ModuleTypeName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SaveCurrentStatus( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PixelSize( 
            /* [retval][out] */ FLOAT *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PixelNumber( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ModuleType( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MaxIntTime( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MinIntTime( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OverallGain( 
            /* [retval][out] */ FLOAT *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OverallGain( 
            /* [in] */ FLOAT newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartPixel( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartPixel( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndPixel( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndPixel( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnBoardOffsetCalibration( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnBoardGainCalibration( 
            /* [in] */ LONG TargetValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ResetGain( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ResetOffset( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FPGA_Version( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FPGA_Build( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MCU_Version( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SerialNumber( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RetrieveSysinfo( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IScannerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IScanner * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IScanner * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IScanner * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DetectorObject )( 
            IScanner * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DetectorObject )( 
            IScanner * This,
            /* [in] */ IUnknown *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OffBoardCalibration )( 
            IScanner * This,
            /* [in] */ LONG CalibrationType,
            /* [in] */ IUnknown *pImgObject,
            /* [in] */ LONG StartPixel,
            /* [in] */ LONG EndPixel,
            /* [in] */ LONG TargetValue);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Gain )( 
            IScanner * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ FLOAT *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Gain )( 
            IScanner * This,
            /* [in] */ LONG Index,
            /* [in] */ FLOAT newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Offset )( 
            IScanner * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Offset )( 
            IScanner * This,
            /* [in] */ LONG Index,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CorrectionGain )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CorrectionGain )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CorrectionOffset )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CorrectionOffset )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CorrectionBaseline )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CorrectionBaseline )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Baseline )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Baseline )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IntegrationTime )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IntegrationTime )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AverageFilter )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AverageFilter )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataPattern )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DataPattern )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FrameTrigger )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FrameTrigger )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineTrigger )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LineTrigger )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IScanner * This,
            /* [in] */ LONG Mode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SaveOffset )( 
            IScanner * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SaveGain )( 
            IScanner * This,
            /* [in] */ LONG Index);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadOffset )( 
            IScanner * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadGain )( 
            IScanner * This,
            /* [in] */ LONG Index);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutputBits )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutputBits )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SendExFrameTrigger )( 
            IScanner * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FrameOut )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FrameOut )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageOutputType )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImageOutputType )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SensitivityLevel )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SensitivityLevel )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SumLines )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SumLines )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WriteDataPattern )( 
            IScanner * This,
            /* [in] */ LONG Base,
            /* [in] */ LONG Step);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsOpened )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ModuleTypeName )( 
            IScanner * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SaveCurrentStatus )( 
            IScanner * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PixelSize )( 
            IScanner * This,
            /* [retval][out] */ FLOAT *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PixelNumber )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ModuleType )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxIntTime )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinIntTime )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OverallGain )( 
            IScanner * This,
            /* [retval][out] */ FLOAT *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OverallGain )( 
            IScanner * This,
            /* [in] */ FLOAT newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartPixel )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartPixel )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndPixel )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndPixel )( 
            IScanner * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnBoardOffsetCalibration )( 
            IScanner * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnBoardGainCalibration )( 
            IScanner * This,
            /* [in] */ LONG TargetValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ResetGain )( 
            IScanner * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ResetOffset )( 
            IScanner * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FPGA_Version )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FPGA_Build )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MCU_Version )( 
            IScanner * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SerialNumber )( 
            IScanner * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RetrieveSysinfo )( 
            IScanner * This);
        
        END_INTERFACE
    } IScannerVtbl;

    interface IScanner
    {
        CONST_VTBL struct IScannerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScanner_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IScanner_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IScanner_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IScanner_get_DetectorObject(This,pVal)	\
    ( (This)->lpVtbl -> get_DetectorObject(This,pVal) ) 

#define IScanner_put_DetectorObject(This,newVal)	\
    ( (This)->lpVtbl -> put_DetectorObject(This,newVal) ) 

#define IScanner_OffBoardCalibration(This,CalibrationType,pImgObject,StartPixel,EndPixel,TargetValue)	\
    ( (This)->lpVtbl -> OffBoardCalibration(This,CalibrationType,pImgObject,StartPixel,EndPixel,TargetValue) ) 

#define IScanner_get_Gain(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Gain(This,Index,pVal) ) 

#define IScanner_put_Gain(This,Index,newVal)	\
    ( (This)->lpVtbl -> put_Gain(This,Index,newVal) ) 

#define IScanner_get_Offset(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Offset(This,Index,pVal) ) 

#define IScanner_put_Offset(This,Index,newVal)	\
    ( (This)->lpVtbl -> put_Offset(This,Index,newVal) ) 

#define IScanner_get_CorrectionGain(This,pVal)	\
    ( (This)->lpVtbl -> get_CorrectionGain(This,pVal) ) 

#define IScanner_put_CorrectionGain(This,newVal)	\
    ( (This)->lpVtbl -> put_CorrectionGain(This,newVal) ) 

#define IScanner_get_CorrectionOffset(This,pVal)	\
    ( (This)->lpVtbl -> get_CorrectionOffset(This,pVal) ) 

#define IScanner_put_CorrectionOffset(This,newVal)	\
    ( (This)->lpVtbl -> put_CorrectionOffset(This,newVal) ) 

#define IScanner_get_CorrectionBaseline(This,pVal)	\
    ( (This)->lpVtbl -> get_CorrectionBaseline(This,pVal) ) 

#define IScanner_put_CorrectionBaseline(This,newVal)	\
    ( (This)->lpVtbl -> put_CorrectionBaseline(This,newVal) ) 

#define IScanner_get_Baseline(This,pVal)	\
    ( (This)->lpVtbl -> get_Baseline(This,pVal) ) 

#define IScanner_put_Baseline(This,newVal)	\
    ( (This)->lpVtbl -> put_Baseline(This,newVal) ) 

#define IScanner_get_IntegrationTime(This,pVal)	\
    ( (This)->lpVtbl -> get_IntegrationTime(This,pVal) ) 

#define IScanner_put_IntegrationTime(This,newVal)	\
    ( (This)->lpVtbl -> put_IntegrationTime(This,newVal) ) 

#define IScanner_get_AverageFilter(This,pVal)	\
    ( (This)->lpVtbl -> get_AverageFilter(This,pVal) ) 

#define IScanner_put_AverageFilter(This,newVal)	\
    ( (This)->lpVtbl -> put_AverageFilter(This,newVal) ) 

#define IScanner_get_DataPattern(This,pVal)	\
    ( (This)->lpVtbl -> get_DataPattern(This,pVal) ) 

#define IScanner_put_DataPattern(This,newVal)	\
    ( (This)->lpVtbl -> put_DataPattern(This,newVal) ) 

#define IScanner_get_FrameTrigger(This,pVal)	\
    ( (This)->lpVtbl -> get_FrameTrigger(This,pVal) ) 

#define IScanner_put_FrameTrigger(This,newVal)	\
    ( (This)->lpVtbl -> put_FrameTrigger(This,newVal) ) 

#define IScanner_get_LineTrigger(This,pVal)	\
    ( (This)->lpVtbl -> get_LineTrigger(This,pVal) ) 

#define IScanner_put_LineTrigger(This,newVal)	\
    ( (This)->lpVtbl -> put_LineTrigger(This,newVal) ) 

#define IScanner_Initialize(This,Mode)	\
    ( (This)->lpVtbl -> Initialize(This,Mode) ) 

#define IScanner_SaveOffset(This)	\
    ( (This)->lpVtbl -> SaveOffset(This) ) 

#define IScanner_SaveGain(This,Index)	\
    ( (This)->lpVtbl -> SaveGain(This,Index) ) 

#define IScanner_LoadOffset(This)	\
    ( (This)->lpVtbl -> LoadOffset(This) ) 

#define IScanner_LoadGain(This,Index)	\
    ( (This)->lpVtbl -> LoadGain(This,Index) ) 

#define IScanner_get_OutputBits(This,pVal)	\
    ( (This)->lpVtbl -> get_OutputBits(This,pVal) ) 

#define IScanner_put_OutputBits(This,newVal)	\
    ( (This)->lpVtbl -> put_OutputBits(This,newVal) ) 

#define IScanner_SendExFrameTrigger(This)	\
    ( (This)->lpVtbl -> SendExFrameTrigger(This) ) 

#define IScanner_get_FrameOut(This,pVal)	\
    ( (This)->lpVtbl -> get_FrameOut(This,pVal) ) 

#define IScanner_put_FrameOut(This,newVal)	\
    ( (This)->lpVtbl -> put_FrameOut(This,newVal) ) 

#define IScanner_get_ImageOutputType(This,pVal)	\
    ( (This)->lpVtbl -> get_ImageOutputType(This,pVal) ) 

#define IScanner_put_ImageOutputType(This,newVal)	\
    ( (This)->lpVtbl -> put_ImageOutputType(This,newVal) ) 

#define IScanner_get_SensitivityLevel(This,pVal)	\
    ( (This)->lpVtbl -> get_SensitivityLevel(This,pVal) ) 

#define IScanner_put_SensitivityLevel(This,newVal)	\
    ( (This)->lpVtbl -> put_SensitivityLevel(This,newVal) ) 

#define IScanner_get_SumLines(This,pVal)	\
    ( (This)->lpVtbl -> get_SumLines(This,pVal) ) 

#define IScanner_put_SumLines(This,newVal)	\
    ( (This)->lpVtbl -> put_SumLines(This,newVal) ) 

#define IScanner_WriteDataPattern(This,Base,Step)	\
    ( (This)->lpVtbl -> WriteDataPattern(This,Base,Step) ) 

#define IScanner_get_IsOpened(This,pVal)	\
    ( (This)->lpVtbl -> get_IsOpened(This,pVal) ) 

#define IScanner_get_ModuleTypeName(This,pVal)	\
    ( (This)->lpVtbl -> get_ModuleTypeName(This,pVal) ) 

#define IScanner_SaveCurrentStatus(This)	\
    ( (This)->lpVtbl -> SaveCurrentStatus(This) ) 

#define IScanner_get_PixelSize(This,pVal)	\
    ( (This)->lpVtbl -> get_PixelSize(This,pVal) ) 

#define IScanner_get_PixelNumber(This,pVal)	\
    ( (This)->lpVtbl -> get_PixelNumber(This,pVal) ) 

#define IScanner_get_ModuleType(This,pVal)	\
    ( (This)->lpVtbl -> get_ModuleType(This,pVal) ) 

#define IScanner_get_MaxIntTime(This,pVal)	\
    ( (This)->lpVtbl -> get_MaxIntTime(This,pVal) ) 

#define IScanner_get_MinIntTime(This,pVal)	\
    ( (This)->lpVtbl -> get_MinIntTime(This,pVal) ) 

#define IScanner_get_OverallGain(This,pVal)	\
    ( (This)->lpVtbl -> get_OverallGain(This,pVal) ) 

#define IScanner_put_OverallGain(This,newVal)	\
    ( (This)->lpVtbl -> put_OverallGain(This,newVal) ) 

#define IScanner_get_StartPixel(This,pVal)	\
    ( (This)->lpVtbl -> get_StartPixel(This,pVal) ) 

#define IScanner_put_StartPixel(This,newVal)	\
    ( (This)->lpVtbl -> put_StartPixel(This,newVal) ) 

#define IScanner_get_EndPixel(This,pVal)	\
    ( (This)->lpVtbl -> get_EndPixel(This,pVal) ) 

#define IScanner_put_EndPixel(This,newVal)	\
    ( (This)->lpVtbl -> put_EndPixel(This,newVal) ) 

#define IScanner_OnBoardOffsetCalibration(This)	\
    ( (This)->lpVtbl -> OnBoardOffsetCalibration(This) ) 

#define IScanner_OnBoardGainCalibration(This,TargetValue)	\
    ( (This)->lpVtbl -> OnBoardGainCalibration(This,TargetValue) ) 

#define IScanner_ResetGain(This)	\
    ( (This)->lpVtbl -> ResetGain(This) ) 

#define IScanner_ResetOffset(This)	\
    ( (This)->lpVtbl -> ResetOffset(This) ) 

#define IScanner_get_FPGA_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_FPGA_Version(This,pVal) ) 

#define IScanner_get_FPGA_Build(This,pVal)	\
    ( (This)->lpVtbl -> get_FPGA_Build(This,pVal) ) 

#define IScanner_get_MCU_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_MCU_Version(This,pVal) ) 

#define IScanner_get_SerialNumber(This,pVal)	\
    ( (This)->lpVtbl -> get_SerialNumber(This,pVal) ) 

#define IScanner_RetrieveSysinfo(This)	\
    ( (This)->lpVtbl -> RetrieveSysinfo(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IScanner_INTERFACE_DEFINED__ */



#ifndef __DetectorControlLib_LIBRARY_DEFINED__
#define __DetectorControlLib_LIBRARY_DEFINED__

/* library DetectorControlLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_DetectorControlLib;

EXTERN_C const CLSID CLSID_CommandChannel;

#ifdef __cplusplus

class DECLSPEC_UUID("BAF59343-011A-4437-A083-964A32319FC7")
CommandChannel;
#endif

#ifndef ___IScannerImageEvents_DISPINTERFACE_DEFINED__
#define ___IScannerImageEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IScannerImageEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IScannerImageEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("E80A089C-354D-4CE9-9BFB-0F2D4F744E76")
    _IScannerImageEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IScannerImageEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IScannerImageEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IScannerImageEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IScannerImageEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IScannerImageEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IScannerImageEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IScannerImageEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IScannerImageEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IScannerImageEventsVtbl;

    interface _IScannerImageEvents
    {
        CONST_VTBL struct _IScannerImageEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IScannerImageEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IScannerImageEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IScannerImageEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IScannerImageEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IScannerImageEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IScannerImageEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IScannerImageEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IScannerImageEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ScannerImage;

#ifdef __cplusplus

class DECLSPEC_UUID("8E7A5B32-5358-4B51-AABA-D9299EDBA835")
ScannerImage;
#endif

#ifndef ___IScannerDisplayEvents_DISPINTERFACE_DEFINED__
#define ___IScannerDisplayEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IScannerDisplayEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IScannerDisplayEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0A01CC4C-400D-4209-ACFD-F5419A5AFE8D")
    _IScannerDisplayEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IScannerDisplayEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IScannerDisplayEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IScannerDisplayEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IScannerDisplayEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IScannerDisplayEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IScannerDisplayEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IScannerDisplayEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IScannerDisplayEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IScannerDisplayEventsVtbl;

    interface _IScannerDisplayEvents
    {
        CONST_VTBL struct _IScannerDisplayEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IScannerDisplayEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IScannerDisplayEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IScannerDisplayEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IScannerDisplayEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IScannerDisplayEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IScannerDisplayEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IScannerDisplayEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IScannerDisplayEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ScannerDisplay;

#ifdef __cplusplus

class DECLSPEC_UUID("34A39CDC-773F-494E-B0F0-7FCB71A5256E")
ScannerDisplay;
#endif

EXTERN_C const CLSID CLSID_FrameObject;

#ifdef __cplusplus

class DECLSPEC_UUID("B17A9A50-BB2B-4068-8DB1-D2B8D73FDD1F")
FrameObject;
#endif

EXTERN_C const CLSID CLSID_Scanner;

#ifdef __cplusplus

class DECLSPEC_UUID("23BE38C8-39D4-4166-A513-95F6BA9C3A2E")
Scanner;
#endif
#endif /* __DetectorControlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


