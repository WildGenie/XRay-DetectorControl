#pragma once
class CDTImage;
class IDTImageEventSink
{
private:

protected:
	CDTImage* m_pDataSrc;
	LONG		m_Cookie;
	void ConnectDataSrc(CDTImage* pSrc);
	void DisConnectDataSrc();
public:
	IDTImageEventSink(void);
	virtual ~IDTImageEventSink(void);
	virtual void OnFrameReady(LONG LineNum){};
	virtual void OnSubFrameReady(LONG NumOfBlockLeft, LONG StartLine, LONG NumLines, BYTE bLastBlock){};
	virtual void OnDatalost(LONG LostlineNum){};
	virtual void OnDTError(LONG ErrorID, BSTR ErrorInfo){};
};
