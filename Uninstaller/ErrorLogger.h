#pragma once

#include <ctime>
#include <iostream>
#include <fstream>
#include "CommonTTypes.h"

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

