#pragma once

class CEventManagerIF
{
public:
	CEventManagerIF(void);
	virtual ~CEventManagerIF(void);
	virtual void OnDTEvent(BYTE EventID,BYTE EventContent)=0;
	virtual void OnDTFrameReady(BYTE* pSrc, DWORD Size)=0;
	virtual void OnDTSubFrameReady(LONG  RowID, LONG NumLines,BOOL bLastFrame)=0;
	virtual void OnNewDataComimg(ULONG Size)=0;
};
