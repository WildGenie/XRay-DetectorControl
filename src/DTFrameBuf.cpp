#include "StdAfx.h"
#include ".\dtframebuf.h"
#include "EventmanagerIF.h"
#include "ImageObject.h"


CDTFrameBuf::CDTFrameBuf(void)
: m_FrameWidth(0),
  m_FrameLength(0),
  m_BytesPerPixel(0),
  m_SubFrameLength(0), 
  m_FrameBufNums(0),
  m_TotalRowsNum(0),
  m_pData(NULL),
  m_pRowAddr(NULL),
  m_CurFrameRowID(0),
  m_CurSubFrameRowID(0),
  m_CurRowID(0),
  m_pEventManager(NULL),
  m_CurLinePos(0),
  m_RowSize(0),
  m_GrabFrameNumTotal(0),
  m_CurGrabFrameNum(0),
  m_pImageObject(NULL)
{

}

CDTFrameBuf::~CDTFrameBuf(void)
{
	if(m_pRowAddr)
		delete m_pRowAddr;
	if(m_pData)
		delete m_pData;
}
void CDTFrameBuf::Reset()//Reset the counter 
{
  m_CurFrameRowID = 0;
  m_CurSubFrameRowID = 0;
  m_CurRowID = 0;
}
void CDTFrameBuf::SetGrabFrameNum(unsigned int Num)//Setup hownay frame want to take
{
	//m_CurGrabFrameNum
	m_CurGrabFrameNum = 0;//Reset the CurFrameNum
	m_GrabFrameNumTotal = Num;
}
void CDTFrameBuf::AddOneFrameLine(BYTE* pSrc,unsigned int Size,BOOL bLineEnd)
{//The addline maybe call serval time for one line data, if it is the last part
	// of the line the blineend should be true
	
	m_pEventManager->OnNewDataComimg(Size);
	if(m_GrabFrameNumTotal > 0)
	{//m_GrabFrameNumTotal == 0 means continues grab no stop. >0 means grab the number of Frame
		if(m_CurGrabFrameNum >= m_GrabFrameNumTotal)
		{
			m_GrabFrameNumTotal = 0;//Reset to continues grab after this grab operation end
			return;
		}
	}
	//Check the Size with the FrameWidth, choose the smaller one as copy length
	unsigned int cpSize;
	//Determine homany bytes should copy
	unsigned int MaxSize = m_RowSize - m_CurLinePos;
	
	if(MaxSize>0)//if there is space in current line
	{
		cpSize = (Size > MaxSize) ? MaxSize:Size;

		if(bLineEnd)
		{
			cpSize = (m_FrameWidth*2 > Size) ? Size:m_FrameWidth*2;
		}
		//Copy the data the the current avalible line
		char* pCurLineAddr = (char*)m_pRowAddr[m_CurRowID] + m_CurLinePos;
		try
		{
    		memcpy(pCurLineAddr,pSrc,cpSize);
		}
		catch(...)
		{
			cpSize=0;
		}
		m_CurLinePos += cpSize;
	}
		//Update the CurLine Addr;
	if(bLineEnd)
	{
		m_CurLinePos=0;
		m_CurRowID++;
		m_CurRowID %= m_TotalRowsNum;
	//	ATLTRACE("One line ready \n");
	//	ATLTRACE("The lineID¡¡is %d\n",(m_CurRowID%m_FrameLength));
		if(0 == (m_CurRowID%m_SubFrameLength))
		{
				//Rise Event with the SubFrame ready
			m_pEventManager->OnDTSubFrameReady(m_CurSubFrameRowID%m_FrameLength,m_SubFrameLength,FALSE);
			m_CurSubFrameRowID += m_SubFrameLength;
			m_CurSubFrameRowID %= m_TotalRowsNum;
			//ATLTRACE("One Sub Frame ready \n");
			//raise event that Frame ready
		
			if(0 == (m_CurRowID%m_FrameLength))
			{
				//Rise Event With The Last SubFrame Falg of SUbFrame ready
		//		ATLTRACE("One FRAME ready \n");
				m_CurGrabFrameNum++;
				//Rise the Event with the Frameready
				ATLASSERT(m_pImageObject);
				m_pImageObject->put_ImageDataAddress((LONG)m_pRowAddr[m_CurFrameRowID]);
				m_pEventManager->OnDTFrameReady(m_pRowAddr[m_CurFrameRowID],m_RowSize*m_FrameLength);

				//	ATLTRACE("On FrameReady ENd \n");
				//Updata the FrameRowID and SubFrame RowID
				m_CurFrameRowID += m_FrameLength;
				m_CurFrameRowID %= m_TotalRowsNum;
				//If frame end the sub frame should be end too. So the m_CurFrameRowID == m_CurSubFrameRowID shoudl be correct
				ATLASSERT(m_CurFrameRowID == m_CurSubFrameRowID);
				
			}
		}
	}
}
bool CDTFrameBuf::Create(CEventManagerIF* pEventManager,unsigned int FrameWidth, unsigned int FrameLength, unsigned int BytesPerPixel, unsigned int SubFrameNum, unsigned int FrameBufNum)
{
	m_FrameWidth = FrameWidth;
  m_FrameLength = FrameLength;
  m_BytesPerPixel = BytesPerPixel;
  
  if(0 == (FrameLength%SubFrameNum))
  {
	m_SubFrameLength = FrameLength/SubFrameNum; 
  }
  else
  {
	  m_SubFrameLength = FrameLength;
  }
  m_FrameBufNums = FrameBufNum; 
  
  m_pEventManager = pEventManager;
	//Allocate the buffer from Heap size = FrameWidth*FrameLegnth*BytesPerPixel
	//Assign the memory to m_pData;
	//Set the m_CurFrameAddr= m_pCurSubFramAddr = m_pData;
  m_TotalRowsNum = m_FrameLength*m_FrameBufNums;
  m_RowSize = m_FrameWidth*m_BytesPerPixel;
  m_pData = new BYTE[m_RowSize*m_BytesPerPixel*m_TotalRowsNum];
  if( NULL == m_pData )
	  return FALSE;
  m_pRowAddr = new PBYTE[m_FrameLength*m_FrameBufNums];
  WORD RowSize = m_FrameWidth * m_BytesPerPixel;
  for(unsigned int i=0;i<m_FrameLength*m_FrameBufNums;i++)
  {
		m_pRowAddr[i] = m_pData + i*RowSize;
  }
  /*
  m_CurFrameRowID = 0;
  m_CurSubFrameRowID = 0;
  m_CurRowID = 0;*/
  Reset();
  return TRUE;
  
}

unsigned int CDTFrameBuf::GetFrameWidth()
{
	return m_FrameWidth;
}
unsigned int CDTFrameBuf::GetFrameLength()
{
	return m_FrameLength;
}
unsigned int CDTFrameBuf::GetBytesPerPixel()
{
	return m_BytesPerPixel;
}
void CDTFrameBuf::SetImageObject(IImageObject* pImageObject)
{
	m_pImageObject = pImageObject;
	if (m_pImageObject!=NULL)
	{
	    m_pImageObject->put_ImageDataAddress((LONG)m_pRowAddr[m_CurFrameRowID]);
	}
}