#ifndef _CNUMSPINCTRL_H_
#define _CNUMSPINCTRL_H_

class CNumSpinCtrl : public CSpinButtonCtrl
{
public:
	CNumSpinCtrl();
	virtual ~CNumSpinCtrl();
	//��ȡ��ת��ť�ؼ�����С���������ֵ����bInfiniteΪ��ʱ��˵���ÿؼ���ΧΪ���ޣ�����
	//dLower\dUpper����
	void GetRangeAndDelta(double &dLower, double& dUpper, double& dDelta, BOOL& bInfinite);
	//������ת��ť�ؼ�����С���������ֵ����bInfiniteΪ��ʱ��˵���ÿؼ���ΧΪ���ޣ�����
	//dLower\dUpper����
	void SetRangeAndDelta(double dLower, double dUpper, double dDelta, BOOL bInfinite = FALSE);
	//��ȡ��ת��ť�ؼ���ǰ��ֵ
	double GetPos();
	//������ת��ť�ؼ���λ�ã�ֵ��
	void SetPos(double val);
	//��ȡ����ֵС����λ����������-1ʱ�������ĸ�ʽΪ%g
	int  GetDecimalPlaces();
	//���ø���ֵС�����λ����������Ϊ-1ʱ�������ĸ�ʽΪ%g
	void SetDecimalPlaces(int num_places);
	//���ø�������ʾ�ĸ�ʽ�ַ���
	void SetFormatString(LPCTSTR lpszFormatString = NULL);
	//�����ǽص�β��0
	void SetTrimTrailingZeros(BOOL bTrim) { m_bTrimTrailingZeros = bTrim; }
	//��ȡ�Ƿ�ص�β��0
	BOOL GetTrimTrailingZeros() { return m_bTrimTrailingZeros; }

protected:
	virtual void PreSubclassWindow();	//���öԻ���ģ�����ɵĿؼ����ڸ��Ӵ���ʱ���øú���
	void InitSpinCtrl();
	void SetIntPos(double pos);
	void SetValueForBuddy(double val);
	CString FormatValue(double val);

	afx_msg BOOL OnDeltapos(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);//����Create���ɵĿؼ������ô˺���
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bInfinite;
	double m_dLowerVal;
	double m_dUpperVal;
	double m_dDelta;
	UINT m_iRange;
	int m_iDecPlaces;
	CString m_strFormat;
	BOOL m_bTrimTrailingZeros;
	char m_chDecSymbol;
};

#endif
