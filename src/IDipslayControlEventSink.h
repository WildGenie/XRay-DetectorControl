#pragma once
class CDTDisplayControl;
class IDipslayControlEventSink
{
protected:
	CDTDisplayControl* m_pDisplayControl;
	LONG		m_Cookie;
	void ConnectDisplayControl(CDTDisplayControl* pSrc){};
	void DisConnectDisplayControl(){};
public:
	IDipslayControlEventSink(void);
	virtual ~IDipslayControlEventSink(void);
};
