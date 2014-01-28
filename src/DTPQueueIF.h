#pragma once
#include "DTPPacket.h"
#include "DTDataSrcIF.h"
#include "EventManagerIF.h "
#include "DTFrameBufIF.h"
class CDTPQueueIF
{
public:
	CDTPQueueIF(void);
	virtual ~CDTPQueueIF(void);
	// Called when a Datasrc packet ready, add the packet to the end of queue and check is there any finnished packet
	virtual void AddTail(CDTPPacketIF* pDTPacket) = 0;
	// Set the data source to input data
	virtual void SetDataSrc(CDTDataSrcIF* pDataSrc)=0;
	//Set evenmanager to accept DTEvent
	virtual void SetEventManager(CEventManagerIF *pEventManager)=0;
	//Set Frame buf to output the Frame data
	virtual void SetFrameBuf(CDTFrameBufIF* pFrameBuf)=0;
	virtual void ClearQueue()=0;
	virtual void ResetImageCounter()=0;
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual BOOL IsRunning()= 0;
	virtual void SetDeviceID(DWORD dwID)=0;
};
