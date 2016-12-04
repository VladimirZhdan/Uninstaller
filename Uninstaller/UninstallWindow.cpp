#include "stdafx.h"
#include "UninstallWindow.h"

bool UninstallWindow::isTerminateWaitingUninstallProgramThread = true;
bool UninstallWindow::isCurrentProgramUninstalled = false;
HANDLE UninstallWindow::hMutex = CreateMutex(NULL, FALSE, NULL);

UninstallWindow::UninstallWindow(ProgramInfo *program) : Window(UninstallWndProc, _T("UNINSTALLWINDOW"), _T("Удаление"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX, 400, 300, WindowManager::GetInstance()->GetWindow(WINDOW_TYPE::MAIN)->GetHwnd())
{
	SetParams(program);
	Init();
}


UninstallWindow::~UninstallWindow()
{
	delete(programName);
	delete(labelProgramName);
	delete(btnRemove);
}

void UninstallWindow::Init()
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	labelProgramName = new StaticText(10, 10, clientRect.right - 20 - GetSystemMetrics(SM_CXBORDER), 30, hWnd, WindowManager::GetHInstance());		
	labelProgramName->SetText(_T("Удаление программы:"));

	programName = new StaticText(30, 30, clientRect.right - 40 - GetSystemMetrics(SM_CXBORDER), 80, hWnd, WindowManager::GetHInstance());
	programName->SetText((TCHAR *)currentUninstallProgram->GetDisplayName().c_str());	

	uninstallStatus = new StaticText(10, 150, clientRect.right - 40 - GetSystemMetrics(SM_CXBORDER), 20, hWnd, WindowManager::GetHInstance());

	btnRemove = new Button(140, 200, clientRect.right - 280 - GetSystemMetrics(SM_CXBORDER), 30, hWnd, ID_BTN_INSTALL, WindowManager::GetHInstance(), _T("Удалить"));
	btnRemove->SetEnabled(true);

	btnOK = new Button(10, 200, 100, 30, hWnd, ID_BTN_OK, WindowManager::GetHInstance(), _T("OK"));
	btnOK->SetEnabled(false);

	btnCancel = new Button(275, 200, 100, 30, hWnd, ID_BTN_CANCEL, WindowManager::GetHInstance(), _T("Отмена"));
	btnCancel->SetEnabled(true);
}

void UninstallWindow::CloseWindow()
{
	WindowManager *windowManager = WindowManager::GetInstance();
	windowManager->ShowWindow(WINDOW_TYPE::MAIN, true);	
}

void UninstallWindow::SetParams(ProgramInfo * program)
{
	this->currentUninstallProgram = program;
}

void UninstallWindow::RunUninstallProgram()
{
	if (currentUninstallProgram != nullptr)
	{
		RunProgram(currentUninstallProgram->GetUninstallString());
	}	
	
	WaitForSingleObject(UninstallWindow::hMutex, INFINITE);

	isTerminateWaitingUninstallProgramThread = false;
	unsigned int hThread = _beginthreadex(NULL, 0, WaitingUninstallProgramThreadFunc, this, 0, NULL);	
	btnRemove->SetEnabled(false);
	uninstallStatus->SetText(_T("Ожидание завершения удаления..."));

	ReleaseMutex(UninstallWindow::hMutex);
}

unsigned __stdcall WaitingUninstallProgramThreadFunc(void* param)
{
	UninstallWindow *thisWindow = (UninstallWindow*)param;
	ProgramInfo *currentUninstallProgram = thisWindow->currentUninstallProgram;
	bool isProgramExist = true;
	bool isTerminateThread;
	do
	{
		Sleep(1000);
		WaitForSingleObject(UninstallWindow::hMutex, INFINITE);

		isTerminateThread = UninstallWindow::isTerminateWaitingUninstallProgramThread;
		if (!isTerminateThread)
		{
			isProgramExist = RegistryWorker::CheckExistProgramInRegister(currentUninstallProgram);
		}		
		UninstallWindow::isCurrentProgramUninstalled = (!isProgramExist);

		ReleaseMutex(UninstallWindow::hMutex);
	} while (isProgramExist && (!isTerminateThread));	

	if (!isProgramExist)
	{
		thisWindow->FinishUninstallingProgram();
	}
	return 0;
}

void UninstallWindow::FinishUninstallingProgram()
{
	btnCancel->SetEnabled(false);
	btnOK->SetEnabled(true);
	uninstallStatus->SetText(_T("Программа успешна удалена"));
}

void UninstallWindow::CancelUninstallingProgram()
{
	WaitForSingleObject(hMutex, INFINITE);
	if (!isTerminateWaitingUninstallProgramThread)
	{
		isTerminateWaitingUninstallProgramThread = true;
	}
	if (!isCurrentProgramUninstalled)
	{
		btnRemove->SetEnabled(false);
		btnCancel->SetEnabled(false);
		btnOK->SetEnabled(true);
		uninstallStatus->SetText(_T("Деинталляция отменена"));
	}	
	ReleaseMutex(hMutex);
}

//DWORD WINAPI WaitingUninstallProgramThreadFunc(LPVOID param)
//{
//	ProgramInfo *currentUninstallProgram = (ProgramInfo *)param;
//	bool isProgramExist = true;
//	while (isProgramExist && (!UninstallWindow::isTerminateWaitingUninstallProgramThread))
//	{
//		isProgramExist = RegistryWorker::CheckExistProgramInRegister(currentUninstallProgram);
//	}
//	return isProgramExist;		
//}


void UninstallWindow::RunProgram(tstring programPath)
{
	tstring pathTemp(programPath);
	FileLogic::AddQuotesToPath(pathTemp);
	TCHAR *path = (TCHAR *)pathTemp.c_str();
	STARTUPINFO startUpInf = { sizeof(startUpInf) };
	PROCESS_INFORMATION processInf;
	DWORD exitCode;
	
	bool isProcessCreated = CreateProcess(NULL, path, NULL, NULL, FALSE, 0, NULL, NULL, &startUpInf, &processInf);
	if (isProcessCreated)
	{
		WaitForSingleObject(processInf.hThread, INFINITE);
		CloseHandle(processInf.hThread);
		WaitForSingleObject(processInf.hProcess, INFINITE);
		GetExitCodeProcess(processInf.hProcess, &exitCode);
		CloseHandle(processInf.hProcess);
	}
	else
	{
		DWORD error = GetLastError();
		ErrorLogger::Log(error, _T("Can't create process\n"));
	}		
}


LRESULT CALLBACK UninstallWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (message)
	{
	case WM_CREATE:
	{

	}
	break;
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 400;
		lpMMI->ptMinTrackSize.y = 300;
		lpMMI->ptMaxTrackSize.x = 400;
		lpMMI->ptMaxTrackSize.y = 300;
	}
	case WM_COMMAND:
	{		
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (wmEvent == BN_CLICKED)
		{
			int i;
			switch (wmId)
			{
			case ID_BTN_INSTALL:
				{
					UninstallWindow *uninstallWindow = (UninstallWindow*)((WindowManager::GetInstance())->GetWindow(WINDOW_TYPE::UNINSTALL));
					uninstallWindow->RunUninstallProgram();
				}				
				break;
			case ID_BTN_OK:
				SendMessage(hWnd, WM_DESTROY, NULL, NULL);
				break;

			case ID_BTN_CANCEL:
				{
					UninstallWindow *uninstallWindow = (UninstallWindow*)((WindowManager::GetInstance())->GetWindow(WINDOW_TYPE::UNINSTALL));
					uninstallWindow->CancelUninstallingProgram();
				}				
				break;
			}
		}
	}
	break;
	case WM_SIZE:
	{
		int newWidth = LOWORD(lParam);
		int newHeight = HIWORD(lParam);	
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:		
		{			
			UninstallWindow *uninstallWindow = (UninstallWindow*)((WindowManager::GetInstance())->GetWindow(WINDOW_TYPE::UNINSTALL));
			uninstallWindow->CloseWindow();
		}		
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

