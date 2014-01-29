// ScannerImage.h : CScannerImage 的声明

#pragma once
#include <comdef.h>
#include "resource.h"       // 主符号
#include "DetectorControl_i.h"
#include "_IScannerImageEvents_CP.h"
#include "src/IFrameEventSink.h"
#include "src/FrameBufFactory.h"
#include "src/DataPacketFactory.h"
#include "src/DataPacketQueueFactory.h"
#include "src/ScannerDataSrcFactory.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;


// CScannerImage

class ATL_NO_VTABLE CScannerImage :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CScannerImage, &CLSID_ScannerImage>,
	public IConnectionPointContainerImpl<CScannerImage>,
	public CProxy_IScannerImageEvents<CScannerImage>,
	public IDispatchImpl<IScannerImage, &IID_IScannerImage, &LIBID_DetectorControlLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public CEventManagerIF
{
public:
	CScannerImage()
	{
		m_ImageHeight = 512;
		m_ImageWidth = 512;
		m_SubFrameHeight = m_ImageHeight;
		m_bIsOpened = FALSE;
		m_CardType = NET;
		m_BytesPerPixel = 2;
		m_ImagePort = 4000;
		m_pDetector = NULL;
		m_pDetector = NULL;
		m_pDataSrc = NULL;
		m_pImageObject = NULL;
		m_LastErrID = 0;
		m_hAllFrameSended = CreateEvent(NULL,TRUE,FALSE,NULL);//Create a manual event
		m_BandWidth = 0;
		m_BytesReceived  = 0;
		m_bExFrameTrigger = FALSE;
		m_Timeout = 10000;
		for(int i = 0;i<SINK_SIZE;i++)
			m_SinkArray[i] = NULL;

	}

DECLARE_REGISTRY_RESOURCEID(IDR_SCANNERIMAGE)


BEGIN_COM_MAP(CScannerImage)
	COM_INTERFACE_ENTRY(IScannerImage)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CScannerImage)
	CONNECTION_POINT_ENTRY(__uuidof(_IScannerImageEvents))
END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(get_ImgHeight)(LONG* pVal);
	STDMETHOD(put_ImgHeight)(LONG newVal);
	STDMETHOD(get_ImgWidth)(LONG* pVal);
	STDMETHOD(put_ImgWidth)(LONG newVal);
	STDMETHOD(get_BytesPerPixel)(LONG* pVal);
	STDMETHOD(put_BytesPerPixel)(LONG newVal);
	STDMETHOD(get_ChannelType)(LONG* pVal);
	STDMETHOD(put_ChannelType)(LONG newVal);
	STDMETHOD(get_ImagePort)(LONG* pVal);
	STDMETHOD(put_ImagePort)(LONG newVal);
	STDMETHOD(get_DetectorObject)(IUnknown** pVal);
	STDMETHOD(put_DetectorObject)(IUnknown* newVal);
	STDMETHOD(get_IsOpened)(LONG* pVal);
	STDMETHOD(get_LastErrID)(LONG* pVal);
	STDMETHOD(Open)(LONG* bOK);
	STDMETHOD(Close)(void);
	STDMETHOD(Grab)(LONG FrameNum, LONG* bOK);
	STDMETHOD(Snap)(LONG FrameNum, LONG* bOK);
	STDMETHOD(PrintErrMsg)(LONG ErrID, BSTR* ErrMsg);

	STDMETHOD(get_SubFrameHeight)(LONG* pVal);
	STDMETHOD(put_SubFrameHeight)(LONG newVal);
	void OnScannerEvent(BYTE EventID,BYTE EventContent);
	void OnFrameReady(BYTE* pSrc, DWORD Size);
	void OnSubFrameReady(LONG  RowID, LONG NumLines,BOOL bLastFrame);
	void OnNewDataComimg(ULONG Size);
	STDMETHOD(Stop)(void);
	STDMETHOD(get_IsGrabing)(LONG* pVal);
	STDMETHOD(get_ImageObject)(IUnknown** pVal);
	STDMETHOD(get_BandWidth)(LONG* pVal);
	void AdviseSink(IFrameEventSink* pSink,LONG* pCookie);
	void UnAdviseSink(LONG Cookie);

	STDMETHOD(get_ObjectHandle)(IUnknown** pVal);
	STDMETHOD(get_TimeOut)(LONG* pVal);
	STDMETHOD(put_TimeOut)(LONG newVal);
	STDMETHOD(get_ExFrameTrigger)(LONG* pVal);
	STDMETHOD(put_ExFrameTrigger)(LONG newVal);

	STDMETHOD(get_DualScanMode)(LONG* pVal);
	STDMETHOD(put_DualScanMode)(LONG newVal);
	STDMETHOD(OpenMemImage)(LONG width, LONG height, BYTE* data);
	STDMETHOD(Advise)(IFrameReadyCallBack* pCallBack, long* cookie);
	STDMETHOD(UnAdvise)(LONG cookie);

private:
	void ResetAllDataPacket();
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	void OnTimer();
	void OnSinkSubFrameReady( LONG NumOfBlockLeft,  LONG StartLine,  LONG NumLines, BYTE bLastBlock);
	void OnSinkFrameReady(LONG NumLines);
	void SetFrameTrigger();
	void SendFrameTrigger();

private:
	ULONG	m_Timeout;
	ULONG	m_ImageHeight;
	ULONG	m_ImageWidth;
	BOOL	m_bIsOpened;
	LONG	m_CardType;
	ULONG	m_BytesPerPixel;
	ULONG	m_ImagePort;
	ULONG	m_LastErrID;
	ULONG	m_SubFrameHeight;

	ULONG	m_BandWidth;
	ULONG	m_BytesReceived ;
	BOOL	m_bExFrameTrigger;

	CFrameBufFactory		m_FrameBufFactory;
	CDataPacketFactory		m_DataPacketFactory;
	CDataPacketQueueFactory		m_DataPacketQueueFactory;
	CScannerDataSrcFactory		m_ScannerDataSrcFactory;

	ULONG			m_FrameNum;
	ULONG			m_CurFrameCount;
	HANDLE			m_hAllFrameSended;

	CScannerDataSrcIF*	m_pDataSrc;
	ICommandChannel*	m_pDetector;
	void*			m_pDisplay;
	CFrameBufIF*	m_pFrameBuf;
	CDataPacketQueueIF*	m_pDataPacketQueue;
	IFrameObject*	m_pImageObject;
	long			m_dualScanMode;
	IFrameEventSink*	m_SinkArray[SINK_SIZE];

};

OBJECT_ENTRY_AUTO(__uuidof(ScannerImage), CScannerImage)
