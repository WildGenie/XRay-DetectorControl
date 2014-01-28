// ScannerImage.h : CScannerImage µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ



#include "DetectorControl_i.h"
#include "_IScannerImageEvents_CP.h"



using namespace ATL;


// CScannerImage

class ATL_NO_VTABLE CScannerImage :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CScannerImage, &CLSID_ScannerImage>,
	public IConnectionPointContainerImpl<CScannerImage>,
	public CProxy_IScannerImageEvents<CScannerImage>,
	public IDispatchImpl<IScannerImage, &IID_IScannerImage, &LIBID_DetectorControlLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CScannerImage()
	{
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



};

OBJECT_ENTRY_AUTO(__uuidof(ScannerImage), CScannerImage)
