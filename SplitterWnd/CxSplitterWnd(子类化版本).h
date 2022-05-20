#pragma once

#define WM_SPLITTER_HOR_MOVED (WM_USER+1000)

class CxSplitterWnd : public CWnd
{
public:
	CxSplitterWnd();
	virtual ~CxSplitterWnd();

	//�󶨸�����ؼ���pParentָ�ؼ��ĸ����ڣ�idCtrlָ�ؼ�ID
	BOOL BindWithCtrl(CWnd* pParent, DWORD idCtrl);	
	//����ؼ������İ󶨹�ϵ
	void UnbindCtrl();
	//�����ƶ��ָ��������жԻ����������С����
	void SetMinWidth(int left, int right);	
	//�ָ������Ŀؼ�ID
	BOOL AttachCtrlAsLeftPane(DWORD idCtrl);
	//�ָ����Ҳ�Ŀؼ�ID
	BOOL AttachCtrlAsRightPane(DWORD idCtrl);
	//����ָ�����������Ŀؼ�
	BOOL DetachAllPanes();
	//���ݷָ���λ�ã������Ի��������пؼ�λ��
	void AdjustLayout();

protected:
	//�ָ��������ƶ��ķ�Χ
	BOOL GetMouseClipRect(LPRECT rcClip, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	CWnd* m_pParent;
	int m_iLeftMin, m_iRightMin;
	CDWordArray m_idLeft, m_idRight;
};