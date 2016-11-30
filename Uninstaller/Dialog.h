#pragma once

#include "WindowManager.h"

typedef INT_PTR(CALLBACK *DIALOG_PROC)(
	HWND hDlg,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
);

class Dialog
{
public:
	Dialog(DIALOG_PROC dlgProc, int uID, HWND hWndParent);
	~Dialog();	
	HWND GetDlgHWND();
private:
	DIALOG_PROC dlgProc;
	HWND dlgHWnd;
};

