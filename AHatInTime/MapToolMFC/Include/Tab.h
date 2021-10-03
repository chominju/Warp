#pragma once
#include "afxcmn.h"

class CTerrainTab;
class CMeshTab;
class CColliderTab;
class CNaviMeshTab;

// CTab 폼 뷰입니다.
class CStage;
class CTab : public CFormView
{
	DECLARE_DYNCREATE(CTab)

protected:
	CTab();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CTab();

public:
	CTerrainTab*	m_pTerrainTab;
	CMeshTab*		m_pMeshTab;
	CColliderTab*	m_pColliderTab;
	CNaviMeshTab*	m_pNaviMeshTab;
	
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	virtual void OnInitialUpdate();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);


	CGraphicDev*			m_pDeviceClass;
	LPDIRECT3DDEVICE9		m_pGraphicDev;

	CStage* m_pScene;
	CManagement*			m_pManagementClass;
};


