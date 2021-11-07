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
	CBitmap m_bmpNormal;	//正常状态位图
	CBitmap m_bmpPress;		//按下位图
	CBitmap m_bmpHover;		//鼠标悬停位图
	CBitmap m_bmpFocus;		//获取焦点位图

	bool m_bTrackMouseEvent;	//是否跟踪鼠标状态
	bool m_bHover;				//鼠标是否悬停上方
};
