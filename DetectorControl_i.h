

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Jan 28 17:31:07 2014
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


