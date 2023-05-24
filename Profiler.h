#pragma once
#include <chrono>

class ProfileItem;
struct PROFILE_SAMPLE;

class Profiler
{
	friend ProfileItem;
public:
	~Profiler();

	static void ProfileDataOutText(LPWSTR szFileName);

	static void ProfileReset(void) {}

	static const int MAXNAME = 64;

private:
	static const int MAXITEM = 20;

	static int getItemNumber(LPCWSTR name);
	static void applyProfile(const int& item_number, std::chrono::microseconds time);

	static PROFILE_SAMPLE Profile_Samples[MAXITEM];
};

class ProfileItem
{
public:
	ProfileItem(LPCWSTR name);
	~ProfileItem();

private:
	int _itemNumber = 0;
	std::chrono::system_clock::time_point  _start;
	std::chrono::system_clock::time_point  _end;
};


