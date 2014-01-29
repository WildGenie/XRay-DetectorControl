// ScannerImage.cpp : CScannerImage 的实现
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "ScannerImage.h"
#include "DetectorControl_i.h"

// CScannerImage

#include <atlctl.h>
#include <comutil.h>
#include "src/ScannerException.h"
#include "src/pixelorderconverter.h"
#include "src/ScannerException.h"
#include <omp.h>

// CScannerImage
#define IDT_TIMER1   0x10000


STDMETHODIMP CScannerImage::get_ImgHeight(LONG* pVal)
{
	
	*pVal = m_ImageHeight;
	return S_OK;
}

STDMETHODIMP CScannerImage::put_ImgHeight(LONG newVal)
{
	
	if(!m_bIsOpened)
	{
		m_ImageHeight = newVal;
	}
	return S_OK;
}

STDMETHODIMP CScannerImage::get_ImgWidth(LONG* pVal)
{
	
	*pVal = m_ImageWidth;
	return S_OK;
}

STDMETHODIMP CScannerImage::put_ImgWidth(LONG newVal)
{
	
	if(!m_bIsOpened)
	{
		m_ImageWidth = newVal;
	}
	return S_OK;
}

STDMETHODIMP CScannerImage::get_BytesPerPixel(LONG* pVal)
{
	
	*pVal = m_BytesPerPixel;
	return S_OK;
}

STDMETHODIMP CScannerImage::put_BytesPerPixel(LONG newVal)
{
	
	if(!m_bIsOpened)
	{
		m_BytesPerPixel = newVal;
	}	
	return S_OK;
}

STDMETHODIMP CScannerImage::get_ChannelType(LONG* pVal)
{
	
	*pVal = m_CardType;
	return S_OK;
}

STDMETHODIMP CScannerImage::put_ChannelType(LONG newVal)
{
	if(!m_bIsOpened)
	{	
		m_CardType = newVal;
	}
	return S_OK;
}

STDMETHODIMP CScannerImage::get_ImagePort(LONG* pVal)
{
	*pVal = m_ImagePort;
	return S_OK;
}

STDMETHODIMP CScannerImage::put_ImagePort(LONG newVal)
{
	
	if(!m_bIsOpened)
	{
		m_ImagePort = newVal;
	}	

	return S_OK;
}

STDMETHODIMP CScannerImage::get_DetectorObject(IUnknown**  pVal)
{
	if(m_pDetector)
	{
		m_pDetector->QueryInterface(IID_IUnknown,(void**)pVal); 
	}
	else
	{
		*pVal = NULL;
	}
	
	return S_OK;
}

STDMETHODIMP CScannerImage::put_DetectorObject(IUnknown* newVal)
{
	
	if(!m_bIsOpened)
	{//If not open then allow change
		newVal->QueryInterface(IID_ICommandChannel,(void**)&m_pDetector); 
	}
	return S_OK;
}

STDMETHODIMP CScannerImage::get_IsOpened(LONG* pVal)
{
	
	*pVal = m_bIsOpened;
	return S_OK;
}

STDMETHODIMP CScannerImage::get_LastErrID(LONG* pVal)
{
	
	*pVal = m_LastErrID;
	return S_OK;
}

STDMETHODIMP CScannerImage::Open(LONG* b_OK)
{
	ULONG SubFrameNum = 1;
	m_dualScanMode = 0;

	m_LastErrID = EID_SUCCESS;
	
	if(m_bIsOpened)
	{
    	
		*b_OK = TRUE;
		return S_OK;
	}
	//Check the SubFrameHeight consistance. If it cannot divided, then reset it same as frame height;


	if( (m_ImageHeight%m_SubFrameHeight) != 0)
	{
		m_SubFrameHeight = m_ImageHeight;
	}
	SubFrameNum = m_ImageHeight/m_SubFrameHeight;
	//Get FrameBuffer
	m_pFrameBuf = m_FrameBufFactory.GetFrameBuf(this,m_ImageWidth,m_ImageHeight,m_BytesPerPixel,SubFrameNum);
	//Apply ImageObejct
			
	HRESULT hr = ::CoCreateInstance(CLSID_FrameObject,NULL,CLSCTX_ALL,IID_IFrameObject,(LPVOID*) &m_pImageObject);
	if(FAILED(hr))
	{
		_com_error err(hr);
		return S_FALSE;
	}
	m_pImageObject->AddRef();

	if(m_pImageObject)
	{
		m_pImageObject->Open(m_ImageWidth,m_ImageHeight,m_BytesPerPixel);
		m_pFrameBuf->SetImageObject(m_pImageObject);
	}
	else
	{
		m_LastErrID = EID_CANNOT_OPEN_IMG_OBJ;
		m_bIsOpened = FALSE;
		*b_OK = FALSE;
	}
	//Get DatapacketQueue
	m_pDataPacketQueue = m_DataPacketQueueFactory.GetDataPacketQueue();
	m_DataPacketFactory.ReleaseAllPacket();
	//Get PacketList
	CDataPacketIF* pPacket = NULL;
	
	pPacket = m_DataPacketFactory.GetNewDataPacketList(NET_PACKET_BUF_SIZE,PACKET_NUM);

	if(m_pFrameBuf)
	{
		//Create DataSrc form CardType
		switch(m_CardType)
		{
		case NET:
			{
				char RemoteIP[20];
				BSTR BSTRIP;
				m_pDetector->get_IPAddress(&BSTRIP);
				CHAR* tempbuf = _com_util::ConvertBSTRToString(BSTRIP);
				strncpy((CHAR*)RemoteIP,tempbuf,19);
				delete [] tempbuf;

				NetParam Param(RemoteIP,m_ImagePort);
				m_pDataSrc = m_ScannerDataSrcFactory.GetScannerDataSrc(NET,m_pDetector,&Param);
				if(m_pDataSrc)
				{
					m_pDataSrc->AddDataPacketList(pPacket);
					m_pDataSrc->SetDataPacketQueue(m_pDataPacketQueue);
					m_pDataPacketQueue->SetScannerDataSrc(m_pDataSrc);
					m_pDataPacketQueue->SetFrameBuf(m_pFrameBuf);
					m_pDataPacketQueue->SetEventManager(this);
					m_bIsOpened = TRUE;
					*b_OK = TRUE;
				}
				else
				{
					m_bIsOpened = FALSE;
					*b_OK = FALSE;
				}
			}
			break;
		default:
			{
				m_LastErrID = EID_UNKNOWN_IMG_CHANNEL;
				m_bIsOpened = FALSE; 
				*b_OK = FALSE;
			}
		}
		
	}
	else
	{
		m_LastErrID = EID_FRAMEBUF_ALLOC_FAIL;
		m_bIsOpened = FALSE;
		*b_OK = FALSE;
	}
	CScannerException Err(m_LastErrID);
	Fire_OnError(Err.m_ERROR_ID,Err.m_ERROR_INFO);
   	
	return S_OK;
}

STDMETHODIMP CScannerImage::Close(void)
{
	// TODO: Release All resource
	m_LastErrID = EID_SUCCESS;
	if(m_bIsOpened )
	{
		m_bIsOpened = FALSE;
		Stop();
		//m_pDataSrc->Close();
	}
	if(m_pImageObject)
		m_pImageObject->Release();
	m_pImageObject = NULL;
	return S_OK;
}
void CScannerImage::SendFrameTrigger()
{
	char cmd[100];
	char rt[100];
	LONG bSuccess;
	if(m_bExFrameTrigger)
	{
		sprintf(cmd,"[SE]");
		m_pDetector->SendCommandA(cmd,rt,&bSuccess);
	}
}
void CScannerImage::SetFrameTrigger()
{
	char cmd[100];
	char rt[100];
	LONG bSuccess;
	if(m_bExFrameTrigger)
	{
		int size = m_ImageHeight/FRAME_UNIT;
		//int size = 7;
		//sprintf(cmd,"[EF,W,%X]",size);
		sprintf(cmd,"[EF,W,%X]",m_ImageHeight);
	}
	else
	{
		sprintf(cmd,"[EF,W,0]");
	}
	if(m_pDataSrc)
		m_pDataSrc->SetTimeOut(m_Timeout);
	m_pDetector->SendCommandA(cmd,rt,&bSuccess);
	if(!bSuccess)
	{
//		throw CScannerException(EID_USB_CMD_SEND_FAIL);
	}
}
STDMETHODIMP CScannerImage::Grab(LONG FrameNums, LONG* bOK)
{
	try
	{
		m_LastErrID = EID_SUCCESS;
		if(m_pDataSrc)
		{   
			m_FrameNum = FrameNums;
			m_CurFrameCount = 0;
			
			m_pFrameBuf->Reset();
			ResetAllDataPacket();//Clear all DataPacket Content
			SetFrameTrigger();
			if(m_pDataSrc->Start())//start the thread to get the fame
			{
				*bOK = TRUE;
			}
			else
			{
				*bOK = FALSE;
			}
		}
		else
		{
			m_LastErrID = EID_NO_IMG_CHANEL;
			*bOK =  FALSE;
			throw CScannerException(m_LastErrID);
		}
		
	}
	catch (CScannerException E)
	{
		//E.PrintErrInfo();
		E.ProcessError();
		//End all commit packet
	}
	return S_OK;
}

STDMETHODIMP CScannerImage::Snap(LONG FrameNums, LONG* bOK)
{
	// TODO: Add your implementation code here
	//If Datasrc avalible
	m_LastErrID = EID_SUCCESS;
	try
	{
		if(m_pDataSrc)
		{
			//Stop First
			
			m_pDataSrc->Stop();
			
			//FrameNum at least be 1
			m_FrameNum = ((FrameNums>1)?FrameNums:1);
			//Reset Current Frame Count
			m_CurFrameCount = 0;
			//Reset the Event Flag of all frame send
			ResetEvent(m_hAllFrameSended);
			//Clear all DataPacket Content to clean the DataPacketStack
			m_pFrameBuf->Reset();
			SetFrameTrigger();
			ResetAllDataPacket();//Clear all DataPacket Content
			//start the therad to get the frame
			if(m_pDataSrc->Start())
			{
				//If start succesful, Wait untill all Frame finnish
				while(WaitForSingleObject(m_hAllFrameSended,10) == WAIT_TIMEOUT)
				{//Check the Frame Number every 10ms
					if(!m_pDataSrc->IsRunning())
					{//If for some reason the thread is stopped, then break,
						//MessageBox("T3");
						break;
					}
				};
				*bOK = TRUE;
			}
			else
			{//If Datasrc start failed then means no image channel
				m_LastErrID = EID_NO_IMG_CHANEL;
				*bOK = FALSE;
				throw CScannerException(m_LastErrID);
			}
		}
		else
		{//If no datasrc 
			m_LastErrID = EID_NO_IMG_CHANEL;
			*bOK =  FALSE;
			throw CScannerException(m_LastErrID);
		}
	
	}
	catch (CScannerException E)
	{
		//E.PrintErrInfo();
		E.ProcessError();
		//End all commit packet
	}
	return S_OK;
}

STDMETHODIMP CScannerImage::PrintErrMsg(LONG ErrID, BSTR* ErrMsg)
{
	

	return S_OK;
}



STDMETHODIMP CScannerImage::get_SubFrameHeight(LONG* pVal)
{
	
	*pVal = m_SubFrameHeight;
	return S_OK;
}

STDMETHODIMP CScannerImage::put_SubFrameHeight(LONG newVal)
{
	
	m_SubFrameHeight = newVal;
	return S_OK;
}
void CScannerImage::ResetAllDataPacket()
{
	m_DataPacketFactory.ClearAllPacket();
	//Move the data packet in Queue and Commit queue into wait queue
	if(m_pDataPacketQueue)
	{
		m_pDataPacketQueue->ClearQueue();//Clear the buffer of packet and return it to wait queue
	}
	if(m_pDataSrc)
	{
		m_pDataSrc->ResetQueue();
	}
}
void CScannerImage::OnScannerEvent(BYTE EventID,BYTE EventContent)
{
		//	ATLTRACE("Event ID is %d\n",EventID);
	switch(EventID)
	{
		case EVENT_DATA_LOST:
			Fire_LineLost(EventContent);
			break;
	}
};
void CScannerImage::OnFrameReady(BYTE* pSrc, DWORD Size)
{
	//Ajuadge whther to stop the datasrc
	//m_FrameNum is the total frame number want to take
	//if ==0 menas continues untill user stop
	if(m_dualScanMode) {
		//::MessageBox( GetForegroundWindow(), _T("Helllo World"), NULL, MB_OK );
		int boardNum = m_ImageWidth/64; //every board have 64 bits
		DualToSingleConverter converter(boardNum, 64);
		converter.process(m_pImageObject);
	}
	if(m_FrameNum>0)//Snap or grab operation with Num
	{
		m_CurFrameCount++;
		if(!m_pDataSrc->GetStopFlag())
		{
			//MessageBox("N1");
			Fire_FrameReady(m_ImageHeight);
			
			OnSinkFrameReady(m_ImageHeight);
			
		}
		//ATLASSERT(m_FrameNum >= m_CurFrameCount);
		if(m_CurFrameCount == m_FrameNum)
		{
			//Here cannot use m_pDataSrc->Stop() to stop the thread
			//Because stop() will wait untill the Grabthread end, the grab thread will wait
			// until the Queue Thread End, but this function will be called by queue thread when
			// Frame Ready happen. The result is deadlock if call stop. So use setstop flag as
			// an asynchronize stop method
			m_pDataSrc->SetStopFlag(TRUE);
			SetEvent(m_hAllFrameSended);
		}
	}
	//ATLTRACE("Frame Send\n");
	else//UnEnd grab
	{
		if(!m_pDataSrc->GetStopFlag())
		{//If the flag still not set then post the Frame Read Message
		//else do nothing . It is useful for the last frame. If user have click stop
			//THen the current unfinnish frame should not overwrite the old one

			Fire_FrameReady(m_ImageHeight);	
			OnSinkFrameReady(m_ImageHeight);
		}
	}
	//ATLTRACE("Frame Send End");
};
void CScannerImage::OnSubFrameReady(LONG  RowID, LONG NumLines,BOOL bLastFrame)
{
	//Caclute the Start Line , Numof lines and left blocks, and the lastblock flag
		if(!m_pDataSrc->GetStopFlag())
		{//If the flag still not set then post the Frame Read Message
		//else do nothing . It is useful for the last frame. If user have click stop
			//THen the current unfinnish frame should not overwrite the old one
			LONG LeftBlocks = (m_ImageHeight - RowID)/m_SubFrameHeight - 1;
			//MessageBox("N2");
			Fire_SubFrameReady(LeftBlocks,RowID,NumLines,bLastFrame);
			OnSinkSubFrameReady(LeftBlocks,RowID,NumLines,bLastFrame);			
		}
};

STDMETHODIMP CScannerImage::Stop(void)
{
	m_LastErrID = EID_SUCCESS;
	if(m_pDataSrc)
	{
		if(m_pDataSrc->IsRunning())
		{
			//m_pFrameBuf->SetImageObject(NULL);
			SendFrameTrigger();//If it is external framer trigger mode,send one trigger to stop
			if(m_pDataSrc->Stop())
			{
			}
			else
			{
				ATLASSERT(0);
			}
		}
	}
	CScannerException Err(m_LastErrID);
	Fire_OnError(Err.m_ERROR_ID,Err.m_ERROR_INFO);
	return S_OK;
}

STDMETHODIMP CScannerImage::get_IsGrabing(LONG* pbGrab)
{
	// TODO: Add your implementation code here
	if(m_pDataSrc)
	{
		if(m_pDataSrc->IsRunning())
		{
			*pbGrab = TRUE;
		}
		else
		{
			*pbGrab = FALSE;
		}
	}
	else
	{
		*pbGrab = FALSE;
	}
	return S_OK;
}

STDMETHODIMP CScannerImage::get_ImageObject(IUnknown** pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_pImageObject;
	return S_OK;
}

STDMETHODIMP CScannerImage::get_BandWidth(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_BandWidth;
	return S_OK;
}

void CScannerImage::OnTimer()
{
	LONG bGrab=0;
		get_IsGrabing(&bGrab);
		if(bGrab)
		{
			m_BandWidth=m_BytesReceived;
			m_BytesReceived = 0;
		}
		else
		{
			m_BandWidth = 0;
			m_BytesReceived = 0;
		}
	
}
void CScannerImage::OnNewDataComimg(ULONG Size)
{
	m_BytesReceived += Size;
}

LRESULT CScannerImage::OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	OnTimer();
	return 0;
}

void CScannerImage::OnSinkFrameReady(LONG NumLines)
{
	for(int i=0;i<SINK_SIZE;i++)
	{
		if(m_SinkArray[i])
			m_SinkArray[i]->OnFrameReady(NumLines);
	}
}
void CScannerImage::OnSinkSubFrameReady( LONG NumOfBlockLeft,  LONG StartLine,  LONG NumLines, BYTE bLastBlock)
{
	for(int i=0;i<SINK_SIZE;i++)
	{
		if(m_SinkArray[i])
			m_SinkArray[i]->OnSubFrameReady(NumOfBlockLeft,StartLine,  NumLines, bLastBlock);;
	}
}

void CScannerImage::AdviseSink(IFrameEventSink* pSink,LONG* pCookie)
{
	int i;
	for(i=0;i<SINK_SIZE;i++)
	{
		if(NULL == m_SinkArray[i])
		{
			m_SinkArray[i] = pSink;
			*pCookie = i;
			break;
		}
	}
	if(SINK_SIZE == i)//Not find avalible position
	{
		*pCookie = -1;
	}
}
void CScannerImage::UnAdviseSink(LONG Cookie)
{
	if(Cookie > SINK_SIZE)
		return;
	if(Cookie < 0)
		return;
	m_SinkArray[Cookie] = NULL; 
	return;
}
STDMETHODIMP CScannerImage::get_ObjectHandle(IUnknown** pVal)
{
	this->QueryInterface(IID_IUnknown,(void**) pVal);
	
	return S_OK;
}

STDMETHODIMP CScannerImage::get_TimeOut(LONG* pVal)
{
	// TODO: Add your implementation code here
	if(m_pDataSrc)
		m_pDataSrc->GetTimeOut(pVal);
	else
		*pVal = m_Timeout;
	return S_OK;
}

STDMETHODIMP CScannerImage::put_TimeOut(LONG newVal)
{
	m_Timeout = newVal;
	if(m_pDataSrc)
		m_pDataSrc->SetTimeOut(m_Timeout);
	return S_OK;
}

STDMETHODIMP CScannerImage::get_ExFrameTrigger(LONG* pVal)
{
	*pVal =	m_bExFrameTrigger ;
	return S_OK;
}

STDMETHODIMP CScannerImage::put_ExFrameTrigger(LONG newVal)
{
	if(newVal)
		m_bExFrameTrigger = 1;
	else
		m_bExFrameTrigger = 0;
	return S_OK;
}


STDMETHODIMP CScannerImage::get_DualScanMode(LONG* pVal)
{
	*pVal = m_dualScanMode;
	return S_OK;
}


STDMETHODIMP CScannerImage::put_DualScanMode(LONG newVal)
{
	m_dualScanMode = newVal;
	return S_OK;
}


STDMETHODIMP CScannerImage::OpenMemImage(LONG width, LONG height, BYTE* data)
{
	return S_OK;
}


STDMETHODIMP CScannerImage::Advise(IFrameReadyCallBack* pCallBack, long* cookie)
{

	return S_OK;
}


STDMETHODIMP CScannerImage::UnAdvise(LONG cookie)
{
	return S_OK;
}
