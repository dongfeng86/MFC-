//本文件为CCustomListCtrl类的头文件

#pragma once
#include <afxcmn.h>
#include <vector>
#include <map>
#include "CDlgAreaCondition.h"

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
	//设置表头单元格的对齐方式，参见DrawText函数中文字对齐格式
	void SetTextAlign(UINT uFormat = DT_CENTER | DT_SINGLELINE | DT_VCENTER);
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	DECLARE_MESSAGE_MAP()
private:
	UINT m_nTextAlignFormat;	//表头文字对齐方式
};


//单元格位置，可用STL库函数排序
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

//单元格单击后行为信息
struct SCellDropListInfo
{
	std::vector<CString> arListString;	//下拉列表显示的条目,如果为空，单元格仅仅可编辑
	CDialog* pDlg;		//若为null,忽略此参数；否则将arListString传入该对话框作为列表条目

	//单元格是否为组合编辑框
	bool IsCombo() { return (!pDlg && !arListString.empty()); }
	//单元格是否为编辑框
	bool IsEditCell() { return (!pDlg && arListString.empty()); }
	//是否弹出包含列表的对话框
	bool IsPopListViewDialog() { return (pDlg && !arListString.empty()); }
	//是否弹出其他对话框
	bool IsPopOtherDialog() { return (pDlg && arListString.empty()); }
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
	//设置列表行高
	void SetRowHeigt(int nHeight);	
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
	afx_msg void OnComboKillFocs(void);		//单元格失去焦点
	afx_msg void OnEditKillFocs(void);		//单元格失去焦点
	afx_msg void OnEditForButtonKillFocs(void);	//右侧带按钮的单元格失去焦点
	afx_msg void OnBtnClick(void);			//单击按钮控件

private:
	CComboBox m_wndCmbTemp;		//用于具有下拉列表的单元格
	CEdit m_wndEdtTemp;			//用于具有编辑功能的单元格
	CEdit m_wndEdtForBtn;		//用于右侧带按钮的单元格
	CButton m_wndBtnTemp;		//带按钮单元格右侧的按钮
	CDlgAreaCondition* m_pDialog;		//如果点击按钮，当前需要弹出的对话框
	std::map<SCellPostion, SCellDropListInfo> m_mapCellPosToInfo;	//每个单元格对应的下拉列表信息
	int m_uRowHeight;		//当前列表行高
	SCellPostion m_posCell;	//当前选中单元格位置
};