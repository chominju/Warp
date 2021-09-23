// Tab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapToolMFC.h"
#include "Tab.h"

#include "TerrainTab.h"
#include "MeshTab.h"
#include "ColliderTab.h"



// CTab

IMPLEMENT_DYNCREATE(CTab, CFormView)

CTab::CTab()
	: CFormView(IDD_TAB)
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


// CTab �����Դϴ�.

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


// CTab �޽��� ó�����Դϴ�.


void CTab::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	m_Tab.InsertItem(0, _T("TerrainTool"));
	m_Tab.InsertItem(1, _T("MeshTool"));
	m_Tab.InsertItem(2, _T("EffectTool"));

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

	this->GetClientRect(&rect);

	int x = rect.Width();
	int y = rect.Height();

}


void CTab::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int sel = m_Tab.GetCurSel();

	switch (sel)
	{
	case 0:
	{
		m_pTerrainTab->ShowWindow(SW_SHOW);
		m_pMeshTab->ShowWindow(SW_HIDE);
		m_pColliderTab->ShowWindow(SW_HIDE);
	}
	break;
	case 1:
	{
		m_pTerrainTab->ShowWindow(SW_HIDE);
		m_pMeshTab->ShowWindow(SW_SHOW);
		m_pColliderTab->ShowWindow(SW_HIDE);
	}
	break;
	case 2:
	{
		m_pTerrainTab->ShowWindow(SW_HIDE);
		m_pMeshTab->ShowWindow(SW_HIDE);
		m_pColliderTab->ShowWindow(SW_SHOW);
	}
	break;
	}

	*pResult = 0;
}