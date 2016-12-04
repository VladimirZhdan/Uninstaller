#include "stdafx.h"
#include "UninstallWindow.h"

UninstallWindow::UninstallWindow(ProgramInfo *program) : Window(UninstallWndProc, _T("UNINSTALLWINDOW"), _T("Удаление"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX, 400, 300, WindowManager::GetInstance()->GetWindow(WINDOW_TYPE::MAIN)->GetHwnd())
{
	SetParams(program);
	Init();
}


UninstallWindow::~UninstallWindow()
{
	delete(programName);
	delete(labelProgramName);
	delete(btnRemove);
}

void UninstallWindow::Init()
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	labelProgramName = new StaticText(10, 10, clientRect.right - 20 - GetSystemMetrics(SM_CXBORDER), 30, hWnd, WindowManager::GetHInstance());		
	labelProgramName->SetText(_T("Удаление программы:"));

	programName = new StaticText(30, 30, clientRect.right - 40 - GetSystemMetrics(SM_CXBORDER), 80, hWnd, WindowManager::GetHInstance());
	programName->SetText((TCHAR *)currentUninstallProgram->GetDisplayName().c_str());	

	btnRemove = new Button(140, 200, clientRect.right - 280 - GetSystemMetrics(SM_CXBORDER), 30, hWnd, ID_BTN_INSTALL, WindowManager::GetHInstance(), _T("Удалить"));
	btnRemove->SetEnabled(true);

	btnOK = new Button(10, 200, 100, 30, hWnd, ID_BTN_OK, WindowManager::GetHInstance(), _T("OK"));
	btnOK->SetEnabled(false);

	btnCancel = new Button(275, 200, 100, 30, hWnd, ID_BTN_CANCEL, WindowManager::GetHInstance(), _T("Отмена"));
	btnCancel->SetEnabled(true);
}

void UninstallWindow::CloseWindow()
{
	WindowManager *windowManager = WindowManager::GetInstance();
	windowManager->ShowWindow(WINDOW_TYPE::MAIN, true);	
}

void UninstallWindow::SetParams(ProgramInfo * program)
{
	this->currentUninstallProgram = program;
}


LRESULT CALLBACK UninstallWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (message)
	{
	case WM_CREATE:
	{

	}
	break;
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 400;
		lpMMI->ptMinTrackSize.y = 300;
		lpMMI->ptMaxTrackSize.x = 400;
		lpMMI->ptMaxTrackSize.y = 300;
	}
	case WM_COMMAND:
	{		
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (wmEvent == BN_CLICKED)
		{
			int i;
			switch (wmId)
			{
			case ID_BTN_INSTALL:
				i = 0;
				break;
			case ID_BTN_OK:
				i = 1;
				break;

			case ID_BTN_CANCEL:
				//SendMessage(hWnd, WM_DESTROY, NULL, NULL);
				break;
			}
		}
	}
	break;
	case WM_SIZE:
	{
		int newWidth = LOWORD(lParam);
		int newHeight = HIWORD(lParam);	
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:		
		{			
			UninstallWindow *uninstallWindow = (UninstallWindow*)((WindowManager::GetInstance())->GetWindow(WINDOW_TYPE::UNINSTALL));
			uninstallWindow->CloseWindow();
		}		
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

