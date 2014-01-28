#pragma once
#include "dtdatasrcif.h"
#include "DTPPacket.h"
#include ".\LIB\CyAPI.h"
#include ".\DTConst.h"
#include ".\DTDetector.h"
//#include ".\DTImage.h"
class CUSBDataSrc :
	public CDTDataSrcIF
{
private:
	BYTE			m_CommitNum;
	CDTPUSBPacket*		m_pCommitPacketHead;//The Commit Queue Head
	//The wait queue head can be operate by 2 thread 
	// USB Src do write and read operation, when do write operation need add a lock
	//DTPQueue do read operation
	CDTPUSBPacket*		m_pPacketListHead;//The wait queue head 
	CDTPUSBPacket*		m_pPacketListTail;
	CDTPQueueIF*	m_pDTPQueue;
	volatile BOOL   m_bThreadStop;
	HANDLE			m_hThread;
	HANDLE			m_hThreadEndEvent;//Event to Inticate the Thread End
	HANDLE			m_hFreePacketReady;//Event to indicate there is free packet to commit
	CRITICAL_SECTION m_ListHeadCR;

	DWORD			m_ThreadID;

	CCyUSBDevice	m_DTUSBDevice;
    CCyUSBEndPoint*	m_pInEndPt;
	CCyControlEndPoint*	m_pCtlEndPt;
	ULONG			m_TimeOut;//Milli Seconds
	IDTDetector*	m_pDetector;
	//Zhangxq
	//remove this line
	//CDTImage*		m_pParent;
private:
//	BOOL SendUSBCommand(BYTE* pSrc, WORD len);
	BOOL SendSFCommand(BOOL bStart);
	BOOL ClearDetectorBuffer();
	void ResetEventObject();
//	BOOL ReadCommand(BYTE* pSrc,UINT &Count);
public:
	CUSBDataSrc(IDTDetector* pDetector);
	virtual ~CUSBDataSrc(void);
	BOOL Start();//Start Grab Thread called by DTImage 
	BOOL Stop();//StopGrab called by dtimage
	BOOL Open(LPVOID pParam=NULL);
	BOOL IsRunning();

	void AddDTPPacketList(CDTPPacketIF* pHead);//Inser the packet to the wait queue called by DTImage to create a wait queue
	void AddDTPPacket(CDTPPacketIF* pPacket);
	//and DTPQueue to return the used packet to the wait queue
	//Create Need the DTPQueuePointer,to accept the DTP Packet
	void SetDTPQueue(CDTPQueueIF* pQueue);

	void SetCommitPacketNum(BYTE CommitNum);//Setup the cocurrent commmit packet number to driver
	void SetTimeOut(LONG timeout);
	void GetTimeOut(LONG* ptimeout);
	void SetStopFlag(BOOL bTrue);
	BOOL GetStopFlag();
	void ResetQueue();
	void Close(void);
public://Thread function
	static DWORD WINAPI ThreadFunc(LPVOID param);
	virtual DWORD ThreadMemberFunc();
};
