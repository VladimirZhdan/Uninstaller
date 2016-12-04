#pragma once

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
private:
	static HINSTANCE hInstance;
	static int nCmdShow;	
	MainWindow *mainWindow;
	UninstallWindow *uninstallWindow;	
	Window *activeWindow;
	WINDOW_TYPE activeWindowType;
	void CloseActiveWindow();

};

