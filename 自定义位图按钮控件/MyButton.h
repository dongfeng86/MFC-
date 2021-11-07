//MyButton.h

#pragma once
#include "afxwin.h"

class CMyButton : public CButton
{
public:
	CMyButton(UINT idBmpNormal,UINT idBmpPress,UINT idBmpHover,UINT idBmpFocus);
	~CMyButton(void);
	void SetBmpId(UINT idBmpNormal,UINT idBmpPress,UINT idBmpHover,UINT idBmpFocus);
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	CBitmap m_bmpNormal;	//����״̬λͼ
	CBitmap m_bmpPress;		//����λͼ
	CBitmap m_bmpHover;		//�����ͣλͼ
	CBitmap m_bmpFocus;		//��ȡ����λͼ

	bool m_bTrackMouseEvent;	//�Ƿ�������״̬
	bool m_bHover;				//����Ƿ���ͣ�Ϸ�
};
