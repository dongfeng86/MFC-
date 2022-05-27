#pragma once
#include <afxcmn.h>
#include <vector>
#include <map>

//-----------------------------------------------------------------------------+
//=ClassName:   CCustomHeader
//=Author:      zdf
//=Description: 重绘ListCtrl类的表头
//=Date:        2022-05-27 
//-----------------------------------------------------------------------------+
class CCustomHeader : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CCustomHeader)
public:
	CCustomHeader();
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	DECLARE_MESSAGE_MAP()
};

//
//struct SCellDropListInfo
//{
//	int iItem;		//项序号
//	int iSubItem;	//子项序号
//	std::vector<CString> arListString;	//下拉列表显示的条目,如果为空，单元格仅仅可编辑
//	CDialog* pDlg;	//若为null,忽略此参数；否则将arListString传入该对话框作为列表条目
//};

struct SCellPostion
{
	int iXPos;
	int iYPos;

	SCellPostion(int ix = 0, int iy = 0)
	{
		iXPos = ix;
		iYPos = iy;
	}

	bool operator==(const SCellPostion& pos) const
	{
		return (iXPos == pos.iXPos && iYPos == pos.iYPos);
	}

	bool operator<(const SCellPostion& pos) const
	{
		if (iXPos == pos.iXPos)
			return iYPos < pos.iYPos;
		return iXPos < pos.iXPos;
	}

	bool operator>(const SCellPostion& pos) const
	{
		return !(*this < pos);
	}
};

struct SCellDropListInfo
{
	std::vector<CString> arListString;	//下拉列表显示的条目,如果为空，单元格仅仅可编辑
	CDialog* pDlg;	//若为null,忽略此参数；否则将arListString传入该对话框作为列表条目
};

//-----------------------------------------------------------------------------+
//=ClassName:   CCustomListCtrl
//=Author:      zdf
//=Description: 重绘ListCtrl类，使其可以改变行高，可编辑
//=Date:        2022-05-27 
//-----------------------------------------------------------------------------+
class CCustomListCtrl :	public CListCtrl
{
	DECLARE_DYNAMIC(CCustomListCtrl)
public:
	CCustomListCtrl();
	void SetRowHeigt(int nHeight);	//设置行高
	//设置表格中某个单元格的下拉菜单
	void SetCellDropList(int iItem, int iSubItem, const std::vector<CString>& arListString, CDialog* pDlg = NULL);

protected:
	DECLARE_MESSAGE_MAP();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnCellSelectItem(void);	//点击单元格后选择某个列表项
	afx_msg void OnComboKillFocs(void);	//单元格失去焦点
	afx_msg void OnEditKillFocs(void);	//单元格失去焦点
	afx_msg void OnDropDown(void);	//准备显示下拉菜单
private:
	std::map<SCellPostion, SCellDropListInfo> m_mapCellPosToInfo;	//每个单元格对应的下拉列表信息
	CComboBox m_wndCmbTemp;
	CEdit m_wndEdtTemp;
	int m_uRowHeight;
	SCellPostion m_posCell;	//当前选中单元格位置
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

