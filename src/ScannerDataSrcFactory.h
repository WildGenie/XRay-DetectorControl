#pragma once

#include "NETDataSrc.h"
#include "../CommandChannel.h"
class CScannerDataSrcFactory
{
private:
    CScannerDataSrcIF* m_pDataSrc;
public:
    CScannerDataSrcFactory(void);
    ~CScannerDataSrcFactory(void);
    CScannerDataSrcIF* GetScannerDataSrc(int CardType,ICommandChannel* pDetector=NULL,LPVOID pParam=NULL);
};
