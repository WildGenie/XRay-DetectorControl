#include "../stdafx.h"
#include "scannerdatasrcfactory.h"
#include "libconst.h"
#include "NETDataSrc.h"



CScannerDataSrcFactory::CScannerDataSrcFactory(void):
m_pDataSrc(NULL)
{

}

CScannerDataSrcFactory::~CScannerDataSrcFactory(void)
{
}

CScannerDataSrcIF* CScannerDataSrcFactory::GetScannerDataSrc(int CardType,ICommandChannel* pDetector,LPVOID pParam)
{
	if(CardType == NET)
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
