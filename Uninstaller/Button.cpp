#include "stdafx.h"
#include "Button.h"


Button::Button(int X, int Y, int nWidth, int nHeight, HWND hWndParent, int btnIdentifier, HINSTANCE hInst, tstring btnName)
{
	hButton = CreateWindowEx(
		0,
		(LPCWSTR)WC_BUTTON, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | BTNS_BUTTON,
		X,
		Y,
		nWidth,
		nHeight,
		hWndParent,
		(HMENU)btnIdentifier,
		hInst,
		NULL
	);
	SendMessage(hButton, WM_SETTEXT, NULL, (LPARAM)btnName.c_str());
}

void Button::SetEnabled(bool value)
{
	EnableWindow(hButton, value);
}


Button::~Button()
{
}
