#pragma once

#include "Window.h"
#include "resource.h"
#include "CommonTTypes.h"
#include "WindowManager.h"
#include "ProgramListView.h"
#include "DialogManager.h";

#define MAX_LOADSTRING 100

class MainWindow : public Window
{
public:
	MainWindow();
	~MainWindow();
	void Show();
	void Hide();
private:
	//controls
	ProgramListView *listViewPrograms;
	HMENU hMenu;
	//methods
	void Init();
	//friends procs
	friend LRESULT CALLBACK MainWndProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);
	friend LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);	
	//fields	
};

