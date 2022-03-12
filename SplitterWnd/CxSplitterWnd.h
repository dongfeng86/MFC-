#pragma once
#include <afxwin.h>
class CxSplitterWnd : public CWnd
{
public:
	CxSplitterWnd();
	virtual ~CxSplitterWnd();

	BOOL BindWithControl(CWnd* pParent, DWORD idCtrl);
	void Unbind();
	void SetMinWidth(int left, int right);
	BOOL AttachAsLeftPane(DWORD idCtrl);
	BOOL AttachAsRightPane(DWORD idCtrl);
	BOOL DetachAllPanes(void);
	void RecalcLayout(void);

protected:
	BOOL GetMouseClipRect(LPRECT rcClip, CPoint point);
private:
	CWnd* m_pParent;
	int m_iLeftMin, m_iRightMin;
	CDWordArray m_idLeft, m_idRight;

};

