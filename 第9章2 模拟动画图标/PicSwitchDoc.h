
// PicSwitchDoc.h : CPicSwitchDoc ��Ľӿ�
//


#pragma once


class CPicSwitchDoc : public CDocument
{
protected: // �������л�����
	CPicSwitchDoc();
	DECLARE_DYNCREATE(CPicSwitchDoc)

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
	virtual ~CPicSwitchDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


