
// Menu3Doc.h : CMenu3Doc ��Ľӿ�
//


#pragma once


class CMenu3Doc : public CDocument
{
protected: // �������л�����
	CMenu3Doc();
	DECLARE_DYNCREATE(CMenu3Doc)

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
	virtual ~CMenu3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


