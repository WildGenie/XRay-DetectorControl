#include "StdAfx.h"
#include ".\dtexception.h"
#include "DTConst.h"
CDTException::CDTException(int ID)
{
	m_ERROR_ID = ID;
	CComBSTR bstrRT;
	// Convert the string to uppercase
	// Return a copy of the string.

	switch(m_ERROR_ID)
	{
	case EID_SUCCESS:
		bstrRT = "Success";
		break;
	case EID_UNKNOWN_CMD_CHANNEL :
		bstrRT = "Unknow command channel type";
		break;
	case EID_UNKNOWN_IMG_CHANNEL	:
		bstrRT = "Unknow image channel type";
		break;
	case EID_USB_CHANEL_OPEN_FAILED	:
		bstrRT = "USB device open failed";
		break;
	case EID_USB_CMD_SEND_FAIL	:
		bstrRT = "USB command send failed";
		break;
	case EID_USB_CMD_REV_FAIL	:
		bstrRT = "USB command receive failed";
		break;
	case EID_USB_IMG_CHANEL_OPEN_FAILED	:
		bstrRT = "USB image channel open failed";
		break;
	case EID_USB_IMG_REV_FAIL	:
		bstrRT = "USB image channel receive failed";
		break;
	case EID_NO_CMD_CHANEL	:
		bstrRT = "Command channel is not open";
		break;
	case EID_NET_CMD_CONNECT_FAILED	:
		bstrRT = "Net command channel connect failed";
		break;
	case EID_NET_IMG_CONNECT_FAILED	:
		bstrRT = "Net command channel connect failed";
		break;
	case EID_NET_CMD_SEND_FAILED	:
		bstrRT = "Net command channel send failed";
		break;
	case EID_NET_CMD_REV_FAILED	:
		bstrRT = "Net command channel receive failed";
		break;
	case EID_NET_IMG_REV_FAILED :
		bstrRT = "Net image channel receive failed";
		break;
	case EID_CMDCHANEL_RT_ERROR	:
		bstrRT = "Net command channel return error";
		break;
	case EID_SERIAL_CMD_OPEN_FAILED:
		bstrRT = "Serial port open failed";
		break;
	case EID_SERIAL_RT_TIMEOUT:
		bstrRT = "Serial command channel return time out";
		break;
	case EID_FRAMEBUF_ALLOC_FAIL:
		bstrRT = "Frame buffer allocate failed";
		break;
	case EID_NO_IMG_CHANEL:
		bstrRT = "No image channel";
		break;
	case EID_CANNOT_OPEN_IMG_OBJ:
		bstrRT = "No image object";
		break;
	case EID_PACKET_LEN_ERROR:
		bstrRT = "DTP packet length error";
		break;
	case EID_DTP_PACKET_NONE:
		bstrRT = "None DTP packet ";
		break;
	default:
			bstrRT = "ErrorHappen";
	}

	bstrRT.CopyTo(&m_ERROR_INFO);
}

CDTException::~CDTException(void)
{
}
void CDTException::ProcessError()
{
}
void CDTException::PrintErrInfo()
{
};
