
// TextDoc.h : CTextDoc ��Ľӿ�
//


#pragma once


class CTextDoc : public CDocument
{
protected: // �������л�����
	CTextDoc();
	DECLARE_DYNCREATE(CTextDoc)

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
	virtual ~CTextDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


