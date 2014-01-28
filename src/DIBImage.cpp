#include "StdAfx.h"
#include ".\dibimage.h"
#include "atlimage.h"
CDIBImage::CDIBImage(void)
{
	m_iBytesPerPixel =3;
	m_pData_Buf = NULL;
	m_pBMI = NULL;
	m_Height = 0;
	m_Width = 0;
	m_bOpened = FALSE;
}

CDIBImage::~CDIBImage(void)
{
	Close();
}
void CDIBImage::Close()
{
	if(m_pData_Buf)
		delete m_pData_Buf;
	if(m_pBMI)
		delete m_pBMI;
	m_pData_Buf = NULL;
	m_pBMI = NULL;
	m_Height = 0;
	m_Width = 0;
	m_bOpened = FALSE;
}
BOOL CDIBImage::Create(LONG Width,LONG Height)//Allocate the image buffer
{
	Close();

	m_pData_Buf = new BYTE[Width*Height*m_iBytesPerPixel];
	ATLASSERT(m_pData_Buf);
	if(NULL == m_pData_Buf)
	{
		Close();
		return FALSE;
	}

	m_pBMI = (BITMAPINFO*)new BYTE[sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD)];
	ATLASSERT(m_pBMI);
	if(NULL == m_pBMI)
	{
		Close();
		return FALSE;
	}
	m_Height = Height;
	m_Width = Width;
	m_pBMI->bmiHeader.biBitCount = 8;
	m_pBMI->bmiHeader.biClrImportant = 0;
	m_pBMI->bmiHeader.biCompression = 0;
	m_pBMI->bmiHeader.biHeight = m_Height;
	m_pBMI->bmiHeader.biClrUsed =256;
	m_pBMI->bmiHeader.biPlanes = 1;
	m_pBMI->bmiHeader.biSize = 40;
	m_pBMI->bmiHeader.biSizeImage = 0;//m_iHeight*m_iWidth;
	m_pBMI->bmiHeader.biWidth = m_Width;//m_iWidth;
	m_pBMI->bmiHeader.biXPelsPerMeter = 0;
	m_pBMI->bmiHeader.biYPelsPerMeter =0;
//here set the palette
	for(int i = 0; i<256;i++)
	{
		m_pBMI->bmiColors[i].rgbBlue =i;
		m_pBMI->bmiColors[i].rgbGreen =i;
		m_pBMI->bmiColors[i].rgbRed =i;
		m_pBMI->bmiColors[i].rgbReserved = 0;
	}
	m_bOpened = TRUE;
	return TRUE;
}
BOOL CDIBImage::IsNull()
{
	return !m_bOpened;
}
BYTE* CDIBImage::GetBits()//Return the m_pData_Buf
{
	return m_pData_Buf;
}
void CDIBImage::Draw(HDC hDC,LPRECT pDestRect)
{
	Draw(hDC,pDestRect,0,m_Height);
}
void CDIBImage::Draw(HDC hDC,LPRECT pDestRect,LONG StartLine,LONG EndLine)
{
	if(hDC)
	{
		int Height = EndLine -StartLine;
		m_pBMI->bmiHeader.biHeight = Height;
		m_pBMI->bmiHeader.biSizeImage = Height*m_Width;
		ATLASSERT(Height>0);
		::StretchDIBits(hDC,pDestRect->left,
			pDestRect->top,pDestRect->right - pDestRect->left,
			pDestRect->bottom - pDestRect->top,
			0,0,m_Width,Height,
			m_pData_Buf+(m_Height-EndLine)*m_Width,m_pBMI,DIB_RGB_COLORS,SRCCOPY);	
	}
}
BOOL CDIBImage::Save(LPSTR pPath)
{
	return TRUE;
}
BOOL CDIBImage::Load(LPSTR pPath)
{
	Close();
	CImage img;
	img.Load(pPath);
	void* pData = img.GetBits();
	m_Width= img.GetWidth();
	m_Height = img.GetHeight();
	m_iBytesPerPixel = img.GetBPP()/8;
	m_pBMI = (BITMAPINFO*)new BYTE[sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD)];
	ATLASSERT(m_pBMI);
	if(NULL == m_pBMI)
	{
		Close();
		return FALSE;
	}
	m_pBMI->bmiHeader.biBitCount = img.GetBPP();
	m_pBMI->bmiHeader.biClrImportant = 0;
	m_pBMI->bmiHeader.biCompression = 0;
	m_pBMI->bmiHeader.biHeight = m_Height;
	m_pBMI->bmiHeader.biClrUsed =256;
	m_pBMI->bmiHeader.biPlanes = 1;
	m_pBMI->bmiHeader.biSize = 40;
	m_pBMI->bmiHeader.biSizeImage = 0;//m_iHeight*m_iWidth;
	m_pBMI->bmiHeader.biWidth = m_Width;//m_iWidth;
	m_pBMI->bmiHeader.biXPelsPerMeter = 0;
	m_pBMI->bmiHeader.biYPelsPerMeter =0;
//here set the palette
	for(int i = 0; i<256;i++)
	{
		m_pBMI->bmiColors[i].rgbBlue =i;
		m_pBMI->bmiColors[i].rgbGreen =i;
		m_pBMI->bmiColors[i].rgbRed =i;
		m_pBMI->bmiColors[i].rgbReserved = 0;
	}
	int pitch = img.GetPitch();
	m_pData_Buf = new BYTE[abs(pitch)*m_Height];

	if(pitch>0)
	{
		memcpy(m_pData_Buf,pData,pitch);
	}
	else
	{
		pData = (void*)((ULONG)pData  - abs(pitch)*(m_Height-1)); 
		memcpy(m_pData_Buf,pData,abs(pitch)*(m_Height));
	}
	m_bOpened = TRUE;

	return TRUE;
}
LONG CDIBImage::GetHeight()
{
	return m_Height;
}
LONG CDIBImage::GetWidth()
{
	return m_Width;
}