
// �༭���ʹ��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C�༭���ʹ��App:
// �йش����ʵ�֣������ �༭���ʹ��.cpp
//

class C�༭���ʹ��App : public CWinAppEx
{
public:
	C�༭���ʹ��App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C�༭���ʹ��App theApp;