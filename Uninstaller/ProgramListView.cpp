#include "stdafx.h"
#include "ProgramListView.h"


ProgramListView::ProgramListView(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst, RECT windowRect)
{
	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;
	if (windowWidth != 0)
	{
		this->ratioX = (double)X / windowWidth;
		this->ratioNWidth = (double)nWidth / windowWidth;
	}
	else
	{
		this->ratioX = 0;
		this->ratioNWidth = 0;
	}
	
	if (windowHeight != 0)
	{
		this->ratioY = (double)Y / windowHeight;
		this->ratioNHeight = (double)nHeight / windowHeight;
	}
	else
	{
		this->ratioY = 0;
		this->ratioNHeight = 0;
	}

	listViewPrograms = new ListView(X, Y, nWidth, nHeight, hWndParent, hInst);
	regWorker = new RegistryWorker();
	programs = regWorker->GetProgramInfoVectorFromRegistry();	
	InitListLiew();
}

void ProgramListView::ChangeSize(int newWidth, int newHeight)
{
	int x = (int)(newWidth * ratioX);
	int y = (int)(newHeight * ratioY);
	int nWidht = (int)(newWidth * ratioNWidth);
	int nHeight = (int)(newHeight * ratioNHeight);
	listViewPrograms->ChangeSize(x, y, nWidht, nHeight);
}

ProgramInfo *ProgramListView::GetSelectedItem()
{
	int selectedRow = listViewPrograms->GetSelectedRow();
	return programs[selectedRow];	
}

void ProgramListView::InitListLiew(bool isRefresh)
{				
	for (int i = 0; i < programs.size(); ++i)
	{
		int imageIndex;
		listViewPrograms->AddImageToListViewImageList((TCHAR*)programs[i]->GetDisplayIcon().c_str(), imageIndex);
		if (imageIndex == -1)
		{
			listViewPrograms->AddImageToListViewImageList((TCHAR*)programs[i]->GetUninstallString().c_str(), imageIndex);
			if (imageIndex == -1)
			{
				listViewPrograms->AddImageToListViewImageList(_T("C:\\Windows\\SysWOW64\\\\msiexec.exe"), imageIndex);
			}
		}
		programImageIndex.push_back(imageIndex);
	}
	listViewPrograms->InitListViewImageLists();

	if (!isRefresh)
	{
		//Inserting Columns	
		listViewPrograms->AddColumn(_T("Приложение"), 0.3);
		listViewPrograms->AddColumn(_T("Размер"), 0.2);
		listViewPrograms->AddColumn(_T("Версия"), 0.2);		
		listViewPrograms->AddColumn(_T("Дата установки"), 0.10);
		listViewPrograms->AddColumn(_T("Компания"), 0.2);
	}

	for (int i = 0; i < programs.size(); ++i)
	{
		int currentRow;
		listViewPrograms->InsertNewRowWithFirstColumn((TCHAR*)programs[i]->GetDisplayName().c_str(), programImageIndex[i], currentRow);
				
		listViewPrograms->SetItem(currentRow, 1, (TCHAR*)programs[i]->GetSize().c_str());
		listViewPrograms->SetItem(currentRow, 2, (TCHAR*)programs[i]->GetVersion().c_str());		
		listViewPrograms->SetItem(currentRow, 3, (TCHAR*)programs[i]->GetInstallDate().c_str());
		listViewPrograms->SetItem(currentRow, 4, (TCHAR*)programs[i]->GetCompany().c_str());
	}
}

void ProgramListView::Refresh()
{		
	delete(regWorker);
	regWorker = new RegistryWorker();
	programs = regWorker->GetProgramInfoVectorFromRegistry();	
	listViewPrograms->Clear();
	InitListLiew(false);
}

ProgramListView::~ProgramListView()
{
	delete regWorker;
}
