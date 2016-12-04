#pragma once

#include "resource.h"
#include "WindowManager.h"

typedef LRESULT(CALLBACK *WINDOW_PROC)(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
);

class Window
{
public:
	Window(WINDOW_PROC wndProc, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwWindowStyle, int width, int height, HWND hWndParent);
	virtual ~Window();
	HWND GetHwnd() const
	{
		return hWnd;
	}
	virtual void Show();
	virtual void Hide();	
	static void MoveToCenter(HWND hWnd);
protected:
	static POINT screenCenter;
	static POINT GetHwndCenter(HWND hWnd);
	HWND hWnd;
	virtual void Init() = 0;	

private:
	LPCTSTR lpClassName;
	LPCTSTR lpWindowTitle;
	WINDOW_PROC wndProc;
	ATOM RegisterWindowClass();
	bool InitInstance(DWORD dwWindowStyle, int width, int height, HWND hWndParent);

};

