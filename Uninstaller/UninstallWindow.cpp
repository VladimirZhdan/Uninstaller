#include "stdafx.h"
#include "UninstallWindow.h"

UninstallWindow::UninstallWindow() : Window(UninstallWndProc, _T("UNINSTALLWINDOW"), _T("Удаление"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX, 400, 300, WindowManager::GetInstance()->GetWindow(WINDOW_TYPE::MAIN)->GetHwnd())
{

}


UninstallWindow::~UninstallWindow()
{	
}

void UninstallWindow::Init()
{

}

void UninstallWindow::CloseWindow()
{
	WindowManager *windowManager = WindowManager::GetInstance();
	windowManager->ShowWindow(WINDOW_TYPE::MAIN, true);	
}


LRESULT CALLBACK UninstallWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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

