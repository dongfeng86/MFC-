
// PropDoc.h : CPropDoc ��Ľӿ�
//


#pragma once


class CPropDoc : public CDocument
{
protected: // �������л�����
	CPropDoc();
	DECLARE_DYNCREATE(CPropDoc)

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
	virtual ~CPropDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


