#include "stdafx.h"
#include "Dialog.h"


Dialog::Dialog(DIALOG_PROC dlgProc, int uID, HWND hWndParent)
{
	this->dlgProc = dlgProc;
	this->dlgHWnd = CreateDialog(WindowManager::GetHInstance(), MAKEINTRESOURCE(uID), hWndParent, dlgProc);
}

Dialog::~Dialog()
{
}

HWND Dialog::GetDlgHWND()
{
	return this->dlgHWnd;
}
