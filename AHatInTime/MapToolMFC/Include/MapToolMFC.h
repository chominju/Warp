
// MapToolMFC.h : MapToolMFC ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMapToolMFCApp:
// �� Ŭ������ ������ ���ؼ��� MapToolMFC.cpp�� �����Ͻʽÿ�.
//

class CMapToolMFCApp : public CWinAppEx
{
public:
	CMapToolMFCApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMapToolMFCApp theApp;
