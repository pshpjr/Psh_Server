﻿#include "stdafx.h"

CLogger* GLogger = nullptr;
SettingParser* GSettingParser = nullptr;
Profiler* GProfiler = nullptr;

class CoreGlobal
{
	//순서 고려하면서 생성/ 소멸시킬 것
public:
	CoreGlobal()
	{
		GLogger = new CLogger();
		GSettingParser = new SettingParser();
		GProfiler = new Profiler();
	}
	~CoreGlobal()
	{
		delete GProfiler;
		delete GSettingParser;
		delete GLogger;
	}
} GCoreGlobal;