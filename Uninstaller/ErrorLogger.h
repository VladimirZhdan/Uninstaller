#pragma once

#include <ctime>
#include <iostream>
#include <fstream>
#include "TString.h"

#if defined(UNICODE) || defined(_UNICODE)
#define tofstream std::wofstream
#else
#define tofstream std::ofstream
#endif

using namespace std;

class ErrorLogger
{
public:	
	static void InitializeCriticalSectionForLog();
	static void Log(DWORD error, tstring message);
private:
	void OutputMessage(tstring currTimeStr, DWORD error, tstring message);
	static tstring errorLogFileName;
	static bool isCriticalSectionInitialize;
	static CRITICAL_SECTION *lockObj;
};

