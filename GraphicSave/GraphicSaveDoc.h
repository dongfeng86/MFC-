
// GraphicSaveDoc.h : CGraphicSaveDoc ��Ľӿ�
//


#pragma once


class CGraphicSaveDoc : public CDocument
{
protected: // �������л�����
	CGraphicSaveDoc();
	DECLARE_DYNCREATE(CGraphicSaveDoc)

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
	virtual ~CGraphicSaveDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


