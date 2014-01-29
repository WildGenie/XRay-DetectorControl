#pragma once

class CScannerImage;
class IFrameEventSink
{
private:

protected:
    CScannerImage* m_pDataSrc;
	LONG		m_Cookie;
	void ConnectDataSrc(CScannerImage* pSrc);
	void DisConnectDataSrc();
public:
    IFrameEventSink(void);
    virtual ~IFrameEventSink(void);
	virtual void OnFrameReady(LONG LineNum){};
	virtual void OnSubFrameReady(LONG NumOfBlockLeft, LONG StartLine, LONG NumLines, BYTE bLastBlock){};
	virtual void OnDatalost(LONG LostlineNum){};
	virtual void OnScannerError(LONG ErrorID, BSTR ErrorInfo){};
};
