#pragma once
class CFrameBufIF;
class CEventManagerIF;
class CFrameBufFactory
{
    CFrameBufIF* m_pFrameBuf;
public:
    CFrameBufFactory(void);
    ~CFrameBufFactory(void);
    CFrameBufIF* GetFrameBuf(CEventManagerIF* pEventManager,unsigned int FrameWidth, unsigned int FrameLength, unsigned int BytesPerPixel=2, unsigned int SubFrameNum=1, unsigned int FrameBufNum=4);
};
