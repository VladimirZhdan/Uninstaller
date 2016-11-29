#pragma once

#include <Windows.h>
#include <vector>
//own files
#include "ProgramInfo.h"
#include "ErrorLogger.h"

#define STRING_LENGTH 256

using namespace std;

class RegistryWorker
{
public:
	RegistryWorker();
	vector<ProgramInfo*> GetProgramInfoVectorFromRegistry();
	~RegistryWorker();

private:
	void SetProgramInfoVector();
	void InitializeProgramInfoVectorFromUninstallSection(HKEY hUninstallSectionKey);
	ProgramInfo* GetProgramInfoFromProgramSection(HKEY hProgramSectionKey, DWORD programSectionIndex);
	void ClearProgramInfoVector();	
	vector<ProgramInfo*> programInfoVector;	
	
};

