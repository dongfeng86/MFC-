
// Menu2Doc.h : CMenu2Doc ��Ľӿ�
//


#pragma once


class CMenu2Doc : public CDocument
{
protected: // �������л�����
	CMenu2Doc();
	DECLARE_DYNCREATE(CMenu2Doc)

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
	virtual ~CMenu2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


