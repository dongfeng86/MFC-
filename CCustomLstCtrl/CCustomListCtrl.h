#pragma once
#include <afxcmn.h>
#include <vector>
#include <map>

//-----------------------------------------------------------------------------+
//=ClassName:   CCustomHeader
//=Author:      zdf
//=Description: �ػ�ListCtrl��ı�ͷ
//=Date:        2022-05-27 
//-----------------------------------------------------------------------------+
class CCustomHeader : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CCustomHeader)
public:
	CCustomHeader();
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	DECLARE_MESSAGE_MAP()
};

//
//struct SCellDropListInfo
//{
//	int iItem;		//�����
//	int iSubItem;	//�������
//	std::vector<CString> arListString;	//�����б���ʾ����Ŀ,���Ϊ�գ���Ԫ������ɱ༭
//	CDialog* pDlg;	//��Ϊnull,���Դ˲���������arListString����öԻ�����Ϊ�б���Ŀ
//};

struct SCellPostion
{
	int iXPos;
	int iYPos;

	SCellPostion(int ix = 0, int iy = 0)
	{
		iXPos = ix;
		iYPos = iy;
	}

	bool operator==(const SCellPostion& pos) const
	{
		return (iXPos == pos.iXPos && iYPos == pos.iYPos);
	}

	bool operator<(const SCellPostion& pos) const
	{
		if (iXPos == pos.iXPos)
			return iYPos < pos.iYPos;
		return iXPos < pos.iXPos;
	}

	bool operator>(const SCellPostion& pos) const
	{
		return !(*this < pos);
	}
};

struct SCellDropListInfo
{
	std::vector<CString> arListString;	//�����б���ʾ����Ŀ,���Ϊ�գ���Ԫ������ɱ༭
	CDialog* pDlg;	//��Ϊnull,���Դ˲���������arListString����öԻ�����Ϊ�б���Ŀ
};

//-----------------------------------------------------------------------------+
//=ClassName:   CCustomListCtrl
//=Author:      zdf
//=Description: �ػ�ListCtrl�࣬ʹ����Ըı��иߣ��ɱ༭
//=Date:        2022-05-27 
//-----------------------------------------------------------------------------+
class CCustomListCtrl :	public CListCtrl
{
	DECLARE_DYNAMIC(CCustomListCtrl)
public:
	CCustomListCtrl();
	void SetRowHeigt(int nHeight);	//�����и�
	//���ñ����ĳ����Ԫ��������˵�
	void SetCellDropList(int iItem, int iSubItem, const std::vector<CString>& arListString, CDialog* pDlg = NULL);

protected:
	DECLARE_MESSAGE_MAP();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnCellSelectItem(void);	//�����Ԫ���ѡ��ĳ���б���
	afx_msg void OnComboKillFocs(void);	//��Ԫ��ʧȥ����
	afx_msg void OnEditKillFocs(void);	//��Ԫ��ʧȥ����
	afx_msg void OnDropDown(void);	//׼����ʾ�����˵�
private:
	std::map<SCellPostion, SCellDropListInfo> m_mapCellPosToInfo;	//ÿ����Ԫ���Ӧ�������б���Ϣ
	CComboBox m_wndCmbTemp;
	CEdit m_wndEdtTemp;
	int m_uRowHeight;
	SCellPostion m_posCell;	//��ǰѡ�е�Ԫ��λ��
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

