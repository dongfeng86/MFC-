
// GraphicDoc.h : CGraphicDoc ��Ľӿ�
//


#pragma once


class CGraphicDoc : public CDocument
{
protected: // �������л�����
	CGraphicDoc();
	DECLARE_DYNCREATE(CGraphicDoc)

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
	virtual ~CGraphicDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


