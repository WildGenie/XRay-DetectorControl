// ScannerDisplay.h : CScannerDisplay 的声明
#pragma once
#include "resource.h"       // 主符号
#include <atlctl.h>
#include "DetectorControl_i.h"
#include "_IScannerDisplayEvents_CP.h"
#include "src\DIBImage.h"
#include "src\IFrameEventSink.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;



// CScannerDisplay
class ATL_NO_VTABLE CScannerDisplay :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IScannerDisplay, &IID_IScannerDisplay, &LIBID_DetectorControlLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IOleControlImpl<CScannerDisplay>,
	public IOleObjectImpl<CScannerDisplay>,
	public IOleInPlaceActiveObjectImpl<CScannerDisplay>,
	public IViewObjectExImpl<CScannerDisplay>,
	public IOleInPlaceObjectWindowlessImpl<CScannerDisplay>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CScannerDisplay>,
	public CProxy_IScannerDisplayEvents<CScannerDisplay>,
	public IQuickActivateImpl<CScannerDisplay>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CScannerDisplay>,
#endif
	public IProvideClassInfo2Impl<&CLSID_ScannerDisplay, &__uuidof(_IScannerDisplayEvents), &LIBID_DetectorControlLib>,
	public CComCoClass<CScannerDisplay, &CLSID_ScannerDisplay>,
	public CComControl<CScannerDisplay>,
	public IDispatchImpl<_IScannerDisplayEvents, &__uuidof(_IScannerDisplayEvents), &LIBID_DetectorControlLib, /* wMajor = */ 1, /* wMinor = */ 0>,
	public IFrameEventSink
{
public:
	
	enum REFRESH_MODE {RF_FRAME,RF_TOPDOWN,RF_MOVING};

	CScannerDisplay()
	{
		m_Height = 0;//Buffer Size
		m_Width = 0;
		m_Scale = 1;
		m_Gamma = 1.0;
		m_mapStart=1;
		m_mapEnd =3000;
		m_pDisplayObject = NULL;
		m_pImageSrcObject = NULL;
		m_pDataSrc = NULL;

		m_Org_X = 0;
		m_Org_X = 0;
		m_Org_Y = 0;
		m_Org_Y = 0;

		m_bOpened = FALSE;
		m_RefreshMode = 0;
		m_RefreshRate = 0;

		m_WndHeight = 0;
		m_WndWidth = 0;

		InitializeLUT();
		m_bWindowOnly = TRUE;
		m_pTempBuf = NULL;

	}

	DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
		OLEMISC_INSIDEOUT |
		OLEMISC_ACTIVATEWHENVISIBLE |
		OLEMISC_SETCLIENTSITEFIRST
		)

		DECLARE_REGISTRY_RESOURCEID(IDR_SCANNERDISPLAY)


	BEGIN_COM_MAP(CScannerDisplay)
		COM_INTERFACE_ENTRY(IScannerDisplay)
		COM_INTERFACE_ENTRY2(IDispatch, _IScannerDisplayEvents)
		COM_INTERFACE_ENTRY(IViewObjectEx)
		COM_INTERFACE_ENTRY(IViewObject2)
		COM_INTERFACE_ENTRY(IViewObject)
		COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
		COM_INTERFACE_ENTRY(IOleInPlaceObject)
		COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
		COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
		COM_INTERFACE_ENTRY(IOleControl)
		COM_INTERFACE_ENTRY(IOleObject)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(IQuickActivate)
#ifndef _WIN32_WCE
		COM_INTERFACE_ENTRY(IDataObject)
#endif
		COM_INTERFACE_ENTRY(IProvideClassInfo)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY(_IScannerDisplayEvents)
	END_COM_MAP()

	BEGIN_PROP_MAP(CScannerDisplay)
		PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
		PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
		// 示例项
		// PROP_ENTRY_TYPE("属性名", dispid, clsid, vtType)
		// PROP_PAGE(CLSID_StockColorPage)
	END_PROP_MAP()

	BEGIN_CONNECTION_POINT_MAP(CScannerDisplay)
		CONNECTION_POINT_ENTRY(__uuidof(_IScannerDisplayEvents))
	END_CONNECTION_POINT_MAP()

	BEGIN_MSG_MAP(CScannerDisplay)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_VSCROLL, OnVScroll)
		MESSAGE_HANDLER(WM_HSCROLL, OnHScroll)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SIZE, OnSize);
		MESSAGE_HANDLER(WM_DISPLAY_REFRESH,OnRefresh)
			CHAIN_MSG_MAP(CComControl<CScannerDisplay>)
			DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()
	// 处理程序原型:
	//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* const arr[] =
		{
			&IID_IScannerDisplay,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

	// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

	// IScannerDisplay
public:
	HRESULT OnDrawAdvanced(ATL_DRAWINFO& di)
	{
		BOOL bRunTime;
		GetAmbientUserMode(bRunTime);
		RECT& Rect = *(RECT*)di.prcBounds;
		// Set Clip region to the rectangle specified by di.prcBounds
		HRGN hRgnOld = NULL;
		if (GetClipRgn(di.hdcDraw, hRgnOld) != 1)
			hRgnOld = NULL;
		bool bSelectOldRgn = false;

		if(!bRunTime)
		{
			HICON hIcon=LoadIcon(_AtlBaseModule.GetResourceInstance(),MAKEINTRESOURCE(IDB_SCANNERDISPLAY)); 
			DrawIcon(di.hdcDraw,Rect.left,Rect.top,hIcon); 
			DeleteObject(hIcon);
		}
		else
		{
			if(!::IsWindow(m_hWnd))
			{
				return 0;
			}
			if(m_SizeChanged)//Redraw all
			{
				Refresh();
				m_SizeChanged = FALSE;
				BitBlt(di.hdcDraw, 
					0,0, 
					m_WndWidth,m_WndHeight,
					m_hMemDC, 
					0,0, 
					SRCCOPY); 
			}
			else//Update Part
			{
				LPRECT prect = (LPRECT)di.prcBounds;
				BitBlt(di.hdcDraw, 
					prect->left, prect->top, 
					(prect->right - prect->left), 
					(prect->bottom - prect->top), 
					m_hMemDC, 
					prect->left + m_xCurrentScroll, 
					prect->top + m_yCurrentScroll, 
					SRCCOPY); 

			}
		}
		//		if( m_Scale == 0)
		//			DrawEdge(di.hdcDraw,&Rect,EDGE_ETCHED,BF_ADJUST|BF_FLAT|BF_TOP|BF_BOTTOM|BF_LEFT|BF_RIGHT);
		return S_OK;
	}


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		RECT rc;
		GetWindowRect(&rc);
		rc.right -= rc.left;
		rc.bottom -= rc.top;
		rc.top = rc.left = 0;
		//Create the memDC Here
		m_hMemDC = CreateCompatibleDC(this->GetDC());
		::SetBkColor(m_hMemDC,RGB(255, 255, 255));
		::SetStretchBltMode(m_hMemDC,HALFTONE);
		HPEN hPen = (HPEN)SelectObject(m_hMemDC,GetStockObject(BLACK_PEN)); 
		DeleteObject(hPen);


		m_xMinScroll = 0;       // minimum horizontal scroll value 
		m_xCurrentScroll = 0;   // current horizontal scroll value 
		m_xMaxScroll = 0;       // maximum horizontal scroll value 

		// These variables are required for vertical scrolling. 

		m_yMinScroll = 0;       // minimum vertical scroll value 
		m_yCurrentScroll = 0;   // current vertical scroll value 
		m_yMaxScroll = 0;       // maximum vertical scroll value 
		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnVScroll(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnHScroll(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnRefresh(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
private:
	int m_WndHeight;//Display Size
	int m_WndWidth;
	LONG m_Height;//Buffer Size
	LONG m_Width;

	float m_Gamma;
	LONG  m_mapStart;
	LONG  m_mapEnd;

	IFrameObject* m_pDisplayObject;
	IFrameObject* m_pImageSrcObject;

	BOOL m_bOpened;
	LONG m_RefreshMode;
	LONG m_RefreshRate;

	BYTE* m_pTempBuf;
	CDIBImage m_DisplayImage;


	// These variables are required for Horizonal scrolling. 
	int m_xMinScroll;       // minimum horizontal scroll value 
	int m_xCurrentScroll;   // current horizontal scroll value 
	int m_xMaxScroll;       // maximum horizontal scroll value 

	// These variables are required for vertical scrolling. 

	int m_yMinScroll;       // minimum vertical scroll value 
	int m_yCurrentScroll;   // current vertical scroll value 
	int m_yMaxScroll;       // maximum vertical scroll value 

	BYTE  m_LUT[MAX_ADC];
	RGBQUAD m_ColorTable[256];
	BOOL m_SizeChanged;
	LONG m_bAutoSize;
	HDC m_hMemDC;
	RECT	m_DrawRect;
	RECT	m_SrcRect;
	SCROLLINFO m_si; 
	LONG m_Scale;//Be 0 1 2,3 ....

	LONG m_Org_X;
	LONG m_Org_Y;
	CComAutoCriticalSection m_displayCs;
private://Service Function
	void	AllocateImgBuffer(LONG Width,LONG Height);
	void	ReleaseImgBuffer();
	void	SetScale();
	void	SetScrollExtend();
	void	SetDrawRect();
	void	SetScrollInfo();
	void	InitializeLUT();
	void	SetWindowing();
	void	LUTMap(LONG StartLine, LONG NumLines,BOOL bMoving);
protected:

	void OnFrameReady(LONG LineNum);

	void OnSubFrameReady(LONG NumOfBlockLeft, LONG StartLine, LONG NumLines, BYTE bLastBlock);
public:
	STDMETHOD(get_ImgWidth)(ULONG* pVal);
	STDMETHOD(put_ImgWidth)(ULONG newVal);
	STDMETHOD(get_ImgHeight)(ULONG* pVal);
	STDMETHOD(put_ImgHeight)(ULONG newVal);

	STDMETHOD(get_Gamma)(FLOAT* pVal);
	STDMETHOD(put_Gamma)(FLOAT newVal);
	STDMETHOD(get_MapStart)(LONG* pVal);
	STDMETHOD(put_MapStart)(LONG newVal);
	STDMETHOD(get_MapEnd)(LONG* pVal);
	STDMETHOD(put_MapEnd)(LONG newVal);

	STDMETHOD(get_DataSource)(IUnknown** pVal);
	STDMETHOD(put_DataSource)(IUnknown* newVal);

	STDMETHOD(Open)(LONG* bOK);
	STDMETHOD(Close)(void);

	STDMETHOD(get_RefreshMode)(LONG* pVal);
	STDMETHOD(put_RefreshMode)(LONG newVal);
	STDMETHOD(get_RefreshRate)(LONG* pVal);
	STDMETHOD(put_RefreshRate)(LONG newVal);
	STDMETHOD(get_ImageObject)(IUnknown** pVal);
	STDMETHOD(get_DisplayScale)(LONG* pVal);
	STDMETHOD(put_DisplayScale)(LONG newVal);

	STDMETHOD(Refresh)(void);
	STDMETHOD(get_OrgPoint_X)(LONG* pVal);
	STDMETHOD(put_OrgPoint_X)(LONG newVal);
	STDMETHOD(get_OrgPoint_Y)(LONG* pVal);
	STDMETHOD(put_OrgPoint_Y)(LONG newVal);
	STDMETHOD(get_ObjectHandle)(IUnknown** pVal);
	STDMETHOD(Load)(BSTR FilePath);
	STDMETHOD(Save)(BSTR FilePath);
	STDMETHOD(RepaintDisplay)(void);


	// _IScannerDisplayEvents Methods
public:
	STDMETHOD(MousePixelInfo)(LONG X, LONG Y, LONG Value)
	{
		// 在此处添加函数实现。
		return E_NOTIMPL;
	}
};

OBJECT_ENTRY_AUTO(__uuidof(ScannerDisplay), CScannerDisplay)
