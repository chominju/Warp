
// MapTool.h : MapTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMapToolApp:
// �� Ŭ������ ������ ���ؼ��� MapTool.cpp�� �����Ͻʽÿ�.
//

class CMapToolApp : public CWinAppEx
{
public:
	CMapToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()


	CGraphicDev*			m_pDeviceClass;// = nullptr;
	LPDIRECT3DDEVICE9		m_pGraphicDev;// = nullptr;

};

extern CMapToolApp theApp;
