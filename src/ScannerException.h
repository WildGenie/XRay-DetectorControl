#pragma once

class CScannerException
{
	public:
	int m_ERROR_ID;
	BSTR m_ERROR_INFO;
    CScannerException(int ID);
    ~CScannerException(void);
	void PrintErrInfo();
	void ProcessError();
};
