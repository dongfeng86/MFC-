#pragma once

#include "Resource.h"
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
};
