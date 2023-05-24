#include "stdafx.h"
#include "SettingParser.h"

#define WORD_START _buffer[_bufferIndex]
#define WORD_END _buffer[wordEnd]

bool SettingParser::init(LPCTSTR location)
{
	const bool isSettingLoaded = loadSetting(location);

	if (isSettingLoaded == false)
		return false;

	parse();

	return true;
}

bool SettingParser::getValue(LPCTSTR name, int32& value)
{
	int groupEnd = 0;

	for (int i = 0; name[i] != TEXT('\0'); i++) {
		if (name[i] == '.')
		{
			groupEnd = i;
		}
	}

	TCHAR Group[WORD_SIZE] = {0,};
	TCHAR Name[WORD_SIZE] = {0,};

	wcsncpy_s(Group, name, groupEnd);
	wcscpy_s(Name, &name[groupEnd + 1]);


	for (int i = 0; i < MAXGROUPSIZE; i++)
	{
		if (wcscmp(_groupsName[i], Group) == 0)
		{
			auto result = _settingsContainer[i].find(Name);
			if (result == _settingsContainer[i].end())
				return false;
			value = _wtoi(result->second.c_str());
			return true;
		}
	}
	return false;
}

//value 배열에 값을 복사한다. 이 때 value 배열의 크기는 SettingParser::WORD_SIZE를 사용한다. 
bool SettingParser::getValue(LPCTSTR name, LPTSTR value)
{
	int groupEnd = 0;

	for(int i = 0; name[i] != TEXT('\0'); i++){
		if(name[i] == '.')
		{
			groupEnd = i;
		}
	}

	TCHAR Group[WORD_SIZE] = { 0, };
	TCHAR Name[WORD_SIZE] = { 0, };

	wcsncpy_s(Group, name, groupEnd);
	wcscpy_s(Name, &name[groupEnd + 1]);


	for(int i =0; i<MAXGROUPSIZE;i++)
	{
		if(wcscmp(_groupsName[i], Group) == 0)
		{
			auto result = _settingsContainer[i].find(Name);
			if (result == _settingsContainer[i].end())
				return false;
			wcscpy_s(value, WORD_SIZE, result->second.c_str());
			return true;
		}
	}
	return false;
}

bool SettingParser::loadSetting(LPCTSTR location)
{

	TCHAR errBuffer[MAXERRLEN];

	//텍스트 모드로 열 경우 ftell의 값과 파일 크기가 다를 수 있다. 
	const auto openRet = _wfopen_s(&_settingStream, location, TEXT("rb"));
	if (openRet != 0 || _settingStream == nullptr)
	{
		swprintf_s(errBuffer, L"errNo : %d | SettingParser::loadSetting, fopen ", openRet);
		GLogger->write(errBuffer);
		return false;
	}

	long fileSize;

	if (fseek(_settingStream, 0, SEEK_END) < 0 || (fileSize = ftell(_settingStream)) < 0) {
		swprintf_s(errBuffer, TEXT("errNo : %d | SettingParser::loadSetting, ftell "), openRet);
		GLogger->write(errBuffer);
		// should read the file and reallocate the buffer as needed
		fclose(_settingStream);
		return false;
	}

	_buffer = (LPTSTR)malloc(fileSize+ 1);
	if (_buffer == nullptr)
	{
		swprintf_s(errBuffer, TEXT("errNo : %d | SettingParser::loadSetting, malloc "), openRet);
		GLogger->write(errBuffer);
		return false;
	}
		
	rewind(_settingStream);

	//파일 읽고 문자열 끝에 null 추가
	const auto readRet = fread_s(_buffer,fileSize, 1,fileSize,_settingStream);
	if (readRet != fileSize)
	{
		swprintf_s(errBuffer, TEXT("errNo : %zd | SettingParser::loadSetting, fread "), readRet);
		GLogger->write(errBuffer);
		return false;
	}

	_buffer[readRet] = '\0';

	fclose(_settingStream);
	return true;
}

//텍스트 파일은 키 : 값 쌍으로 이루어짐
bool SettingParser::parse()
{
	TCHAR key[WORD_SIZE];
	TCHAR value[WORD_SIZE];
	TCHAR op[WORD_SIZE];

	while(true)
	{

		if (getTok(key) == false)
			break;

		//그룹 종료 예외 처리
		if(key[0] == '}')
		{
			continue;
		}
		
		if (getTok(op) == false)
			break;

		// ':' 위치에 다른 거 있으면 에러
		if(op[0] != ':')
		{
			GLogger->write(TEXT("parseError: Invalid Operand. Incorrect file syntax may occur this problem."));
			return false;
		}

		if (getTok(value) == false)
			break;

		//그룹 시작 예외 처리
		if(value[0] == '{')
		{
			_groupIndex++;
			wcscpy_s(_groupsName[_groupIndex], WORD_SIZE, key);
			continue;
		}
		_settingsContainer[_groupIndex].insert({key,value});
	}

	free(_buffer);
	_buffer = nullptr;

	return true;
}

bool SettingParser::getTok(LPTCH  word)
{
	//의미 있는 문자까지 이동. 널문자를 만나도 탈출
	while (true)
	{
		if (WORD_START == TEXT('﻿') || WORD_START == TEXT('\n') || WORD_START == TEXT( ' ' ) || WORD_START == 0x09 || WORD_START == 0x0a || WORD_START == 0x0d)
		{
			_bufferIndex++;
		}
		else
			break;
	}

	//널문자 만났는지 확인
	if (WORD_START == TEXT('\0'))
		return false;

	size_t wordEnd = _bufferIndex+1;

	//의미 있는 문자가 한 줄 주석이면 다음 줄 시작까지 이동
	if (WORD_START == TEXT('/') && WORD_END == TEXT('/'))
	{
		while (true)
		{
			if (WORD_END == '\n')
			{
				wordEnd++;
				break;
			}
			else
				wordEnd++;
		}
		_bufferIndex = wordEnd;
		return getTok(word);
	}

	//여러 줄 주석이면 */ 만날 때 까지 이동
	if (WORD_START == TEXT('/') && WORD_END == TEXT('*'))
	{
		while (true)
		{
			if (WORD_END == TEXT('*') && _buffer[wordEnd+1] == TEXT ('/'))
			{
				wordEnd+=2;
				break;
			}
			else
				wordEnd++;
		}
		_bufferIndex = wordEnd;
		return getTok(word);
	}

	if (WORD_START == TEXT('"'))
	{
		//시작하는 " 문자열에 안 들어가게 하기 위한 처리
		_bufferIndex++;
		while (true)
		{
			if (WORD_END == TEXT('"'))
			{
				wordEnd++;
				break;
			}
			else
				wordEnd++;
		}

		//끝나는 " 문자열에 안 들어가게 
		size_t wordSize = wordEnd - _bufferIndex-1;

		wcsncpy_s(word, WORD_SIZE, &WORD_START, wordSize);
		_bufferIndex = wordEnd;
		return true;
	}


	//하나짜리 토큰이면 바로 리턴
	if(WORD_START == TEXT( ':') || WORD_START == TEXT('{') || WORD_START == TEXT( '}') )
	{
		const size_t wordSize = wordEnd - _bufferIndex;
		wcsncpy_s(word, WORD_SIZE, &WORD_START, wordSize);
		word[wordSize] = '\0';

		_bufferIndex = wordEnd;

		return true;
	}


	//긴 토큰 받는 곳
	while (true)
	{
		if (WORD_END == TEXT('\n') || WORD_END == TEXT(' ') || WORD_END == 0x09 ||
			WORD_END == 0x0a || WORD_END == 0x0d || WORD_END == TEXT ('\0') ||
			WORD_END == TEXT(':') || WORD_END == TEXT('{') || WORD_END == TEXT( '}'))
		{
			break;
		}
		else
			wordEnd++;
	}


	size_t wordSize = wordEnd - _bufferIndex;
	wcsncpy_s(word,WORD_SIZE, &WORD_START, wordSize);
	word[wordSize] = '\0';

	_bufferIndex = wordEnd;

	return true;
}
