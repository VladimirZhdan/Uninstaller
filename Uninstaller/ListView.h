#pragma once

#include <CommCtrl.h>

class ListView
{
public:
	ListView(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst);
	HWND GetHWND();
	void AddColumn(TCHAR *nameColumn);
	void InsertNewRowWithFirstColumn(TCHAR* firstColumnValue, int &rowIndex);
	void SetItem(int rowIndex, int columnIndex, TCHAR* value);
	int GetCountColumns();
	~ListView();
private:
	HWND hListView;	
	LVITEM lvItem;
	LVCOLUMN lvCol;	
	int countCols;
	int countRows;
};

