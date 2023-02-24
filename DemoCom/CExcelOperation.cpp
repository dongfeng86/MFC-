#include "pch.h"

#include "CExcelOperation.h"
#include <winuser.h>
#include <vector>

void ConstCharConver(const char* pFileName, CString &pWideChar)
{
	//计算char *数组大小，以字节为单位，一个汉字占两个字节
	int charLen = strlen(pFileName);

	//计算多字节字符的大小，按字符计算。
	int len = MultiByteToWideChar(CP_ACP, 0, pFileName, charLen, NULL, 0);

	//为宽字节字符数组申请空间，数组大小为按字节计算的多字节字符大小
	TCHAR *buf = new TCHAR[len + 1];

	//多字节编码转换成宽字节编码
	MultiByteToWideChar(CP_ACP, 0, pFileName, charLen, buf, len);

	buf[len] = '\0';  //添加字符串结尾，注意不是len+1

	//将TCHAR数组转换为CString

	pWideChar.Append(buf);
}

CExcelOperation* CExcelOperation::m_excel = nullptr;

CExcelOperation::CExcelOperation()
{
	m_lpDisp = NULL;
	m_ExcelVer = 0;
}

//获取对象
CExcelOperation* CExcelOperation::getInstance()
{
	if (m_excel == NULL)
	{
		m_excel = new CExcelOperation();
	}
	return m_excel;
}
//销毁对象
void CExcelOperation::destroyInstance()
{
	if (m_excel != NULL)
	{
		delete m_excel;
		m_excel = NULL;
	}
}


BOOL CExcelOperation::judgeExcelVer(int Ver)
{
	HKEY hkey;
	int ret;
	CString str;
	LONG len;
	str.Format(_T("Excel.Application.%d"), Ver);
	str += _T("\\CLSID");
	ret = RegCreateKey(HKEY_CLASSES_ROOT, str, &hkey);
	if (ret == ERROR_SUCCESS)
	{
		RegQueryValue(HKEY_CLASSES_ROOT, str, NULL, &len);
		//如果注册表中 HKEY_CLASSES_ROOT\Excel.Application.x\CPLSID中的值为空，则读取到'\0'，长度为2
		return len == 2 ? FALSE : TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CExcelOperation::createServer(CString officeVer)
{
	//去除前后空格
	officeVer.Trim();
	//获取版本号字符
	CString verNum = officeVer.Right(4);
	int ver = _ttoi(verNum);
	switch (ver)
	{
	case 2003:
		if (judgeExcelVer(11))
		{
			if (m_ExcelApp.CreateDispatch(_T("Excel.Application.11"), NULL))
			{
				m_ExcelVer = 2003;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
		break;
	case 2007:
		if (judgeExcelVer(12))
		{
			if (m_ExcelApp.CreateDispatch(_T("Excel.Application.12"), NULL))
			{
				m_ExcelVer = 2007;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
		break;
	case 2010:
		if (judgeExcelVer(14))
		{
			if (m_ExcelApp.CreateDispatch(_T("Excel.Application.14"), NULL))
			{
				m_ExcelVer = 2010;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
		break;
	case 2013:
		if (judgeExcelVer(15))
		{
			if (m_ExcelApp.CreateDispatch(_T("Excel.Application.15"), NULL))
			{
				m_ExcelVer = 2013;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
		break;
	case 2016:
		if (judgeExcelVer(16))
		{
			if (m_ExcelApp.CreateDispatch(_T("Excel.Application.16"), NULL))
			{
				m_ExcelVer = 2016;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
		break;
	}
	return TRUE;
}

BOOL CExcelOperation::init()
{
	InitializeUI();

	CString strOfficeVer[5] = { _T("office 2003"), _T("office 2007"), _T("office 2010"), _T("office 2013"), _T("office 2016") };
	BOOL result = FALSE;
	for (int i = 4; i >= 0; i--)
	{
		if (!createServer(strOfficeVer[i]))
			continue;
		else
		{
			result = TRUE;
		}
	}
	if (m_ExcelVer == 0)
	{
		result = FALSE;
	}
	return result;
}

void CExcelOperation::setView(bool show)
{
	m_ExcelApp.put_Visible(TRUE);
	m_ExcelApp.put_UserControl(FALSE);
}

void CExcelOperation::saveExcelAs(const char* savePath)
{
	CString savePathCSt;
	ConstCharConver(savePath, savePathCSt);
	savePathCSt.Trim();
	m_book.SaveAs(_variant_t(savePathCSt),
		vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, 0,
		vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing);
}

BOOL CExcelOperation::openExcelFile(const char*path, const char* excleTemplate)
{
	m_lpDisp = NULL;

	/*判断当前Excel的版本*/
	CString strExcelVersion = m_ExcelApp.get_Version();
	int iStart = 0;
	strExcelVersion = strExcelVersion.Tokenize(_T("."), iStart);

	setView(false);

	/*得到工作簿容器*/
	m_books.AttachDispatch(m_ExcelApp.get_Workbooks());

	/*打开一个工作簿，如不存在，则新增一个工作簿*/
	CString strBookPath;
	ConstCharConver(path, strBookPath);
	try
	{
		/*打开一个工作簿*/
		m_lpDisp = m_books.Open(strBookPath,
			vtMissing, vtMissing, vtMissing, vtMissing, vtMissing,
			vtMissing, vtMissing, vtMissing, vtMissing, vtMissing,
			vtMissing, vtMissing, vtMissing, vtMissing);
		m_book.AttachDispatch(m_lpDisp);
	}
	catch (...)
	{
		/*增加一个新的工作簿*/
		if (excleTemplate == nullptr)
		{
			m_lpDisp = m_books.Add(vtMissing);
		}
		else
		{
			m_lpDisp = m_books.Add(_variant_t(excleTemplate));
		}
		m_book.AttachDispatch(m_lpDisp);
		saveExcelAs(path);
	}
	return true;
}

void CExcelOperation::OpenSheet(const char* sheetName)
{
	LPDISPATCH lpDisp = NULL;
	/*得到工作簿中的Sheet的容器*/
	m_sheets.AttachDispatch(m_book.get_Sheets());
	/*打开一个Sheet，如不存在，就新增一个Sheet*/
	CString strSheetName(sheetName);
	try
	{
		/*打开一个已有的Sheet*/
		lpDisp = m_sheets.get_Item(_variant_t(strSheetName));
		m_sheet.AttachDispatch(lpDisp);
	}
	catch (...)
	{
		/*创建一个新的Sheet*/
		lpDisp = m_sheets.Add(vtMissing, vtMissing, _variant_t((long)1), vtMissing);
		m_sheet.AttachDispatch(lpDisp);
		m_sheet.put_Name(strSheetName);
	}
}

void CExcelOperation::setCellFormat(const char* ccellIndexChar, const char* cellFormat)
{
	CString cellIndex, cellFormatChar;
	ConstCharConver(ccellIndexChar, cellIndex);
	ConstCharConver(cellFormat, cellFormatChar);
	m_range = m_sheet.get_Range(_variant_t(cellIndex), _variant_t(cellIndex));
	m_range.put_NumberFormat(_variant_t(cellFormatChar));
}

void CExcelOperation::setCellsFormat(const char* cellBeginChar, const char* cellBEndChar, const char* cellFormat)
{
	CString cellBegin, cellEnd, format;
	ConstCharConver(cellBeginChar, cellBegin);
	ConstCharConver(cellBEndChar, cellEnd);
	ConstCharConver(cellFormat, format);
	m_lpDisp = m_sheet.get_Range(_variant_t(cellBegin), _variant_t(cellEnd));
	m_range.AttachDispatch(m_lpDisp);
	m_range.put_NumberFormatLocal(_variant_t(format));
}

void CExcelOperation::setCellValue(const char* ccellIndexChar, const char* valueChar)
{
	CString cellIndex, value;
	ConstCharConver(ccellIndexChar, cellIndex);
	ConstCharConver(valueChar, value);
	m_range = m_sheet.get_Range(_variant_t(cellIndex), _variant_t(cellIndex));
	m_range.put_Value2(_variant_t(value));
}

void CExcelOperation::InitializeUI()
{
	if (S_OK != CoInitialize(NULL)) {
		AfxMessageBox(_T("Initialize com failed..."));
		return;
	}
}

void CExcelOperation::UnInitializeUI()
{
	CoUninitialize();
}

void CExcelOperation::saveExcel()
{
	m_ExcelApp.put_DisplayAlerts(FALSE);
	//book.Close(vtMissing, vtMissing, vtMissing);
	m_book.Save();
}

CString CExcelOperation::GetAutoWrapText(LPCTSTR pszText, int iCellWidth, int iPointSize, LPCTSTR szFontName)
{
	CString sText;

	//获取当前屏幕的DC
	CWindowDC dcScreen(CWnd::GetDesktopWindow());
	CFont font;
	if (font.CreatePointFont(iPointSize * 10, szFontName, NULL))
	{
		CFont* pOldFont2 = dcScreen.SelectObject(&font);
		TEXTMETRIC tm;
		dcScreen.GetTextMetrics(&tm);

		sText = pszText;
		CString sLine;
		CSize sizeLine;
		for (int iBeg = 0; iBeg < sText.GetLength(); iBeg++)
		{
			if (_T('\n') == sText[iBeg])
			{
				sLine.Empty();
				continue;
			}
			else
			{
				//判断长度
				sLine += sText[iBeg];
				sizeLine = dcScreen.GetTextExtent(sLine);
				if (sizeLine.cx > iCellWidth)
				{
					sText.Insert(iBeg, _T('\r'));
					sLine.Empty();
				}
			}
		}
		dcScreen.SelectObject(pOldFont2);
	}

	return sText;
}

CString CExcelOperation::GetAutoWrapText(const CRange& cell)
{
	if (!cell.m_lpDispatch)
		return _T("");

	VARIANT vResult = const_cast<CRange&>(cell).get_Text();
	CString sCellText = vResult.bstrVal;
	if (sCellText.IsEmpty())
		return sCellText;
	sCellText.Replace(_T("\n"), _T("\r\n"));

	//获取字体信息
	CFont0 fontCell;
	fontCell.AttachDispatch(const_cast<CRange&>(cell).get_Font());
	VARIANT vtFontStyle = fontCell.get_FontStyle();
	VARIANT vtFontName = fontCell.get_Name();
	VARIANT vtSize = fontCell.get_Size();
	CString sFontName = vtFontName.bstrVal; //字样名称
	int iPointSize = vtSize.dblVal;			//字体磅值
	fontCell.ReleaseDispatch();

	//获取单元格宽度
	CWnd* pDeskTop = CWnd::GetDesktopWindow();
	CWindowDC dcScreen(pDeskTop);
	int logPix = dcScreen.GetDeviceCaps(LOGPIXELSX);
	VARIANT vtWidth3 = const_cast<CRange&>(cell).get_Width();
	int iCellWidth = vtWidth3.dblVal * logPix / 72.0;	//单元格宽度（像素）
	VARIANT vtHeight = const_cast<CRange&>(cell).get_Height();
	int iCellHeight = vtHeight.dblVal*logPix / 72.0;	//单元格高度(像素)

	//计算文本自动换行位置
	//这个地方利用非常特殊的方法：由于在EXCEL中无法判断单元格内文字距离单元格边框的距离，因此
	//我们采用了CEdit来模拟EXCEL中的单元格
	CString sResult;
	CFont font;
	if (font.CreatePointFont(iPointSize * 10, sFontName, NULL))
	{
		CEdit m_wndEdtWrapText;
		m_wndEdtWrapText.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
			CRect(0, 0, iCellWidth, iCellHeight), CWnd::GetDesktopWindow(), 1);

		m_wndEdtWrapText.SetFont(&font);
		DWORD dw = m_wndEdtWrapText.GetMargins();
		m_wndEdtWrapText.SetMargins(LOWORD(dw), LOWORD(dw));
		m_wndEdtWrapText.SetWindowText(sCellText);

		CString strLine;
		int iLineLen;
		int nLineCount = m_wndEdtWrapText.GetLineCount();
		for (int i = 0; i < nLineCount; i++)
		{
			iLineLen = m_wndEdtWrapText.LineLength(m_wndEdtWrapText.LineIndex(i));
			m_wndEdtWrapText.GetLine(i, strLine.GetBuffer(iLineLen), iLineLen);
			strLine.ReleaseBuffer(iLineLen);
			sResult += strLine + _T("\r\n");
		}
	}

	return sResult;
}

CString CExcelOperation::ReadCell(const char* ccellIndexChar)
{
	CString sCellIndex;
	ConstCharConver(ccellIndexChar, sCellIndex);
	CRange cell = m_sheet.get_Range(_variant_t(sCellIndex), _variant_t(sCellIndex));
	VARIANT vResult = cell.get_Text();
	VARIANT vResult2 = cell.get_Value2();
	cell.get_WrapText();

	CString sCellText;
	if (vResult.vt == VT_BSTR) //字符串  
	{
		sCellText = vResult.bstrVal;
	}

	return sCellText;
}

void CExcelOperation::GetCellFont(const char* ccellIndexChar,CString& sFontName, double& dPoint)
{
	CString sCellIndex;
	ConstCharConver(ccellIndexChar, sCellIndex);
	CRange cell = m_sheet.get_Range(_variant_t(sCellIndex), _variant_t(sCellIndex));

	CFont0 fontCell;
	fontCell.AttachDispatch(cell.get_Font());
	VARIANT vtFontStyle = fontCell.get_FontStyle();
	VARIANT vtFontName = fontCell.get_Name();
	VARIANT vtSize = fontCell.get_Size();
	fontCell.ReleaseDispatch();

	sFontName = vtFontName.bstrVal;
	dPoint = vtSize.dblVal;
}

void CExcelOperation::GetCellWidth(const char* ccellIndexChar, double& iWidth)
{
	CString sCellIndex;
	ConstCharConver(ccellIndexChar, sCellIndex);
	CRange cell = m_sheet.get_Range(_variant_t(sCellIndex), _variant_t(sCellIndex));	
	VARIANT vWidth3 = cell.get_Width();

	HDC hDc = ::GetDC(NULL);
	int logPix = ::GetDeviceCaps(hDc, LOGPIXELSX);
	iWidth = vWidth3.dblVal * logPix / 72.0;
	ReleaseDC((HWND)NULL, hDc);

	CString ssss = GetAutoWrapText(cell);
	int m = 0;;
	m += 3;
}

bool CExcelOperation::IsWrapCell(const char* ccellIndexChar)
{
	CString sCellIndex;
	ConstCharConver(ccellIndexChar, sCellIndex);
	CRange cell = m_sheet.get_Range(_variant_t(sCellIndex), _variant_t(sCellIndex));
	VARIANT vtWrap = cell.get_WrapText();
	return vtWrap.boolVal;
}

CExcelOperation::~CExcelOperation()
{
	try
	{
		m_books.Close();
		m_sheet.ReleaseDispatch();
		m_sheets.ReleaseDispatch();
		m_book.ReleaseDispatch();
		m_books.ReleaseDispatch();
		m_ExcelApp.ReleaseDispatch();
		m_ExcelApp.Quit();
		//退出伪装的app
		if (!m_ExcelApp_fake.get_ActiveSheet())
		{
			m_books_fake.ReleaseDispatch();
			m_ExcelApp_fake.ReleaseDispatch();
			m_ExcelApp_fake.Quit();
		}
	}
	catch (COleDispatchException*)
	{
		//AfxMessageBox(Notice_get_by_id(IDS_POW_OFF_EXCEL_FAIL));
		AfxMessageBox(_T("关闭Excel服务出错。"));
	}

	UnInitializeUI();
}
