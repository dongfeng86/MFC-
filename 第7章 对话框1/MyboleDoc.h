
// MyboleDoc.h : CMyboleDoc ��Ľӿ�
//


#pragma once


class CMyboleDoc : public CDocument
{
protected: // �������л�����
	CMyboleDoc();
	DECLARE_DYNCREATE(CMyboleDoc)

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
	virtual ~CMyboleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


