#pragma once

#include <CommCtrl.h>
#include "CommonTTypes.h"

class Button
{
public:
	Button(int X, int Y, int nWidth, int nHeight, HWND hWndParent, int btnIdentifier, HINSTANCE hInst, tstring btnName);
	void SetEnabled(bool value);
	~Button();
private:
	HWND hButton;
};

