#include "stdafx.h"
#include "ListView.h"

ListView::ListView(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst)
{
	hListView = CreateWindowEx(
		0,
		(LPCWSTR)WC_LISTVIEWW, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_SHOWSELALWAYS | LVS_REPORT | LVS_SINGLESEL,
		X,
		Y,
		nWidth,
		nHeight,
		hWndParent,
		NULL,
		hInst,
		NULL);
	countCols = 0;
	countRows = 0;

	memset(&lvCol, 0, sizeof(lvCol)); 
	lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM | LVCF_FMT; 	
	lvCol.fmt = LVCFMT_CENTER;

	memset(&lvItem, 0, sizeof(lvItem));	 
	lvItem.cchTextMax = 256; 		

	SendMessage(hListView, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT); // Set style	
	hLarge = ImageList_Create(64, 64, ILC_MASK | ILC_COLORDDB, 300, 1);
	hSmall = ImageList_Create(32, 32, ILC_MASK | ILC_COLORDDB, 300, 1);
}

HWND ListView::GetHWND()
{
	return hListView;
}

void ListView::InitListViewImageLists()
{						
	ListView_SetImageList(hListView, hLarge, LVSIL_NORMAL);
	ListView_SetImageList(hListView, hSmall, LVSIL_SMALL);		
}

void ListView::AddImageToListViewImageList(TCHAR * imagePath, int &indexImage)
{
	indexImage = -1;
	HICON hiconItem;	
	WORD indexIcon;
	
	if (!FileLogic::isMsiExecFile(imagePath) && (_tcslen(imagePath) != 0))
	{
		hiconItem = FileLogic::GetIconFromFile(imagePath);		
		if (hiconItem != NULL)
		{			

			ImageList_AddIcon(hLarge, hiconItem);
			ImageList_AddIcon(hSmall, hiconItem);
			DestroyIcon(hiconItem);
			indexImage = ImageList_GetImageCount(hSmall) - 1;
		}		
	}	
}

void ListView::AddColumn(TCHAR *nameColumn, double columnRatio)
{		
	columnRatioVector.push_back(columnRatio);
	lvCol.cx = 0x86;
	lvCol.pszText = nameColumn;
	SendMessage(hListView, LVM_INSERTCOLUMN, countCols, (LPARAM)&lvCol);	
	++countCols;
}

void ListView::InsertNewRowWithFirstColumn(TCHAR* firstColumnValue, int imageIndex, int &rowIndex)
{		
	rowIndex = countRows;
	lvItem.iItem = countRows; 
	lvItem.iSubItem = 0;      
	lvItem.pszText = firstColumnValue; 
	lvItem.mask = LVIF_IMAGE | LVIF_TEXT;
	lvItem.iImage = imageIndex;	
	SendMessage(hListView, LVM_INSERTITEM, 0, (LPARAM)&lvItem); 		
	++countRows;
}

void ListView::SetItem(int rowIndex, int columnIndex, TCHAR* value)
{	
	lvItem.iSubItem = columnIndex;
	lvItem.pszText = value;
	SendMessage(hListView, LVM_SETITEM, 0, (LPARAM)&lvItem);
}

int ListView::GetCountColumns()
{
	return countCols;
}

void ListView::ChangeSize(int newX, int newY, int newWidth, int newHeight)
{		
	MoveWindow(hListView, newX, newY, newWidth, newHeight, true);
	int widthVertScrollBar = GetSystemMetrics(SM_CXVSCROLL);
	int listViewWidth = (newWidth - widthVertScrollBar);
	int columnWidth;
	for (int i = 0; i < countCols; ++i)
	{
		columnWidth = (int)(columnRatioVector[i] * listViewWidth);
		ListView_SetColumnWidth(hListView, i, columnWidth);
	}	
}

int ListView::GetSelectedRow()
{
	int selectedItemNumber;
	selectedItemNumber = SendMessage(hListView, LVM_GETSELECTIONMARK, NULL, NULL);	
	return selectedItemNumber;
}

ListView::~ListView()
{
	ImageList_Destroy(hLarge);
	ImageList_Destroy(hSmall);
}
