#include "stdafx.h"
#include "Convert.h"

tstring Convert::ConvertRegDateToTString(tstring date)
{
	if (date.length() == 8)
	{
		tstring year = date.substr(0, 4);
		tstring month = date.substr(4, 2);
		tstring day = date.substr(6, 2);
		return tstring(day + _T(".") + month + _T(".") + year);
	}
	else
	{
		return tstring(date);
	}
}

//RENAME!!!
tstring Convert::ConvertSizeDwordToTString(DWORD value)
{	
	tstring result;
	if (value > 1048576)
	{
		DWORD fullGB = value / 1048576;
		DWORD partGB = (value % 1048576) * 100 / 1048576;
		result = to_tstring(fullGB) + _T(",") + to_tstring(partGB) + _T("GB");
	}
	else
	{
		if (value > 1024)
		{
			DWORD fullMB = value / 1024;
			DWORD partMB = (value % 1024) * 100 / 1024;
			result = to_tstring(fullMB) + _T(",") + to_tstring(partMB) + _T("MB");
		}
		else
		{
			result = to_tstring(value) + _T("B");
		}
	}
	return tstring(result);
}

tstring Convert::ConvertDoubleToTString(double value)
{	
	return tstring(to_tstring(value));
}
