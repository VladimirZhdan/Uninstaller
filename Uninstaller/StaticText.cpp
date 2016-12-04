#include "stdafx.h"
#include "StaticText.h"


StaticText::StaticText(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst)
{
	hStaticText = CreateWindowEx(
		0,
		(LPCWSTR)WC_EDIT, NULL, WS_VISIBLE | WS_CHILD | ES_LEFT | ES_READONLY | ES_MULTILINE,
		X,
		Y,
		nWidth,
		nHeight,
		hWndParent,
		NULL,
		hInst,
		NULL
	);	
}

void StaticText::SetText(TCHAR *value)
{	
	SendMessage(hStaticText, WM_SETTEXT, NULL, (LPARAM)value);
}

StaticText::~StaticText()
{
}
