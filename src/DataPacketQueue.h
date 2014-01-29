#pragma once
#include "./LibConst.h"
#include "datapacketqueueif.h"
#include "ScannerDataSrcIF.h"


//typedef unsigned * PBEGINTHREADEX_THREADID;
//typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC) (LPVOID lpThreadParameter);
class CDataPacketQueue :
    public CDataPacketQueueIF
{
private:
	BYTE				m_ImageCounter;
	BYTE				m_Header[PACKET_HEAD_LEN];
	BYTE*				m_pBuffer;
	ULONG				m_BufferSize;
	CScannerDataSrcIF*		m_pDataSrc;
	CEventManagerIF*	m_pEventManager;
    CFrameBufIF*		m_pFrameBUF;


    CDataPacketIF*			m_pHead;
    CDataPacketIF*			m_pTail;
	LONG					m_QueueSize;
	FILE*						m_hTraceFile;
	CRITICAL_SECTION  m_TailCR;

	enum{IMG = 0x00,CONTROL = 0x01,DUMY = 0x02};
private:
    void CheckDataPacket();
    ULONG GetCurDataPacketLen();
	ULONG GetQueueSize();
	BYTE GetCurType();
	BYTE GetCurContent();	
	void MoveHeader();
	void ClearQueue();
	void OnDataLostEvent(BYTE LostNum);
	void CheckAndAllocateDataBuffer(ULONG BufferSize);
	void ReleaseDataBuffer();
	void CopyDataToBuffer();
public:
    CDataPacketQueue(int iEventNum=0);
	virtual ~CDataPacketQueue(void);
		// Called when a Datasrc packet ready, add the packet to the end of queue and check is there any finnished packet
    void AddTail(CDataPacketIF* pPacket);
	// Set the data source to input data top returnt the used DataPacket
    void SetScannerDataSrc(CScannerDataSrcIF* pDataSrc);
	//Set evenmanager to accept Event
	void SetEventManager(CEventManagerIF *pEventManager);
	//Set Frame buf to output the Frame data
    void SetFrameBuf(CFrameBufIF* pFrameBuf);
	void Start();
	void Stop();
	BOOL IsRunning();
	void ResetImageCounter();
	void ReturnAllPacket();
	void ResetHeader();
	void SetDeviceID(DWORD dwID);

public://Thread function
	static DWORD WINAPI ThreadFunc(LPVOID param);
	virtual DWORD ThreadMemberFunc();

private:
	volatile BOOL   m_bThreadStop;
	HANDLE			m_hThread;
	HANDLE			m_hThreadEndEvent;
	HANDLE			m_hPacketReady;
	DWORD			m_ThreadID;
    DWORD           m_DeviceID;
};
