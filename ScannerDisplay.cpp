// ScannerDisplay.cpp : CScannerDisplay 的实现
#include "stdafx.h"
#include "ScannerDisplay.h"

#include <math.h>
#include <comutil.h>
#include "ScannerImage.h"
#include "Wingdi.h"
#include "Windows.h"
#include <omp.h>


// CScannerDisplay

#define DISP_BLANK_H	20
#define DISP_BLANK_W	20
#define DISP_ORG_X		10
#define DISP_ORG_Y		10
#define DISP_SCROLL_W	10

STDMETHODIMP CScannerDisplay::put_ImgWidth(ULONG newVal)
{
	// TODO: Add your implementation code here
	m_Width = newVal;
	return S_OK;
}

STDMETHODIMP CScannerDisplay::get_ImgHeight(ULONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_Height;
	return S_OK;
}

STDMETHODIMP CScannerDisplay::put_ImgHeight(ULONG newVal)
{
	// TODO: Add your implementation code here
	m_Height = newVal;
	return S_OK;
}
STDMETHODIMP CScannerDisplay::get_ImgWidth(ULONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_Width;
	return S_OK;
}
STDMETHODIMP CScannerDisplay::get_Gamma(FLOAT* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_Gamma;
	return S_OK;
}

STDMETHODIMP CScannerDisplay::put_Gamma(FLOAT newVal)
{
	// TODO: Add your implementation code here
	newVal = m_Gamma;
//	SetWindowing();
	return S_OK;
}

STDMETHODIMP CScannerDisplay::get_MapStart(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_mapStart;

	return S_OK;
}

STDMETHODIMP CScannerDisplay::put_MapStart(LONG newVal)
{
	// TODO: Add your implementation code here
	m_mapStart = newVal;
	if(m_mapStart < 0)
		m_mapStart = 0;
	if(m_mapStart > MAX_ADC)
		m_mapStart = MAX_ADC;
	SetWindowing();
	return S_OK;
}

STDMETHODIMP CScannerDisplay::get_MapEnd(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_mapEnd;
	return S_OK;
}

STDMETHODIMP CScannerDisplay::put_MapEnd(LONG newVal)
{
	// TODO: Add your implementation code here
	if(m_mapEnd < 0)
		m_mapEnd = 0;
	if(m_mapEnd > MAX_ADC)
		m_mapEnd = MAX_ADC;

	m_mapEnd = newVal;
	SetWindowing();
	return S_OK;
}
STDMETHODIMP CScannerDisplay::get_DataSource(IUnknown** pVal)
{
	// TODO: Add your implementation code here
	if(m_pDataSrc)
	{
		m_pDataSrc->QueryInterface(IID_IUnknown,(void**)pVal); 
	}
	else
	{
		*pVal = NULL;
	}
	return S_OK;
}

STDMETHODIMP CScannerDisplay::put_DataSource(IUnknown* newVal)
{
	// Get the image source image buffer address and connnect the event sink
	if(newVal)
	{
		LONG val = (LONG)newVal;
		ConnectDataSrc(((CScannerImage*)val));
	}
	else
	{
		DisConnectDataSrc();
		return S_OK;
	}
	return S_OK;
}


STDMETHODIMP CScannerDisplay::Open(LONG* bOK)
{
	// TODO: Add your implementation code here
	//Create the m_pImageDipslay

	if(m_pDataSrc == NULL)
	{
		*bOK = FALSE;
		m_bOpened = FALSE;
		return S_OK;
	}
	if(m_bOpened)
	{
		Close();
	}
	if(0==m_Width)
	{
		m_pDataSrc->get_ImgWidth(&m_Width);
	}
	
	if(0==m_Height)
	{
		m_pDataSrc->get_ImgHeight(&m_Height);
	}
	//Create internal Display buf
		HRESULT hr = ::CoCreateInstance(CLSID_FrameObject,NULL,CLSCTX_ALL,IID_IFrameObject,(LPVOID*) &m_pDisplayObject);
		if(FAILED(hr))
		{
			_com_error err(hr);
			MessageBox(err.ErrorMessage(),NULL);
			*bOK = FALSE;
			m_bOpened = FALSE;
			return S_OK;
		}
		
	AllocateImgBuffer(m_Width,m_Height);
//Put Image Object
	IUnknown* pUI;
	m_pDataSrc->get_ImageObject(&pUI);
	pUI->QueryInterface(IID_IFrameObject,(void**)&m_pImageSrcObject);
	m_pImageSrcObject->AddRef();

	m_bOpened = TRUE;
	if(m_RefreshRate)
	{
		SetTimer(1001,m_RefreshRate,NULL);
	}
	SetScale();
	*bOK = TRUE;
	return S_OK;
}
STDMETHODIMP CScannerDisplay::Close(void)
{
	// TODO: Add your implementation code here
	//Unconnect the data source and display control if there is 
	//Release m_pImageDisplay
	put_DataSource(NULL);
	if(m_pDisplayObject)
	{
		m_pDisplayObject->Release();
		m_pDisplayObject = NULL;
	}
	if(m_pImageSrcObject)
	{
		m_pImageSrcObject->Release();
		m_pImageSrcObject=NULL;
	}
	ReleaseImgBuffer();

	m_bOpened = FALSE;
	return S_OK;
}
STDMETHODIMP CScannerDisplay::get_RefreshMode(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_RefreshMode ;
	return S_OK;
}

STDMETHODIMP CScannerDisplay::put_RefreshMode(LONG newVal)
{
	// TODO: Add your implementation code here
	m_RefreshMode = newVal;
	return S_OK;
}

STDMETHODIMP CScannerDisplay::get_RefreshRate(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_RefreshRate ;
	return S_OK;
}

STDMETHODIMP CScannerDisplay::put_RefreshRate(LONG newVal)
{
	// TODO: Add your implementation code here
	m_RefreshMode = newVal;
	return S_OK;
}

STDMETHODIMP CScannerDisplay::get_ImageObject(IUnknown** pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_pDisplayObject;
	//m_pDisplayObject->AddRef();
	return S_OK;
}

STDMETHODIMP CScannerDisplay::get_DisplayScale(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_Scale;
	return S_OK;
}

STDMETHODIMP CScannerDisplay::put_DisplayScale(LONG newVal)
{
	// TODO: Add your implementation code here
	m_Scale = newVal;
	SetScale();
//	Refresh();
	return S_OK;
}
STDMETHODIMP CScannerDisplay::Refresh(void)
{
		//Do the LUT Map
	PostMessage(WM_DISPLAY_REFRESH);
	return S_OK;
}

STDMETHODIMP CScannerDisplay::RepaintDisplay(void)
{
    //Do LUT
	if(m_bOpened) {
		LUTMap(0,m_Height,FALSE);//Refresh WHole Frame
		PostMessage(WM_DISPLAY_REFRESH);
	}
	PostMessage(WM_DISPLAY_REFRESH);
	return S_OK;
}

STDMETHODIMP CScannerDisplay::get_OrgPoint_X(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_Org_X;
	return S_OK;
}

STDMETHODIMP CScannerDisplay::put_OrgPoint_X(LONG newVal)
{
	// TODO: Add your implementation code here
	m_Org_X = newVal; 
	return S_OK;
}

STDMETHODIMP CScannerDisplay::get_OrgPoint_Y(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_Org_X;
	return S_OK;
}

STDMETHODIMP CScannerDisplay::put_OrgPoint_Y(LONG newVal)
{
	// TODO: Add your implementation code here
	m_Org_Y = newVal;
	return S_OK;
}

STDMETHODIMP CScannerDisplay::get_ObjectHandle(IUnknown** pVal)
{
	// TODO: Add your implementation code here
	this->QueryInterface(IID_IUnknown,(void**) pVal);
	return S_OK;
}

STDMETHODIMP CScannerDisplay::Load(BSTR FilePath)
{
	// TODO: Add your implementation code here
	if(m_bOpened )
	{
		Close();
	}
	
	CHAR* pPath = _com_util::ConvertBSTRToString(FilePath);
	m_DisplayImage.Load(pPath);
	//m_DisplayImage.Load("D:\\testpattern.jpg");
	if(!m_DisplayImage.IsNull())
	{
		m_bOpened = TRUE;
		m_Height = m_DisplayImage.GetHeight();
		m_Width = m_DisplayImage.GetWidth();
		SetScale();
		Refresh();
	}
	return S_OK;
}

STDMETHODIMP CScannerDisplay::Save(BSTR FilePath)
{
	// TODO: Add your implementation code here
	CHAR* pPath = _com_util::ConvertBSTRToString(FilePath);
	m_DisplayImage.Save(pPath);
	return S_OK;
}
/****************************Service Funtion**********************/
void CScannerDisplay::ReleaseImgBuffer()
{
	if(m_pTempBuf)
	{
		delete [] m_pTempBuf;
		m_pTempBuf = NULL;
		m_DisplayImage.Close();
	}
}
void CScannerDisplay::AllocateImgBuffer(LONG Width,LONG Height)
{
	m_DisplayImage.Create(m_Width,m_Height);
	m_pTempBuf = new BYTE[m_Width*m_Height];
	m_pDisplayObject->Open(m_Width,m_Height,1);
	m_pDisplayObject->put_ImageDataAddress((LONG)m_DisplayImage.GetBits());
}
void  CScannerDisplay::SetScale()
 {
	SetScrollExtend();
	SetScrollInfo();
	if(::IsWindow(m_hWnd))
	{
		Invalidate();
	}
 }
 void CScannerDisplay::SetScrollExtend()
{
	if(::IsWindow(m_hWnd))
	{
		RECT rc;
		GetClientRect(&rc);
			m_xMinScroll = 0;       // minimum horizontal scroll value 
			m_xCurrentScroll = 0;   // current horizontal scroll value 
			m_xMaxScroll = 0;       // maximum horizontal scroll value 
	 
	// These variables are required for vertical scrolling. 
	 
			m_yMinScroll = 0;       // minimum vertical scroll value 
			m_yCurrentScroll = 0;   // current vertical scroll value 
			m_yMaxScroll = 0;       // maximum vertical scroll value 
 		if(0 == m_Scale)
		{
			m_WndHeight = rc.bottom - rc.top;
			m_WndWidth = rc.right - rc.left;
		}
		else
		{//The Content size thould the bigger one of Windows' client area and the Image Size
			m_WndHeight = m_Height*sqrt((float)m_Scale) + DISP_BLANK_H;
			if(m_WndHeight<(rc.bottom - rc.top))
				m_WndHeight = rc.bottom - rc.top;
			m_WndWidth = m_Width*sqrt((float)m_Scale) + DISP_BLANK_W;
			if(m_WndWidth < (rc.right - rc.left))
				m_WndWidth = rc.right - rc.left;
		}
		//After the range determined, select the proper bitmap
		HBITMAP hBitmap = CreateCompatibleBitmap(this->GetDC(),m_WndWidth, m_WndHeight);
		HBITMAP OldBitMap = (HBITMAP)SelectObject( m_hMemDC, hBitmap );
		RECT rect;
		rect.top = 0;
		rect.left = 0;
		rect.bottom = m_WndHeight;
		rect.right = m_WndWidth;
		FillRect(m_hMemDC,&rect,(HBRUSH)GetStockObject(WHITE_BRUSH));
		DeleteObject(OldBitMap);  
		SetDrawRect();
	}
}

void CScannerDisplay::SetDrawRect()
{
	int WndHeight = m_WndHeight-DISP_BLANK_H;
	int WndWidth = m_WndWidth-DISP_BLANK_W;
	int MidWidth = m_WndWidth/2;
	int MidHeight = m_WndHeight/2;
	float scaleWnd = ((float)(WndHeight))/WndWidth;
	float scaleImg = ((float)(m_Height))/m_Width;
	int Width ;
	int Height;
	if(scaleWnd>scaleImg)
	{
		Width =  WndWidth;
		Height = ((float)Width * scaleImg) ;
	}
	else
	{
		Height =  WndHeight ;
		Width = ((float)Height / scaleImg) ;
	}
	m_DrawRect.right = MidWidth+Width/2;
	m_DrawRect.left = MidWidth - Width/2;
	m_DrawRect.top = MidHeight - Height/2;
	m_DrawRect.bottom = MidHeight + Height/2;
	m_SrcRect.left = 0;
	m_SrcRect.top = 0;
	m_SrcRect.right = m_Width;
	m_SrcRect.bottom = m_Height;
}
void CScannerDisplay::SetScrollInfo()
{
	if(::IsWindow(m_hWnd))
	{
		RECT rc;
		GetClientRect(&rc);
		int PageWidth = rc.right - rc.left;
		int PageHeight = rc.bottom - rc.top;

		if(PageWidth == m_WndWidth)
		{
			::ShowScrollBar(this->m_hWnd, SB_HORZ,FALSE);
		}
		else
		{
			m_xMaxScroll = max(m_WndWidth, 0); 
			m_xCurrentScroll = min(m_xCurrentScroll, m_xMaxScroll); 
			m_si.cbSize = sizeof(m_si); 
			m_si.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS; 
			m_si.nMin   = m_xMinScroll; 
			m_si.nMax   = m_xMaxScroll; 
			m_si.nPage  = PageWidth; 
			m_si.nPos   = m_xCurrentScroll; 
			::SetScrollInfo(this->m_hWnd, SB_HORZ, &m_si, TRUE); 
		} 
        // The vertical scrolling range is defined by 
        // (bitmap_height) - (client_height). The current vertical 
        // scroll value remains within the vertical scrolling range. 
 		if(PageHeight == m_WndHeight)
		{
			::ShowScrollBar(this->m_hWnd, SB_VERT,FALSE);
		}
		else
		{
			m_yMaxScroll = max(m_WndHeight , 0); 
			m_yCurrentScroll = min(m_yCurrentScroll, m_yMaxScroll); 
			m_si.cbSize = sizeof(m_si); 
			m_si.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS; 
			m_si.nMin   = m_yMinScroll; 
			m_si.nMax   = m_yMaxScroll; 
			m_si.nPage  = PageHeight; 
			m_si.nPos   = m_yCurrentScroll; 
			::SetScrollInfo(this->m_hWnd, SB_VERT, &m_si, TRUE); 
		}
	}
}

void CScannerDisplay::InitializeLUT()
{		
		m_Gamma = 1.0;
		m_mapStart = 0;
		m_mapEnd = 3000;
		for(int i=0;i<256;i++)
		{
			m_ColorTable[i].rgbBlue = i;
			m_ColorTable[i].rgbGreen = i;
			m_ColorTable[i].rgbRed = i;
			m_ColorTable[i].rgbReserved = 0;
		}
		SetWindowing();
}


void CScannerDisplay::SetWindowing()
{
	
	int map_extend;
	map_extend = abs(m_mapEnd-m_mapStart);
	if((m_mapStart>MAX_ADC)||(m_mapEnd > MAX_ADC))
	{//if start or end more than MAX_ADC, then need increase the MAC_ADC
		m_mapStart %= MAX_ADC; 
		m_mapEnd %= MAX_ADC;
	}
	//(MAX_GRAY- MIN_GRAY)
	int i;
	if(m_mapStart <= m_mapEnd)
	{
		for(i=0;i<=m_mapStart;i++)
		{
			m_LUT[i] = 0;
		}
		for(i=m_mapEnd;i<MAX_ADC;i++)
		{
			m_LUT[i] = 255;
		};
		for( i=m_mapStart;i<m_mapEnd;i++)
		{
			int extend = 255;
			float fscale = ((float)(i-m_mapStart))/map_extend ;
			m_LUT[i] = pow( fscale,m_Gamma)*extend;
		}
	}
	else//Start > End
	{
		for(i=m_mapStart;i<MAX_ADC;i++)
		{
			m_LUT[i] = 0;
		}
		for(i=0;i<=m_mapEnd;i++)
		{
			m_LUT[i] = 255;
		};
		for(i=m_mapEnd;i<m_mapStart;i++)
		{
			int extend = 255;
			float fscale = (float)(i-m_mapEnd)/map_extend ;
			m_LUT[m_mapStart-i+m_mapEnd] = pow( fscale,m_Gamma)*extend;
		}
	}
}

void CScannerDisplay::LUTMap(LONG StartLine, LONG NumLines,BOOL bMoving)
{//Map 16 bit to 8 bits
	//The statline is the startline in the display
	m_displayCs.Lock();
	LONG Index;
	if(!bMoving)
	{
//		for(unsigned int j = StartLine;j<StartLine+NumLines;j++)
		int YBase = StartLine;
#pragma omp parallel for 
		for(int j = 0;j<NumLines;j++)
		{
			long bytes = 0;
			m_pImageSrcObject->get_BytesPerPixel(&bytes);
			if(bytes == 2) {
				long Addr = 0 ;
				m_pImageSrcObject->get_ImageLineAddress(m_Org_Y + j +YBase, &Addr);
				WORD* pSrc = (WORD*) Addr;
				m_pDisplayObject->get_ImageLineAddress(j + YBase, &Addr);
				BYTE* pDest = (BYTE*) Addr;
				for (int i = 0; i < m_Width; i++) {
					pDest[i] = m_LUT[pSrc[m_Org_X+i]];	
				}
			} else {
				for(unsigned int i= 0;i<m_Width;i++)
				{
					m_pImageSrcObject->get_Pixel(m_Org_X+i,m_Org_Y+j+YBase,&Index);
					m_pDisplayObject->put_Pixel(i,YBase+j,m_LUT[Index]);
				}
			}

		}
	}
	else
	{
		//Move the previous data
		LONG pSrc; 
		m_pDisplayObject->get_ImageDataAddress(&pSrc);
		memcpy((void*)m_pTempBuf ,(void*)pSrc, m_Width* (m_Height-NumLines));
		LONG pDest;
		m_pDisplayObject->get_ImageLineAddress(NumLines,&pDest);
		memcpy((void*)pDest, (void*)m_pTempBuf ,m_Width* (m_Height-NumLines));
		//Update the last block
		int BaseY=m_Org_Y+StartLine;
		for(int j = 0;j<NumLines;j++)
		{
			for(int i= 0;i<m_Width;i++)
			{
				m_pImageSrcObject->get_Pixel(m_Org_X+i,BaseY+j,&Index);
				m_pDisplayObject->put_Pixel(i,NumLines - j -1,m_LUT[Index]);
			}
		}
	}
	m_displayCs.Unlock();
}
/***********************************Message Handle***************************/
LRESULT CScannerDisplay::OnHScroll(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
        int xDelta;     // xDelta = new_pos - current_pos  
        int xNewPos;    // new position 
        int yDelta = 0; 
		RECT rc;
		GetClientRect(&rc);
        switch (LOWORD(wParam)) 
        { 
            // User clicked the shaft left of the scroll box. 
 
            case SB_PAGEUP: 
                xNewPos = m_xCurrentScroll - 50; 
                break; 
 
            // User clicked the shaft right of the scroll box. 
 
            case SB_PAGEDOWN: 
                xNewPos = m_xCurrentScroll + 50; 
                break; 
 
            // User clicked the left arrow. 
 
            case SB_LINEUP: 
                xNewPos = m_xCurrentScroll - 5; 
                break; 
 
            // User clicked the right arrow. 
 
            case SB_LINEDOWN: 
                xNewPos = m_xCurrentScroll + 5; 
                break; 
 
            // User dragged the scroll box. 
 
            case SB_THUMBPOSITION: 
                xNewPos = HIWORD(wParam); 
                break; 
 
            default: 
                xNewPos = m_xCurrentScroll; 
        } 
 
        // New position must be between 0 and the screen width. 
 
        xNewPos = max(0, xNewPos); 
		xNewPos = min(m_xMaxScroll-(rc.right-rc.left), xNewPos); 
 
        // If the current position does not change, do not scroll.
 
        if (xNewPos == m_xCurrentScroll) 
            return 0; 
 
        // Determine the amount scrolled (in pixels). 
 
        xDelta = xNewPos - m_xCurrentScroll; 
 
        // Reset the current scroll position. 
 
        m_xCurrentScroll = xNewPos; 
 
        // Scroll the window. (The system repaints most of the 
        // client area when ScrollWindowEx is called; however, it is 
        // necessary to call UpdateWindow in order to repaint the 
        // rectangle of pixels that were invalidated.) 
 
		::ScrollWindowEx(this->m_hWnd, -xDelta, -yDelta, (CONST RECT *) NULL, 
            (CONST RECT *) NULL, (HRGN) NULL, (LPRECT) NULL, 
            SW_INVALIDATE); 
		::UpdateWindow(this->m_hWnd); 
 
        // Reset the scroll bar. 
 
        m_si.cbSize = sizeof(m_si); 
        m_si.fMask  = SIF_POS; 
        m_si.nPos   = m_xCurrentScroll; 
		::SetScrollInfo(this->m_hWnd, SB_HORZ, &m_si, TRUE); 
		
	return 0;
}

LRESULT CScannerDisplay::OnVScroll(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
      int xDelta = 0; 
      int yDelta;     // yDelta = new_pos - current_pos 
      int yNewPos;    // new position 
		RECT rc;
		GetClientRect(&rc);
    switch (LOWORD(wParam)) 
    { 
        // User clicked the shaft above the scroll box. 

        case SB_PAGEUP: 
            yNewPos = m_yCurrentScroll - 50; 
            break; 

        // User clicked the shaft below the scroll box. 

        case SB_PAGEDOWN: 
            yNewPos = m_yCurrentScroll + 50; 
            break; 

        // User clicked the top arrow. 

        case SB_LINEUP: 
            yNewPos = m_yCurrentScroll - 5; 
            break; 

        // User clicked the bottom arrow. 

        case SB_LINEDOWN: 
            yNewPos = m_yCurrentScroll + 5; 
            break; 

        // User dragged the scroll box. 

        case SB_THUMBPOSITION: 
            yNewPos = HIWORD(wParam); 
            break; 

        default: 
            yNewPos = m_yCurrentScroll; 
    } 

    // New position must be between 0 and the screen height. 

    yNewPos = max(0, yNewPos); 
	yNewPos = min(m_yMaxScroll - (rc.bottom-rc.top), yNewPos); 

    // If the current position does not change, do not scroll.

    if (yNewPos == m_yCurrentScroll) 
        return 0; 

    // Determine the amount scrolled (in pixels). 

    yDelta = yNewPos - m_yCurrentScroll; 

    // Reset the current scroll position. 

    m_yCurrentScroll = yNewPos; 

    // Scroll the window. (The system repaints most of the 
    // client area when ScrollWindowEx is called; however, it is 
    // necessary to call UpdateWindow in order to repaint the 
    // rectangle of pixels that were invalidated.) 

	::ScrollWindowEx(this->m_hWnd, -xDelta, -yDelta, (CONST RECT *) NULL, 
        (CONST RECT *) NULL, (HRGN) NULL, (LPRECT) NULL, 
        SW_INVALIDATE); 
	::UpdateWindow(this->m_hWnd); 

    // Reset the scroll bar. 

    m_si.cbSize = sizeof(m_si); 
    m_si.fMask  = SIF_POS; 
    m_si.nPos   = m_yCurrentScroll; 
	::SetScrollInfo(this->m_hWnd, SB_VERT, &m_si, TRUE); 
	return 0;
}

LRESULT CScannerDisplay::OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// Refresh the image data here
	if(m_bOpened)
		Refresh();
	return 0;
}

LRESULT CScannerDisplay::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	if(m_bOpened)
		Close();
	ReleaseDC(m_hMemDC);
	return 0;
}
LRESULT CScannerDisplay::OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	if(!m_bOpened)
		return 0;
	LONG Value = 0;
	//Convert the Mouse coordinate the the Pixel Col and Row
	POINT pt;
	pt.x = LOWORD(lParam); 
	pt.y  = HIWORD(lParam); 
	DPtoLP(this->GetDC(),&pt,1);

	if(m_pDataSrc)
	{
		//Gett he value from the data source
		m_pImageSrcObject->get_Pixel(pt.x ,pt.y ,&Value);
	}
	this->MousePixelInfo(pt.x ,pt.y,Value);
	return 0;
}
LRESULT CScannerDisplay::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	BOOL bRunTime;
	GetAmbientUserMode(bRunTime);
	if(bRunTime)
	{
		SetScrollExtend();
		SetScrollInfo();
		m_SizeChanged = TRUE;
		Invalidate();
	}
	return 0;
}
LRESULT CScannerDisplay::OnRefresh(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(m_bOpened)
	{
		m_DisplayImage.Draw(m_hMemDC,&m_DrawRect);
		InvalidateRect(&m_DrawRect,FALSE);
		BitBlt(this->GetDC(), 
               0,0, 
                m_WndWidth,m_WndHeight,
                m_hMemDC, 
                0,0, 
                SRCCOPY); 
	}
	return 0;
}
void CScannerDisplay::OnFrameReady(LONG LineNum)
{
	//Refresh Dipslay buffer use m_pImageSrcObject
	if(RF_FRAME == m_RefreshMode)
	{
		//Do the LUT Map
		LUTMap(0,m_Height,FALSE);//Refresh WHole Frame
		Refresh();
	}
};
void CScannerDisplay::OnSubFrameReady(LONG NumOfBlockLeft, LONG StartLine, LONG NumLines, BYTE bLastBlock)
{
	//Refresh the Buffer 
	if(RF_TOPDOWN == m_RefreshMode)
	{//Update if the Start Line - Y is in the Display extend
		if((StartLine>= m_Org_Y)&&(StartLine<(m_Org_Y+m_Height)))
		{//Here the startline is the start line in the image data source
			LUTMap(StartLine-m_Org_Y,NumLines,FALSE);
			Refresh();
		}
	}
	else if(RF_MOVING == m_RefreshMode)
	{
		if((StartLine>= m_Org_Y)&&(StartLine<(m_Org_Y+m_Height)))
		{
			LUTMap(StartLine,NumLines,TRUE);
		}
		else
		{
			ATLTRACE("No LUTMap\n");
		}
		//If rate = 0 then refresh by every sub frame ready
		if(0 == m_RefreshRate)
		{
			Refresh();
		}
	}
};
