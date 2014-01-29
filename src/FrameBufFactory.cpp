
#include ".\framebuffactory.h"
#include "FrameBuf.h"
CFrameBufFactory::CFrameBufFactory(void)
{
	m_pFrameBuf = NULL;
}

CFrameBufFactory::~CFrameBufFactory(void)
{
	if(m_pFrameBuf)
		delete m_pFrameBuf;
}
CFrameBufIF* CFrameBufFactory::GetFrameBuf(CEventManagerIF* pEventManager,unsigned int FrameWidth, unsigned int FrameLength, unsigned int BytesPerPixel, unsigned int SubFrameNum, unsigned int FrameBufNum)
{
	if(m_pFrameBuf)
	{
		delete m_pFrameBuf;
	}
    m_pFrameBuf = new CFrameBuf();
	if(m_pFrameBuf->Create(pEventManager,FrameWidth, FrameLength,BytesPerPixel,SubFrameNum,FrameBufNum))
	{
		return m_pFrameBuf;
	}
	else
	{
		return NULL;
	}
};
