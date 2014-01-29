#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "../stdafx.h"
#include ".\scannerdatasrcif.h"
#include ".\TCPSocket.h"
#include "..\CommandChannel.h"

class NetParam
{
public:
	char IP[20];
	WORD Port;
	NetParam(char* strIP,WORD port)
	{
		strcpy_s(IP,20,strIP);
		Port = port;
	}
};
class CNETDataSrc :
    public CScannerDataSrcIF
{
private:
	CTCPSocket m_Socket;
	CDataPacketIF*		m_pCommitPacketHead;//The Commit Queue Head
	//The wait queue head can be operate by 2 thread 
	// USB Src do write and read operation, when do write operation need add a lock
	//Queue do read operation
    CDataPacketIF*		m_pPacketListHead;//The wait queue head
    CDataPacketQueueIF*	m_pDataPacketQueue;
	volatile BOOL   m_bThreadStop;
	HANDLE			m_hThread;
	HANDLE			m_hThreadEndEvent;//Event to Inticate the Thread End
	HANDLE			m_hFreePacketReady;//Event to indicate there is free packet to commit
	HANDLE			m_hSoketListen;
	CRITICAL_SECTION m_ListHeadCR;
	DWORD			m_ThreadID;
	ICommandChannel*	m_pDetector;
	WORD			m_ListenPort;
	char			m_RemoteIP[20];
	LONG			m_TimeOut;
private:
	void ResetEventObject();
	BOOL SendSFCommand(BOOL bStart);
	BOOL ResetImageChannel();
	BOOL ClearDetectorBuffer();
	void ClearSocketBuffer();

public:
	CNETDataSrc(ICommandChannel* pDetector);
	virtual ~CNETDataSrc(void);
	virtual BOOL Open(LPVOID pParam);
	virtual BOOL Start();//Start Grab Thread called by ScannerImage FALSE Failed to start
	virtual BOOL Stop();//StopGrab called by ScannerImage FALSE TIme Out
    virtual void AddDataPacket(CDataPacketIF* pPacket);//Inser the single packet to the wait queue called by ScannerImage to create a wait queue
    virtual void AddDataPacketList(CDataPacketIF* pHead);//Inser the packet list to the wait queue called by ScannerImage to create a wait queue

	//and Queue to return the used packet to the wait queue
	//Create Need the DataPacketQueuePointer,to accept the  Packet
	virtual void SetDataPacketQueue(CDataPacketQueueIF* pQueue);
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
