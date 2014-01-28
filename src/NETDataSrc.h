#pragma once
#include "dtdatasrcif.h"
#include ".\TCPSocket.h"
#include ".\DTDetector.h"
//#include "DTImage.h"
class NetParam
{
public:
	char IP[20];
	WORD Port;
	NetParam(char* strIP,WORD port)
	{
		strcpy(IP,strIP);
		Port = port;
	}
};
class CNETDataSrc :
	public CDTDataSrcIF
{
private:
	CTCPSocket m_Socket;
	CDTPPacketIF*		m_pCommitPacketHead;//The Commit Queue Head
	//The wait queue head can be operate by 2 thread 
	// USB Src do write and read operation, when do write operation need add a lock
	//DTPQueue do read operation
	CDTPPacketIF*		m_pPacketListHead;//The wait queue head 
	CDTPQueueIF*	m_pDTPQueue;
	volatile BOOL   m_bThreadStop;
	HANDLE			m_hThread;
	HANDLE			m_hThreadEndEvent;//Event to Inticate the Thread End
	HANDLE			m_hFreePacketReady;//Event to indicate there is free packet to commit
	HANDLE			m_hSoketListen;
	CRITICAL_SECTION m_ListHeadCR;
	DWORD			m_ThreadID;
	IDTDetector*	m_pDetector;
	WORD			m_ListenPort;
	char			m_RemoteIP[20];
	//Zhangxq
	//remove this line
	//CDTImage*		m_pParent;
	LONG			m_TimeOut;
private:
	void ResetEventObject();
	BOOL SendSFCommand(BOOL bStart);
	BOOL ResetImageChannel();
	BOOL ClearDetectorBuffer();
	void ClearSocketBuffer();

public:
	CNETDataSrc(IDTDetector* pDetector);
	virtual ~CNETDataSrc(void);
	virtual BOOL Open(LPVOID pParam);
	virtual BOOL Start();//Start Grab Thread called by DTImage FALSE Failed to start
	virtual BOOL Stop();//StopGrab called by dtimage FALSE TIme Out
	virtual void AddDTPPacket(CDTPPacketIF* pPacket);//Inser the single packet to the wait queue called by DTImage to create a wait queue
	virtual void AddDTPPacketList(CDTPPacketIF* pHead);//Inser the packet list to the wait queue called by DTImage to create a wait queue

	//and DTPQueue to return the used packet to the wait queue
	//Create Need the DTPQueuePointer,to accept the DTP Packet
	virtual void SetDTPQueue(CDTPQueueIF* pQueue);
	virtual BOOL IsRunning();
	virtual void SetStopFlag(BOOL bTRue);//becalled by thread to stop itself, asynchronize stop
	virtual BOOL GetStopFlag();//Get stop flag
	virtual void ResetQueue();//Clear Packet Content in the Queue
	void Close(void);
	void SetTimeOut(LONG timeout);
	void GetTimeOut(LONG* ptimeout);
public://Thread function
	static DWORD WINAPI ThreadFunc(LPVOID param);
	virtual DWORD ThreadMemberFunc();
	
};
