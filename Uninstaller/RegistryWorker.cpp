#include "stdafx.h"
#include "RegistryWorker.h"


RegistryWorker::RegistryWorker()
{
}

vector<ProgramInfo*> RegistryWorker::GetProgramInfoVectorFromRegistry()
{
	return programInfoVector;
}

void RegistryWorker::SetProgramInfoVector()
{
	ClearProgramInfoVector();
	
	LONG lResult;
	HKEY hUninstallSectionKey;
	TCHAR *lpSubKey = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall");

	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_ENUMERATE_SUB_KEYS, &hUninstallSectionKey);

	if (lResult != ERROR_SUCCESS)
	{
		DWORD error = GetLastError();
		ErrorLogger::Log(error, _T("Key not found\n"));
	}

	InitializeProgramInfoVectorFromUninstallSection(hUninstallSectionKey);	

	if (RegCloseKey(hUninstallSectionKey) != ERROR_SUCCESS)
	{
		DWORD error = GetLastError();
		ErrorLogger::Log(error, _T("Close error\n"));		
	}
}

void RegistryWorker::InitializeProgramInfoVectorFromUninstallSection(HKEY hUninstallSectionKey)
{
	DWORD lResult;
	DWORD subSectionNameLength = STRING_LENGTH;
	DWORD stringClassLength;
	TCHAR subSectionName[STRING_LENGTH] = _T("");
	DWORD subSectionIndex = 0;
	while ((lResult = RegEnumKeyEx(hUninstallSectionKey, subSectionIndex, subSectionName, &subSectionNameLength, NULL, NULL, &stringClassLength, NULL)) != ERROR_NO_MORE_ITEMS && (subSectionIndex < 10))
	{
		if (lResult == ERROR_SUCCESS)
		{
			HKEY hSubSectionKey;
			lResult = RegOpenKeyEx(hUninstallSectionKey, subSectionName, 0, KEY_QUERY_VALUE, &hSubSectionKey);
			if (lResult == ERROR_SUCCESS)
			{
				ProgramInfo *programInfo = GetProgramInfoFromProgramSection(hSubSectionKey, subSectionIndex);
				if (programInfo != NULL)
				{
					programInfoVector.push_back(programInfo);
				}
			}
			RegCloseKey(hSubSectionKey);
		}
		subSectionNameLength = STRING_LENGTH;
		++subSectionIndex;
	}
}

ProgramInfo* RegistryWorker::GetProgramInfoFromProgramSection(HKEY hProgramSectionKey, DWORD programSectionIndex)
{
	DWORD lResult;
	bool hasUninstallString = false;
	TCHAR uninstallString[STRING_LENGTH];
	TCHAR displayName[STRING_LENGTH];

	DWORD parameterIndex = 0;
	DWORD parameterNameLength = STRING_LENGTH;
	BYTE data[STRING_LENGTH];
	DWORD dataLength = STRING_LENGTH;
	TCHAR parameterName[STRING_LENGTH] = _T("");
	while ((lResult = RegEnumValue(hProgramSectionKey, parameterIndex, parameterName, &parameterNameLength, NULL, NULL, data, &dataLength)) == ERROR_SUCCESS)
	{
		if (_tcscmp(parameterName, _T("UninstallString")) == 0)
		{
			hasUninstallString = true;
			_tcscpy_s(uninstallString, (LPTSTR)data);
		}
		if (_tcscmp(parameterName, _T("DisplayName")) == 0)
		{
			_tcscpy_s(displayName, (LPTSTR)data);
		}
		parameterNameLength = STRING_LENGTH;
		dataLength = STRING_LENGTH;
		++parameterIndex;
	}

	if (hasUninstallString)
	{
		return new ProgramInfo(programSectionIndex, displayName, uninstallString);
	}
	else
	{
		return NULL;
	}
}

void RegistryWorker::ClearProgramInfoVector()
{
	for (ProgramInfo* programInfo : programInfoVector)
	{
		delete programInfo;
	}
	programInfoVector.clear();
}

RegistryWorker::~RegistryWorker()
{
}
