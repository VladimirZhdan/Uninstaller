#include "stdafx.h"
#include "ProgramInfo.h"

ProgramInfo::ProgramInfo(int indexInUninstallSection, tstring displayName, tstring uninstallString)
{
	this->indexInUninstallSection = indexInUninstallSection;
	this->displayName = displayName;
	this->uninstallString = uninstallString;
}

tstring ProgramInfo::GetDisplayName()
{
	return this->displayName;
}

tstring ProgramInfo::GetUninstallString()
{
	return this->uninstallString;
}

ProgramInfo::~ProgramInfo()
{
}
