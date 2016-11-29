#pragma once

#include "ListView.h"
#include "RegistryWorker.h"

class ProgramListView
{
public:
	ProgramListView(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst);
	~ProgramListView();

private:
	ListView *listViewPrograms;
	void InitListLiew();
	RegistryWorker *regWorker;
	vector<ProgramInfo*> programs;
};

