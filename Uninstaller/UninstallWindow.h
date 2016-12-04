#pragma once

#include "Window.h"
#include "WindowManager.h"

class UninstallWindow : public Window
{
public:
	UninstallWindow();
	void CloseWindow();
	~UninstallWindow();
private:
	void Init();

	friend LRESULT CALLBACK UninstallWndProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);	

};

