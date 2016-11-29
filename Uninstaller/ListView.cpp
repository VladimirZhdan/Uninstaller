#include "stdafx.h"
#include "ListView.h"

ListView::ListView(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst)
{
	hListView = CreateWindowEx(0, (LPCWSTR)WC_LISTVIEWW, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_SHOWSELALWAYS | LVS_REPORT, X, Y, nWidth, nHeight, hWndParent, NULL, hInst, NULL);
	countCols = 0;
	countRows = 0;

	memset(&lvCol, 0, sizeof(lvCol)); 
	lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM | LVCF_FMT; 
	lvCol.cx = 0x86;
	lvCol.fmt = LVCFMT_CENTER;

	memset(&lvItem, 0, sizeof(lvItem));
	lvItem.mask = LVIF_TEXT; 
	lvItem.cchTextMax = 256; 		

	SendMessage(hListView, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT); // Set style
}

HWND ListView::GetHWND()
{
	return hListView;
}

void ListView::AddColumn(TCHAR *nameColumn)
{	
	lvCol.pszText = nameColumn;
	SendMessage(hListView, LVM_INSERTCOLUMN, countCols, (LPARAM)&lvCol);	
	++countCols;
}

void ListView::InsertNewRowWithFirstColumn(TCHAR* firstColumnValue, int &rowIndex)
{
	lvItem.iItem = countRows; 
	lvItem.iSubItem = 0;      
	lvItem.pszText = firstColumnValue; 
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

ListView::~ListView()
{
}
