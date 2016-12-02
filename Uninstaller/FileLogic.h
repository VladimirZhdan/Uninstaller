#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include <shellapi.h>

#include "CommonTTypes.h"

using namespace std;

class FileLogic
{
public:
	static __int64 GetFolderSize(tstring path);
	static HICON GetIconFromFile(tstring filePath);
	static void GetIconFromFileEx(tstring filePath, HICON &smallIcon, HICON &largeIcon);
	static bool isMsiExecFile(tstring filePath);
	static bool isIcoFile(tstring filePath);
	static bool isExeFile(tstring filePath);
private:
	static bool isTypeFile(tstring filePath, tstring extension);
};

