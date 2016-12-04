#pragma once

#include <CommCtrl.h>
#include <vector>
#include <shellapi.h>
#include "FileLogic.h"

class ListView
{
public:
	ListView(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst);
	HWND GetHWND();
	void InitListViewImageLists();
	void AddImageToListViewImageList(TCHAR *imagePath, int &indexImage);
	void AddColumn(TCHAR *nameColumn, double columnRatio);
	void InsertNewRowWithFirstColumn(TCHAR* firstColumnValue, int imageIndex, int &rowIndex);
	void SetItem(int rowIndex, int columnIndex, TCHAR* value);
	int GetCountColumns();
	void ChangeSize(int newX, int newY, int newWidth, int newHeight);
	int GetSelectedRow();
	void Clear();
	~ListView();
private:
	void InitParamsWithStartValue();
	HWND hListView;	
	LVITEM lvItem;
	LVCOLUMN lvCol;	
	int countCols;
	int countRows;
	std::vector<double> columnRatioVector;
	HIMAGELIST hLarge;
	HIMAGELIST hSmall;
};

