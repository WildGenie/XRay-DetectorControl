#include "StdAfx.h"
#include ".\dtppacketfactory.h"
CDTPPacketFactory::CDTPPacketFactory(void)
{
	for(int i = 0;i<MAX_PACKET_NUM;i++)
	{
		m_PacketArray[i] = 0;
	}
}

CDTPPacketFactory::~CDTPPacketFactory(void)
{
		// Dump the list elements to the debug window.
	ReleaseAllPacket();
}
void CDTPPacketFactory::ReleaseAllPacket(void)
{
	for(int i = 0;i<MAX_PACKET_NUM;i++)
	{
		CDTPPacketIF* pPacket = m_PacketArray[i];
		if(pPacket)
		{
			delete pPacket;
		}
	}
	for(int i = 0;i<MAX_PACKET_NUM;i++)
	{
		m_PacketArray[i] = 0;
	}
}
CDTPPacketIF* CDTPPacketFactory::GetNewDTPPacketList(BYTE PacketType, DWORD PacketBufSize, WORD PacketNum)//Return a list of packet with the size buffer
{
	ReleaseAllPacket();
	CDTPPacketIF* pHead=NULL;
	if(PacketNum > MAX_PACKET_NUM)
	{
		PacketNum = MAX_PACKET_NUM;
	}
	if(DT_USB == PacketType)
	{
		CDTPPacketIF* pPacket = NULL;
		for(int i=0;i<PacketNum;i++)
		{
			pPacket = new CDTPUSBPacket(PacketBufSize);
			m_PacketArray[i] = pPacket;
		}

		for(int i=0;i<(PacketNum-1);i++)
		{
			pPacket = m_PacketArray[i];
			pPacket->SetNext(m_PacketArray[i+1]);
		}
		pPacket = m_PacketArray[PacketNum-1];
		pPacket->SetNext(NULL);
		pHead = m_PacketArray[0];
	}
	return pHead;
}
void CDTPPacketFactory::ClearAllPacket()
{
	CDTPPacketIF* pPacket;
	for(int i = 0;i<MAX_PACKET_NUM;i++)
	{
		 pPacket = m_PacketArray[i];
		if(pPacket)
			pPacket->Clear();
	}
};