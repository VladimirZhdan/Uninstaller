#pragma once

#include "Window.h"
#include "WindowManager.h"
#include "StaticText.h"
#include "ProgramInfo.h"

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
	StaticText *labelProgramName;
	StaticText *programName;
	ProgramInfo *currentUninstallProgram;
};

