// Form.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "Form.h"

#include "TerrainTool.h"
#include "MeshTool.h"
#include "CollisionTool.h"

//#include "Engine_Define.h"

// CForm

IMPLEMENT_DYNCREATE(CForm, CFormView)

CForm::CForm()
	: CFormView(IDD_FORM)
{

}

CForm::~CForm()
{
}

void CForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CForm, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CForm::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CForm 진단입니다.

#ifdef _DEBUG
void CForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CForm 메시지 처리기입니다.


void CForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//this->MoveWindow(1000, 25, 300, 600);



	m_Tab.InsertItem(0, _T("TerrainTool"));
	m_Tab.InsertItem(1, _T("MeshTool"));
	m_Tab.InsertItem(2, _T("EffectTool"));

	m_Tab.SetCurSel(0);

	CRect rect;

	m_Tab.GetWindowRect(&rect);

	pTerrainTool = new CTerrainTool;
	pTerrainTool->Create(IDD_DIALOG1, &m_Tab);
	pTerrainTool->MoveWindow(0, 25, rect.Width(), rect.Height());
	pTerrainTool->ShowWindow(SW_SHOW);

	pMeshTool = new CMeshTool;
	pMeshTool->Create(IDD_DIALOG2, &m_Tab);
	pMeshTool->MoveWindow(0, 25, rect.Width(), rect.Height());
	pMeshTool->ShowWindow(SW_HIDE);

	pCollisionTool = new CCollisionTool;
	pCollisionTool->Create(IDD_DIALOG3, &m_Tab);
	pCollisionTool->MoveWindow(0, 25, rect.Width(), rect.Height());
	pCollisionTool->ShowWindow(SW_HIDE);

	this->GetClientRect(&rect);

	int x = rect.Width();
	int y = rect.Height();

}


void CForm::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = m_Tab.GetCurSel();

	switch (sel)
	{
	case 0:
	{
		pTerrainTool->ShowWindow(SW_SHOW);
		pMeshTool->ShowWindow(SW_HIDE);
		pCollisionTool->ShowWindow(SW_HIDE);
	}
	break;
	case 1:
	{
		pTerrainTool->ShowWindow(SW_HIDE);
		pMeshTool->ShowWindow(SW_SHOW);
		pCollisionTool->ShowWindow(SW_HIDE);
	}
	break;
	case 2:
	{
		pTerrainTool->ShowWindow(SW_HIDE);
		pMeshTool->ShowWindow(SW_HIDE);
		pCollisionTool->ShowWindow(SW_SHOW);
	}
	break;
	}
	
	*pResult = 0;
}

void CForm::PostNcDestroy()
{
	//// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//pTerrainTool->DestroyWindow();
	//Safe_Delete(pTerrainTool);

	//pMeshTool->DestroyWindow();
	//Safe_Delete(pMeshTool);

	//pEffectTool->DestroyWindow();
	//Safe_Delete(pEffectTool);

	CFormView::PostNcDestroy();
}
