
// CustomComboBoxDlg.h: 头文件
//

#pragma once
#include <string.h>

class CCustomComboBox :public CComboBox
{
	DECLARE_DYNAMIC(CCustomComboBox)

public:
	CCustomComboBox();
	~CCustomComboBox();

//protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};


class CSWColorComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CSWColorComboBox)

#define MAX_COLOR_COUNT 16
#define MAX_COLOR_NAME	16
	struct TColorProperty
	{
		COLORREF m_clrColor;
		TCHAR m_szName[MAX_COLOR_NAME];
		TColorProperty()
		{
			memset(this, 0, sizeof(TColorProperty));
		};
		TColorProperty(COLORREF color, LPCTSTR lpszName)
			: TColorProperty()
		{
			m_clrColor = color;								// 颜色值
			_tcscpy_s(m_szName, lpszName);
			//strncpy_s(m_szName, lpszName, MAX_COLOR_NAME);	// 颜色名称
		};
	};

public:
	CSWColorComboBox();
	virtual ~CSWColorComboBox();

private:
	static TColorProperty s_clrPropertys[MAX_COLOR_COUNT]; // WEB标准颜色数组

private:
	void CommonConstruct(); // 初始化

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();

protected:
	DECLARE_MESSAGE_MAP()

public:
	// 获取选择色彩值
	COLORREF GetSelColor();

	// 选择色彩项
	void SelectColor(COLORREF color);
	void SelectColor(LPCTSTR lpszName);

	// 删除色彩项
	void DeleteColor(LPCTSTR lpszName);
	void DeleteColor(COLORREF color);

	// 添加色彩项
	int AddColor(LPCTSTR lpszName, COLORREF color);
};


// CCustomComboBoxDlg 对话框
class CCustomComboBoxDlg : public CDialog
{
// 构造
public:
	CCustomComboBoxDlg(CWnd* pParent = nullptr);	// 标准构造函数
	enum { IDD = IDD_CUSTOMCOMBOBOX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CCustomComboBox m_wndCmbCustom;
public:
	afx_msg void OnCbnKillfocusCombo1();
	afx_msg void OnCbnSelchangeCombo1();
private:
	//CComboBox m_wndComboNorml;
	//CSWColorComboBox m_wndCmbNew;
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
