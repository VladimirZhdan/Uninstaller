#include "stdafx.h"
#include "UninstallWindow.h"


UninstallWindow::UninstallWindow() : Window(UninstallWndProc, _T("UNIN"), _T("Unin"), 400, 300)
{

}


UninstallWindow::~UninstallWindow()
{
}

void UninstallWindow::Init()
{

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

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

