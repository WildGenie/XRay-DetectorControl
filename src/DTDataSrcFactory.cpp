#include "StdAfx.h"
#include "dtdatasrcfactory.h"





CDTDataSrcFactory::CDTDataSrcFactory(void):
m_pDataSrc(NULL)
{

}

CDTDataSrcFactory::~CDTDataSrcFactory(void)
{
}

CDTDataSrcIF* CDTDataSrcFactory::GetDataSrc(int CardType,IDTDetector* pDetector,LPVOID pParam)
{

	if(CardType == DT_USB)
	{
		if(m_pDataSrc)
		{
			delete m_pDataSrc;
			m_pDataSrc = NULL;
		}
		m_pDataSrc = new CUSBDataSrc(pDetector);
		//Check the USB device avability
		if(m_pDataSrc->Open(pParam))
		{
			((CUSBDataSrc*)m_pDataSrc)->SetCommitPacketNum(DT_USB_COMMIT_NUM);
		}
		else
		{
			//Not open delete the device
			delete m_pDataSrc;
			m_pDataSrc = NULL;
		}
	}
	else if(CardType == DT_NET)
	{
		if(m_pDataSrc)
		{
			delete m_pDataSrc;
			m_pDataSrc = NULL;
		}
		m_pDataSrc = new CNETDataSrc(pDetector);
		if(m_pDataSrc->Open(pParam))
		{
			
		}
		else
		{
			//Not open delete the device
			delete m_pDataSrc;
			m_pDataSrc = NULL;
		}
	}
	return m_pDataSrc;
}
