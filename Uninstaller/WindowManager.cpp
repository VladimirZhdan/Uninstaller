#include "stdafx.h"
#include "WindowManager.h"

#include "Window.h"
#include "MainWindow.h"
#include "UninstallWindow.h"


HINSTANCE WindowManager::hInstance;
int WindowManager::nCmdShow;


WindowManager::WindowManager()
{
	mainWindow = NULL;
	uninstallWindow = NULL;
	activeWindow = NULL;
	activeWindowType = WINDOW_TYPE::NONE;
	currentUninstallProgram = NULL;
}


WindowManager::~WindowManager()
{
	if (mainWindow != NULL)
	{
		delete(mainWindow);
	}
	if (uninstallWindow != NULL)
	{
		delete(uninstallWindow);
	}
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
		if (uninstallWindow == NULL && (currentUninstallProgram != NULL))
		{
			uninstallWindow = new UninstallWindow(currentUninstallProgram);
		}		
		return uninstallWindow;
	default:
		return NULL;
	}
}

void WindowManager::ShowWindow(WINDOW_TYPE wndType, bool isCloseActive)
{
	Window* targetWindow = GetWindow(wndType);
	if (isCloseActive)
	{
		CloseActiveWindow();
	}
	targetWindow->Show();
	activeWindow = (Window*)targetWindow;
	activeWindowType = wndType;
}

bool WindowManager::SetUninstallProgram(ProgramInfo * uninstallProgram)
{
	if (currentUninstallProgram == NULL)
	{
		currentUninstallProgram = uninstallProgram;
		return true;
	}
	else
	{
		return false;
	}	
}

void WindowManager::CloseActiveWindow()
{
	if ((activeWindow != NULL) && (activeWindowType != WINDOW_TYPE::NONE))
	{
		activeWindow->Hide();
		activeWindow = NULL;
		switch (activeWindowType)
		{
		case WINDOW_TYPE::MAIN:
			delete(mainWindow);
			mainWindow = NULL;
			break;
		case WINDOW_TYPE::UNINSTALL:
			delete(uninstallWindow);
			uninstallWindow = NULL;
			currentUninstallProgram = NULL;
			break;
		default:
			break;
		}
		activeWindowType = WINDOW_TYPE::NONE;
	}
}
