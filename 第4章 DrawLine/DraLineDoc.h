
// DraLineDoc.h : CDraLineDoc ��Ľӿ�
//


#pragma once


class CDraLineDoc : public CDocument
{
protected: // �������л�����
	CDraLineDoc();
	DECLARE_DYNCREATE(CDraLineDoc)

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
	virtual ~CDraLineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


