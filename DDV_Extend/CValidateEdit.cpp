// E:\MFC\MFC_Examples\DDV_Extend\CValidateEdit.cpp: 实现文件
//

#include "pch.h"
#include "DDV_Extend.h"
#include "CValidateEdit.h"


// CValidateEdit

IMPLEMENT_DYNAMIC(CValidateEdit, CEdit)

CValidateEdit::CValidateEdit()
{

}

CValidateEdit::~CValidateEdit()
{
}


void CValidateEdit::SetEditType(EInputType eType)
{
	m_eType = eType;
}

void CValidateEdit::SetRange(double dMin, double dMax, BOOL bApplyMin, BOOL bApplyMax)
{
	if (dMin > dMax)
	{
		double dTemp = dMax;
		dMax = dMin;
		dMin = dTemp;
	}
	m_dMin = dMin;
	m_dMax = dMax;
	m_bApplyMin = bApplyMin;
	m_bApplyMax = bApplyMax;
}

BEGIN_MESSAGE_MAP(CValidateEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_KEYUP()
	ON_CONTROL_REFLECT_EX(EN_KILLFOCUS, &CValidateEdit::OnEnKillfocus)
	ON_CONTROL_REFLECT_EX(EN_SETFOCUS, &CValidateEdit::OnEnSetfocus)
END_MESSAGE_MAP()

// CValidateEdit 消息处理程序
void CValidateEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CString str;
	GetWindowText(str);
	if (kInt == m_eType)
	{
		if (str.GetLength() == 0 && nChar == _T('0')) {
			MessageBox(_T("第一位不可以是0"), _T("天正软件"), MB_ICONERROR);
			return;
		}

		if (_T('0') <= nChar && nChar <= _T('9') || nChar == 0x08)
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		else
			MessageBox(_T("只能输入数字，退格键"), _T("天正软件"), MB_ICONERROR);
	}
	else if (kDouble == m_eType)
	{
		if (nChar == _T('.'))
		{		
			if (str.GetLength() == 0) // 限制第一位不为小数
			{
				MessageBox(_T("第一位不可以是小数点"), _T("天正软件"), MB_ICONERROR);
				return;
			}

			if (str.Find(_T('.')) == -1)	// 限制只允许有一个小数点
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			else
			{
				if (str[0] == '.') 
				{
					SetWindowText(str.Mid(1, str.GetLength()));
					MessageBox(_T("第一位不可以是小数点"), _T("天正软件"), MB_ICONERROR);
				}
				MessageBox(_T("小数点只能输入一次"), _T("天正软件"), MB_ICONERROR);
			}
		}		
		else if ((nChar >= _T('0') && nChar <= _T('9')) || nChar == 0x08) // 数理数字和退格键
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		else
			MessageBox(_T("只能输入数字，退格键"), _T("天正软件"), MB_ICONERROR);
	}
}

void CValidateEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CString str;
	if (m_eType == kDouble)	{
		if (nChar == VK_DECIMAL || nChar == VK_OEM_PERIOD) {
			GetWindowText(str);
			if (str[0] == _T('.')) {
				SetWindowText(str.Mid(1, str.GetLength()));
				MessageBox(_T("第一位不可以是小数点"), _T("天正软件"), MB_ICONERROR);
			}
		}
	}
	else if (m_eType == kInt)	{
		if (nChar == _T('0') || nChar == VK_NUMPAD0) {
			GetWindowText(str);
			if (str[0] == _T('0')) {
				SetWindowText(str.Mid(1, str.GetLength()));
				MessageBox(_T("第一位不可以是0"), _T("天正软件"), MB_ICONERROR);
			}
		}
	}

	CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}

BOOL CValidateEdit::OnEnKillfocus()
{
	CString str;
	GetWindowText(str);
	if (str.IsEmpty())
		return FALSE;

	CRect rect;
	GetClientRect(rect);
	POINTS pt;
	pt.x = (rect.left + rect.right) / 2;
	pt.y = (rect.top + rect.bottom) / 2;
	LPARAM lParam = MAKELPARAM(pt.x, pt.y);

	if (m_eType == kInt)
	{
		int iValue = _ttoi(str);
		if (m_bApplyMin)
			if (fabs(iValue - m_dMin) > FLT_EPSILON && iValue < m_dMin)
			{
				str.Format(_T("请输入大于%g的值"), m_dMin);
				MessageBox(str);
				SetWindowText(m_sLastValue);
				::PostMessage(m_hWnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, WM_LBUTTONUP, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, EM_SETSEL, 0, -1);

			}
		if (m_bApplyMax)
			if (fabs(m_dMax - iValue) > FLT_EPSILON && iValue > m_dMax)
			{
				str.Format(_T("请输入小于%g的值"), m_dMax);
				MessageBox(str);
				SetWindowText(m_sLastValue);
				::PostMessage(m_hWnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, WM_LBUTTONUP, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, EM_SETSEL, 0, -1);

			}
	}
	else if (m_eType == kDouble)
	{
		double dValue = _ttof(str);
		if (m_bApplyMin)
			if (fabs(dValue - m_dMin) > FLT_EPSILON && dValue < m_dMin)
			{
				str.Format(_T("请输入大于%g的值"), m_dMin);
				MessageBox(str);
				SetWindowText(m_sLastValue);
				::PostMessage(m_hWnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, WM_LBUTTONUP, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, EM_SETSEL, 0, -1);
			}
		if (m_bApplyMax)
			if (fabs(m_dMax - dValue) > FLT_EPSILON && dValue > m_dMax)
			{
				str.Format(_T("请输入小于%g的值"), m_dMax);
				MessageBox(str);
				SetWindowText(m_sLastValue);
				::PostMessage(m_hWnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, WM_LBUTTONUP, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, EM_SETSEL, 0, -1);
			}
	}

	return FALSE;
}

BOOL CValidateEdit::OnEnSetfocus()
{
	GetWindowText(m_sLastValue);
	return FALSE;
}