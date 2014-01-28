#pragma once
#define TCP_READ		1
#define TCP_CONNECTED	2
#define TCP_WRITE		2
#define TCP_CLOSED		0
#define TCP_ERROR		-1
const WORD STACK_SIZE = 4096;

class CTCPSocket
{
	BOOL m_bConnected;
	BYTE* m_pRevBuf;
	BYTE* m_pSendBuf;
	ULONG m_StackSize;
	SOCKET m_socket;
	SOCKET m_ListenSocket;
	WORD  m_ListenPort;
	LONG m_TimeOut;
public:
	CTCPSocket(void);
	int SendData(BYTE* pSrc,WORD len);
	int ReceiveData(BYTE* pDest,int Len);
	BOOL Connect(BYTE* pDestIP, WORD Port,int bufsize=0x20000);//Default buffer is 128K
	void DisConnect();
	BOOL WaitForConnection(WORD ListenPort,char* RemoteIP);
	
	BOOL IsCanRead();
	BOOL IsConnected();
	~CTCPSocket(void);
	int SetSocketTimeout(int milliseconds);
private:
	int GetConnectionState();
	BOOL IsNetworkOK(BYTE* pDestIP, WORD Port);
};
