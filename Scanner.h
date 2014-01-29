// Scanner.h : CScanner 的声明

#pragma once
#include "resource.h"       // 主符号



#include "DetectorControl_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;


// CScanner

class ATL_NO_VTABLE CScanner :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CScanner, &CLSID_Scanner>,
	public IScanner
{
public:
	CScanner()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SCANNER)


BEGIN_COM_MAP(CScanner)
	COM_INTERFACE_ENTRY(IScanner)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(get_DetectorObject)(IUnknown** pVal);
	STDMETHOD(put_DetectorObject)(IUnknown* newVal);
	STDMETHOD(OffBoardCalibration)(LONG CalibrationType, IUnknown* pImgObject, LONG StartPixel, LONG EndPixel, LONG TargetValue);
	STDMETHOD(get_Gain)(LONG Index, FLOAT* pVal);
	STDMETHOD(put_Gain)(LONG Index, FLOAT newVal);
	STDMETHOD(get_Offset)(LONG Index, LONG* pVal);
	STDMETHOD(put_Offset)(LONG Index, LONG newVal);
	STDMETHOD(get_CorrectionGain)(LONG* pVal);
	STDMETHOD(put_CorrectionGain)(LONG newVal);
	STDMETHOD(get_CorrectionOffset)(LONG* pVal);
	STDMETHOD(put_CorrectionOffset)(LONG newVal);
	STDMETHOD(get_CorrectionBaseline)(LONG* pVal);
	STDMETHOD(put_CorrectionBaseline)(LONG newVal);
	STDMETHOD(get_Baseline)(LONG* pVal);
	STDMETHOD(put_Baseline)(LONG newVal);
	STDMETHOD(get_IntegrationTime)(LONG* pVal);
	STDMETHOD(put_IntegrationTime)(LONG newVal);
	STDMETHOD(get_AverageFilter)(LONG* pVal);
	STDMETHOD(put_AverageFilter)(LONG newVal);
	STDMETHOD(get_DataPattern)(LONG* pVal);
	STDMETHOD(put_DataPattern)(LONG newVal);
	STDMETHOD(get_FrameTrigger)(LONG* pVal);
	STDMETHOD(put_FrameTrigger)(LONG newVal);
	STDMETHOD(get_LineTrigger)(LONG* pVal);
	STDMETHOD(put_LineTrigger)(LONG newVal);
	STDMETHOD(Initialize)(LONG Mode);
	STDMETHOD(SaveOffset)(void);
	STDMETHOD(SaveGain)(LONG Index);
	STDMETHOD(LoadOffset)(void);
	STDMETHOD(LoadGain)(LONG Index);
	STDMETHOD(get_OutputBits)(LONG* pVal);
	STDMETHOD(put_OutputBits)(LONG newVal);
	STDMETHOD(SendExFrameTrigger)(void);
	STDMETHOD(get_FrameOut)(LONG* pVal);
	STDMETHOD(put_FrameOut)(LONG newVal);
	STDMETHOD(get_ImageOutputType)(LONG* pVal);
	STDMETHOD(put_ImageOutputType)(LONG newVal);
	STDMETHOD(get_SensitivityLevel)(LONG* pVal);
	STDMETHOD(put_SensitivityLevel)(LONG newVal);
	STDMETHOD(get_SumLines)(LONG* pVal);
	STDMETHOD(put_SumLines)(LONG newVal);
	STDMETHOD(WriteDataPattern)(LONG Base, LONG Step);
	STDMETHOD(get_IsOpened)(LONG* pVal);
	STDMETHOD(get_ModuleTypeName)(BSTR* pVal);
	STDMETHOD(SaveCurrentStatus)(void);
	STDMETHOD(get_PixelSize)(FLOAT* pVal);
	STDMETHOD(get_PixelNumber)(LONG* pVal);
	STDMETHOD(get_ModuleType)(LONG* pVal);
	STDMETHOD(get_MaxIntTime)(LONG* pVal);
	STDMETHOD(get_MinIntTime)(LONG* pVal);
	STDMETHOD(get_OverallGain)(FLOAT* pVal);
	STDMETHOD(put_OverallGain)(FLOAT newVal);
	STDMETHOD(get_StartPixel)(LONG* pVal);
	STDMETHOD(put_StartPixel)(LONG newVal);
	STDMETHOD(get_EndPixel)(LONG* pVal);
	STDMETHOD(put_EndPixel)(LONG newVal);
	STDMETHOD(OnBoardOffsetCalibration)(void);
	STDMETHOD(OnBoardGainCalibration)(LONG TargetValue);
	STDMETHOD(ResetGain)(void);
	STDMETHOD(ResetOffset)(void);
	STDMETHOD(get_FPGA_Version)(LONG* pVal);
	STDMETHOD(get_FPGA_Build)(LONG* pVal);
	STDMETHOD(get_MCU_Version)(LONG* pVal);
	
	STDMETHOD(get_SerialNumber)(BSTR* pVal);

	STDMETHOD(RetrieveSysinfo)(void);

	private:
		ICommandChannel*	m_pDetector;
		CHAR			m_Command[100];
		CHAR			m_Return[100];
		LONG			m_bOK;
		//Following parameter is the detector property
		//FI command
		LONG			m_FPGA_Version;
		LONG			m_FPGA_Build;
		//RI Command
		LONG			m_MCU_Version;
		LONG			m_PixelNumber;
		float			m_PixelSize;
		LONG			m_ModuleType;
		char			m_ModuleName[20];
		char			m_SerialNum[20];
		LONG			m_FEBoardNum;
		LONG			m_MaxIntTime;
		LONG			m_MinIntTime;
		BOOL			m_bRetrieved;//Flag to indicate whether there is RI Called
	private:
		LONG Min(LONG* pData,LONG Width);
		LONG Mean(LONG* pData,LONG Width);
		LONG Max(LONG* pData,LONG Width);
		ULONG GetNumber(CHAR* pSrc ,LONG Index);
		LONG GetString(CHAR* pSrc ,LONG Index,CHAR* pDest);
public:


};

OBJECT_ENTRY_AUTO(__uuidof(Scanner), CScanner)
