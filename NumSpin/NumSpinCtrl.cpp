// NumSpinCtrl.cpp : implementation file
//
// Damir Valiulin, Rocscience Inc.
//
// See header file for usage.
//

#include "stdafx.h"
#include "NumSpinCtrl.h"
#include <math.h>
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define EPS 1.0e-9

/////////////////////////////////////////////////////////////////////////////
// CNumSpinCtrl

CNumSpinCtrl::CNumSpinCtrl()
{
	m_dDelta = 1;
	m_dLowerVal = 0;
	m_dUpperVal = 100;
	m_iRange = 100;
	m_bInfinite = FALSE;

	lconv* pLconv = localeconv ();
	m_chDecSymbol = *pLconv->decimal_point;
	m_bTrimTrailingZeros = TRUE;
	SetDecimalPlaces (-1); // simple formatting through "%g"
	SetFormatString (NULL);
}

CNumSpinCtrl::~CNumSpinCtrl()
{
}

BEGIN_MESSAGE_MAP(CNumSpinCtrl, CSpinButtonCtrl)
	ON_NOTIFY_REFLECT_EX(UDN_DELTAPOS, OnDeltapos)
	ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumSpinCtrl message handlers

void CNumSpinCtrl::SetValueForBuddy (double val)
{
	CWnd* pEdit = GetBuddy();
	if (pEdit)
	{
		CString str;
		if (m_strFormat.IsEmpty ())
			str = FormatValue (val);
		else
			str.Format (m_strFormat, val);
		
		pEdit->SetWindowText (str);
	}
}

void CNumSpinCtrl::SetPos(double val)
{
	SetValueForBuddy (val);
	SetIntPos (val);
}

double CNumSpinCtrl::GetPos()
{
	CWnd* pEdit = GetBuddy();
	if (pEdit)
	{
		CString str;
		pEdit->GetWindowText (str);
		double val = _ttof(str);
		return val;
	}
	else
		return 0.0;
}

void CNumSpinCtrl::GetRangeAndDelta(double &dLower, double& dUpper, double& dDelta, BOOL& bInfinite)
{
	dLower = m_dLowerVal;
	dUpper = m_dUpperVal;
	dDelta = m_dDelta;
	bInfinite = m_bInfinite;
}

void CNumSpinCtrl::SetRangeAndDelta(double dLower, double dUpper, double dDelta, BOOL bInfinite)
{
	m_bInfinite = bInfinite;
	m_dDelta = dDelta;
	if (m_bInfinite)
		return;

	m_dLowerVal = dLower;
	m_dUpperVal = dUpper;

	ASSERT (m_dUpperVal > m_dLowerVal); // reversed min/max is not implemented, although it's probably easy

	//// avoid division by zero
	if (m_dDelta == 0.0)
		return;

	/// Figure out the integer range to use, so that acceleration can work properly
	double range = fabs ((m_dUpperVal - m_dLowerVal) / m_dDelta);
	if (range > (double)UD_MAXVAL)
		m_iRange = UD_MAXVAL;
	else
		m_iRange = (int) range;
	CSpinButtonCtrl::SetRange32 (0, m_iRange);

	/// Set integer position
	SetIntPos (GetPos());
}

void CNumSpinCtrl::SetIntPos (double pos)
{
	// avoid division by zero
	if (m_dUpperVal == m_dLowerVal)
		return;

	int iPos;	
	if (pos < m_dLowerVal)
		iPos = 0;
	else if (pos > m_dUpperVal)
		iPos = m_iRange;
	else
	{
		// where in the range is current position?
		double dPosInRange = (pos - m_dLowerVal) / (m_dUpperVal - m_dLowerVal);
		iPos = (int)(m_iRange * dPosInRange + 0.5);
	}
	CSpinButtonCtrl::SetPos (iPos);
}


BOOL CNumSpinCtrl::OnDeltapos(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pUD = (NM_UPDOWN*)pNMHDR;	
	double dCurVal = GetPos () + m_dDelta * pUD->iDelta;

	if (!m_bInfinite)	//如果时范围有限的旋转按钮控件
	{
		const bool can_wrap = (UDS_WRAP & GetStyle());	//最小、最大值是否首尾循环

		if (pUD->iDelta < 0) // spin down
		{
			double abs_eps = fabs(EPS * max(dCurVal, m_dLowerVal));
			if (abs_eps < EPS)
				abs_eps = EPS;
			if (m_dLowerVal - dCurVal > abs_eps) {  //if (val < m_MinVal){		
				if (can_wrap) {
					dCurVal = m_dUpperVal;
				}
				else {
					dCurVal = m_dLowerVal;
				}
			}
		}
		else  // spin up
		{
			double abs_eps = fabs(EPS * max(dCurVal, m_dUpperVal));
			if (abs_eps < EPS)
				abs_eps = EPS;
			if (dCurVal - m_dUpperVal > abs_eps) {   //if (val > m_MaxVal){		
				if (can_wrap) {
					dCurVal = m_dLowerVal;
				}
				else {
					dCurVal = m_dUpperVal;
				}
			}
		}
	}

	SetValueForBuddy (dCurVal);
	*pResult = 0;

	return FALSE; // let parent process this notification too.
}

int CNumSpinCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSpinButtonCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	InitSpinCtrl();
	
	return 0;
}

void CNumSpinCtrl::PreSubclassWindow() 
{
	CSpinButtonCtrl::PreSubclassWindow();
	InitSpinCtrl();
}

void CNumSpinCtrl::InitSpinCtrl()
{
	//这一句非常重要，否则会出错
	ASSERT ((GetStyle () & UDS_SETBUDDYINT) != UDS_SETBUDDYINT); // Otherwise control won't work properly!

	//ModifyStyle (UDS_SETBUDDYINT, UDS_ARROWKEYS);	
	SetRangeAndDelta (m_dLowerVal, m_dUpperVal, m_dDelta, m_bInfinite); // set default values
}

CString CNumSpinCtrl::FormatValue (double dVal)
{
	CString str;
	
	if (m_iDecPlaces == -1) // no precision specified
	{
		str.Format (_T("%g"), dVal);
		return str;
	}

	CString sFloatFormat;
	// Check which format to use ('e' or 'f')
	bool bExponential;
	sFloatFormat.Format (_T("%g"), dVal);
	if (sFloatFormat.Find (_T('e')) != -1)
	{
		sFloatFormat.Format (_T("%%.%de"), m_iDecPlaces);
		bExponential = true;
	}
	else
	{
		sFloatFormat.Format (_T("%%.%df"), m_iDecPlaces);
		bExponential = false;
	}
	str.Format (sFloatFormat, dVal);

	// Check for trailing zeros and remove them
	if (m_bTrimTrailingZeros)
	{
		if (bExponential)
		{
			// separate base and exponent
			CString strBase, strExponent;
			int e_pos = str.Find (_T('e'));
			strBase = str.Left (e_pos);
			strExponent = str.Right (str.GetLength () - e_pos);
			
			if (str.Find (m_chDecSymbol) != -1){
				strBase.TrimRight (_T('0'));
				strBase.TrimRight (m_chDecSymbol); // if dot is all that's left
			}
			
			str = strBase + strExponent; //reconstruct
		}
		else
		{
			if (str.Find (m_chDecSymbol) != -1){
				str.TrimRight (_T('0'));
				str.TrimRight (m_chDecSymbol); // if dot is all that's left
			}
		}
	}
	
	return str;
}

void CNumSpinCtrl::SetDecimalPlaces(int number)
{
	m_iDecPlaces = number;
}

int CNumSpinCtrl::GetDecimalPlaces()
{
	return m_iDecPlaces;
}

void CNumSpinCtrl::SetFormatString (LPCTSTR lpszFormatString /*= NULL*/)
{
	if (lpszFormatString == NULL)
		m_strFormat.Empty ();
	else
		m_strFormat = lpszFormatString;
}