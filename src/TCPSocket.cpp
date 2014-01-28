#include "../StdAfx.h"
#include "tcpsocket.h"
#include  "Winsock2.h"
#pragma comment(lib, "Ws2_32.lib")

CTCPSocket::CTCPSocket(void)
{
	m_bConnected = FALSE;
	m_pRevBuf = NULL;
	m_pSendBuf = NULL;
	m_ListenPort =3000;
	m_socket = 0;
	m_TimeOut = 10000;
	
}

CTCPSocket::~CTCPSocket(void)
{
}
void CTCPSocket::DisConnect()
{
	char buf[10];
	shutdown(m_socket,0);
	while(1)
	{
		int len = recv(m_socket,buf,10,0);
		if(len<=0)
			break;
	}
	closesocket(m_ListenSocket);
	closesocket(m_socket);
}
int CTCPSocket::SendData(BYTE* pSrc,WORD len)
{
	WORD SendLen = 0;
	int rt;
	while(SendLen < len)
	{//Should Add the head XTP
		rt= send(m_socket,(const char*)(pSrc+SendLen),len - SendLen,0);
		if(SOCKET_ERROR == rt)
		{
			return -1;
		}
		SendLen += rt;
	}
	return SendLen;
}
int CTCPSocket::ReceiveData(BYTE* pDest,int Len)
{
//	int len = recv(m_socket,(char*)pDest,Len,0);
	int len = recv(m_socket,(char*)pDest,Len,0);
	if(len <= 0)
	{
		m_bConnected = FALSE;
	}
	return len;
}
BOOL CTCPSocket::IsNetworkOK(BYTE* pDestIP, WORD Port)
{

	return TRUE;
}
BOOL CTCPSocket::Connect(BYTE* pDestIP, WORD Port,int bufsize)
{
	WORD wVersionRequested = MAKEWORD( 2, 2 );
	WSADATA wsaData;
	int err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
    /* Tell the user that we could not find a usable */
    /* WinSock DLL.                                  */
		m_bConnected = FALSE;
		return FALSE;
	}
/*************************************/
//Check Network connection
	
	if(!IsNetworkOK(pDestIP,Port))
	{
		WSACleanup();
		m_bConnected = FALSE;
		return FALSE;
	}

/*************************************/
	m_socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( m_socket == INVALID_SOCKET ) 
	{
		WSACleanup();
		return FALSE;
	}
	sockaddr_in clientService;

	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr((char*) pDestIP );
	clientService.sin_port = htons( Port);
	//Set the Socket Option
	int TimeOut = 1000;
	int rt;
	
	rt = setsockopt(m_socket,SOL_SOCKET,SO_RCVTIMEO,(char*)&TimeOut,sizeof(int));
	
	if ( connect( m_socket, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR) 
	{
		WSACleanup();
		m_bConnected = FALSE;
		closesocket(m_socket);
		return FALSE;
	}

	int bNodelay = 1; 

	err = setsockopt( m_socket, IPPROTO_TCP, TCP_NODELAY, (char *)&bNodelay, sizeof(bNodelay));//
	if (err != NO_ERROR) 
		ATLTRACE ("setsockopt failed for some reason\n");
	
	err = setsockopt( m_socket, SOL_SOCKET, SO_RCVBUF, (char *)&bufsize, sizeof(bufsize));//
	if (err != NO_ERROR) 
		ATLTRACE ("setsockopt failed for some reason\n");; 
	SetSocketTimeout(m_TimeOut);
	m_bConnected = TRUE;
	return TRUE;
}

BOOL CTCPSocket::WaitForConnection(WORD ListenPort,char* RemoteIP)
{
	closesocket(m_socket);
	
	m_ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_ListenSocket == INVALID_SOCKET) 
	{
		return FALSE;
	}
	m_ListenPort =  ListenPort;
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = ADDR_ANY ;
	service.sin_port = htons(m_ListenPort);
	
  int rt = bind( m_ListenSocket,(SOCKADDR*)&service,sizeof(service));
  if (rt == SOCKET_ERROR)
  {
		int err =  WSAGetLastError();
		closesocket(m_ListenSocket);

		return FALSE;
  }

  //----------------------
  // Listen for incoming connection requests.
  // on the created socket
  if (listen( m_ListenSocket, 1 ) == SOCKET_ERROR)
  {
    return FALSE;
  }

  //----------------------
  // Accept the connection.
	sockaddr_in in_addr;
    m_socket = SOCKET_ERROR;
	int size = sizeof(sockaddr);
    m_socket = accept( m_ListenSocket, (SOCKADDR*)&in_addr,&size);
    
	closesocket(m_ListenSocket);
	if(m_socket == SOCKET_ERROR)
	{
		return FALSE;
	}
//	char* pIP = inet_ntoa(in_addr.sin_addr);
	m_bConnected = TRUE;
//	strcpy_s(RemoteIP,(const char*)pIP);
    ATLTRACE("Client connected.\n");
	return TRUE;

}
BOOL CTCPSocket::IsCanRead()
{
	int rt = GetConnectionState();
	if((rt & 0x1) != 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
BOOL CTCPSocket::IsConnected()
{
	int rt = GetConnectionState();
	if((rt & 0x2) != 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
int CTCPSocket::GetConnectionState()
{
	int RT = 0;
	TIMEVAL tv01 = {0, 1};
	FD_SET fdr ; 
	FD_ZERO(&fdr);  
    FD_SET(m_socket, &fdr); 
	int nSelectRet= select(0,NULL,&fdr, NULL, &tv01);//Check Write
	if(SOCKET_ERROR==nSelectRet) 
	{
		return TCP_ERROR;
	}
    if(nSelectRet!=0)
	{
		m_bConnected = TCP_CONNECTED;
		RT |= 0x2; 
	}
	else
	{
		m_bConnected = FALSE;
		return RT ;
	}

	nSelectRet= select(0, &fdr, NULL, NULL, &tv01);//
	if(SOCKET_ERROR==nSelectRet) 
	{
		return TCP_ERROR;
	};
	if(nSelectRet!=0)
	{
		RT |= 0x1;
	}
	return RT;
}
int CTCPSocket::SetSocketTimeout(int milliseconds)
{
   struct timeval tv;
	m_TimeOut = milliseconds;
    tv.tv_sec = milliseconds / 1000 ;
    tv.tv_usec = ( milliseconds % 1000) * 1000  ;
   if(m_socket)	
		return setsockopt (m_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof tv);
   else
	   return 0;
}