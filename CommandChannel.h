// CommandChannel.h : CCommandChannel µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ

#include "src/CommandChannelPrv.h"

#include "DetectorControl_i.h"



using namespace ATL;


// CCommandChannel

class ATL_NO_VTABLE CCommandChannel :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CCommandChannel, &CLSID_CommandChannel>,
	public ICommandChannel
{
public:
	CCommandChannel()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMMANDCHANNEL)


BEGIN_COM_MAP(CCommandChannel)
	COM_INTERFACE_ENTRY(ICommandChannel)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(get_IPAddress)(BSTR* pVal);
	STDMETHOD(put_IPAddress)(BSTR newVal);
	STDMETHOD(get_CmdPort)(LONG* pVal);
	STDMETHOD(put_CmdPort)(LONG newVal);
	STDMETHOD(get_ObjectHandle)(IUnknown** pVal);
	STDMETHOD(get_IsOpened)(LONG* pVal);
	STDMETHOD(get_LastErrID)(LONG* pVal);
	STDMETHOD(get_ChannelType)(LONG* pVal);
	STDMETHOD(put_ChannelType)(LONG newVal);
	STDMETHOD(get_CmdTimeOut)(LONG* pVal);
	STDMETHOD(put_CmdTimeOut)(LONG newVal);

	STDMETHOD(Open)(LONG* bOK);
	STDMETHOD(Close)(void);
	STDMETHOD(SendCommand)(BSTR bstrCmd, BSTR* bstrRTMsg, LONG* bOK);
	STDMETHOD(SendCommandA)(CHAR* Cmd, CHAR* pRT,LONG* pbOK);
	
private:
	CommandChannelPrv* m_pCommandChannelPrv;
};

OBJECT_ENTRY_AUTO(__uuidof(CommandChannel), CCommandChannel)
