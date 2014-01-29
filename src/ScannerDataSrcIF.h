#pragma once
#include "DataPacket.h"
class CDataPacketQueueIF;
class CScannerDataSrcIF
{
public:
    CScannerDataSrcIF(void);
    virtual ~CScannerDataSrcIF(void);
	virtual BOOL Open(LPVOID pParam)=0;//DO initial work
	virtual BOOL Start()=0;//Start Grab Thread called by ScannerImage FALSE Failed to start
	virtual BOOL Stop()=0;//StopGrab called by dtimage FALSE TIme Out
    virtual void AddDataPacket(CDataPacketIF* pPacket)=0;//Inser the single packet to the wait queue called by ScannerImage to create a wait queue
    virtual void AddDataPacketList(CDataPacketIF* pHead)=0;//Inser the packet list to the wait queue called by ScannerImage to create a wait queue

	//and Queue to return the used packet to the wait queue
	//Create Need the QueuePointer,to accept the Packet
    virtual void SetDataPacketQueue(CDataPacketQueueIF* pQueue)=0;
	virtual BOOL IsRunning()=0;
	virtual void SetStopFlag(BOOL bTRue)=0;//becalled by thread to stop itself
	virtual BOOL GetStopFlag()=0;
	virtual void ResetQueue()=0;
	virtual void Close(void) = 0;
	virtual void SetTimeOut(LONG timeout)=0;
	virtual void GetTimeOut(LONG* ptimeout)=0;
	
};
