#pragma once

#include "Window.h"
#include "WindowManager.h"
#include "StaticText.h"
#include "ProgramInfo.h"
#include "Button.h"

#define ID_BTN_INSTALL	1000
#define ID_BTN_OK		1001
#define ID_BTN_CANCEL	1002

class UninstallWindow : public Window
{
public:
	UninstallWindow(ProgramInfo *program);
	void CloseWindow();	
	~UninstallWindow();
private:
	void Init();
	void SetParams(ProgramInfo *program);

	friend LRESULT CALLBACK UninstallWndProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);	
	//Controls
	StaticText *labelProgramName;
	StaticText *programName;
	ProgramInfo *currentUninstallProgram;
	Button *btnRemove;
	Button *btnOK;
	Button *btnCancel;
};

