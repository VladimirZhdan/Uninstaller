#pragma once

#include "Window.h"
#include "WindowManager.h"
#include "StaticText.h"
#include "ProgramInfo.h"
#include "Button.h"
#include "FileLogic.h"
#include "ErrorLogger.h"
#include "RegistryWorker.h"
#include <process.h>

#define ID_BTN_INSTALL	1000
#define ID_BTN_OK		1001
#define ID_BTN_CANCEL	1002

class UninstallWindow : public Window
{
public:
	UninstallWindow(ProgramInfo *program);
	void CloseWindow();	
	void RunUninstallProgram();
	~UninstallWindow();
private:
	void Init();
	void SetParams(ProgramInfo *program);
	void RunProgram(tstring programPath);
	void FinishUninstallingProgram(); 
	void CancelUninstallingProgram();

	friend LRESULT CALLBACK UninstallWndProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);	

	static HANDLE hMutex;
	friend unsigned __stdcall WaitingUninstallProgramThreadFunc(void* param);
	static bool isTerminateWaitingUninstallProgramThread;
	static bool isCurrentProgramUninstalled;
	//Controls
	StaticText *labelProgramName;
	StaticText *programName;
	StaticText *uninstallStatus;
	ProgramInfo *currentUninstallProgram;
	Button *btnRemove;
	Button *btnOK;
	Button *btnCancel;
};

