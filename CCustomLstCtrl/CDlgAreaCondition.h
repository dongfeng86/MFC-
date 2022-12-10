#pragma once

#include "Resource.h"
// CDlgAreaCondition 对话框

class CDlgAreaCondition : public CDialog
{
	DECLARE_DYNAMIC(CDlgAreaCondition)

public:
	CDlgAreaCondition(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgAreaCondition();
	enum { IDD = IDD_CONDITION };
	CString GetCheckItem() const;	//获取用户选中的每一项，用逗号隔开
	void SetCheckItemList(const std::vector<CString>& arItemText);	//添加对话框列表项目

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()

private:
	CListCtrl m_wndLstCtrl;
	CString m_sCheckItem;
	std::vector<CString> m_arItemText;	//列表框中所有项的字符串
};
