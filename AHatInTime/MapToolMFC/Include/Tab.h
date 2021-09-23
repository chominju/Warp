#pragma once
#include "afxcmn.h"

class CTerrainTab;
class CMeshTab;
class CColliderTab;

// CTab �� ���Դϴ�.

class CTab : public CFormView
{
	DECLARE_DYNCREATE(CTab)

protected:
	CTab();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CTab();

public:
	CTerrainTab*	m_pTerrainTab;
	CMeshTab*		m_pMeshTab;
	CColliderTab*	m_pColliderTab;


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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	virtual void OnInitialUpdate();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};


