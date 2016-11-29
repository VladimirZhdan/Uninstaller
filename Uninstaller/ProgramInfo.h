#pragma once

#include "TString.h"

class ProgramInfo
{
public:
	ProgramInfo(int indexInUninstallSection, tstring displayName, tstring uninstallString);
	tstring GetDisplayName();
	tstring GetUninstallString();
	~ProgramInfo();
private:
	int indexInUninstallSection;
	tstring displayName;
	tstring uninstallString;
};

