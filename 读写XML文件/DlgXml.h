#pragma once

class CDlgXml : public CDialog
{
	DECLARE_DYNAMIC(CDlgXml)
public:
	CDlgXml(CWnd* pParent = NULL);
	virtual ~CDlgXml();
	enum { IDD = IDD_DLG_XML };

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö
	//void ReadXml(CString strXmlPath);
	//void ReadCase(MSXML2::IXMLDOMNodeListPtr nodeList);
	//void ReadXml();
	void WriteXml();
	CString m_fileProjectPath;
public:
	afx_msg void OnBnClickedBtnConnect();
};
