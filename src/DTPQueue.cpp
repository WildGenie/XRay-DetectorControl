#include "StdAfx.h"
#include ".\dtpqueue.h"
#include "EventManagerIF.h"
#include ".\dtexception.h"
#include "DTImage.h"
#include <process.h>


CDTPQueue::CDTPQueue(int iEventNum):
m_pTail(NULL),
m_pHead(NULL),
m_pDataSrc(NULL),
m_pEventManager(NULL),
m_pFrameBUF(NULL),
m_ImageCounter(1),
m_QueueSize(0),
m_DeviceID(0)
{

	m_hThread = NULL;//Thread Handle
	char sz[50];
	sprintf(sz, "%s_%d", "ApponsDTView_ThreadEnd", iEventNum);

	m_hThreadEndEvent = CreateEvent(NULL,TRUE,FALSE,sz);////Flag to indicate that the thread is runing
	SetEvent(m_hThreadEndEvent);
	sprintf(sz, "%s_%d", "ApponsDTView_PacketReady", iEventNum);
	m_hPacketReady = CreateEvent(NULL,TRUE,FALSE,sz);
	ResetEvent(m_hPacketReady);//At first there is no packet
	InitializeCriticalSection(&m_TailCR);
	m_ThreadID = 0;
	ResetHeader();
	m_bThreadStop = TRUE;
	
	m_pBuffer = NULL;
	m_BufferSize = 0;
}

CDTPQueue::~CDTPQueue(void)
{
	CloseHandle(m_hThreadEndEvent);
	CloseHandle(m_hPacketReady);
	DeleteCriticalSection(&m_TailCR);
	ReleaseDataBuffer();
}

void CDTPQueue::CheckAndAllocateDataBuffer(ULONG BufferSize)
{
	if(BufferSize > m_BufferSize)
	{
		ReleaseDataBuffer();
		m_pBuffer = new BYTE[BufferSize];
		if(m_pBuffer)
			m_BufferSize = BufferSize;
		else
			ATLASSERT(0);
	}
}
void CDTPQueue::ReleaseDataBuffer()
{
	if(m_pBuffer)
		delete [] m_pBuffer;
	m_pBuffer = NULL;
}
void CDTPQueue:: ResetImageCounter()
{
	m_ImageCounter = 0;
}
		// Called when a Datasrc packet ready, add the packet to the end of queue and check is there any finnished packet
//AddTail is Called By DataSrc Thread to update the m_Tail Pointer
void CDTPQueue::AddTail(CDTPPacketIF* pDTPacket)
{
	//Append the new packet to the end of queue
	//Should set the pDTPacket->next as NULL because 
	//currently there is no relation between this packet and the datasrc list
	EnterCriticalSection(&m_TailCR);
	pDTPacket->SetNext(NULL);
	if(m_pHead == NULL)
	{
		//if (m_QueueSize == 0) return;
		m_pHead = pDTPacket;
		m_pTail = m_pHead;
	}
	else
	{
		m_pTail->SetNext(pDTPacket);
		m_pTail = pDTPacket;
	}
	
	m_QueueSize += pDTPacket->GetDTPLen();//m_QueueSize is a protected variable, it is shared by 2 threads
	//It is only be add here and sub at the MoveHeader and Copydata function
	LeaveCriticalSection(&m_TailCR);
	SetEvent(m_hPacketReady);
}
void CDTPQueue::CopyDataToBuffer()
{
	//Copy the data form packet list to the m_pBuffer
	//When call this function, there is enoough packet already
	CDTPPacketIF* pCurPacket = NULL;
	int DataLen = GetCurDTPLen()-DTP_HEAD_LEN;
	int CopyLen = DataLen;
	int BufferOffset = 0;
	int iTmpLen=DataLen;
	int iOldQueueSize=m_QueueSize;
	
    while(DataLen > 0 )
	{
		pCurPacket = m_pHead;
		int CurPacketLen = pCurPacket->GetDTPLen();
		if( CurPacketLen >= DataLen)
		{//Direct copy total length data
			memcpy(m_pBuffer+BufferOffset,pCurPacket->GetBuf(),DataLen);
			//Update the pCurPacket content;
			pCurPacket->MoveFirstToWithOffset(DataLen);
			EnterCriticalSection(&m_TailCR);
			m_QueueSize -= DataLen;
			LeaveCriticalSection(&m_TailCR);
			DataLen -= DataLen;
			if (CurPacketLen == DataLen)
			{
			//Return the use DTPPacket to DataSrc
				pCurPacket->Reset();//Need reset the offset and buf size to be reuse
				m_pDataSrc->AddDTPPacket(pCurPacket);
			}
		}
		else//(CurPacketLen < DataLen)
		{
			memcpy(m_pBuffer+BufferOffset,pCurPacket->GetBuf(),CurPacketLen);
			
			EnterCriticalSection(&m_TailCR);
			m_QueueSize -= CurPacketLen; //Update the QueueSize
			m_pHead = m_pHead->GetNext();
			LeaveCriticalSection(&m_TailCR);
			
			DataLen -= CurPacketLen;
			BufferOffset += CurPacketLen;
			//Return the use DTPPacket to DataSrc
			pCurPacket->Reset();//Need reset the offset and buf size to be reuse
			m_pDataSrc->AddDTPPacket(pCurPacket);
		}
	}
	//Handle the m_pBuffer data
	BYTE PacketType = GetCurType();
	if((PacketType == DT_IMG) && (!m_bThreadStop))
	{
		m_pFrameBUF->AddOneFrameLine(m_pBuffer,CopyLen,TRUE);
	}
	else
	{
		BYTE EventID = PacketType;
		BYTE EventContent = GetCurContent();
		m_pEventManager->OnDTEvent(EventID,EventContent);
	}
};
void CDTPQueue::CheckDTP()
{
	//Curretly already add on packet 
	//The Len maybe 0 or not zero

	ULONG DataLen = 0;

	BOOL bHeaderEmpty = TRUE;
	while(!m_bThreadStop)
	{
		if(bHeaderEmpty)
		{
        	//if the m_header is empty then check the Packet list and copy the header to the m_header
			if(GetQueueSize()>DTP_HEAD_LEN)
			{
				MoveHeader();
				bHeaderEmpty = FALSE;
			}
			//if current queue size is not more than DTP Head Len then just wait for next DTPPacket insert
			else
			{
				ResetEvent(m_hPacketReady);
				DWORD dwWait=WaitForSingleObject(m_hPacketReady,1000);
				
			}
		}
		else
		{//m_bHeader is not empty, it had been move data, so the data len and the data packet type can get
			ULONG  CurDTPLen = GetCurDTPLen();
			
			CheckAndAllocateDataBuffer(CurDTPLen);//Get the m_pBuffer available
			while(!m_bThreadStop)
			{
				if(GetQueueSize()>= CurDTPLen)
				{
					if (m_bThreadStop)
					{
             			
						break;
					}
   					CopyDataToBuffer();//Copy the data from packet list to a buffer and handle the data
					bHeaderEmpty = TRUE;//After handle one DTPPacket need set the header empty to load next header
					break;
				}
				else
				{//There is no enough packe to finnish a DTP packet, so wait for more packet
					ResetEvent(m_hPacketReady);
					DWORD dwWait=WaitForSingleObject(m_hPacketReady,1000);
					if (dwWait!=WAIT_OBJECT_0)
					{

					}
				}
			}
		}
	}

	m_QueueSize = 0;
}
void CDTPQueue::OnDataLostEvent(BYTE LostNum)
{
	m_pEventManager->OnDTEvent(DT_EVENT_DATA_LOST,LostNum);
}
void CDTPQueue::ClearQueue()
{
   	
    //Move all DTPPacket to the Data Src Wait Queue
	CDTPPacketIF* pPacket;
	ResetHeader();
	while(m_pHead)
	{
		pPacket = m_pHead;
		m_pHead = m_pHead->GetNext();
		pPacket->Reset();
		if(m_pDataSrc)
		{
			m_pDataSrc->AddDTPPacket(pPacket);
		}
	}
}
void CDTPQueue::MoveHeader()
{
	EnterCriticalSection(&m_TailCR);
		CDTPPacketIF* pCurPacket = m_pHead;
		int len = pCurPacket->GetDTPLen();
		int i=0;
		
		len = (len> DTP_HEAD_LEN)?DTP_HEAD_LEN:len;
		memcpy(m_Header,pCurPacket->GetBuf(),len);//Copy Header
		pCurPacket->MoveFirstToWithOffset(len);
		if(pCurPacket->GetDTPLen()==0)//if the pCurPacket is empty then maybe the Header is not copy totally
		{
			ATLASSERT((DTP_HEAD_LEN - len)>=0);
			m_pHead = pCurPacket->GetNext();
			//Return pCurPacket to DataSrc
			pCurPacket->Reset();
			m_pDataSrc->AddDTPPacket(pCurPacket);
		}
		if((DTP_HEAD_LEN - len)>0)
		{//Copy the left byte in the current packet to m_Header
			memcpy(m_Header+len,m_pHead->GetBuf(),DTP_HEAD_LEN - len);//Copy the rest part
			m_pHead->MoveFirstToWithOffset(DTP_HEAD_LEN - len);
		}
	m_QueueSize -= DTP_HEAD_LEN;
    LeaveCriticalSection(&m_TailCR);
}
BYTE CDTPQueue::GetCurContent()	
{
	return *m_pBuffer;
}
ULONG CDTPQueue::GetCurDTPLen()
{
	/*
	if((*m_Header) != 0)
	{
		FILE* hTraceFile = fopen( "D:\\ErrorPacket.txt", "a" );
		m_pTail->Trace(hTraceFile);
		fclose( hTraceFile);
		throw CDTException(EID_PACKET_LEN_ERROR);
	}
	*/
	WORD Len = *(m_Header+1);
	Len <<= 8;
	Len |= *(m_Header+2);
	return Len;
}
BYTE CDTPQueue::GetCurType()
{
	return m_Header[4];
}

DWORD CDTPQueue::GetQueueSize()
{
	return m_QueueSize;
};

// Set the data source to input data top returnt the used DTPacket
void CDTPQueue::SetDataSrc(CDTDataSrcIF* pDataSrc)
{
	m_pDataSrc = pDataSrc;
}
	//Set evenmanager to accept DTEvent
void CDTPQueue::SetEventManager(CEventManagerIF *pEventManager)
{
	m_pEventManager = pEventManager;
}
	//Set Frame buf to output the Frame data
void CDTPQueue::SetFrameBuf(CDTFrameBufIF* pFrameBuf)
{
	m_pFrameBUF = pFrameBuf;
}

DWORD WINAPI CDTPQueue::ThreadFunc(LPVOID param)
{
	CDTPQueue* pSrc = (CDTPQueue*) param;

	return pSrc->ThreadMemberFunc();
}
DWORD CDTPQueue::ThreadMemberFunc()
{

	ResetEvent(m_hThreadEndEvent);//Indicate the Thread Running
	m_QueueSize = 0;
	try
	{
		CheckDTP();
	}
	catch (CDTException E)
	{

		LeaveCriticalSection(&m_TailCR);
		E.ProcessError();
		((CDTImage*)m_pEventManager)->DTError(E.m_ERROR_ID,E.m_ERROR_INFO);
//		m_pDataSrc->Stop();
	}
	//ReturnAllPacket();
	SetEvent(m_hThreadEndEvent);
	ResetHeader();//When stop the grab, need reset the header for next time receive
						//When start grab, the header maybe operatate by DataSrc. So when start just reserve the header value

	return 0;
}
void  CDTPQueue::Start()
{

	if(IsRunning())
	{

		return ;
	}
	m_bThreadStop = FALSE;
	m_hThread = (HANDLE)_beginthreadex(NULL,0,(PBEGINTHREADEX_THREADFUNC)CDTPQueue::ThreadFunc,(LPVOID)this,0,(PBEGINTHREADEX_THREADID)&m_ThreadID);
};
BOOL CDTPQueue::IsRunning()
{
	if(WaitForSingleObject(m_hThreadEndEvent,0) == WAIT_TIMEOUT)
	{//Event Not Set So the Thread is Runing
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
void  CDTPQueue::Stop()
{

	if(m_hThread)
	{
		//Do some action to stop thread.
		if(IsRunning())
		{
			m_bThreadStop = TRUE;
			SetEvent(m_hPacketReady);
			DWORD dwWait=WaitForSingleObject(m_hThreadEndEvent,1000);
			CloseHandle(m_hThread);
			m_hThread = NULL;
		}
	}
};
void CDTPQueue::ReturnAllPacket()
{
	while(m_pHead)
	{
		m_pHead->Reset();//Need reset the offset and buf size to be reuse
		m_pDataSrc->AddDTPPacket(m_pHead);
		m_pHead = m_pHead->GetNext();
	}
	ResetHeader();
}
void CDTPQueue::ResetHeader()
{
	memset(m_Header,0,DTP_HEAD_LEN);
}

void CDTPQueue::SetDeviceID(DWORD dwID)
{
	m_DeviceID=dwID;
}
