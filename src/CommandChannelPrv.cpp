
#include "../stdafx.h"
#include "CommandChannelPrv.h"
#include "LibConst.h"
// CommandChannelPrv

char* CommandChannelPrv::get_IPAddress()
{
	return m_RemoteIP;
}

long CommandChannelPrv::put_IPAddress(char* ip)
{
	// TODO: Add your implementation code here
	memset(m_RemoteIP,0,20);
	strncpy_s((CHAR*)m_RemoteIP,20, ip,20);
	return 0;
}

long CommandChannelPrv::get_CmdPort(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_CmdPort;
	return 0;
}

long CommandChannelPrv::put_CmdPort(LONG newVal)
{
	// TODO: Add your implementation code here
	m_CmdPort = newVal;
	return 0;
}

long CommandChannelPrv::get_IsOpened(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_bIsOpened;
	return 0;
}

long CommandChannelPrv::get_LastErrID(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_LastErrID;
	return 0;
}

long CommandChannelPrv::get_ChannelType(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_CardType;
	return 0;
}

long CommandChannelPrv::put_ChannelType(LONG newVal)
{
	// TODO: Add your implementation code here
	m_CardType = newVal;
	return 0;
}

long CommandChannelPrv::Open(LONG* bOK)
{
	m_LastErrID = EID_SUCCESS;
	BOOL bPortOpened = FALSE;
	int iCount=0;
	UCHAR ucUSBPort=0;
	if(m_bIsOpened)
	{
		Close();
	}
		switch(m_CardType)
		{
			case NET:
				if(m_Socket.Connect((BYTE*)m_RemoteIP,(WORD)m_CmdPort))
				{
					bPortOpened = TRUE;
				}
				else
				{
					m_LastErrID  = EID_NET_CMD_CONNECT_FAILED;
					bPortOpened = FALSE;
				}
				break;
			default:
				m_LastErrID  = EID_UNKNOWN_CMD_CHANNEL;
				bPortOpened = FALSE;
		}

		if(bPortOpened)
		{
			if(TestConnection())
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
			*bOK = FALSE;
		}
	if(*bOK)
	{
		m_bIsOpened = TRUE;
	}
	else
	{
		m_bIsOpened = FALSE;
	}
	return 0;
}

long CommandChannelPrv::Close(void)
{
	// TODO: Add your implementation code here
	m_LastErrID = EID_SUCCESS;
	switch(m_CardType)
	{
	case NET:
		m_Socket.DisConnect();
		break;
	}

	m_bIsOpened = FALSE;
	return 0;
}

long CommandChannelPrv::SendCommandA(CHAR* pSendCmd, CHAR* pRTBuffer,LONG* pbSuccess)
{
	m_LastErrID = EID_SUCCESS;
	if(m_bIsOpened)
	{
		switch(m_CardType)
		{
		case NET:
			int len =0;
			int Retry=0;
			len = SendNETData(pSendCmd);
			if(len == strlen(pSendCmd))
			{
REV:			Sleep(m_TimeOut);
				len = RevNETData(pRTBuffer);
				if(len > 0)
				{
					if(pRTBuffer[2] == '0')
					{
						*pbSuccess = TRUE;
						char* end = strrchr(pRTBuffer,']');
						if(end)
							*(end+1) = 0;
					}
					else
					{
						m_LastErrID = EID_CMDCHANEL_RT_ERROR;
						*pbSuccess = FALSE;
					}
				}
				else
				{
					m_LastErrID = EID_NET_CMD_REV_FAILED;
					*pbSuccess = FALSE;
					Retry++;
					int ErrID = WSAGetLastError();
					//if((ErrID  == WSAETIMEDOUT)&&(Retry>10))
					if(Retry<10)
						goto REV;
				}
			}
			else
			{
				m_LastErrID = EID_NET_CMD_SEND_FAILED;
				*pbSuccess = FALSE;
			}
			break;
		}
	}
	else
	{
		m_LastErrID = EID_NO_CMD_CHANEL;
		*pbSuccess = FALSE;
	}

    return 0;
}

long CommandChannelPrv::get_CmdTimeOut(LONG* pVal)
{
    // TODO: Add your implementation code here
    *pVal = m_TimeOut;
    return 0;
}

long CommandChannelPrv::put_CmdTimeOut(LONG newVal)
{
    // TODO: Add your implementation code here
    m_TimeOut = newVal;
    return 0;
}

//BOOL CommandChannelPrv::SendUSBData(CHAR* pStrCmd)
//{
//	m_pCtlEndPt->Target    = TGT_DEVICE;

//	m_pCtlEndPt->ReqType   = REQ_VENDOR;

//	m_pCtlEndPt->Direction = DIR_TO_DEVICE;

//	m_pCtlEndPt->ReqCode   = 0xB0;

//	m_pCtlEndPt->Value     = 1;

//	m_pCtlEndPt->Index     = 0;

//	long temp = (long)strlen(pStrCmd);
//	if(!m_pCtlEndPt->XferData((PUCHAR)pStrCmd,temp))
//	{
//		m_LastErrID = EID_USB_CMD_SEND_FAIL;
//		return FALSE;
//	};
//	//Todo check here the Count is equal to XTPLength
//	if(temp != strlen(pStrCmd))
//	{
//		m_LastErrID = EID_USB_CMD_SEND_FAIL;
//		return FALSE;
//	};
//	return TRUE;

//}
//BOOL CommandChannelPrv::RevUSBData(CHAR* pStrRT)
//{
//	const int MAX_REV_SIZE = 64;
//	BOOL bStart = FALSE;
//	BOOL bEnd = FALSE;
//	BYTE PacketBuf[64];
//	memset(PacketBuf,0,64);
//	m_pCtlEndPt->Target    = TGT_DEVICE;

//	m_pCtlEndPt->ReqType   = REQ_VENDOR;

//	m_pCtlEndPt->Direction = DIR_FROM_DEVICE;

//	m_pCtlEndPt->ReqCode   = 0xB0;

//	m_pCtlEndPt->Value     = 1;

//	m_pCtlEndPt->Index     = 0;

//	long RevSize = 64;//The size of every transfer
//	WORD BufCounter = 0;
//	while(!bEnd)
//	{
//		if(!m_pCtlEndPt->XferData((PUCHAR)PacketBuf, RevSize))
//		{
//			m_LastErrID = EID_USB_CMD_REV_FAIL;
//			return FALSE;
//		}
//		if(RevSize == 0)
//		{
//			m_LastErrID = EID_USB_CMD_REV_FAIL;
//			return FALSE;
//		}
//		for(int i = 0; i< RevSize; i++)
//		{
//			if(PacketBuf[i] == STX)
//			{
//				bStart = TRUE;
//			}

//			if(bStart)
//			{
//				pStrRT[BufCounter] = PacketBuf[i];
//				BufCounter++;
//				if(BufCounter > MAX_REV_SIZE)//
//				{
//					m_LastErrID = EID_USB_CMD_REV_FAIL;
//					return FALSE;
//				}
//			}
//			if(PacketBuf[i] == ETX)
//			{
//				bEnd = TRUE;
//				break;
//			}
//		}
//	}
//	return TRUE;
//};
int CommandChannelPrv::SendNETData(CHAR* pStrCmd)
{
	return m_Socket.SendData((BYTE*)pStrCmd,strlen(pStrCmd));
};
int CommandChannelPrv::RevNETData(CHAR* pRT,WORD BuffSize)
{
	int len = 0;
	int Index = 0;
	BYTE Buf[64];
	BOOL StartCpy = FALSE;
	while(1)
	{
		if(!m_Socket.IsConnected())
		{
			*pRT = 0;
			return 0;
		}
		if(m_Socket.IsCanRead())
			len = m_Socket.ReceiveData(Buf,64);
		else
			break;
		for(int i = 0; i<len;i++)
		{
			if(StartCpy)
			{
				pRT[Index] = Buf[i];
				if(pRT[Index] == ETX)
				{
					return Index;
				}
				Index++;
			}
			else
			{
				if(Buf[i] == STX)
				{
					StartCpy = TRUE;
					pRT[Index] = Buf[i];
					Index++;
				}
			}
		}
	};
	return Index;
};