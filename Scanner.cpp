// Scanner.cpp : CScanner µÄÊµÏÖ
#define _CRT_SECURE_NO_DEPRECATE
#include "stdafx.h"
#include "Scanner.h"
#include <comutil.h>


// CScanner

STDMETHODIMP CScanner::get_DetectorObject(IUnknown** pVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		m_pDetector->QueryInterface(IID_IUnknown,(void**)pVal); 
	}
	else
	{
		*pVal = NULL;
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_DetectorObject(IUnknown* newVal)
{
	// TODO: Add your implementation code here
	if(newVal)
	{//If not open then allow change
		newVal->QueryInterface(IID_ICommandChannel,(void**)&m_pDetector); 
	}
	return S_OK;
}

STDMETHODIMP CScanner::OffBoardCalibration(LONG CalibrationType, IUnknown* pImgObject, LONG StartPixel, LONG EndPixel, LONG TargetValue)
{
	LONG Width;
	LONG Height;
	LONG* pAvg=NULL;
	IFrameObject* pImageObject;
	pImageObject->QueryInterface(IID_IFrameObject,(void**)&pImageObject);
	//Get the average value
	if(pImageObject)
	{
		pImageObject->get_Width(&Width);
		pImageObject->get_Height(&Height);
		pAvg = new LONG[Width];
		ATLASSERT(pAvg);
		pImageObject->get_ColAverage(pAvg);
		if(m_pDetector)
		{
		//Offset Calibration
			if(OFFSET==CalibrationType)
			{
			//Get the ColAvg value from pImgObject which take after disable the gain offset and baseline
			//call SetOffsetValue(Pixel,Value) accord to the Startpixel and Endpixel
				for(int i= StartPixel;i<=EndPixel;i++)
				{
					put_Offset(i,pAvg[i]*0x10000);
				}
			}
			else if(GAIN==CalibrationType)
			{
			//Gain correction
				float fGain=0;
				LONG lGain=0;
				if(MIN == TargetValue )
				{
					TargetValue = Min(pAvg,Width);
				}
				else if (MEAN == TargetValue)
				{
					TargetValue = Mean(pAvg,Width);
				}
				else if(MAX == TargetValue)
				{
					TargetValue = Max(pAvg,Width);
				}

				for(int i = StartPixel; i<=EndPixel;i++)
				{
			//call SetOffsetValue(Pixel,Value) accord to the Startpixel and Endpixel
                    fGain = ((float)TargetValue)/(float)(pAvg[i]);
					put_Gain(i,fGain);
				}
			}
		}
		if(pAvg)
			delete [] pAvg;
		pAvg = NULL;
	}
	return S_OK;
}


STDMETHODIMP CScanner::get_Gain(LONG Index, FLOAT* pVal)
{
	// TODO: Add your implementation code here
	ULONG lGain = 0;
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[SC,R,%X]",Index);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		//[0,CB0000,18000]
		if(m_bOK)
		{
			lGain = GetNumber(m_Return,1);
			*pVal = ((float)lGain)/0x10000;
		}
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_Gain(LONG Index, FLOAT newVal)
{
	// TODO: Add your implementation code here
	ULONG lGain = newVal* 0x10000;
	if(m_pDetector)
	{
		sprintf(m_Command,"[SC,W,G,%X,%X]",Index,lGain);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_Offset(LONG Index, LONG* pVal)
{
	// TODO: Add your implementation code here
	ULONG lOffset = 0;
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[SC,R,%X]",Index);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		//[0,CB0000,18000]
		lOffset = GetNumber(m_Return,2);
		*pVal = lOffset>>16;
	}

	return S_OK;
}

STDMETHODIMP CScanner::put_Offset(LONG Index, LONG newVal)
{
	// TODO: Add your implementation code here
	ULONG lGain = newVal* 0x10000;
	if(m_pDetector)
	{
		sprintf(m_Command,"[SC,W,O,%X,%X]",Index,lGain);
		//sprintf(m_Command,"[UI]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}

	return S_OK;
}

STDMETHODIMP CScanner::get_CorrectionGain(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[CS,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		//[0,Gain offset baseline]
		*pVal = GetNumber(m_Return,1);
	}

	return S_OK;
}

STDMETHODIMP CScanner::put_CorrectionGain(LONG newVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		if(newVal)
		{
			//
			sprintf(m_Command,"[CS,W,G,%X]",1);
			m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		}
		else
		{
			sprintf(m_Command,"[CS,W,G,%X]",0);
			m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		}
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_CorrectionOffset(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[CS,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		//[0,Gain offset baseline]
		*pVal = GetNumber(m_Return,2);
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_CorrectionOffset(LONG newVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		if(newVal)
		{
			//
			sprintf(m_Command,"[CS,W,O,%X]",1);
			m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		}
		else
		{
			sprintf(m_Command,"[CS,W,O,%X]",0);
			m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		}
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_CorrectionBaseline(LONG* pVal)
{
	// TODO: Ad your implementation code here
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[CS,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		//[0,Gain offset baseline]
		*pVal = GetNumber(m_Return,3);
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_CorrectionBaseline(LONG newVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		if(newVal)
		{
			//
			sprintf(m_Command,"[CS,W,B,%X]",1);
			m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		}
		else
		{
			sprintf(m_Command,"[CS,W,B,%X]",0);
			m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		}
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_Baseline(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[BS,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		*pVal = GetNumber(m_Return,1);
	}

	return S_OK;
}

STDMETHODIMP CScanner::put_Baseline(LONG newVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[BS,W,%X]",newVal);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_IntegrationTime(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[ST,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		*pVal = GetNumber(m_Return,1);
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_IntegrationTime(LONG newVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[ST,W,%X]",newVal);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}	
	return S_OK;
}

STDMETHODIMP CScanner::get_AverageFilter(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[AF,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		*pVal = GetNumber(m_Return,1);
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_AverageFilter(LONG newVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[AF,W,%X]",newVal);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_DataPattern(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[ED,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		*pVal = GetNumber(m_Return,1);
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_DataPattern(LONG newVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[ED,W,%X]",newVal);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}

	return S_OK;
}

STDMETHODIMP CScanner::get_FrameTrigger(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[EF,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		*pVal = GetNumber(m_Return,1);
	}

	return S_OK;
}

STDMETHODIMP CScanner::put_FrameTrigger(LONG newVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[EF,W,%X]",newVal);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_LineTrigger(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[EL,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_LineTrigger(LONG newVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[EL,W,%X]",newVal);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::Initialize(LONG Mode)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[IN,%X]",Mode);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::SaveOffset(void)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[OS,S]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::SaveGain(LONG Index)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[GS,S,%X]",Index);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::LoadOffset(void)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[OS,L]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::LoadGain(LONG Index)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[GS,L,%X]",Index);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_OutputBits(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[SB,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		*pVal = GetNumber(m_Return,1);
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_OutputBits(LONG newVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[SB,W,%X]",newVal);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::SendExFrameTrigger(void)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[SE]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_FrameOut(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = 0;
	if(m_pDetector)//Direct Get the frame scanbits
	{
		sprintf(m_Command,"[WR,R,CFFF,0]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		BYTE Val = (BYTE)GetNumber(m_Return,1);
		*pVal = Val & 0x1;
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_FrameOut(LONG newVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[SF,%X]",newVal);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_ImageOutputType(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[SI,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		*pVal = GetNumber(m_Return,1);		
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_ImageOutputType(LONG newVal)
{
	// TODO: Add your implementation code here
	//To change the output port permantly need use RI command
	if(m_pDetector)
	{
		sprintf(m_Command,"[SI,W,%X]",newVal);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_SensitivityLevel(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[SS,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		*pVal = GetNumber(m_Return,1);	
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_SensitivityLevel(LONG newVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[SS,W,%X]",newVal);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_SumLines(LONG* pVal)
{
	// TODO: Add your implementation code here
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[SU,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		*pVal = GetNumber(m_Return,1);
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_SumLines(LONG newVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[SU,W,%X]",newVal);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}
LONG CScanner::Min(LONG* pData,LONG Width)
{
	LONG Min=pData[0];
	for(int i=0;i<Width;i++)
	{
		if(Min>pData[i])
			Min = pData[i];
	}
	return Min;
}
LONG CScanner::Max(LONG* pData,LONG Width)
{
	LONG Max=pData[0];
	for(int i=0;i<Width;i++)
	{
		if(Max < pData[i])
			Max = pData[i];
	}
	return Max;
}
LONG CScanner::Mean(LONG* pData,LONG Width)
{
	LONG Sum=0;
	for(int i = 0; i<Width;i++)
	{
		Sum += pData[i];
	}
	Sum /= Width;
	return Sum;
}

//[0,CB0000,18000]
ULONG CScanner::GetNumber(CHAR* pSrc ,LONG Index)
{
	char Flag = ',';
	char End = ']';
	CHAR* pTemp=pSrc;
	CHAR Buffer[10];
	ULONG Value = 0;
	int i;
	for(i=0;i<Index;i++)
	{
		pTemp = strchr(pTemp,Flag);
		if(NULL == pTemp)
			return 0;
		pTemp++;
	}
	i=0;
	while(isxdigit(*pTemp))
	{
		Buffer[i] = *pTemp;
		pTemp++;
		i++;
		if(i==9)
			break;
	}
	Buffer[i] = 0;
	sscanf(Buffer,"%X",&Value);
    return Value;
}
LONG CScanner::GetString(CHAR* pSrc ,LONG Index,CHAR* pDest)
{//Get the string from the input psrc
	//[ 0,L-Shap,1,2]
	char Flag = ',';
	char End = ']';
	CHAR* pTemp=pSrc;
	CHAR* pTemp2 = pDest;
//	CHAR Buffer[10];
	ULONG Value = 0;
	int i;
	//Find the correct position
	for(i=0;i<Index;i++)
	{
		pTemp = strchr(pTemp,Flag);
		if(NULL == pTemp)
		{
			*pDest = 0;
			return 0;			
		}
		pTemp++;
	}
	i=0;
	//
	for(i=0;i<19;i++)
	{
		if((Flag == pTemp[i])||(End == pTemp[i])||(!isprint(pTemp[i])))
		{
			break;
		}
		pDest[i] = pTemp[i];
	}
	pDest[i] = 0;
	return i;
}
STDMETHODIMP CScanner::WriteDataPattern(LONG Base, LONG Step)
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CScanner::get_IsOpened(LONG* pVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		m_pDetector->get_IsOpened(pVal);
	}
	else
	{
		*pVal = FALSE;
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_ModuleTypeName(BSTR* pVal)
{
	// TODO: Add your implementation code here
//ConvertStringToBSTR(
	if(!m_bRetrieved)
	{
		RetrieveSysinfo();
	}
	CComBSTR bstrRT;
	bstrRT = _com_util::ConvertStringToBSTR(m_ModuleName);
	bstrRT.CopyTo(pVal);
	
	return S_OK;
}

STDMETHODIMP CScanner::SaveCurrentStatus(void)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[SR,S]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_PixelSize(FLOAT* pVal)
{
	// TODO: Add your implementation code here
	if(!m_bRetrieved)
	{
		RetrieveSysinfo();
	}
	*pVal = m_PixelSize;
	return S_OK;
}

STDMETHODIMP CScanner::get_PixelNumber(LONG* pVal)
{
	// TODO: Add your implementation code here
	if(!m_bRetrieved)
	{
		RetrieveSysinfo();
	}
	*pVal = m_PixelNumber;
	return S_OK;
}

STDMETHODIMP CScanner::get_ModuleType(LONG* pVal)
{
	// TODO: Add your implementation code here
	if(!m_bRetrieved)
	{
		RetrieveSysinfo();
	}
	*pVal = m_ModuleType;

	return S_OK;
}

STDMETHODIMP CScanner::get_MaxIntTime(LONG* pVal)
{
	// TODO: Add your implementation code here
	if(!m_bRetrieved)
	{
		RetrieveSysinfo();
	}
	*pVal = m_MaxIntTime;
	return S_OK;
}

STDMETHODIMP CScanner::get_MinIntTime(LONG* pVal)
{
	// TODO: Add your implementation code here
	if(!m_bRetrieved)
	{
		RetrieveSysinfo();
	}
	*pVal = m_MinIntTime;
	return S_OK;
}

STDMETHODIMP CScanner::get_OverallGain(FLOAT* pVal)
{
	// TODO: Add your implementation code here
	*pVal = 0;
	if(m_pDetector)
	{
		sprintf(m_Command,"[RG,R,0]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		if(m_bOK)
		{
			*pVal = GetNumber(m_Return,1)*10/0x100;
			*pVal /= 10;
		}
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_OverallGain(FLOAT newVal)
{
	// TODO: Add your implementation code here
	ULONG LGain  = newVal*0x100;//Need confirm the formula of the gain
	if(m_pDetector)
	{
		sprintf(m_Command,"[RG,W,-,%X]",LGain);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_StartPixel(LONG* pVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[AC,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		if(m_bOK)
		{
			*pVal = GetNumber(m_Return,1);
		}
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_StartPixel(LONG newVal)
{
	// TODO: Add your implementation code here
	LONG EndPixel=0;
	if(m_pDetector)
	{
		get_EndPixel(&EndPixel);
		sprintf(m_Command,"[AC,W,%X,%X]",newVal,EndPixel);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_EndPixel(LONG* pVal)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[AC,R]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		if(m_bOK)
		{
			*pVal = GetNumber(m_Return,2);
		}
	}
	return S_OK;
}

STDMETHODIMP CScanner::put_EndPixel(LONG newVal)
{
	// TODO: Add your implementation code here
	LONG StartPixel=0;
	if(m_pDetector)
	{
		get_StartPixel(&StartPixel);
		sprintf(m_Command,"[AC,W,%X,%X]",StartPixel,newVal);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::OnBoardOffsetCalibration(void)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[OC]");
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::OnBoardGainCalibration(LONG TargetValue)
{
	// TODO: Add your implementation code here
// TODO: Add your implementation code here
	TargetValue &= 0xFFFF; 
	long timeout;
	if(m_pDetector)
	{
		m_pDetector->get_CmdTimeOut(&timeout);
//		m_pDetector->put_CmdTimeOut(1000);
		sprintf(m_Command,"[GC,%X]",TargetValue);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
		m_pDetector->put_CmdTimeOut(timeout);
	}
	return S_OK;
}

STDMETHODIMP CScanner::ResetGain(void)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[RC,%X,0]",1);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::ResetOffset(void)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		sprintf(m_Command,"[RC,0,%X]",1);
		m_pDetector->SendCommandA(m_Command,m_Return,&m_bOK);
	}
	return S_OK;
}

STDMETHODIMP CScanner::get_FPGA_Version(LONG* pVal)
{
	// TODO: Add your implementation code here
	if(!m_bRetrieved)
	{
		RetrieveSysinfo();
	}
	*pVal = m_FPGA_Version;
	return S_OK;
}


STDMETHODIMP CScanner::get_FPGA_Build(LONG* pVal)
{
	// TODO: Add your implementation code here
	if(!m_bRetrieved)
	{
		RetrieveSysinfo();
	}
	*pVal = m_FPGA_Build;
	return S_OK;
}


STDMETHODIMP CScanner::get_MCU_Version(LONG* pVal)
{
	// TODO: Add your implementation code here
	if(!m_bRetrieved)
	{
		RetrieveSysinfo();
	}
	*pVal = m_MCU_Version;
	return S_OK;
}



STDMETHODIMP CScanner::get_SerialNumber(BSTR* pVal)
{
	// TODO: Add your implementation code here
	if(!m_bRetrieved)
	{
		RetrieveSysinfo();
	}
	CComBSTR bstrRT;
	bstrRT = _com_util::ConvertStringToBSTR(m_SerialNum);
	bstrRT.CopyTo(pVal);
	return S_OK;
}


STDMETHODIMP CScanner::RetrieveSysinfo(void)
{
	// TODO: Add your implementation code here
	if(m_pDetector)
	{
		m_pDetector->SendCommandA("[RI]",m_Return,&m_bOK);
		if(m_bOK)
		{
			GetString(m_Return,1,m_SerialNum);
			m_ModuleType = GetNumber(m_Return,2);
			GetString(m_Return,3,m_ModuleName);
			m_PixelNumber	= GetNumber(m_Return,5);
			m_PixelSize = (1.0*GetNumber(m_Return,6 ))/100;
			m_MCU_Version =  GetNumber(m_Return,8);
			m_MinIntTime = GetNumber(m_Return,9);
			m_MaxIntTime = GetNumber(m_Return,10);
		}
		m_pDetector->SendCommandA("[FI]",m_Return,&m_bOK);
		if(m_bOK)
		{
			m_FPGA_Build = GetNumber(m_Return,2);
			m_FPGA_Version = GetNumber(m_Return,1);
		}
		//Zhangxq Mar 25, 2011
		//don't use this variable
		//m_bRetrieved = TRUE;
	}
	return S_OK;
}
