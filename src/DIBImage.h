#pragma once
//CDIBImage maintain a DIB Bitmap which be used for draw image
//Include the image data buffer and Pallete
class CDIBImage
{
private:
	HBITMAP m_hBMP;
	BITMAPINFO* m_pBMI;
	BYTE* m_pData_Buf;
	LONG m_iBytesPerPixel;
	LONG m_Height;
	LONG m_Width;
	BOOL m_bOpened;
private:

public:
	CDIBImage(void);
	BOOL Create(LONG Width,LONG Height);//Allocate the image buffer
	void Close();
	BOOL IsNull();
	BYTE* GetBits();//Return the m_pData_Buf
	void Draw(HDC hDC,LPRECT pDestRect,LONG StartLine,LONG EndLine);
	void Draw(HDC hDC,LPRECT pDestRect);
	BOOL Load(LPSTR pPath);
	BOOL Save(LPSTR pPath);
	LONG GetHeight();
	LONG GetWidth();
	~CDIBImage(void);
};
