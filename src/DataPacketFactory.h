#pragma once
//Maintain the packet list
//Create new packet
//releaes the packet resource
#include "DataPacket.h"

#define USB_PACKET	0
#define MAX_PACKET_NUM	256
class CDataPacketFactory
{
    CDataPacketIF* m_PacketArray[MAX_PACKET_NUM];//Every create packet will add one pointer in List
public:
    CDataPacketFactory(void);
    CDataPacketIF* GetNewDataPacketList(DWORD PacketBufSize, WORD PacketNum);//Return a list of packet with the size buffer
	void ReleaseAllPacket(void);
	void ClearAllPacket();
    ~CDataPacketFactory(void);
};
