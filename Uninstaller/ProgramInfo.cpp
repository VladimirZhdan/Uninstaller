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

bool ProgramInfo::Compare(ProgramInfo * obj)
{
	if (obj == NULL)
	{
		return false;
	}
	if (this == obj)
	{
		return true;
	}	
	if (this->displayIcon != obj->displayIcon)
	{
		return false;
	}
	if (this->displayName != obj->displayName)
	{
		return false;
	}
	if (this->uninstallString != obj->uninstallString)
	{
		return false;
	}
	if (this->size != obj->size)
	{
		return false;
	}
	if (this->version != obj->version)
	{
		return false;
	}
	if (this->installDate != obj->installDate)
	{
		return false;
	}
	if (this->company != obj->company)
	{
		return false;
	}
	return true;
}

ProgramInfo::~ProgramInfo()
{
}


