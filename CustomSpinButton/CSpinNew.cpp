// CSpinNew.cpp: 实现文件
//

#include "pch.h"
#include "CustomSpinButton.h"
#include "CSpinNew.h"


// CSpinNew

IMPLEMENT_DYNAMIC(CSpinNew, CSpinButtonCtrl)

CSpinNew::CSpinNew()
{

}

CSpinNew::~CSpinNew()
{
}


BEGIN_MESSAGE_MAP(CSpinNew, CSpinButtonCtrl)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CSpinNew 消息处理程序




int CSpinNew::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CSpinButtonCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


void CSpinNew::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	CSpinButtonCtrl::PreSubclassWindow();
}
