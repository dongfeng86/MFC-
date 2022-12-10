#ifndef _CNUMSPINCTRL_H_
#define _CNUMSPINCTRL_H_

class CNumSpinCtrl : public CSpinButtonCtrl
{
public:
	CNumSpinCtrl();
	virtual ~CNumSpinCtrl();
	//获取旋转按钮控件的最小、最大、增量值；当bInfinite为真时，说明该控件范围为无限，忽略
	//dLower\dUpper参数
	void GetRangeAndDelta(double &dLower, double& dUpper, double& dDelta, BOOL& bInfinite);
	//设置旋转按钮控件的最小、最大、增量值；当bInfinite为真时，说明该控件范围为无限，忽略
	//dLower\dUpper参数
	void SetRangeAndDelta(double dLower, double dUpper, double dDelta, BOOL bInfinite = FALSE);
	//获取旋转按钮控件当前的值
	double GetPos();
	//设置旋转按钮控件的位置（值）
	void SetPos(double val);
	//获取浮点值小数点位数，当返回-1时浮点数的格式为%g
	int  GetDecimalPlaces();
	//设置浮点值小数点的位数，当参数为-1时浮点数的格式为%g
	void SetDecimalPlaces(int num_places);
	//设置浮点数显示的格式字符串
	void SetFormatString(LPCTSTR lpszFormatString = NULL);
	//设置是截掉尾部0
	void SetTrimTrailingZeros(BOOL bTrim) { m_bTrimTrailingZeros = bTrim; }
	//获取是否截掉尾部0
	BOOL GetTrimTrailingZeros() { return m_bTrimTrailingZeros; }

protected:
	virtual void PreSubclassWindow();	//利用对话框模板生成的控件，在附加窗口时调用该函数
	void InitSpinCtrl();
	void SetIntPos(double pos);
	void SetValueForBuddy(double val);
	CString FormatValue(double val);

	afx_msg BOOL OnDeltapos(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);//调用Create生成的控件，调用此函数
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
