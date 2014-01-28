#include "StdAfx.h"
#include ".\netdatasrc.h"
#include "DTPQueueIF.h"
#include "DTConst.h"
#include "DTException.h"
#include <process.h>


CNETDataSrc::CNETDataSrc(IDTDetector* pDetector)
:	
	m_pPacketListHead(NULL),
	m_pDTPQueue(NULL),
	m_hThread(NULL),
	m_ThreadID(0),
	m_pCommitPacketHead(NULL)
{
	m_hThreadEndEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_hFreePacketReady = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_hSoketListen = CreateEvent(NULL,TRUE,FALSE,NULL);
	ResetEventObject();
	m_pDetector = pDetector;
	//Zhangxq
	//remove this line
	//m_pParent = pParent;
	m_TimeOut = 10000;
}
void CNETDataSrc::ResetEventObject()
{
	SetEvent(m_hThreadEndEvent);//At First The Thread is End
	ResetEvent(m_hFreePacketReady);//at first there is no ready packet
	ResetEvent(m_hSoketListen);
	InitializeCriticalSection(&m_ListHeadCR);
}
CNETDataSrc::~CNETDataSrc(void)
{
	CloseHandle(m_hThreadEndEvent);
	CloseHandle(m_hFreePacketReady);
	DeleteCriticalSection(&m_ListHeadCR);
}
BOOL CNETDataSrc::Open(LPVOID pParam)
{//Open here should estableish  the image channel;
	//pPrame should include detector IP address and Port
	strcpy(m_RemoteIP,((NetParam*)pParam)->IP);
	m_ListenPort = ((NetParam*)pParam)->Port;
	m_Socket.SetSocketTimeout(m_TimeOut);
	if(!m_Socket.Connect((BYTE*)m_RemoteIP,m_ListenPort,0x1400000))
	{
		if(ResetImageChannel())
		{
			if(!m_Socket.Connect((BYTE*)m_RemoteIP,m_ListenPort))
			{
				return FALSE;
			}
		}
		else
		{
				return FALSE;
		}
	}
	//Start the Receing Thread when Open the connection
	return TRUE;

}
void CNETDataSrc::Close(void)
{
	//Stop the thread when close
	Stop();
	m_Socket.DisConnect();
}
BOOL CNETDataSrc::Start()//Start Grab Thread called by DTImage, return  FALSE Failed to start
{
	if(IsRunning())
	{
		return TRUE;
	}
	ResetEventObject();
	m_hThread = (HANDLE)_beginthreadex(NULL,0,(PBEGINTHREADEX_THREADFUNC)CNETDataSrc::ThreadFunc,(LPVOID)this,0,(PBEGINTHREADEX_THREADID)&m_ThreadID);
	SetThreadPriority(m_hThread ,THREAD_PRIORITY_TIME_CRITICAL );
	m_pDTPQueue->ResetImageCounter();//Clear the start image couter used to check is there lost frame
	Sleep(1);//Wait a moment let m_Thread run to avoid the data lost

	if(m_hThread)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
	return TRUE;
}

BOOL CNETDataSrc::Stop()//StopGrab called by dtimage return FALSE TIme Out
{
	if(IsRunning())
	{
		//Do some action to stop thread.
		m_bThreadStop = TRUE;
		
		ATLTRACE("Wait For NetSrc m_hThreadEndEvent\n");
		WaitForSingleObject(m_hThreadEndEvent,3000/*not INFINITE*/);
		ATLTRACE("Get NetSrc m_hThreadEndEvent\n");
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	//Always return TRUE
	return TRUE;
}
void CNETDataSrc::AddDTPPacket(CDTPPacketIF* pPacket)//Inser the single packet to the wait queue called by DTImage to create a wait queue
{
	EnterCriticalSection(&m_ListHeadCR);
	pPacket->Reset();//Clear the content and set the next as null;
//	ATLTRACE("Add %p Packet\n",pPacket);
	CDTPPacketIF* pLast = m_pPacketListHead;
	if(m_pPacketListHead)
	{
		while((pLast->GetNext()) != NULL)
		{//Find the last packet
			pLast = pLast->GetNext();
		}
        pLast->SetNext(pPacket);//append to the end
		
	}
	else
	{
		m_pPacketListHead = (CDTPUSBPacket*)pPacket;
	//	ATLTRACE("ADD FREE Packet and Set Event\n");
	}
	SetEvent(m_hFreePacketReady);
	LeaveCriticalSection(&m_ListHeadCR);
}
void CNETDataSrc::AddDTPPacketList(CDTPPacketIF* pHead)//Inser the packet list to the wait queue called by DTImage to create a wait queue
{
	EnterCriticalSection(&m_ListHeadCR);
	CDTPPacketIF* pLast = m_pPacketListHead;
	if(m_pPacketListHead)
	{
		while((pLast->GetNext()) != NULL)
		{//Find the last packet
			pLast = pLast->GetNext();
		}
        pLast->SetNext(pHead);//append to the end
	}
	else
	{
		m_pPacketListHead = (CDTPUSBPacket*)pHead;
	}
	LeaveCriticalSection(&m_ListHeadCR);
	SetEvent(m_hFreePacketReady);
}

	//and DTPQueue to return the used packet to the wait queue
	//Create Need the DTPQueuePointer,to accept the DTP Packet
void CNETDataSrc::SetDTPQueue(CDTPQueueIF* pQueue)
{
	m_pDTPQueue = pQueue;
}
BOOL CNETDataSrc::IsRunning()
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
void CNETDataSrc::SetStopFlag(BOOL bTrue)//becalled by thread to stop itself, asynchronize stop
{
	m_bThreadStop = bTrue;
	//SendSFCommand(FALSE);//Stop FPGA data output
}
BOOL CNETDataSrc::GetStopFlag()//Get stop flag
{
		return m_bThreadStop;
}
void CNETDataSrc::ResetQueue()//Clear Packet Content in the Queue
{
	EnterCriticalSection(&m_ListHeadCR);
	if(m_pCommitPacketHead)
		m_pPacketListHead = m_pCommitPacketHead;
	CDTPPacketIF* pPacket = m_pPacketListHead;
	while(pPacket)
	{
		pPacket->Clear();
		pPacket = pPacket->GetNext();
	}
	LeaveCriticalSection(&m_ListHeadCR);
}

DWORD WINAPI CNETDataSrc::ThreadFunc(LPVOID param)
{
	CNETDataSrc* pSrc = (CNETDataSrc*) param;
	return pSrc->ThreadMemberFunc();
}
BOOL CNETDataSrc::ResetImageChannel()
{
	char cmd[100];
	char rt[100];
	LONG bSuccess;
	sprintf(cmd,"[NA,I]");
	m_pDetector->SendCommandA(cmd,rt,&bSuccess);
	
	return bSuccess;

}
BOOL CNETDataSrc::SendSFCommand(BOOL bStart)
{
	char cmd[100];
	char rt[100];
	LONG bSuccess;
	if(bStart)
	{
		sprintf(cmd,"[SF,1]");
	}
	else
	{
		sprintf(cmd,"[SF,0]");
	}
	m_pDetector->SendCommandA(cmd,rt,&bSuccess);
	
	return bSuccess;
};
void CNETDataSrc::ClearSocketBuffer()
{
	int i=0;
	int Len=0;
	while(1)
	{
		Sleep(10);
		if(m_Socket.IsCanRead())
		{
			Len =m_Socket.ReceiveData(m_pCommitPacketHead->GetBuf(),m_pCommitPacketHead->GetBufSize());
			if(Len == SOCKET_ERROR)
			{
				break;
			}
			if(Len == 0)
			{
				ATLTRACE("NetSrc Clean the TCP Queue\n");
				break;
			}
		}
		else
		{
			if(i>5)
			{
				ATLTRACE("NetSrc Clean the TCP Queue\n");
				break;//Total wait time is 5*50 = 250ms to clean the TCP stack
			
			}
		}
		i++;
	}
}
DWORD CNETDataSrc::ThreadMemberFunc()
{
	//Do Some Thing Here
	//Start the Wait queue

	//Here the Queue Buffer is Ready
	//m_pListHead indicate the first queue
	//commit the first 4 packet indicate by head

	
	int Len;
	BOOL RT;
	BOOL bTCPStackClean;
	m_bThreadStop = FALSE;
	ATLTRACE("Reset NetSrc m_hThreadEndEvent\n");
	ResetEvent(m_hThreadEndEvent);
	m_pDTPQueue->Start();//Start the DTP Queue Check Thread
	Sleep(1);//Give DTPQueue thread a change to run
	m_pCommitPacketHead = m_pPacketListHead;
	
	//Use the Commit head to point to the first commit packet
	m_pPacketListHead = m_pPacketListHead->GetNext();
	//Todo: Here after commit the packet wait still need send start frame command to MCU to 
	//reset FIFO and clear the error flag of FPGA then send image data.
	try
	{
		//4 do an endless loop to recevie data
		//5 before close the socket , call recv again to make sure the tx buiffer empty
			
		RT = SendSFCommand(TRUE);//Start Frame out.
		ATLTRACE("Send SF START %d\n",RT);
		bTCPStackClean = FALSE;
		while(1)	//while not stop. And when stop flag is true, the thread should confirmware that there is not data in TCP stack
		{
			//wait for commit head finnish
			if(m_bThreadStop)
			{//Receive until no data
				int i = 0;
				RT = SendSFCommand(FALSE);//Stop FPGA data output
				ATLTRACE("Send SF STOP %d\n",RT);
				ClearSocketBuffer();
				break;//Here should out of the thread loop
			}
			Len = 0;
			Len =m_Socket.ReceiveData(m_pCommitPacketHead->GetBuf(),m_pCommitPacketHead->GetBufSize());
			if(Len == SOCKET_ERROR)
			{
				int ErrID;
				ErrID = WSAGetLastError();
				if(ErrID  == WSAETIMEDOUT)
					continue;
				throw CDTException(EID_NET_IMG_REV_FAILED);
			}
			else if(Len == 0)
			{
				throw CDTException(EID_NET_IMG_REV_FAILED);
			}
					//Set the Data Len
				//	ATLTRACE("FINISH Transfer\n");recv
			else if(Len>0)
			{
					m_pCommitPacketHead->SetDataSize(Len);
					//Move to DTPQueue
					CDTPPacketIF* pCommitPacket = m_pCommitPacketHead;
					EnterCriticalSection(&m_ListHeadCR);
					m_pCommitPacketHead = m_pCommitPacketHead->GetNext();
					LeaveCriticalSection(&m_ListHeadCR);
					if(m_pCommitPacketHead	== NULL)
							throw CDTException(EID_DTP_REVQUEUE_EMPTY);
			//		ATLTRACE("Tail Bigin\n");
					m_pDTPQueue->AddTail(pCommitPacket);
			//		ATLTRACE("Tail ENd\n");
					//commit head = head.next
			}
				//commit the m_pListHead packet
			EnterCriticalSection(&m_ListHeadCR);
			if(NULL == m_pPacketListHead->GetNext())
			{	//Wait for NextAvalible Packet insert. 
				//The DTPQueue thread should return the free packet to the DataSrc Queue
				ResetEvent(m_hFreePacketReady);
				LeaveCriticalSection(&m_ListHeadCR);//Here the Judgement of ResetEvent Should be in CriticalSection 
	//			ATLTRACE("net src No Free Packet\n");
				if(WaitForSingleObject(m_hFreePacketReady,3000/*not INFINITE*/)==WAIT_OBJECT_0)
				{
					//	ATLTRACE("net src Have Free Packet\n");
				}
				else
				{
						throw CDTException(EID_DTP_PACKET_NONE);
				}
			}
			else
			{
			//	ATLTRACE("Normal\n");
				LeaveCriticalSection(&m_ListHeadCR);
			}
			//At this Point the GetNext Should Not Be NULL
		//		ATLTRACE("BEGIN Transfer\n");
				//Here before update the PacketListHead , need enter critical section, the
				//PacketListHead is shared by this therad and DTPQueue Thread
				EnterCriticalSection(&m_ListHeadCR);
				//ATLASSERT(m_pPacketListHead->GetNext() != NULL);
		//		int l = m_pPacketListHead->GetDTPLen();
		//		ATLTRACE("m_pPacketListHead is %p packet \n",m_pPacketListHead);
				m_pPacketListHead = m_pPacketListHead->GetNext();
				m_pPacketListHead->GetNext();
				LeaveCriticalSection(&m_ListHeadCR);
		}//end while
	}//end try
	catch (CDTException E)
	{
		SendSFCommand(FALSE);
		ClearSocketBuffer();
		E.ProcessError();
		//Zhangxq
		//remove this line
		//m_pParent->DTError(E.m_ERROR_ID,E.m_ERROR_INFO);
	}
	m_pDTPQueue->Stop();//Stop the DTPQueueThread
	ATLTRACE("Set the NetSrc m_hThreadEndEvent Event\n");
    SetEvent(m_hThreadEndEvent);
	return 0;
}
BOOL CNETDataSrc::ClearDetectorBuffer()
{
	return SendSFCommand(FALSE);
}
void CNETDataSrc::SetTimeOut(LONG timeout)
{
	m_TimeOut = timeout;
}
void CNETDataSrc::GetTimeOut(LONG* ptimeout)
{
	*ptimeout = m_TimeOut ;
}

