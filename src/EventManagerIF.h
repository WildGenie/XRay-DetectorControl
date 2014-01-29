#pragma once

class CEventManagerIF
{
public:
	CEventManagerIF(void);
	virtual ~CEventManagerIF(void);
    virtual void OnScannerEvent(BYTE EventID,BYTE EventContent)=0;
    virtual void OnFrameReady(BYTE* pSrc, DWORD Size)=0;
    virtual void OnSubFrameReady(LONG  RowID, LONG NumLines,BOOL bLastFrame)=0;
	virtual void OnNewDataComimg(ULONG Size)=0;
};
