#pragma once
#include "dtpqueueif.h"

typedef unsigned * PBEGINTHREADEX_THREADID;
typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC) (LPVOID lpThreadParameter);
class CDTPQueue :
	public CDTPQueueIF
{
private:
	BYTE				m_ImageCounter;
	BYTE				m_Header[DTP_HEAD_LEN];
	BYTE*				m_pBuffer;
	ULONG				m_BufferSize;
	CDTDataSrcIF*		m_pDataSrc;
	CEventManagerIF*	m_pEventManager;
	CDTFrameBufIF*		m_pFrameBUF;


	CDTPPacketIF*			m_pHead;
	CDTPPacketIF*			m_pTail;
	LONG					m_QueueSize;
	FILE*						m_hTraceFile;
	CRITICAL_SECTION  m_TailCR;

	enum{DT_IMG = 0x00,DT_CONTROL = 0x01,DT_DUMY = 0x02};
private:
	void CheckDTP();
	ULONG GetCurDTPLen();
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
	CDTPQueue(int iEventNum=0);
	virtual ~CDTPQueue(void);
		// Called when a Datasrc packet ready, add the packet to the end of queue and check is there any finnished packet
	void AddTail(CDTPPacketIF* pDTPacket);
	// Set the data source to input data top returnt the used DTPacket
	void SetDataSrc(CDTDataSrcIF* pDataSrc);
	//Set evenmanager to accept DTEvent
	void SetEventManager(CEventManagerIF *pEventManager);
	//Set Frame buf to output the Frame data
	void SetFrameBuf(CDTFrameBufIF* pFrameBuf);
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
