#pragma once
#include "ImageObject.h"
class CEventManagerIF;

class CDTFrameBufIF
{
public:
	CDTFrameBufIF(void);
	virtual ~CDTFrameBufIF(void);
	virtual bool Create(CEventManagerIF* pEventManager,unsigned int FrameWidth, unsigned int FrameLength, unsigned int BytesPerPixel, unsigned int SubFrameNum, unsigned int FrameBufNum) = 0;
	virtual void AddOneFrameLine(BYTE* pSrc, unsigned int Size,BOOL bLineEnd) = 0;

	virtual void SetGrabFrameNum(unsigned int Num)=0;//Set want to grab how many frames
	virtual unsigned int GetFrameWidth()=0;
	virtual unsigned int GetFrameLength()=0;
	virtual unsigned int GetBytesPerPixel()=0;
	virtual void SetImageObject(IImageObject* pImageObject)=0;
	virtual void Reset()=0;
};
