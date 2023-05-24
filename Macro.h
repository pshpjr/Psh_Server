#pragma once

/*---------------
	  Crash
---------------*/

#define CRASH(cause)								\
{																			\
	uint32* crash = nullptr;							\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;							\
}

#define ASSERT_CRASH(expr)			\
{																	\
	if (!(expr))												\
	{																\
		CRASH("ASSERT_CRASH");		\
		__analysis_assume(expr);			\
	}																\
}


/*--------------------
		Util Function
---------------------*/

static void to_str(int num, OUT char* dest, int bufferSize)
{
	sprintf_s(dest, bufferSize, "%d", num);
}

#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)


/*--------------------
		Profiler
---------------------*/

#ifdef USEPROFILE
#define PRO_BEGIN(TagName) ProfileItem t__COUNTER__(L#TagName);
#else

#define PRO_BEGIN(TagName)
#define PRO_END(TagName)
#endif

