#pragma once

#include "ListView.h"
#include "RegistryWorker.h"

class ProgramListView
{
public:
	ProgramListView(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst, RECT windowRect);
	void ChangeSize(int newWidth, int newHeight);
	ProgramInfo *GetSelectedItem();
	void Refresh();
	~ProgramListView();

private:
	ListView *listViewPrograms;
	void InitListLiew(bool isRefresh = false);
	RegistryWorker *regWorker;
	vector<ProgramInfo*> programs;
	vector<int> programImageIndex;
	double ratioX;
	double ratioY;
	double ratioNWidth;
	double ratioNHeight;
};

