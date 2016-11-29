#include "stdafx.h"
#include "ProgramListView.h"


ProgramListView::ProgramListView(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst)
{
	listViewPrograms = new ListView(X, Y, nWidth, nHeight, hWndParent, hInst);
	regWorker = new RegistryWorker();
	programs = regWorker->GetProgramInfoVectorFromRegistry();	
	InitListLiew();
}




void ProgramListView::InitListLiew()
{			
	//Inserting Columns	
	listViewPrograms->AddColumn(_T("Приложение"));
	listViewPrograms->AddColumn(_T("Размер"));
	listViewPrograms->AddColumn(_T("Версия"));
	listViewPrograms->AddColumn(_T("Тип"));
	listViewPrograms->AddColumn(_T("Дата установки"));
	listViewPrograms->AddColumn(_T("Компания"));

	for (int i = 0; i < programs.size(); ++i)
	{
		int currentRow;
		listViewPrograms->InsertNewRowWithFirstColumn((TCHAR*)programs[i]->GetDisplayName().c_str(), currentRow);
				
		listViewPrograms->SetItem(currentRow, 1, (TCHAR*)programs[i]->GetSize().c_str());
		listViewPrograms->SetItem(currentRow, 2, (TCHAR*)programs[i]->GetVersion().c_str());
		//listViewPrograms->SetItem(currentRow, 3, (TCHAR*)programs[i]->GetUninstallString().c_str());
		listViewPrograms->SetItem(currentRow, 4, (TCHAR*)programs[i]->GetInstallDate().c_str());
		listViewPrograms->SetItem(currentRow, 5, (TCHAR*)programs[i]->GetCompany().c_str());
	}


}


ProgramListView::~ProgramListView()
{
	delete regWorker;
}
