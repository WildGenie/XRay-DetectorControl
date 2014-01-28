// FrameObject.h : CFrameObject µÄÉùÃ÷

#pragma once
#include "stdafx.h"
#include "resource.h"       // Ö÷·ûºÅ
#include "DetectorControl_i.h"
#include "src/FrameObjectPrv.h"
using namespace ATL;


// CFrameObject

class ATL_NO_VTABLE CFrameObject :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFrameObject, &CLSID_FrameObject>,
	public IFrameObject
{
private:
	FrameObjectPrv* m_pFrameObject;
public:
	CFrameObject()
	{
		m_pFrameObject = new FrameObjectPrv();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FRAMEOBJECT)


BEGIN_COM_MAP(CFrameObject)
	COM_INTERFACE_ENTRY(IFrameObject)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		m_pFrameObject = new FrameObjectPrv();
		if(m_pFrameObject)
			return S_OK;
		else
			return S_FALSE;
	}

	void FinalRelease()
	{
		if(m_pFrameObject) {
			delete m_pFrameObject;
			m_pFrameObject = 0;
		}

	}

public:
	STDMETHOD(get_ImageDataAddress)(LONG* pVal);
	STDMETHOD(put_ImageDataAddress)(LONG newVal);
	STDMETHOD(get_Width)(LONG* pVal);
	STDMETHOD(get_Height)(LONG* pVal);
	STDMETHOD(get_BytesPerPixel)(LONG* pVal);
	STDMETHOD(get_Pixel)(LONG X, LONG Y, LONG* pVal);
	STDMETHOD(put_Pixel)(LONG X, LONG Y, LONG newVal);
	STDMETHOD(Open)(LONG Width, LONG Height, LONG BytesPerPixel);
	STDMETHOD(get_ImageLineAddress)(LONG LineIndex, LONG* pVal);

	STDMETHOD(get_ColAverage)(LONG* pAvg);
	STDMETHOD(get_ColMax)(LONG* pMax);
	STDMETHOD(get_ColMin)(LONG* pMin);
	STDMETHOD(get_RowMin)(LONG* pMin);
	STDMETHOD(get_RowMax)(LONG* pMax);
	STDMETHOD(get_RowAverage)(LONG* pAvg);
	STDMETHOD(get_ColNoise)(FLOAT* pNoise);
	STDMETHOD(get_RowNoise)(FLOAT* pNoise);
};

OBJECT_ENTRY_AUTO(__uuidof(FrameObject), CFrameObject)
