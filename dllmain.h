// dllmain.h : 模块类的声明。

class CDetectorControlModule : public ATL::CAtlDllModuleT< CDetectorControlModule >
{
public :
	DECLARE_LIBID(LIBID_DetectorControlLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DETECTORCONTROL, "{C54C4278-58A8-4700-A383-7ACD15EE06C2}")
};

extern class CDetectorControlModule _AtlModule;
