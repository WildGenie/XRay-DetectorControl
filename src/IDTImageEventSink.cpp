#include "StdAfx.h"
#include ".\idtimageeventsink.h"
#include "DTImage.h"
IDTImageEventSink::IDTImageEventSink(void)
{
	m_pDataSrc = NULL;
}

IDTImageEventSink::~IDTImageEventSink(void)
{
}
void IDTImageEventSink::ConnectDataSrc(CDTImage* pSrc)
{
	
	if(pSrc)
	{
		m_pDataSrc = pSrc;
		m_pDataSrc->AdviseSink(this,&m_Cookie);
	}
}
void IDTImageEventSink::DisConnectDataSrc()
{
	if(m_pDataSrc)
		m_pDataSrc->UnAdviseSink(m_Cookie);
	m_pDataSrc = NULL;
}