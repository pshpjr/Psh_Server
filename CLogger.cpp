#include "stdafx.h"
#include "CLogger.h"


CLogger::CLogger(LPCTCH fileName)
{
	LPCTCH tmp = fileName;
	wcscpy_s(_ioStream, tmp);
}

void CLogger::write(LPCTSTR log)
{
	FILE* stream;
	auto openRet = _wfopen_s(&stream, _ioStream, L"a+");

	fwprintf_s(stream, L"%s\n", log);

	fclose(stream);
}
