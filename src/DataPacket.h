#pragma once
#include <Windows.h>
#include <stdio.h>

class CDataPacketIF
{
public:
    CDataPacketIF()
    {}
    virtual ~CDataPacketIF(void){}
	virtual BYTE* GetBuf() = 0;//called by datasrc to copy data from driver
	virtual DWORD GetFirstIndex() = 0;
	virtual void  MoveFirstToWithOffset(DWORD pos) = 0;//Called by queue copy to Frame buffer
	virtual void  Reset() = 0;
    virtual DWORD GetDataPacketLen() = 0;//offset is start from First. Becalled to get the Len
    virtual void  SetNext(CDataPacketIF* pNext)=0;
	virtual CDataPacketIF* GetNext()=0;
	virtual DWORD  GetBufSize()=0;

	virtual void SetDataSize(DWORD len)=0;//be called by the data input function to set the avalible length
	virtual void Clear()=0;
	virtual void Trace(FILE* pFile)=0;
	

};

class CDataPacket : public CDataPacketIF
{
	BYTE* m_pBuf;
	DWORD m_FirstIndex;
	DWORD m_DataLen;
	DWORD m_BufSize;
    CDataPacketIF* m_pNext;
public:
	PUCHAR m_pContext;//get the return value from the begin transfer and be used in endtransfer
	OVERLAPPED m_InOvLap;//the event to wait the end of transfer;

public:
    CDataPacket(DWORD BufSize);
    ~CDataPacket(void);
    BYTE* GetBuf();//called by datasrc to copy data from driver
	DWORD GetFirstIndex();
	void  MoveFirstToWithOffset(DWORD pos);//Called by queue copy to Frame buffer
	void  Reset();
    DWORD GetDataPacketLen();//offset is start from First. Becalled to get the Len
	DWORD  GetBufSize();
	void  SetNext(CDataPacketIF* pNext);
	void SetDataSize(DWORD len);	//be called by the data input function to set the avalible length
	void Clear();
	void Trace(FILE* pFile);
    CDataPacketIF* GetNext();
};
