
// ��дXML�ļ�Dlg.h : ͷ�ļ�
//

#pragma once


// C��дXML�ļ�Dlg �Ի���
class C��дXML�ļ�Dlg : public CDialog
{
// ����
public:
	C��дXML�ļ�Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_XML_DIALOG };

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
};
