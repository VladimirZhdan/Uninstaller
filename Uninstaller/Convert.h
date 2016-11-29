#pragma once

#include "CommonTTypes.h"
#include <sstream>

class Convert
{
public:
	static tstring ConvertRegDateToTString(tstring date);
	static tstring ConvertSizeDwordToTString(DWORD value);
	static tstring ConvertDoubleToTString(double value);
};

