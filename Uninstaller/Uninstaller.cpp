// Uninstaller.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Uninstaller.h"
#include "WindowManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_UNINSTALLER));
	WindowManager::SetAppParams(hInstance, nCmdShow);
	WindowManager *windowManager = WindowManager::GetInstance();
	windowManager->ShowWindow(WINDOW_TYPE::MAIN);

	MSG msg;
	int ret;
	while ((ret = GetMessage(&msg, nullptr, 0, 0)) != 0)
	{
		if (ret == -1)
		{
			return -1;
		}
		if (!IsDialogMessage(GetActiveWindow(), &msg))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	return (int)msg.wParam;
}