#include "stdafx.h"
#include "ProgramInfo.h"

ProgramInfo::ProgramInfo(
	int indexInUninstallSection, 
	tstring displayIcon,
	tstring displayName, 
	tstring uninstallString,
	DWORD size, 
	tstring version, 
	tstring installDate, 
	tstring company)
{
	this->indexInUninstallSection = indexInUninstallSection;
	this->displayIcon = displayIcon;
	this->displayName = displayName;
	this->uninstallString = uninstallString;
	this->size = Convert::ConvertSizeDwordToTString(size);
	this->version = version;
	this->installDate = Convert::ConvertRegDateToTString(installDate);
	this->company = company;
	//this->company = company;
}

tstring ProgramInfo::GetDisplayIcon()
{
	return this->displayIcon;
}

tstring ProgramInfo::GetDisplayName()
{
	return this->displayName;
}

tstring ProgramInfo::GetUninstallString()
{
	return this->uninstallString;
}

tstring ProgramInfo::GetSize()
{
	return this->size;
}

tstring ProgramInfo::GetVersion()
{
	return this->version;
}

tstring ProgramInfo::GetInstallDate()
{
	return this->installDate;
}

tstring ProgramInfo::GetCompany()
{
	return this->company;
}

ProgramInfo::~ProgramInfo()
{
}


