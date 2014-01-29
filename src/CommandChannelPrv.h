#pragma once
#include "TCPSocket.h"
class CommandChannelPrv
{
public:

    CommandChannelPrv()
		: m_CardType(1),
		m_bIsOpened(0),
		m_CmdPort(3000),
		m_LastErrID(0),
        m_TimeOut(100)
	{
		memset(m_RemoteIP,0,20);
	}

    char* get_IPAddress();
    long put_IPAddress(char* newVal);
    long get_CmdPort(LONG* pVal);
    long put_CmdPort(LONG newVal);
    long get_IsOpened(LONG* pVal);
    long get_LastErrID(LONG* pVal);
    long get_ChannelType(LONG* pVal);
    long put_ChannelType(LONG newVal);
    long Open(LONG* bOK);
    long Close(void);
    long get_CmdTimeOut(LONG* pVal);
    long put_CmdTimeOut(LONG newVal);
    long SendCommandA(CHAR* Cmd, CHAR* pRT,LONG* pbOK);

//    long PrintErrMsg(LONG ErrID, BSTR* ErrMsg);
//    long get_BaudRate(LONG* pVal);
//    long put_BaudRate(LONG newVal);
//    long get_SerialPort(LONG* pVal);
//    long put_SerialPort(LONG newVal);


private:
	LONG m_CardType;
//	ULONG m_SerialPortNum;
	BOOL m_bIsOpened;
	char m_RemoteIP[20];
	ULONG m_CmdPort;
    ULONG m_LastErrID;
//	LONG m_BaudRate;
	LONG m_TimeOut;
private:
    CTCPSocket			m_Socket;
    //Todo Refactory the channel to channel interface


private:

	BOOL TestConnection() { return true;};
    int SendNETData(CHAR* pStrCmd);
    int RevNETData(CHAR* pRT,WORD BuffSize = 100);

public:
};

