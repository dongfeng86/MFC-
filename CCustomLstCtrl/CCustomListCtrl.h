//���ļ�ΪCCustomListCtrl���ͷ�ļ�

#pragma once
#include <afxcmn.h>
#include <vector>
#include <map>
#include "CDlgAreaCondition.h"

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
	//���ñ�ͷ��Ԫ��Ķ��뷽ʽ���μ�DrawText���������ֶ����ʽ
	void SetTextAlign(UINT uFormat = DT_CENTER | DT_SINGLELINE | DT_VCENTER);
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	DECLARE_MESSAGE_MAP()
private:
	UINT m_nTextAlignFormat;	//��ͷ���ֶ��뷽ʽ
};


//��Ԫ��λ�ã�����STL�⺯������
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

//��Ԫ�񵥻�����Ϊ��Ϣ
struct SCellDropListInfo
{
	std::vector<CString> arListString;	//�����б���ʾ����Ŀ,���Ϊ�գ���Ԫ������ɱ༭
	CDialog* pDlg;		//��Ϊnull,���Դ˲���������arListString����öԻ�����Ϊ�б���Ŀ

	//��Ԫ���Ƿ�Ϊ��ϱ༭��
	bool IsCombo() { return (!pDlg && !arListString.empty()); }
	//��Ԫ���Ƿ�Ϊ�༭��
	bool IsEditCell() { return (!pDlg && arListString.empty()); }
	//�Ƿ񵯳������б�ĶԻ���
	bool IsPopListViewDialog() { return (pDlg && !arListString.empty()); }
	//�Ƿ񵯳������Ի���
	bool IsPopOtherDialog() { return (pDlg && arListString.empty()); }
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
	//�����б��и�
	void SetRowHeigt(int nHeight);	
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
	afx_msg void OnComboKillFocs(void);		//��Ԫ��ʧȥ����
	afx_msg void OnEditKillFocs(void);		//��Ԫ��ʧȥ����
	afx_msg void OnEditForButtonKillFocs(void);	//�Ҳ����ť�ĵ�Ԫ��ʧȥ����
	afx_msg void OnBtnClick(void);			//������ť�ؼ�

private:
	CComboBox m_wndCmbTemp;		//���ھ��������б�ĵ�Ԫ��
	CEdit m_wndEdtTemp;			//���ھ��б༭���ܵĵ�Ԫ��
	CEdit m_wndEdtForBtn;		//�����Ҳ����ť�ĵ�Ԫ��
	CButton m_wndBtnTemp;		//����ť��Ԫ���Ҳ�İ�ť
	CDlgAreaCondition* m_pDialog;		//��������ť����ǰ��Ҫ�����ĶԻ���
	std::map<SCellPostion, SCellDropListInfo> m_mapCellPosToInfo;	//ÿ����Ԫ���Ӧ�������б���Ϣ
	int m_uRowHeight;		//��ǰ�б��и�
	SCellPostion m_posCell;	//��ǰѡ�е�Ԫ��λ��
};