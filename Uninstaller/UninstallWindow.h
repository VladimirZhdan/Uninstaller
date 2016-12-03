#pragma once

#include "Window.h"

class UninstallWindow : public Window
{
public:
	UninstallWindow();
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

