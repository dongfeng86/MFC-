
// SerializeDoc.h : CSerializeDoc ��Ľӿ�
//


#pragma once


class CSerializeDoc : public CDocument
{
protected: // �������л�����
	CSerializeDoc();
	DECLARE_DYNCREATE(CSerializeDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	CObArray m_obArray;

// ʵ��
public:
	virtual ~CSerializeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DeleteContents();
};


