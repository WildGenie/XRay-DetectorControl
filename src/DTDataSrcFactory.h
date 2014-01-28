#pragma once
#include "USBDataSrc.h"
#include "NETDataSrc.h"
//#include ".\DTImage.h"
#include "DTDetector.h"
class CDTDataSrcFactory
{
private:
	CDTDataSrcIF* m_pDataSrc;
public:
	CDTDataSrcFactory(void);
	~CDTDataSrcFactory(void);
	CDTDataSrcIF* GetDataSrc(int CardType,IDTDetector* pDetector=NULL,LPVOID pParam=NULL);
};
