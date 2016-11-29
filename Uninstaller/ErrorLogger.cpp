#include "stdafx.h"
#include "ErrorLogger.h"

void ErrorLogger::InitializeCriticalSectionForLog()
{
	/*InitializeCriticalSection(ErrorLogger::lockObj);
	isCriticalSectionInitialize = true;*/
}

void ErrorLogger::Log(DWORD error, tstring message)
{	
	time_t currTime = time(NULL);
	tstring currTimeStr = _tctime(&currTime);		
	currTimeStr.pop_back();
	tofstream outputStream(errorLogFileName, tofstream::app);
	/*if (isCriticalSectionInitialize)
	{
		EnterCriticalSection(lockObj);
	}*/		
	try
	{
		if (outputStream.is_open())
		{
			outputStream << currTimeStr << _T(" : Error-") << error << _T("; ") << message << _T("\n");
		}
	}
	catch(...)
	{
		outputStream.close();
		throw;
	}
	outputStream.close();		
	
	/*if (isCriticalSectionInitialize)
	{	
		LeaveCriticalSection(lockObj);
	}*/	
}

tstring ErrorLogger::errorLogFileName = _T("ErrorLogger.txt");
bool ErrorLogger::isCriticalSectionInitialize = false;
