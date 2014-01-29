#include "../stdafx.h"
#include ".\iframeeventsink.h"
#include "..\ScannerImage.h"
IFrameEventSink::IFrameEventSink(void)
{
	m_pDataSrc = NULL;
}

IFrameEventSink::~IFrameEventSink(void)
{
}
void IFrameEventSink::ConnectDataSrc(CScannerImage* pSrc)
{
	
	if(pSrc)
	{
		m_pDataSrc = pSrc;
		m_pDataSrc->AdviseSink(this,&m_Cookie);
	}
}
void IFrameEventSink::DisConnectDataSrc()
{
	if(m_pDataSrc)
		m_pDataSrc->UnAdviseSink(m_Cookie);
	m_pDataSrc = NULL;
}
