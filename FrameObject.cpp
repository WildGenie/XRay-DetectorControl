// FrameObject.cpp : CFrameObject µÄÊµÏÖ

#include "stdafx.h"
#include "FrameObject.h"


// CFrameObject



STDMETHODIMP CFrameObject::get_ImageDataAddress(LONG* pVal)
{
	// TODO: Add your implementation code here
	
	return m_pFrameObject->get_ImageDataAddress(pVal);
}
STDMETHODIMP  CFrameObject::put_ImageDataAddress(LONG newVal)
{
	m_pFrameObject->put_ImageDataAddress(newVal);
	return S_OK;
}

STDMETHODIMP CFrameObject::get_Width(LONG* pVal)
{
	m_pFrameObject->get_Width(pVal);
	return S_OK;
}

STDMETHODIMP CFrameObject::get_Height(LONG* pVal)
{
	// TODO: Add your implementation code here
	m_pFrameObject->get_Height(pVal);
	return S_OK;
}

STDMETHODIMP CFrameObject::get_BytesPerPixel(LONG* pVal)
{
	m_pFrameObject->get_BytesPerPixel(pVal);
	return S_OK;
}

STDMETHODIMP CFrameObject::get_Pixel(LONG X, LONG Y, LONG* pVal)
{
	m_pFrameObject->get_Pixel(X, Y, pVal);
	return S_OK;
}

STDMETHODIMP CFrameObject::put_Pixel(LONG X, LONG Y, LONG newVal)
{
	// TODO: Add your implementation code here
	m_pFrameObject->put_Pixel(X, Y, newVal);
	return S_OK;
}

STDMETHODIMP CFrameObject::Open(LONG Width, LONG Height, LONG BytesPerPixel)
{
	m_pFrameObject->Open(Width, Height, BytesPerPixel);
	return S_OK;
}

STDMETHODIMP CFrameObject::get_ImageLineAddress(LONG LineIndex, LONG* pVal)
{
	m_pFrameObject->get_ImageLineAddress(LineIndex, pVal);
	return S_OK;
}


STDMETHODIMP CFrameObject::get_ColAverage(LONG* pAvg)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFrameObject::get_ColMax(LONG* pMax)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFrameObject::get_ColMin(LONG* pMin)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFrameObject::get_RowMin(LONG* pMin)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFrameObject::get_RowMax(LONG* pMax)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFrameObject::get_RowAverage(LONG* pAvg)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFrameObject::get_ColNoise(FLOAT* pNoise)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFrameObject::get_RowNoise(FLOAT* pNoise)
{
	// TODO: Add your implementation code here

	return S_OK;
}
