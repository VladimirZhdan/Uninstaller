#pragma once

#include <CommCtrl.h>

class StaticText
{
public:
	StaticText(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst);
	void SetText(TCHAR *value);
	~StaticText();
private:
	HWND hStaticText;	
};

