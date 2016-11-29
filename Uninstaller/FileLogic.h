#pragma once

#include <iostream>
#include <windows.h>
#include <string>

#include "CommonTTypes.h"

using namespace std;

class FileLogic
{
public:
	static __int64 GetFolderSize(tstring path);
};

