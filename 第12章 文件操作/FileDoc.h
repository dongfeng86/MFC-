
// FileDoc.h : CFileDoc ��Ľӿ�
//


#pragma once


class CFileDoc : public CDocument
{
protected: // �������л�����
	CFileDoc();
	DECLARE_DYNCREATE(CFileDoc)

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
	virtual ~CFileDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


