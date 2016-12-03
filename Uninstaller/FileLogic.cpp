#include "stdafx.h"
#include "FileLogic.h"

__int64 FileLogic::GetFolderSize(tstring path)
{
	WIN32_FIND_DATA data;
	__int64 size = 0;
	
	tstring fname = path + _T("\\*.*");
	//string fname = path + "\\*.*";
	HANDLE h = FindFirstFile(fname.c_str(), &data);
	if (h != INVALID_HANDLE_VALUE)
	{
		do {
			if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				// make sure we skip "." and "..".  Have to use strcmp here because
				// some file names can start with a dot, so just testing for the 
				// first dot is not suffient.						
				if (_tcscmp(data.cFileName, _T(".")) != 0 && _tcscmp(data.cFileName, _T("..")) != 0)
				//if (strcmp(data.cFileName, ".") != 0 && strcmp(data.cFileName, "..") != 0)
				{
					// We found a sub-directory, so get the files in it too
					fname = path + _T("\\") + data.cFileName;
					// recurrsion here!
					size += GetFolderSize(fname);
				}
			}
			else
			{
				LARGE_INTEGER sz;
				// All we want here is the file size.  Since file sizes can be larger
				// than 2 gig, the size is reported as two DWORD objects.  Below we
				// combine them to make one 64-bit integer.
				sz.LowPart = data.nFileSizeLow;
				sz.HighPart = data.nFileSizeHigh;
				size += sz.QuadPart;
			}
		} while (FindNextFile(h, &data) != 0);
		FindClose(h);
	}
	return size;
}

bool FileLogic::isIcoFile(tstring filePath)
{
	return isTypeFile(filePath, _T("ico"));
}

bool FileLogic::isExeFile(tstring filePath)
{
	return isTypeFile(filePath, _T("exe"));
}

bool FileLogic::isTypeFile(tstring filePath, tstring extension)
{
	int filePathLength = filePath.length();
	int extensionLength = extension.length();
	if (filePathLength > (extensionLength + 1))
	{		
		if (filePath.substr(filePathLength - extensionLength, extensionLength) == extension)
		{
			return true;
		}
	}
	return false;
}

HICON FileLogic::GetIconFromFile(tstring filePath)
{		
	unsigned int iconIndex;
	tstring path = GetIconFilePathEx(filePath, iconIndex);
	HICON result;
	EraseQuotesFromPath(path);
	if (isIcoFile(path))
	{		
		result = ExtractIcon(NULL, path.c_str(), iconIndex);
		return result;
	}
	if (isExeFile(path))
	{
		WORD iconIndexWord = (WORD)iconIndex;		
		result = ExtractAssociatedIcon(NULL, (TCHAR *)path.c_str(), &iconIndexWord);
		return result;
	}
	return NULL;
}

tstring FileLogic::GetIconFilePathEx(tstring filePath, unsigned int &iconIndex)
{	
	iconIndex = 0;
	string tempPath = Convert::TStringToString(filePath);

	/*string str = "\"C:\\uTorrent.exe\\\",0";*/
	regex pat {R"(((.+)\,|.+)(\d+){0,1})"};
	smatch mathes;
	if (regex_search(tempPath, mathes, pat))
	{		
		string index = mathes[3];
		string path;
		if (index.length() != 0)
		{
			iconIndex = stoi(index);
			path = mathes[2];			
		}
		else
		{
			path = mathes[1];
		}
		return Convert::StringToTString(path);		
	}
	return NULL;
}

void FileLogic::GetIconFromFileEx(tstring filePath, HICON &smallIcon, HICON &largeIcon)
{
	smallIcon = NULL;
	largeIcon = NULL;
	HICON result;
	EraseQuotesFromPath(filePath);
	if (isIcoFile(filePath))
	{
		smallIcon = (HICON)LoadImage(NULL, filePath.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
		largeIcon = (HICON)LoadImage(NULL, filePath.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	}
	if (isExeFile(filePath))
	{
		WORD indexIcon;

		ExtractIconEx((TCHAR *)filePath.c_str(), 0, &largeIcon, &smallIcon, 1);
	}	
}

bool FileLogic::isMsiExecFile(tstring filePath)
{	
	if (filePath == _T("msiexec.exe"))
	{
		return true;
	}
	return false;
}

void FileLogic::EraseQuotesFromPath(tstring &path)
{
	TCHAR quoteChar = _T('"');
	if (path.length() > 0)
	{
		if (path[0] == quoteChar)
		{
			path.erase(path.end() - 1);
			path.erase(path.begin());			
		}
	}
}