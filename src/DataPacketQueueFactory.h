#pragma once
#include "DataPacketQueueIf.h"
class CDataPacketQueueFactory
{
private:
    CDataPacketQueueIF* m_pDataPacketQueue;
public:
    CDataPacketQueueFactory(void);
    ~CDataPacketQueueFactory(void);
    CDataPacketQueueIF* GetDataPacketQueue(void);
};
