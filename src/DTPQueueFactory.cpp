#include "StdAfx.h"
#include ".\dtpqueuefactory.h"
int giDTCount=0;
CDTPQueueFactory::CDTPQueueFactory(void):
m_pDTPQueue(NULL)
{
}

CDTPQueueFactory::~CDTPQueueFactory(void)
{
	if(m_pDTPQueue)
		delete m_pDTPQueue;
}

CDTPQueueIF* CDTPQueueFactory::GetDTPQueue(void)
{
	if(m_pDTPQueue)
		delete m_pDTPQueue;
	m_pDTPQueue = new CDTPQueue(giDTCount);
	giDTCount++;
	return m_pDTPQueue;
}
