#pragma once
#include <afxcmn.h>

class CCustomHeader : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CCustomHeader)
public:
	CCustomHeader();

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	DECLARE_MESSAGE_MAP()
};

