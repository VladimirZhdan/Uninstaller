#include "stdafx.h"
#include "MainWindow.h"

MainWindow::MainWindow() : Window(MainWndProc, _T("MAINWINDOW"), _T("MainWindow"), 800, 600)
{
	hMenu = LoadMenu(WindowManager::GetHInstance(), MAKEINTRESOURCE(IDC_UNINSTALLER));
	SetMenu(hWnd, hMenu);
	Init();
}


MainWindow::~MainWindow()
{
	
}

void MainWindow::Show()
{
	//Refrech controls
	Window::Show();
}

void MainWindow::Hide()
{
	Window::Hide();
}

void MainWindow::Init()
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	listViewPrograms = new ProgramListView(0, 50, clientRect.right, clientRect.bottom - 50, hWnd, WindowManager::GetHInstance(), clientRect);
}

static MainWindow *mainWindow = (MainWindow*)((WindowManager::GetInstance())->GetWindow(WINDOW_TYPE::MAIN));

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam)
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
		lpMMI->ptMinTrackSize.x = 800;
		lpMMI->ptMinTrackSize.y = 600;		
	}
	case WM_COMMAND:
	{		
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogManager::GetInstance()->ShowDialog(DIALOG_TYPE::ABOUT, hWnd);			
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_SIZE:
	{				
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		if (mainWindow != nullptr)
		{
			mainWindow->listViewPrograms->ChangeSize(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
		}		
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
