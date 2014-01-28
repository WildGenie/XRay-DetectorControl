#include "StdAfx.h"
#include ".\dtframebuffactory.h"
#include "DTFrameBuf.h"
CDTFrameBufFactory::CDTFrameBufFactory(void)
{
	m_pFrameBuf = NULL;
}

CDTFrameBufFactory::~CDTFrameBufFactory(void)
{
	if(m_pFrameBuf)
		delete m_pFrameBuf;
}
CDTFrameBufIF* CDTFrameBufFactory::GetDTFrameBuf(CEventManagerIF* pEventManager,unsigned int FrameWidth, unsigned int FrameLength, unsigned int BytesPerPixel, unsigned int SubFrameNum, unsigned int FrameBufNum)
{
	if(m_pFrameBuf)
	{
		delete m_pFrameBuf;
	}
	m_pFrameBuf = new CDTFrameBuf();
	if(m_pFrameBuf->Create(pEventManager,FrameWidth, FrameLength,BytesPerPixel,SubFrameNum,FrameBufNum))
	{
		return m_pFrameBuf;
	}
	else
	{
		return NULL;
	}
};
