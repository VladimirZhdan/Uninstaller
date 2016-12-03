#pragma once

#include "CommonTTypes.h"
#include <sstream>
#include <string.h>

class Convert
{
public:
	static tstring ConvertRegDateToTString(tstring date);
	static tstring ConvertSizeDwordToTString(DWORD value);
	static tstring ConvertDoubleToTString(double value);
	static tstring StringToTString(std::string value);
	static std::string TStringToString(tstring value);	
};

