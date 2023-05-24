#include "stdafx.h"

Logger* GLogger = nullptr;
SettingParser* GSettingParser = nullptr;
Profiler* GProfiler = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GLogger = new Logger();
		GSettingParser = new SettingParser();
		GProfiler = new Profiler();
	}
	~CoreGlobal()
	{
		delete GLogger;
		delete GSettingParser;
		delete GProfiler;
	}
} GCoreGlobal;