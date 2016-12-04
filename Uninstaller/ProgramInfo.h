#pragma once

#include "CommonTTypes.h"
#include "Convert.h"

class ProgramInfo
{
public:
	ProgramInfo(
		int indexInUninstallSection, 
		tstring displayIcon,
		tstring displayName, 
		tstring uninstallString, 
		DWORD size, 
		tstring version, 
		tstring installDate, 
		tstring company);
	tstring GetDisplayIcon();
	tstring GetDisplayName();
	tstring GetUninstallString();	
	tstring GetSize();
	tstring GetVersion();
	//tstring GetType;
	tstring GetInstallDate();
	tstring GetCompany();
	bool Compare(ProgramInfo *obj);
	~ProgramInfo();
private:
	int indexInUninstallSection;
	tstring displayIcon;
	tstring displayName;
	tstring uninstallString;
	tstring size;
	tstring version;
	//tstring type;
	tstring installDate;
	tstring company;	
};

