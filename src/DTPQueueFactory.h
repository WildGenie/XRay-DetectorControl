#pragma once
#include "DTPQueue.h"
class CDTPQueueFactory
{
private:
	CDTPQueueIF* m_pDTPQueue;
public:
	CDTPQueueFactory(void);
	~CDTPQueueFactory(void);
	CDTPQueueIF* GetDTPQueue(void);
};
