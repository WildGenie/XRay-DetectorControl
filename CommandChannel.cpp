// CommandChannel.cpp : CCommandChannel µÄÊµÏÖ

#include "stdafx.h"
#include "CommandChannel.h"
#include <comutil.h>

#pragma comment(lib, "comsuppw.lib")
// CCommandChannel

long CCommandChannel::get_IPAddress(BSTR* pVal)
{
	CComBSTR bstrRT(m_pCommandChannelPrv->get_IPAddress());
	bstrRT.CopyTo(pVal);
	return S_OK;
}

long CCommandChannel::put_IPAddress(BSTR newVal)
{
	CHAR* tempbuf = _com_util::ConvertBSTRToString(newVal);
	m_pCommandChannelPrv->put_IPAddress(tempbuf);
	delete [] tempbuf;
	return S_OK;
}

STDMETHODIMP CCommandChannel::get_CmdPort(LONG* pVal)
{

	m_pCommandChannelPrv->get_CmdPort(pVal);
	return S_OK;
}

STDMETHODIMP CCommandChannel::put_CmdPort(LONG newVal)
{
	m_pCommandChannelPrv->put_CmdPort(newVal);
	return S_OK;
}


STDMETHODIMP CCommandChannel::get_ObjectHandle(IUnknown** pVal)
{

	this->QueryInterface(IID_IUnknown,(void**)pVal); 
	return S_OK;
}

STDMETHODIMP CCommandChannel::get_IsOpened(LONG* pVal)
{

	m_pCommandChannelPrv->get_IsOpened(pVal);
	return S_OK;
}

STDMETHODIMP CCommandChannel::get_LastErrID(LONG* pVal)
{

	m_pCommandChannelPrv->get_LastErrID(pVal);
	return S_OK;
}

STDMETHODIMP CCommandChannel::get_ChannelType(LONG* pVal)
{
	m_pCommandChannelPrv->get_ChannelType(pVal);
	return S_OK;
}

STDMETHODIMP CCommandChannel::put_ChannelType(LONG newVal)
{
	m_pCommandChannelPrv->put_ChannelType(newVal);
	return S_OK;
}

STDMETHODIMP CCommandChannel::Open(LONG* bOK)
{
	m_pCommandChannelPrv->Open(bOK);
	return S_OK;
}

STDMETHODIMP CCommandChannel::Close(void)
{
	m_pCommandChannelPrv->Close();
	return S_OK;
}

STDMETHODIMP CCommandChannel::SendCommandA(CHAR* pSendCmd, CHAR* pRTBuffer,LONG* pbSuccess)
{
	m_pCommandChannelPrv->SendCommandA(pSendCmd, pRTBuffer, pbSuccess);
	return S_OK;
}

STDMETHODIMP CCommandChannel::SendCommand(BSTR bstrCmd, BSTR* bstrRTMsg, LONG* bOK)
{

	CHAR REVBUF[100];
	memset(REVBUF,0,100);
	CHAR* CMDBUF = _com_util::ConvertBSTRToString(bstrCmd);
	m_pCommandChannelPrv->SendCommandA(CMDBUF, REVBUF,bOK);
	CComBSTR bstrRT(REVBUF);
	// Convert the string to uppercase
	// Return a copy of the string.
	bstrRT.CopyTo(bstrRTMsg);
	delete [] CMDBUF;
	return S_OK;
}


STDMETHODIMP CCommandChannel::get_CmdTimeOut(LONG* pVal)
{
    // TODO: Add your implementation code here
    m_pCommandChannelPrv->get_CmdTimeOut(pVal);
    return S_OK;
}

STDMETHODIMP CCommandChannel::put_CmdTimeOut(LONG newVal)
{
    m_pCommandChannelPrv->put_CmdTimeOut(newVal);
    return S_OK;
}

