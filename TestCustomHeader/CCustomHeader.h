#pragma once


// CCustomHeader

class CCustomHeader : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CCustomHeader)

public:
	CCustomHeader();
	virtual ~CCustomHeader();
	//设置表头单元格的对齐方式，参见DrawText函数中文字对齐格式
	void SetTextAlign(UINT uFormat = DT_CENTER | DT_SINGLELINE | DT_VCENTER);

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	DECLARE_MESSAGE_MAP()

private:
	UINT m_nTextAlignFormat;	//表头文字对齐方式
};