#include "stdafx.h"
#include "Window.h"

POINT Window::screenCenter = POINT{ 0,0 };

Window::Window(WINDOW_PROC wndProc, LPCTSTR lpClassName, LPCTSTR lpWindowTitle, DWORD dwWindowStyle, int width, int height, HWND hWndParent)
{
	this->lpClassName = lpClassName;
	this->lpWindowTitle = lpWindowTitle;
	this->wndProc = wndProc;
	RegisterWindowClass();	
	InitInstance(dwWindowStyle, width, height, hWndParent);
}

ATOM Window::RegisterWindowClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = this->wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = WindowManager::GetHInstance();
	wcex.hIcon = LoadIcon(WindowManager::GetHInstance(), MAKEINTRESOURCE(IDI_UNINSTALLER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = this->lpClassName;
	wcex.hIconSm = LoadIcon(WindowManager::GetHInstance(), MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

bool Window::InitInstance(DWORD dwWindowStyle, int width, int height, HWND hWndParent)
{
	hWnd = CreateWindow(
		this->lpClassName,
		this->lpWindowTitle,
		dwWindowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		hWndParent,
		nullptr,
		WindowManager::GetHInstance(),
		nullptr);
	if (!hWnd)
	{
		return false;
	}
	return true;
}

void Window::Show()
{
	MoveToCenter(hWnd);
	ShowWindow(hWnd, WindowManager::GetNCmdShow());
	UpdateWindow(hWnd);
	InvalidateRect(hWnd, NULL, TRUE);
}

void Window::Hide()
{
	ShowWindow(hWnd, SW_HIDE);
}

void Window::MoveToCenter(HWND hWnd)
{
	if (screenCenter.x == 0)
	{
		screenCenter = GetHwndCenter(GetDesktopWindow());
	}
	RECT wndRect;
	GetWindowRect(hWnd, &wndRect);
	int width = wndRect.right - wndRect.left;
	int height = wndRect.bottom - wndRect.top;
	SetWindowPos(hWnd, NULL, screenCenter.x - width / 2, screenCenter.y - height / 2, width, height, 0);
}

POINT Window::GetHwndCenter(HWND hWnd)
{
	POINT center;
	RECT wndRect;
	GetWindowRect(hWnd, &wndRect);
	int width = wndRect.right - wndRect.left;
	int height = wndRect.bottom - wndRect.top;
	center.x = width / 2;
	center.y = height / 2;
	return center;
}



Window::~Window()
{
	DestroyWindow(hWnd);
}