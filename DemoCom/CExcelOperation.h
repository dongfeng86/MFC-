#pragma once

#pragma once
#include "CRange.h"
#include "CApplication.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "CValidation.h"
#include "Cnterior.h"
#include "CFont0.h"
#include "CNames.h"

class ExcelOperation
{
private:
	ExcelOperation();
	~ExcelOperation();
	static ExcelOperation* m_excel;
public:
	static ExcelOperation* getInstance();
	static void destroyInstance();
	BOOL judgeExcelVer(int Ver);
	BOOL createServer(CString officeVer);
	BOOL init();
	void setView(bool show);
	void saveExcelAs(const char* savePath);
	BOOL openExcelFile(const char*path, const char* excleTemplate=nullptr);
	void OpenSheet(const char* sheetName);
	void setCellFormat(const char* ccellIndexChar, const char* cellFormat);
	void setCellsFormat(const char* cellBeginChar, const char* cellBEndChar, const char* cellFormat);
	void setCellValue(const char* ccellIndexChar, const char* valueChar);
	void InitializeUI();
	void UnInitializeUI();
	void saveExcel();
	//void close();

	//add by zdf ¶ÁÈ¡
	CString ReadCell(const char* ccellIndexChar);
	void GetCellFont(const char* ccellIndexChar, CString& sFontName, double& dPoint);
	void GetCellWidth(const char* ccellIndexChar, double& iWidth);

private:
	CApplication m_ExcelApp;
	CWorkbooks m_books;
	CWorkbook m_book;
	CWorksheets m_sheets;
	CWorksheet m_sheet;
	CRange m_range;
	CValidation m_validation;
	Cnterior m_interior;
	CFont0 m_font;
	CNames m_names;
	//CString filePath;
	LPDISPATCH m_lpDisp;
	//Î±ÔìµÄExcelApp
	CApplication m_ExcelApp_fake;
	CWorkbooks m_books_fake;
	int m_ExcelVer;
};

