#pragma once

//TODO: 멀티스레드에서 안전하게 동작하도록 수정.

class CLogger
{
public:
	CLogger(LPCWCH fileName = L"log.txt");

	void write(LPCTSTR log);

private:
	WCHAR _ioStream[128];
};

