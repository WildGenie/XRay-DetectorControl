#include "StdAfx.h"
#include ".\dtppacket.h"

CDTPUSBPacket::CDTPUSBPacket(DWORD BufSize):CDTPPacketIF()
{
	m_pBuf = new BYTE[BufSize];
	if(m_pBuf)
	{
		m_BufSize = BufSize;
		m_InOvLap.hEvent = CreateEvent(NULL, FALSE,FALSE, NULL);
	}
	else
	{
		m_BufSize = 0;
	}
	m_FirstIndex = 0;
	m_DataLen = 0;
	m_pNext = NULL;;
}

CDTPUSBPacket::~CDTPUSBPacket(void)
{
	if(m_BufSize>0)
	{
		delete m_pBuf;
		m_BufSize =0;
		m_pBuf = NULL;
		CloseHandle(m_InOvLap.hEvent);
	}

}
DWORD CDTPUSBPacket::GetBufSize()
{
	return m_BufSize;
}

BYTE* CDTPUSBPacket::GetBuf()//called by datasrc to copy data from driver
{
	return (m_pBuf+m_FirstIndex);
}
DWORD CDTPUSBPacket::GetFirstIndex()
{
	return m_FirstIndex;
}
void  CDTPUSBPacket::MoveFirstToWithOffset(DWORD pos)//Called by dtpqueue after copy to Frame buffer 
{
	m_FirstIndex += pos;//decrease the copied part
	m_DataLen -= pos; //recaculate the avalible size
}
void  CDTPUSBPacket::Reset()
{
	
	Clear();
	m_pNext =NULL;
}
void CDTPUSBPacket::Clear()
{
	m_FirstIndex = 0;
	m_DataLen = 0;
};
DWORD CDTPUSBPacket::GetDTPLen()//offset is start from First. Becalled to get the Len
{
	return m_DataLen;
}
void  CDTPUSBPacket::SetNext(CDTPPacketIF* pNext)
{
	m_pNext = pNext;
}
CDTPPacketIF* CDTPUSBPacket::GetNext()
{
	return m_pNext;
}
void  CDTPUSBPacket::SetDataSize(DWORD len)
{
	m_DataLen = len;
}
void CDTPUSBPacket::Trace(FILE * pFile)
{//Here append the Trace recoed to the File
	fprintf(pFile,"\nm_FirstIndex is %04X	Len is %d	\n",m_FirstIndex,m_DataLen);
	for(DWORD i = 0;i<(m_DataLen+m_FirstIndex);i++)
	{
		if((i%0x10) == 0)
		{
			//Print the header
			fprintf(pFile,"\n%04X		",i);
		}
		fprintf(pFile,"%02X	",*(m_pBuf+i));

	}
}