
// cgshFillPoly.h : cgshFillPoly Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CcgshFillPolyApp:
// �йش����ʵ�֣������ cgshFillPoly.cpp
//

class CcgshFillPolyApp : public CWinAppEx
{
public:
	CcgshFillPolyApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CcgshFillPolyApp theApp;
