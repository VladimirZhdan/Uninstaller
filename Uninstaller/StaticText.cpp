#include "stdafx.h"
#include "StaticText.h"


StaticText::StaticText(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst)
{
	hStaticText = CreateWindowEx(
		0,
		(LPCWSTR)WC_EDIT, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_SHOWSELALWAYS | LVS_REPORT | LVS_SINGLESEL,
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

void StaticText::SetControlsParams()
{
	SendMessage(hStaticText, EM_SETREADONLY, TRUE, NULL);
	//HFONT hfont = ;
	//SendMessage(hStaticText, WM_SETFONT, , TRUE);
}

void StaticText::SetText(TCHAR *value)
{	
	SendMessage(hStaticText, WM_SETTEXT, NULL, (LPARAM)value);
}

StaticText::~StaticText()
{
}
