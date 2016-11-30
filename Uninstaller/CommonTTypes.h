#pragma once

#include <string>

typedef std::basic_string<TCHAR> tstring;

#if defined(UNICODE) || defined(_UNICODE)
#define tofstream std::wofstream
#define tsprintf swprintf_s
#define to_tstring std::to_wstring
#define tsprintf swprintf_s
#define LoadStringT LoadStringW

#else
#define tofstream std::ofstream
#define tsprintf sprintf_s
#define to_tstring std::to_string
#define tsprintf sprintf_s
#define LoadStringT LoadStringA

#endif
