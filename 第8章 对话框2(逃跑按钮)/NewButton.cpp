// NewButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NewButton.h"


// CNewButton

IMPLEMENT_DYNAMIC(CNewButton, CButton)

CNewButton::CNewButton()
{

}

CNewButton::~CNewButton()
{
}


BEGIN_MESSAGE_MAP(CNewButton, CButton)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CNewButton ��Ϣ�������



void CNewButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��ȡ���ڸ����ڵ�ʵ��λ�úʹ�С
	CRect rectParent;
	GetParent()->GetWindowRect(&rectParent);

	CRect rectIt;
	GetWindowRect(&rectIt);
	

	static int i=0;
	if((i++)%2==0)
	{
		this->SetWindowPos(NULL,0,0,rectIt.Width(),rectIt.Height(),SWP_NOZORDER);
	}
	else
		this->SetWindowPos(NULL,rectParent.Width()/2,rectParent.Height()/2,rectIt.Width(),rectIt.Height(),SWP_NOZORDER);


	CButton::OnMouseMove(nFlags, point);
}
