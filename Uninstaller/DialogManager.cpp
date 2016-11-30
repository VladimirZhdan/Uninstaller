#include "stdafx.h"
#include "DialogManager.h"


DialogManager::DialogManager()
{
	aboutDialog = NULL;
}


DialogManager::~DialogManager()
{
}

DialogManager * DialogManager::GetInstance()
{
	static DialogManager instance = DialogManager();
	return &instance;
}

void DialogManager::ShowDialog(DIALOG_TYPE dlgType, HWND hWndParent)
{
	Dialog* dialog = GetDialog(dlgType, hWndParent);
	Window::MoveToCenter(dialog->GetDlgHWND());
	ShowWindow(dialog->GetDlgHWND(), WindowManager::GetNCmdShow());
}



Dialog* DialogManager::GetDialog(DIALOG_TYPE dlgType, HWND hWndParent)
{
	switch (dlgType)
	{
		case DIALOG_TYPE::ABOUT:
			if (aboutDialog == NULL)
			{
				aboutDialog = new AboutDialog(hWndParent);
			}
			return aboutDialog;			
		default:
			return nullptr;
	}
}
