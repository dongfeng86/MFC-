
// WriteXMLDlg.h : ͷ�ļ�
//

#pragma once


// CWriteXMLDlg �Ի���
class CWriteXMLDlg : public CDialog
{
// ����
public:
	CWriteXMLDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WRITEXML };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnWritexml();
	afx_msg void OnBnClickedBtnWriteinit();
	afx_msg void OnBnClickedBtnReadini();
	afx_msg void OnBnClickedBtnReadxml();
};
