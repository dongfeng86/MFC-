
// WinIniDoc.h : CWinIniDoc ��Ľӿ�
//


#pragma once


class CWinIniDoc : public CDocument
{
protected: // �������л�����
	CWinIniDoc();
	DECLARE_DYNCREATE(CWinIniDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CWinIniDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


