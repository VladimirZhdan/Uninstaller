#pragma once

#include "Dialog.h"
#include "resource.h"

class AboutDialog : public Dialog
{
public:
	AboutDialog(HWND hWndParent);
	~AboutDialog();
private:
	friend INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

