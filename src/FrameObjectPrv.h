// ImageObject.h : Declaration of the CImageObject

#pragma once

class FrameObjectPrv
{
public:
    FrameObjectPrv()
	{
		m_Width = 0;
		m_Height = 0;
		m_BytesPerPixel = 2;
		m_XTable = 0;
		m_YTable = 0;
		m_DataBase = 0;
	}
	
     ~FrameObjectPrv()
	{
		if(m_XTable)
			delete [] m_XTable;
			
		if(m_YTable)
			delete [] m_YTable;
	}

public:
	
    long get_ImageDataAddress(long* pVal);
    long put_ImageDataAddress(long newVal);
    long get_Width(long* pVal);
    long get_Height(long* pVal);
    long get_BytesPerPixel(long* pVal);
    long get_Pixel(long X, long Y, long* pVal);
    long put_Pixel(long X, long Y, long newVal);

	
public:
    long Open(long Width, long Height, long BytesPerPixel);
    long get_ImageLineAddress(long LineIndex, long* pVal);
    long get_ColAverage(long* pAvg);
    long get_ColMax(long* pMax);
    long get_ColMin(long* pMin);
    long get_RowMin(long* pMin);
    long get_RowMax(long* pMax);
    long get_RowAverage(long* pAvg);
    long get_ColNoise(float* pNoise);
    long get_RowNoise(float* pNoise);

private:
    long m_Width;
    long m_Height;
    long m_BytesPerPixel;
    long* m_XTable;
    long* m_YTable;
    unsigned char* m_DataBase;

};

