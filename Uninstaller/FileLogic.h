#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include <shellapi.h>
#include <regex>

#include "CommonTTypes.h"
#include "Convert.h"

using namespace std;

class FileLogic
{
public:
	static __int64 GetFolderSize(tstring path);
	static HICON GetIconFromFile(tstring filePath);
	static void GetIconFromFileEx(tstring filePath, HICON &smallIcon, HICON &largeIcon);
	static tstring GetIconFilePathEx(tstring filePath, unsigned int &iconIndex);
	static bool isMsiExecFile(tstring filePath);
	static bool isIcoFile(tstring filePath);
	static bool isExeFile(tstring filePath);
	static void EraseQuotesFromPath(tstring &path);
	static void AddQuotesToPath(tstring &path);
private:
	static bool isTypeFile(tstring filePath, tstring extension);
};

