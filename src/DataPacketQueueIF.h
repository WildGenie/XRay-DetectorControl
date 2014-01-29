#pragma once
#include "DataPacket.h"
#include "ScannerDataSrcIF.h"
#include "EventManagerIF.h "
#include "FrameBufIF.h"
class CDataPacketQueueIF
{
public:
    CDataPacketQueueIF(void);
    virtual ~CDataPacketQueueIF(void);
	// Called when a Datasrc packet ready, add the packet to the end of queue and check is there any finnished packet
    virtual void AddTail(CDataPacketIF* pPacket) = 0;
	// Set the data source to input data
    virtual void SetScannerDataSrc(CScannerDataSrcIF* pDataSrc)=0;
	//Set evenmanager to accept Event
	virtual void SetEventManager(CEventManagerIF *pEventManager)=0;
	//Set Frame buf to output the Frame data
	virtual void SetFrameBuf(CFrameBufIF* pFrameBuf)=0;
	virtual void ClearQueue()=0;
	virtual void ResetImageCounter()=0;
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual BOOL IsRunning()= 0;
	virtual void SetDeviceID(DWORD dwID)=0;
};
