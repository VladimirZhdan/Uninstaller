#pragma once

#include "ProgramInfo.h"

enum class WINDOW_TYPE { NONE, MAIN, UNINSTALL };

class Window;
class MainWindow;
class UninstallWindow;



class WindowManager
{
public:
	WindowManager();
	~WindowManager();
	static void SetAppParams(HINSTANCE hInstanceValue, int nCmdShowValue)
	{
		hInstance = hInstanceValue;
		nCmdShow = nCmdShowValue;
	}	
	static HINSTANCE GetHInstance()
	{
		return hInstance;
	}
	static int GetNCmdShow()
	{
		return nCmdShow;
	}
	static WindowManager* GetInstance();
	Window* GetWindow(WINDOW_TYPE wndType);
	void ShowWindow(WINDOW_TYPE wndType, bool isCloseActive = false);
	bool SetUninstallProgram(ProgramInfo *uninstallProgram);
private:
	//fields
	static HINSTANCE hInstance;
	static int nCmdShow;	
	MainWindow *mainWindow;
	UninstallWindow *uninstallWindow;	
	Window *activeWindow;
	WINDOW_TYPE activeWindowType;
	ProgramInfo *currentUninstallProgram;
	//methods
	void CloseActiveWindow();

};

