#pragma once

#include "Resource.h"
#include "afxwin.h"
// CTestDlg �Ի���

class CTestDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestDlg();

// �Ի�������
	enum { IDD = IDD_DLG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAdd();
private:
	CButton m_cBtn;
	BOOL m_bIsCreate;
public:
	afx_msg void OnStnClickedStatic1();
	double m_dNum1;
	double m_dNum2;
	double m_dNum3;

	CEdit m_wndEdit1;
	CEdit m_wndEdit2;
	CEdit m_wndEdit3;
	afx_msg void OnBnClickedBtnShrink();
	virtual BOOL OnInitDialog();

protected:
//	virtual void OnOK();
	virtual void OnOK();
public:
	double m_dTest;
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnEnSetfocusEdit3();
};
