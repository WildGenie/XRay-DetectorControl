#include "StdAfx.h"
#include ".\usbdatasrc.h"
#include "process.h"
#include "DTPQueue.h"
#include ".\dtexception.h"


CUSBDataSrc::CUSBDataSrc(IDTDetector* pDetector)
:	m_CommitNum(1),
	m_pPacketListHead(NULL),
	m_pDTPQueue(NULL),
	m_hThread(NULL),
	m_ThreadID(0),
	m_pCommitPacketHead(NULL),
	m_pPacketListTail(NULL),
	m_TimeOut(10000)
{
	m_pDetector = pDetector;
	m_hThreadEndEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_hFreePacketReady = CreateEvent(NULL,TRUE,FALSE,NULL);
	ResetEventObject();
	//Zhangxq
	//remove this line
	//m_pParent = pParent;
	
}
void CUSBDataSrc::ResetEventObject()
{
	SetEvent(m_hThreadEndEvent);//At First The Thread is End
	ResetEvent(m_hFreePacketReady);//at first there is no ready packet
	InitializeCriticalSection(&m_ListHeadCR);
}
BOOL CUSBDataSrc::IsRunning()
{
	if(WaitForSingleObject(m_hThreadEndEvent,0) == WAIT_TIMEOUT)
	{//Event Not Set So the Thread is Runing
		return TRUE;
	}
	else
	{
		return FALSE;
	}
};
BOOL CUSBDataSrc::Open(LPVOID pParam)
{
	UCHAR ucUSBPort=0;
	if (pParam!=NULL)
	{
		ucUSBPort=*(UCHAR *)pParam;
	}
	
	if(m_DTUSBDevice.DeviceCount()  && !m_DTUSBDevice.Open(ucUSBPort)) 
    { 
        m_DTUSBDevice.Reset(); 
        m_DTUSBDevice.Open(ucUSBPort); 
		m_DTUSBDevice.ReConnect();//RE enumerate
    } 
    if (!m_DTUSBDevice.IsOpen()) 
    {
    	
 	    return FALSE; 
	}; 

    m_pInEndPt = m_DTUSBDevice.BulkInEndPt;//The first Bulk IN Point  
    m_pCtlEndPt = m_DTUSBDevice.ControlEndPt;   
	return TRUE;
}
void CUSBDataSrc::Close(void)
{
	Stop();
//DO nothing for USB Device cloase operation
	//Need SHutdown the thread of the datgasrc and the data queue and wait the exit event
}

CUSBDataSrc::~CUSBDataSrc(void)
{
	CloseHandle(m_hThreadEndEvent);
	CloseHandle(m_hFreePacketReady);
	DeleteCriticalSection(&m_ListHeadCR);
	
}

BOOL CUSBDataSrc::Start()//Start Grab Thread called by DTImage 
{
   	
	if(IsRunning())
	{
    	
		return TRUE;
	}
	if(m_DTUSBDevice.IsOpen())
	{
		if(!ClearDetectorBuffer())
		{
        	
			return FALSE;
		};
		m_pDTPQueue->ResetImageCounter();
		m_pDTPQueue->Start();//Start the DTP Queue Check Thread
		m_hThread = (HANDLE)_beginthreadex(NULL,0,(PBEGINTHREADEX_THREADFUNC)CUSBDataSrc::ThreadFunc,(LPVOID)this,0,(PBEGINTHREADEX_THREADID)&m_ThreadID);
		SetThreadPriority(m_hThread ,THREAD_PRIORITY_TIME_CRITICAL );
		if(m_hThread)
		{
			return TRUE;
		}
		else
		{
        	
			return FALSE;
		}
	}
   	
	return FALSE;
}

BOOL CUSBDataSrc::Stop()//StopGrab called by dtimage
{
   	
	if(IsRunning())
	{
		//Do some action to stop thread.
		//MessageBox(NULL,"Stop Action",NULL,MB_OK);
		m_pDTPQueue->Stop();
		m_bThreadStop = TRUE;
		SetEvent( m_hFreePacketReady);
		DWORD dwWait=WaitForSingleObject(m_hThreadEndEvent,INFINITE);

		Sleep(1000);
		CloseHandle(m_hThread);
		m_hThread = NULL;
		//MessageBox(NULL,"DTPQueue Stop Action",NULL,MB_OK);
		SendSFCommand(FALSE);//Stop FPGA data output
	}

	//Always return TRUE
	return TRUE;
}
DWORD WINAPI CUSBDataSrc::ThreadFunc(LPVOID param)
{
	CUSBDataSrc* pSrc = (CUSBDataSrc*) param;
	return pSrc->ThreadMemberFunc();
}
void CUSBDataSrc::SetTimeOut(LONG timeout)
{
	m_TimeOut = timeout;
}
void CUSBDataSrc::GetTimeOut(LONG* ptimeout)
{
	*ptimeout = m_TimeOut;
}
void CUSBDataSrc::SetStopFlag(BOOL bTrue)
{
	m_bThreadStop = bTrue;
}
BOOL CUSBDataSrc::GetStopFlag()
{
	return m_bThreadStop;
}
DWORD CUSBDataSrc::ThreadMemberFunc()
{
   	
	//Do Some Thing Here
	//Start the Wait queue

	//Here the Queue Buffer is Ready
	//m_pListHead indicate the first queue
	//commit the first 4 packet indicate by head
	int Timeout=0;
	m_bThreadStop = FALSE;
					
	Sleep(100);//In VB2005 the Snap fucntion cannot without this sleep
				//maybe it related with the Thread Model
	ResetEvent(m_hThreadEndEvent);
	m_pInEndPt->SetXferSize(m_pPacketListHead->GetBufSize());
	m_pCommitPacketHead = m_pPacketListHead;
	for(int i=0;i<m_CommitNum;i++)
	{
		m_pPacketListHead->m_pContext = m_pInEndPt->BeginDataXfer(m_pPacketListHead->GetBuf(),m_pPacketListHead->GetBufSize() , &(m_pPacketListHead->m_InOvLap));
		m_pPacketListHead =(CDTPUSBPacket*) m_pPacketListHead->GetNext();
	}
	//Use the Commit head to point to the first commit packet


	//Todo: Here after commit the packet wait still need send start frame command to MCU to 
	//reset FIFO and clear the error flag of FPGA then send image data.
	try
	{
		if(!SendSFCommand(TRUE))
		{
        	
			throw CDTException(EID_USB_CMD_SEND_FAIL);
		}
		LONG len;
		while(!m_bThreadStop)	//while not stop
		{
			//wait for commit head finnish
			if (!m_pInEndPt->WaitForXfer(&(m_pCommitPacketHead->m_InOvLap), m_TimeOut))
			{ //Time Out
            	
				m_pInEndPt->Abort();
				// Wait for the stalled command to complete 
				DWORD dwWait=WaitForSingleObject(m_pCommitPacketHead->m_InOvLap.hEvent,3000);
				
			}
			//move commit heade to the dtpqueue
			else//Success
			{
				
			}
				if (m_pInEndPt->FinishDataXfer(m_pCommitPacketHead->GetBuf(), len,&(m_pCommitPacketHead->m_InOvLap), m_pCommitPacketHead->m_pContext ))
				{			
					//Set the Data Len
					Timeout = 0;
					m_pCommitPacketHead->SetDataSize(len);
					CDTPPacketIF* pCommitPacket = m_pCommitPacketHead;
					EnterCriticalSection(&m_ListHeadCR);
					m_pCommitPacketHead = (CDTPUSBPacket*) m_pCommitPacketHead->GetNext();
					LeaveCriticalSection(&m_ListHeadCR);
					if(m_pCommitPacketHead	== NULL)
					{
                
						throw CDTException(EID_USB_IMG_REV_FAIL);
					}
					m_pDTPQueue->AddTail(pCommitPacket);
				}
				else
				{
					Timeout++;
				
					CDTPPacketIF* pPacket =(CDTPPacketIF*) m_pCommitPacketHead;
					m_pCommitPacketHead = (CDTPUSBPacket*)m_pCommitPacketHead->GetNext();
					pPacket->Reset();
					AddDTPPacket(pPacket);
                    if(Timeout> m_CommitNum)
					{
    			
						throw CDTException(EID_USB_IMG_REV_FAIL);
					}
				}
			
			//commit the m_pListHead packet
			EnterCriticalSection(&m_ListHeadCR);
			if(NULL == m_pPacketListHead->GetNext())
			{	
				
				if(m_bThreadStop)
				{
    			
        			LeaveCriticalSection(&m_ListHeadCR);//Here the Judgement of ResetEvent Should be in CriticalSection 
					break;
				}
    			LeaveCriticalSection(&m_ListHeadCR);//Here the Judgement of ResetEvent Should be in CriticalSection 
				//Wait for NextAvalible Packet insert. 
				//The DTPQueue thread should return the free packet to the DataSrc Queue
				ResetEvent(m_hFreePacketReady);
				if(WaitForSingleObject(m_hFreePacketReady,3000)==WAIT_OBJECT_0)
				{
				}
				else
				{
    			
					break;
					//throw CDTException(EID_DTP_PACKET_NONE);
				}
			}
			else
			{
				LeaveCriticalSection(&m_ListHeadCR);
			}
			//At this Point the GetNext Should Not Be NULL
			m_pPacketListHead->m_pContext = m_pInEndPt->BeginDataXfer(m_pPacketListHead->GetBuf(),m_pPacketListHead->GetBufSize() , &(m_pPacketListHead->m_InOvLap));
			//Here before update the PacketListHead , need enter critical section, the
			//PacketListHead is shared by this therad and DTPQueue Thread
			EnterCriticalSection(&m_ListHeadCR);
			m_pPacketListHead = (CDTPUSBPacket*) m_pPacketListHead->GetNext();
			LeaveCriticalSection(&m_ListHeadCR);
		}
		//m_pDTPQueue->Stop();
	}
	catch (CDTException E)
	{
		
		E.ProcessError();
		m_pDTPQueue->Stop();
		//Zhangxq
		//remove this line
		//m_pParent->DTError(E.m_ERROR_ID,E.m_ERROR_INFO);
		
		//End all commit packet
	}
	while(m_pCommitPacketHead!=NULL && m_pCommitPacketHead != m_pPacketListHead)//Before exit clear the commited packet
	{
		m_pInEndPt->Abort();
		// Wait for the stalled command to complete 
		DWORD dwWait=WaitForSingleObject(m_pCommitPacketHead->m_InOvLap.hEvent,1000);
		if (dwWait!=WAIT_OBJECT_0)
		{
		
			break;
		}
		CDTPPacketIF* pPacket = (CDTPPacketIF*)m_pCommitPacketHead;
		m_pCommitPacketHead = (CDTPUSBPacket*)m_pCommitPacketHead->GetNext();
		pPacket->Reset();
		AddDTPPacket(pPacket);
	}
	SetEvent(m_hThreadEndEvent);
	
	return 0;
}

BOOL CUSBDataSrc::ClearDetectorBuffer()
{
	return SendSFCommand(FALSE);
}
BOOL CUSBDataSrc::SendSFCommand(BOOL bStart)
{
	
	char cmd[100];
	char rt[100];
	LONG bSuccess;
	if(bStart)
	{
		sprintf((char*)cmd,"[SF,1]");
	}
	else
	{
		sprintf((char*)cmd,"[SF,0]");
	}
	m_pDetector->SendCommandA(cmd,rt,&bSuccess);
	
	return bSuccess;
};

void CUSBDataSrc::AddDTPPacketList(CDTPPacketIF* pHead)//Inser the packet to the wait queue called by DTImage to create a wait queue
{
	EnterCriticalSection(&m_ListHeadCR);
	//CDTPPacketIF* pLast = m_pPacketListHead;
	if(m_pPacketListHead)
	{
		m_pPacketListTail->SetNext(pHead);
	}
	else
	{
		m_pPacketListHead = (CDTPUSBPacket*)pHead;
		CDTPPacketIF* pLast = m_pPacketListHead;
		while((pLast->GetNext()) != NULL)
		{//Find the last packet
			pLast = pLast->GetNext();
		}
		m_pPacketListTail = (CDTPUSBPacket*)pLast;
	}
	SetEvent(m_hFreePacketReady);
	LeaveCriticalSection(&m_ListHeadCR);
}
void CUSBDataSrc::AddDTPPacket(CDTPPacketIF* pPacket)//Inser the packet to the wait queue called by DTImage to create a wait queue
{
	
	
	EnterCriticalSection(&m_ListHeadCR);
	pPacket->Reset();//Clear the content and set the next as null;
	CDTPPacketIF* pLast = m_pPacketListHead;
	if(m_pPacketListHead)
	{//If the Head is not empty then means the tail is also no tempty
		m_pPacketListTail->SetNext(pPacket);//append to the end
		m_pPacketListTail = (CDTPUSBPacket*)pPacket;
	}
	else
	{
		m_pPacketListHead = (CDTPUSBPacket*)pPacket;
		m_pPacketListTail = m_pPacketListHead;
//		ATLTRACE("ADD FREE Packet and Set Event\n");
	}
	SetEvent(m_hFreePacketReady);
	LeaveCriticalSection(&m_ListHeadCR);

}
	//and DTPQueue to return the used packet to the wait queue
	//Create Need the DTPQueuePointer,to accept the DTP Packet
void CUSBDataSrc::SetDTPQueue(CDTPQueueIF* pQueue)
{
	m_pDTPQueue = pQueue;
}

void CUSBDataSrc::SetCommitPacketNum(BYTE CommitNum)//Setup the cocurrent commmit packet number to driver
{
	m_CommitNum = CommitNum;
}
void CUSBDataSrc::ResetQueue()
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