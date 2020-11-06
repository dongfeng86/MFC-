
// SerializeDoc.h : CSerializeDoc 类的接口
//


#pragma once


class CSerializeDoc : public CDocument
{
protected: // 仅从序列化创建
	CSerializeDoc();
	DECLARE_DYNCREATE(CSerializeDoc)

// 属性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	CObArray m_obArray;

// 实现
public:
	virtual ~CSerializeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DeleteContents();
};


