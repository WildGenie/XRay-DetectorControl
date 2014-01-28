#pragma once
class CDTFrameBufIF;
class CEventManagerIF;
class CDTFrameBufFactory
{
	CDTFrameBufIF* m_pFrameBuf;
public:
	CDTFrameBufFactory(void);
	~CDTFrameBufFactory(void);
	CDTFrameBufIF* GetDTFrameBuf(CEventManagerIF* pEventManager,unsigned int FrameWidth, unsigned int FrameLength, unsigned int BytesPerPixel=2, unsigned int SubFrameNum=1, unsigned int FrameBufNum=4);
};
