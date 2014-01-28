
#pragma once
//Error Type
#define EID_SUCCESS						0

#define EID_UNKNOWN_CMD_CHANNEL			1
#define EID_UNKNOWN_IMG_CHANNEL			2
#define EID_NO_IMG_CHANEL				3
#define EID_NO_CMD_CHANEL				4


#define EID_USB_CHANEL_OPEN_FAILED		5
#define EID_USB_CMD_SEND_FAIL			6
#define EID_USB_CMD_REV_FAIL			7
#define EID_USB_IMG_CHANEL_OPEN_FAILED	8
#define EID_USB_IMG_REV_FAIL			9



#define EID_NET_CMD_CONNECT_FAILED		10
#define EID_NET_IMG_CONNECT_FAILED		11
#define EID_NET_CMD_SEND_FAILED			12
#define EID_NET_CMD_REV_FAILED			13
#define EID_NET_IMG_REV_FAILED			14

#define EID_SERIAL_CMD_OPEN_FAILED		15
#define EID_SERIAL_RT_TIMEOUT			16

#define EID_CMDCHANEL_RT_ERROR			17

#define EID_FRAMEBUF_ALLOC_FAIL			18
#define EID_CANNOT_OPEN_IMG_OBJ			19
#define EID_PACKET_LEN_ERROR			20
#define EID_DTP_PACKET_NONE				21
#define EID_DTP_REVQUEUE_EMPTY			22

#define EVENT_DATA_LOST	1
//Channel Type
#define PCDIG		0
#define USB			1
#define NET			2
#define SERIAL		0

//Return Msg
#define STX		'['
#define ETX		']'
#define	REV_BUF_SIZE 64

#define USB_PACKET_BUF_SIZE		0x8000//0x10000            //128*512//BufSize must be multiple of the 512
#define NET_PACKET_BUF_SIZE		0x8000            
#define PACKET_NUM				256//64
#define USB_COMMIT_NUM		4
#define SINK_SIZE				10
#define MAX_ADC					0xFFFF


#define PACKET_HEAD_LEN			6
#define PACKET_HEAD_LENSEG_LEN		3
#define USB_PXIEL_NUMBER		2048
#define USB_PACKET_LEN		2048		
//Calibration Type
#define GAIN					0
#define OFFSET				1
#define BASELINE				2
#define MIN					0
#define MEAN					1
#define MAX					2
#define FRAME_UNIT			32

#define WM_DISPLAY_REFRESH		0x10000		

typedef unsigned * PBEGINTHREADEX_THREADID;
typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC) (LPVOID lpThreadParameter);