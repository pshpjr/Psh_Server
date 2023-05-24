#include "stdafx.h"
#include "Profiler.h"

struct PROFILE_SAMPLE {
	PROFILE_SAMPLE() :iTotalTime(0), iMin(987654321), iMax(-1) {  }
	long			lFlag = false;				// 프로파일의 사용 여부. (배열시에만)
	WCHAR			szName[Profiler::MAXNAME] = L"";			// 프로파일 샘플 이름.

	std::chrono::microseconds			iTotalTime;			// 전체 사용시간 카운터 Time.	(출력시 호출회수로 나누어 평균 구함)
	std::chrono::microseconds			iMin;			// 최소 사용시간 카운터 Time.	(초단위로 계산하여 저장 / [0] 가장최소 [1] 다음 최소 [2])
	std::chrono::microseconds			iMax;			// 최대 사용시간 카운터 Time.	(초단위로 계산하여 저장 / [0] 가장최대 [1] 다음 최대 [2])

	__int64			iCall = 0;				// 누적 호출 횟수.
};

PROFILE_SAMPLE Profiler::Profile_Samples[Profiler::MAXITEM];

Profiler::~Profiler()
{
	time_t timer = time(NULL);
	tm t;
	localtime_s(&t, &timer);
	WCHAR buffer[100];
	wsprintfW(buffer,
		L"profile_%d-%d-%d_%2d%2d.txt",
		t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min);
	ProfileDataOutText(buffer);
}

/*
 * 	TCHAR errBuffer[MAXERRLEN];

	//텍스트 모드로 열 경우 ftell의 값과 파일 크기가 다를 수 있다.
	const auto openRet = _tfopen_s(&_settingStream, location, TEXT("rb"));
	if (openRet != 0 || _settingStream == nullptr)
	{
		_stprintf_s(errBuffer, TEXT("errNo : %d | SettingParser::loadSetting, fopen "), openRet);
		GLogger->write(errBuffer);
		return false;
	}
 */
void Profiler::ProfileDataOutText(LPWSTR szFileName)
{
	FILE* fout;

	const auto openRet = _wfopen_s(&fout, szFileName, L"wb");
	if (openRet != 0 || fout == nullptr)
	{
		WCHAR errBuffer[100];
		WCHAR buffer[100];
		_wcserror_s(buffer, openRet);
		swprintf_s(errBuffer, TEXT("errNo : %d | SettingParser::loadSetting, fopen %s"), openRet, buffer);
		GLogger->write(errBuffer);
		return;
	}
	fwprintf_s(fout, L"\t\tName\t\t|\t\t\tAvg\t\t\t|\t\tCall\t\t|\t\tMin\t\t|\t\tMax\t\t|\t\t\n");

	for (auto& sample : Profile_Samples)
	{
		if (sample.lFlag == false)
			break;

		auto tot = sample.iTotalTime;
		auto cnt = sample.iCall;
		if (sample.iCall > 2)
		{
			tot -= sample.iMax;
			tot -= sample.iMin;
			cnt -= 2;
		}


		auto avg = tot / ((double)cnt);

		fwprintf_s(fout, L"\t%10s\t\t\t\t%10.6fus\t\t\t\t%10lld\t\t\t%10lld\t\t\t%10lld\t\t\n", sample.szName, avg.count(), sample.iCall, sample.iMin.count(), sample.iMax.count());
	}

	fclose(fout);
}


int Profiler::getItemNumber(LPCWSTR name)
{
	for (int i = 0; i < MAXITEM; i++)
	{
		if (Profile_Samples[i].lFlag == false)
		{
			Profile_Samples[i].lFlag = true;
			memcpy_s(Profile_Samples[i].szName, MAXNAME, name, MAXNAME);
			return i;
		}

		if (wcscmp(Profile_Samples[i].szName, name) == 0)
		{
			return i;
		}
	}
	return -1;
}

#define ITEM Profile_Samples[item_number]
void Profiler::applyProfile(const int& item_number, std::chrono::microseconds time)
{
	Profile_Samples[item_number].iCall++;
	Profile_Samples[item_number].iTotalTime += time;

	if (time > Profile_Samples[item_number].iMax)
	{
		Profile_Samples[item_number].iMax = time;
	}
	if (time < Profile_Samples[item_number].iMin)
	{
		Profile_Samples[item_number].iMin = time;
	}
}
#undef ITEM




ProfileItem::ProfileItem(LPCWSTR name)
{
	_itemNumber = Profiler::getItemNumber(name);
	_start = std::chrono::system_clock::now();
}

ProfileItem::~ProfileItem()
{
	_end = std::chrono::system_clock::now();
	Profiler::applyProfile(_itemNumber, std::chrono::duration_cast<std::chrono::microseconds>(_end - _start));
}


