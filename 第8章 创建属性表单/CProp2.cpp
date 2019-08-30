// CProp2.cpp : 实现文件
//

#include "stdafx.h"
#include "CProp2.h"


// CProp2 对话框

IMPLEMENT_DYNAMIC(CProp2, CPropertyPage)

CProp2::CProp2()
	: CPropertyPage(CProp2::IDD)
	, m_bFootBall(FALSE)
	, m_bBasketBall(FALSE)
	, m_bVolBall(FALSE)
	, m_bSwim(FALSE)
{

}

CProp2::~CProp2()
{
}

void CProp2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_bFootBall);
	DDX_Check(pDX, IDC_CHECK3, m_bBasketBall);
	DDX_Check(pDX, IDC_CHECK2, m_bVolBall);
	DDX_Check(pDX, IDC_CHECK4, m_bSwim);
}


BEGIN_MESSAGE_MAP(CProp2, CPropertyPage)
END_MESSAGE_MAP()


// CProp2 消息处理程序

BOOL CProp2::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_BACK|PSWIZB_NEXT);

	return CPropertyPage::OnSetActive();
}

LRESULT CProp2::OnWizardNext()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);

	if(m_bFootBall || m_bBasketBall || m_bSwim ||m_bBasketBall)
	{
		return CPropertyPage::OnWizardNext();
	}
	else
	{
		MessageBox(_T("请选择你的兴趣爱好"));
		return -1;
	}
}
