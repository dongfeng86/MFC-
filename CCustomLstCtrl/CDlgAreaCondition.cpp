// CDlgAreaCondition.cpp: 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include <vector>
#include "CDlgAreaCondition.h"

// CDlgAreaCondition 对话框

IMPLEMENT_DYNAMIC(CDlgAreaCondition, CDialog)

CDlgAreaCondition::CDlgAreaCondition(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONDITION, pParent)
{
}

CDlgAreaCondition::~CDlgAreaCondition()
{
}

CString CDlgAreaCondition::GetCheckItem() const
{
	return m_sCheckItem;
}

void CDlgAreaCondition::SetCheckItemList(const std::vector<CString>& arItemText)
{
	m_arItemText = arItemText;
}

void CDlgAreaCondition::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_wndLstCtrl);
}


BEGIN_MESSAGE_MAP(CDlgAreaCondition, CDialog)
END_MESSAGE_MAP()


BOOL CDlgAreaCondition::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_wndLstCtrl.GetStyle();
	m_wndLstCtrl.ModifyStyle(0, LVS_NOCOLUMNHEADER);
	m_wndLstCtrl.SetExtendedStyle(m_wndLstCtrl.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
	CRect rect;
	m_wndLstCtrl.GetWindowRect(rect);
	m_wndLstCtrl.InsertColumn(0, _T("房间类型"), LVCFMT_CENTER, rect.Width());

	for (int i = 0; i < m_arItemText.size(); i++)
	{
		m_wndLstCtrl.InsertItem(i, m_arItemText[i]);
	}

	return TRUE; 
}


void CDlgAreaCondition::OnOK()
{
	m_sCheckItem.Empty();
	int iCount = m_wndLstCtrl.GetItemCount();
	for (int i = 0; i < iCount; i++)
	{
		if (m_wndLstCtrl.GetCheck(i))
			m_sCheckItem += m_wndLstCtrl.GetItemText(i, 0)+_T(',');
	}
	if(!m_sCheckItem.IsEmpty())
		m_sCheckItem.Delete(m_sCheckItem.GetLength() - 1, 1);

	CDialog::OnOK();
}
