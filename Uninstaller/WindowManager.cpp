#include "stdafx.h"
#include "WindowManager.h"

#include "Window.h"
#include "MainWindow.h"


HINSTANCE WindowManager::hInstance;
int WindowManager::nCmdShow;


WindowManager::WindowManager()
{
	mainWindow = NULL;
	//unInstallWindow = NULL;
}


WindowManager::~WindowManager()
{
	delete(mainWindow);
}

WindowManager * WindowManager::GetInstance()
{
	static WindowManager instance = WindowManager();
	return &instance;
}

Window * WindowManager::GetWindow(WINDOW_TYPE wndType)
{
	switch (wndType)
	{
	case WINDOW_TYPE::MAIN:
		if (mainWindow == NULL)
		{
			mainWindow = new MainWindow();
		}
		return mainWindow;
	case WINDOW_TYPE::UNINSTALL:
		/*if (loginWindow == NULL)
		{
			loginWindow = new LoginWindow();
		}
		return loginWindow;	*/
	default:
		return NULL;
	}
}

void WindowManager::ShowWindow(WINDOW_TYPE wndType, bool hide_active)
{
	Window* targetWindow = GetWindow(wndType);
	if (hide_active)
	{
		if (activeWindow != NULL)
		{
			activeWindow->Hide();
		}
	}
	targetWindow->Show();
	activeWindow = (Window*)targetWindow;
}
