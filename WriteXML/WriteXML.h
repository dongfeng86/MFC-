
// WriteXML.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWriteXMLApp:
// �йش����ʵ�֣������ WriteXML.cpp
//

class CWriteXMLApp : public CWinAppEx
{
public:
	CWriteXMLApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWriteXMLApp theApp;