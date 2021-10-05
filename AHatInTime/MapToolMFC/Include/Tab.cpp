// Tab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapToolMFC.h"
#include "Tab.h"

#include "TerrainTab.h"
#include "MeshTab.h"
#include "ColliderTab.h"
#include "Tool_Stage.h"
#include "NaviMeshTab.h"

// CTab

IMPLEMENT_DYNCREATE(CTab, CFormView)

CTab::CTab()
	: CFormView(IDD_TAB)
	, m_pDeviceClass(CGraphicDev::GetInstance())
	, m_pGraphicDev(CGraphicDev::GetInstance()->Get_Device())
{

}

CTab::~CTab()
{
}

void CTab::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CTab, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTab::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CTab 진단입니다.

#ifdef _DEBUG
void CTab::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTab::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTab 메시지 처리기입니다.


void CTab::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	m_Tab.InsertItem(0, _T("TerrainTool"));
	m_Tab.InsertItem(1, _T("MeshTool"));
	m_Tab.InsertItem(2, _T("ColliderTool"));
	m_Tab.InsertItem(3, _T("NaviMeshTool"));

	m_Tab.SetCurSel(0);

	CRect rect;

	m_Tab.GetWindowRect(&rect);

	m_pTerrainTab = new CTerrainTab;
	m_pTerrainTab->Create(IDD_DIALOG1, &m_Tab);
	m_pTerrainTab->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_pTerrainTab->ShowWindow(SW_SHOW);

	m_pMeshTab = new CMeshTab;
	m_pMeshTab->Create(IDD_DIALOG2, &m_Tab);
	m_pMeshTab->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_pMeshTab->ShowWindow(SW_HIDE);

	m_pColliderTab = new CColliderTab;
	m_pColliderTab->Create(IDD_DIALOG3, &m_Tab);
	m_pColliderTab->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_pColliderTab->ShowWindow(SW_HIDE);

	m_pNaviMeshTab = new CNaviMeshTab;
	m_pNaviMeshTab->Create(IDD_DIALOG4, &m_Tab);
	m_pNaviMeshTab->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_pNaviMeshTab->ShowWindow(SW_HIDE);

	this->GetClientRect(&rect);

	int x = rect.Width();
	int y = rect.Height();


	Create_Management(&m_pManagementClass);
	m_pManagementClass->AddRef();

	m_pScene = CStage::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_pScene);
	m_pManagementClass->Set_Scene(m_pScene);

}


void CTab::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int sel = m_Tab.GetCurSel();

	switch (sel)
	{
	case 0:
	{
		m_pTerrainTab->ShowWindow(SW_SHOW);
		m_pMeshTab->ShowWindow(SW_HIDE);
		m_pColliderTab->ShowWindow(SW_HIDE);
		m_pNaviMeshTab->ShowWindow(SW_HIDE);
	}
	break;
	case 1:
	{
		m_pTerrainTab->ShowWindow(SW_HIDE);
		m_pMeshTab->ShowWindow(SW_SHOW);
		m_pColliderTab->ShowWindow(SW_HIDE);
		m_pNaviMeshTab->ShowWindow(SW_HIDE);
	}
	break;
	case 2:
	{
		m_pTerrainTab->ShowWindow(SW_HIDE);
		m_pMeshTab->ShowWindow(SW_HIDE);
		m_pColliderTab->ShowWindow(SW_SHOW);
		m_pNaviMeshTab->ShowWindow(SW_HIDE);
	}
	case 3:
	{
		m_pTerrainTab->ShowWindow(SW_HIDE);
		m_pMeshTab->ShowWindow(SW_HIDE);
		m_pColliderTab->ShowWindow(SW_HIDE);
		m_pNaviMeshTab->ShowWindow(SW_SHOW);
	}
	break;
	}

	*pResult = 0;
}
