#pragma once


// CCustomHeader

class CCustomHeader : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CCustomHeader)

public:
	CCustomHeader();
	virtual ~CCustomHeader();
	//���ñ�ͷ��Ԫ��Ķ��뷽ʽ���μ�DrawText���������ֶ����ʽ
	void SetTextAlign(UINT uFormat = DT_CENTER | DT_SINGLELINE | DT_VCENTER);

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	DECLARE_MESSAGE_MAP()

private:
	UINT m_nTextAlignFormat;	//��ͷ���ֶ��뷽ʽ
};