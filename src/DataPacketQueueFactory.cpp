#include "../stdafx.h"
#include "DataPacketQueue.h"
#include ".\datapacketqueuefactory.h"
//????
int giCount=0;
CDataPacketQueueFactory::CDataPacketQueueFactory(void):
m_pDataPacketQueue(NULL)
{
}

CDataPacketQueueFactory::~CDataPacketQueueFactory(void)
{
    if(m_pDataPacketQueue)
        delete m_pDataPacketQueue;
}

CDataPacketQueueIF* CDataPacketQueueFactory::GetDataPacketQueue(void)
{
    if(m_pDataPacketQueue)
        delete m_pDataPacketQueue;
    m_pDataPacketQueue = new CDataPacketQueue(giCount);
	giCount++;
	return m_pDataPacketQueue;
}
