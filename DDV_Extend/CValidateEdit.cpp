// CValidateEdit.cpp: 实现文件
//

#include "pch.h"
#include "CValidateEdit.h"
#include <algorithm>
#include <functional>

IMPLEMENT_DYNAMIC(CValidateEdit, CEdit)

CValidateEdit::CValidateEdit()
	:m_eType(kDouble)
	,m_bIncludeMin(FALSE)
	,m_bIncludeMax(FALSE)
	,m_dMaxValue(1000)
	,m_dMinValue(0)
	, m_bAllowEmpty(false)
	, m_sPromptLessThanMin(_T("输入数值低于设定最小值！"))
	, m_sPromptMoreThanMax(_T("输入数值高于设定最大值！"))
	, m_sPromptInvalid(_T("请输入合法数值！"))
	, m_sInputEmpty(_T("编辑框不能为空，请输入数值！"))
{
}

CValidateEdit::~CValidateEdit()
{
}

void CValidateEdit::SetEditType(EInputType eType)
{
	m_eType = eType;
}

void CValidateEdit::SetRange(double dMin, double dMax, BOOL bIncludeMin, BOOL bIncludeMax)
{
	if (dMin > dMax)
		std::swap(dMin, dMax);
	m_dMinValue = dMin;
	m_dMaxValue = dMax;
	m_bIncludeMin = bIncludeMin;
	m_bIncludeMax = bIncludeMax;
}

void CValidateEdit::AllowEmpty(bool bAllowEmpty /*= false*/)
{
	m_bAllowEmpty = bAllowEmpty;
}

void CValidateEdit::SetPromptMsg(LPCTSTR pszLessThanMin, LPCTSTR pszMoreThanMax, LPCTSTR pszInvalid, LPCTSTR pszInputEmpty)
{
	m_sPromptLessThanMin = pszLessThanMin;
	m_sPromptMoreThanMax = pszMoreThanMax;
	m_sPromptInvalid = pszInvalid;
	m_sInputEmpty = pszInputEmpty;
}

BEGIN_MESSAGE_MAP(CValidateEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_KEYUP()
	ON_CONTROL_REFLECT_EX(EN_KILLFOCUS, &CValidateEdit::OnEnKillfocus)
	ON_CONTROL_REFLECT_EX(EN_SETFOCUS, &CValidateEdit::OnEnSetfocus)
END_MESSAGE_MAP()

void CValidateEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CString str;
	GetWindowText(str);
	if (kInt == m_eType)
	{
		//整数如果多个位，第1位不能为0
		int nStart, nEnd;
		GetSel(nStart, nEnd);
		if (nStart == 0 && nEnd != str.GetLength() && nChar == _T('0'))
		{
			MessageBox(_T("第一位不可以是0！"), _T("天正软件"), MB_ICONWARNING);
			return;
		}

		if (_T('0') <= nChar && nChar <= _T('9') || nChar == 0x08)
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		else
			//zdf add 20230721 设置输入非法时的提示字符串
			//MessageBox(_T("请输入整数值！"), _T("天正软件"), MB_ICONWARNING);
			MessageBox(m_sPromptInvalid, _T("天正软件"), MB_ICONWARNING);
	}
	else if (kDouble == m_eType)
	{
		if (nChar == _T('.'))
		{
			int nStart, nEnd;
			GetSel(nStart, nEnd);
			if (nStart < nEnd)
				str.Delete(nStart, nEnd - nStart);
			str.Insert(nStart, nChar);
			if (_T('.') == str[0])
			{
				MessageBox(_T("第一位不可以是小数点"), _T("天正软件"), MB_ICONWARNING);
				return;
			}
			else
			{
				int iRepeat = std::count_if((LPCTSTR)str, (LPCTSTR)str + str.GetLength(),
					std::bind2nd(std::equal_to<TCHAR>(), _T('.')));
				if (iRepeat > 1)
				{
					MessageBox(_T("小数点只能输入一次!"), _T("天正软件"), MB_ICONWARNING);
					return;
				}
				else
					CEdit::OnChar(nChar, nRepCnt, nFlags);

			}
		}
		else if ((nChar >= _T('0') && nChar <= _T('9')) || nChar == 0x08) // 数理数字和退格键
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		else
		{
			//zdf add 20230721 设置输入非法时的提示字符串
			//MessageBox(_T("请输入数值！"), _T("天正软件"), MB_ICONWARNING);
			MessageBox(m_sPromptInvalid, _T("天正软件"), MB_ICONWARNING);
			return;
		}
	}
}

BOOL CValidateEdit::OnEnKillfocus()
{
	CWnd* pWnd = GetParent();

	CRect rect;
	GetClientRect(rect);
	POINTS pt;
	pt.x = (rect.left + rect.right) / 2;
	pt.y = (rect.top + rect.bottom) / 2;
	LPARAM lParam = MAKELPARAM(pt.x, pt.y);
	CString str;
	GetWindowText(str);
	// ↓ zdf mod on 20230721 设置输入非法时的提示字符串
	//if (str.IsEmpty())
	if (!m_bAllowEmpty && str.IsEmpty())
	{
		if (pWnd && pWnd->IsWindowVisible())
		{
			SetWindowText(m_sLastValue);
			//str.Format(_T("编辑框不能为空，请输入数值！"));
			//MessageBox(str, _T("天正软件"), MB_ICONWARNING);
			MessageBox(m_sInputEmpty, _T("天正软件"), MB_ICONWARNING);
			//如果下一个消息不是关闭对话框，投递下面消息
			::PostMessage(m_hWnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
			::PostMessage(m_hWnd, WM_LBUTTONUP, MK_LBUTTON, lParam);
			::PostMessage(m_hWnd, EM_SETSEL, 0, -1);
		}
		return TRUE;
	}
	// ↑ zdf mod on 20230721 设置输入非法时的提示字符串

	if (m_eType == kInt)
	{
		int iValue = _ttoi(str);
		if ((m_bIncludeMin ? FALSE : (fabs(iValue - m_dMinValue) < FLT_EPSILON))
			|| iValue < m_dMinValue)
		{
			if (pWnd && pWnd->IsWindowVisible())
			{
				SetWindowText(m_sLastValue);
				MessageBox(m_sPromptLessThanMin, _T("天正软件"), MB_ICONWARNING);
				::PostMessage(m_hWnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, WM_LBUTTONUP, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, EM_SETSEL, 0, -1);
			}
			return TRUE;
		}

		if ((m_bIncludeMax ? FALSE : (fabs(iValue - m_dMaxValue) < FLT_EPSILON))
			|| iValue > m_dMaxValue)
		{
			if (pWnd && pWnd->IsWindowVisible())
			{
				SetWindowText(m_sLastValue);
				MessageBox(m_sPromptMoreThanMax, _T("天正软件"), MB_ICONWARNING);
				::PostMessage(m_hWnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, WM_LBUTTONUP, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, EM_SETSEL, 0, -1);
			}
			return TRUE;
		}
	}
	else if (m_eType == kDouble)
	{
		double dValue = _tstof(str);
		if ((m_bIncludeMin ? FALSE : (fabs(dValue - m_dMinValue) < FLT_EPSILON))
			|| dValue < m_dMinValue)
		{
			if (pWnd && pWnd->IsWindowVisible())
			{
				SetWindowText(m_sLastValue);
				MessageBox(m_sPromptLessThanMin, _T("天正软件"), MB_ICONWARNING);
				::PostMessage(m_hWnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, WM_LBUTTONUP, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, EM_SETSEL, 0, -1);
			}
			return TRUE;
		}

		if ((m_bIncludeMax ? FALSE : (fabs(dValue - m_dMaxValue) < FLT_EPSILON))
			|| dValue > m_dMaxValue)
		{
			if (pWnd && pWnd->IsWindowVisible())
			{
				SetWindowText(m_sLastValue);
				MessageBox(m_sPromptMoreThanMax, _T("天正软件"), MB_ICONWARNING);
				::PostMessage(m_hWnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, WM_LBUTTONUP, MK_LBUTTON, lParam);
				::PostMessage(m_hWnd, EM_SETSEL, 0, -1);
			}
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CValidateEdit::OnEnSetfocus()
{
	GetWindowText(m_sLastValue);
	return FALSE;
}
