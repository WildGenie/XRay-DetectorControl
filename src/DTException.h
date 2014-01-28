#pragma once

class CDTException
{
	public:
	int m_ERROR_ID;
	BSTR m_ERROR_INFO;
	CDTException(int ID);
	~CDTException(void);
	void PrintErrInfo();
	void ProcessError();
};
