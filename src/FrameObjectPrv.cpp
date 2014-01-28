// ImageObject.cpp : Implementation of CImageObject
#include "../stdafx.h"
#include ".\FrameObjectPrv.h"




long FrameObjectPrv::get_ImageDataAddress(long* pVal)
{
	// TODO: Add your implementation code here
	*pVal = (long)m_DataBase;
	return 0;
}
long FrameObjectPrv::put_ImageDataAddress(long newVal)
{
	// TODO: Add your implementation code here
	//Update the image pointer when the frame ready
	m_DataBase = (BYTE*)newVal;
    return 0;
}

long FrameObjectPrv::get_Width(long* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_Width;
	return 0;
}

long FrameObjectPrv::get_Height(long* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_Height;
	return 0;
}

long FrameObjectPrv::get_BytesPerPixel(long* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_BytesPerPixel;
	return 0;
}

long FrameObjectPrv::get_Pixel(long X, long Y, long* pVal)
{
	// TODO: Add your implementation code here
	switch(m_BytesPerPixel)
	{
		case 2:
			*pVal = *((WORD*)(m_DataBase+m_YTable[Y]+m_XTable[X]));
			break;
		case 1:
			*pVal = *((BYTE*)(m_DataBase+m_YTable[Y]+m_XTable[X]));
			break;
	} 
	return 0;
}

long FrameObjectPrv::put_Pixel(long X, long Y, long newVal)
{

	switch(m_BytesPerPixel)
	{
	case 2:
		*(WORD*)(&(m_DataBase[m_YTable[Y]+m_XTable[X]])) = (WORD)newVal;
		break;
	case 1:
		m_DataBase[m_YTable[Y]+m_XTable[X]] = (BYTE)newVal;
		break;
	}
	return 0;
}

long FrameObjectPrv::Open(long Width, long Height, long BytesPerPixel)
{

	m_Width = Width;
	m_Height = Height;
	m_BytesPerPixel = BytesPerPixel;
	if(m_XTable)
		delete [] m_XTable ;
	m_XTable = new long [m_Width];
	if(m_YTable)
		delete [] m_YTable ;
	m_YTable = new long [m_Height];
	for(int i = 0; i<m_Width;i++)
	{
		m_XTable[i] = i*m_BytesPerPixel; 
	}
	for(int i = 0; i<m_Height;i++)
	{
		m_YTable[i] = i*m_Width*m_BytesPerPixel;
	}
	return 0;
}

long FrameObjectPrv::get_ImageLineAddress(long LineIndex, long* pVal)
{
	*pVal = m_YTable[LineIndex]+(long)m_DataBase;
	return 0;
}


long FrameObjectPrv::get_ColAverage(long* pAvg)
{
	// TODO: Add your implementation code here

	return 0;
}

long FrameObjectPrv::get_ColMax(long* pMax)
{
	// TODO: Add your implementation code here

	return 0;
}

long FrameObjectPrv::get_ColMin(long* pMin)
{
	// TODO: Add your implementation code here

	return 0;
}

long FrameObjectPrv::get_RowMin(long* pMin)
{
	// TODO: Add your implementation code here

	return 0;
}

long FrameObjectPrv::get_RowMax(long* pMax)
{
	// TODO: Add your implementation code here

	return 0;
}

long FrameObjectPrv::get_RowAverage(long* pAvg)
{
	// TODO: Add your implementation code here

	return 0;
}

long FrameObjectPrv::get_ColNoise(float* pNoise)
{
	// TODO: Add your implementation code here

	return 0;
}

long FrameObjectPrv::get_RowNoise(FLOAT* pNoise)
{
	// TODO: Add your implementation code here

	return 0;
}
