#include ".\datapacketfactory.h"

CDataPacketFactory::CDataPacketFactory(void)
{
	for(int i = 0;i<MAX_PACKET_NUM;i++)
	{
		m_PacketArray[i] = 0;
	}
}

CDataPacketFactory::~CDataPacketFactory(void)
{
		// Dump the list elements to the debug window.
	ReleaseAllPacket();
}
void CDataPacketFactory::ReleaseAllPacket(void)
{
	for(int i = 0;i<MAX_PACKET_NUM;i++)
	{
		CDataPacketIF* pPacket = m_PacketArray[i];
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

CDataPacketIF* CDataPacketFactory::GetNewDataPacketList(DWORD PacketBufSize, WORD PacketNum)//Return a list of packet with the size buffer
{
	ReleaseAllPacket();
    CDataPacketIF* pHead=NULL;
	if(PacketNum > MAX_PACKET_NUM)
	{
		PacketNum = MAX_PACKET_NUM;
	}


        CDataPacketIF* pPacket = NULL;
		for(int i=0;i<PacketNum;i++)
		{
			pPacket = new CDataPacket(PacketBufSize);
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

	return pHead;
}

void CDataPacketFactory::ClearAllPacket()
{
    CDataPacketIF* pPacket;
	for(int i = 0;i<MAX_PACKET_NUM;i++)
	{
        pPacket = m_PacketArray[i];
		if(pPacket)
			pPacket->Clear();
	}
};
