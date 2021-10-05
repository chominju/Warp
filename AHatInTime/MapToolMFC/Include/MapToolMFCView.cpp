
// MapToolMFCView.cpp : CMapToolMFCView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MapToolMFC.h"
#endif

#include "MapToolMFCDoc.h"
#include "MapToolMFCView.h"

#include "Tool_Terrain.h"
#include "TerrainTex.h"
#include "Tool_DynamicCamera.h"
#include "Tool_Stage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapToolMFCView

IMPLEMENT_DYNCREATE(CMapToolMFCView, CView)

BEGIN_MESSAGE_MAP(CMapToolMFCView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMapToolMFCView 생성/소멸

CMapToolMFCView::CMapToolMFCView()
	:m_pDeviceClass(CGraphicDev::GetInstance())
	, m_pGraphicDev(CGraphicDev::GetInstance()->Get_Device())
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_pManagementClass = CManagement::GetInstance();
	m_pManagementClass->AddRef();
}

CMapToolMFCView::~CMapToolMFCView()
{
}

BOOL CMapToolMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMapToolMFCView 그리기

void CMapToolMFCView::OnDraw(CDC* /*pDC*/)
{
	CMapToolMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Update_TimeDelta(L"Timer_Immediate");
	_float fTimeImmediate = Get_TimeDelta(L"Timer_Immediate");

	if (IsPermit_Call(L"Frame60", fTimeImmediate))
	{
		Update_TimeDelta(L"Timer_FPS60");
		_float fTimeFPS60 = Get_TimeDelta(L"Timer_FPS60");

		Update_InputDev();

		m_pManagementClass->Update_Scene(fTimeFPS60);

		m_pDeviceClass->Render_Begin(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));

		m_pManagementClass->Render_Scene(m_pGraphicDev);

		m_pDeviceClass->Render_End(m_hWnd);

	}
	Invalidate(FALSE);

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMapToolMFCView 인쇄

BOOL CMapToolMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMapToolMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMapToolMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMapToolMFCView 진단

#ifdef _DEBUG
void CMapToolMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMapToolMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapToolMFCDoc* CMapToolMFCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapToolMFCDoc)));
	return (CMapToolMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapToolMFCView 메시지 처리기


void CMapToolMFCView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// 타이머
	Ready_Timer(L"Timer_Immediate");// , FALSE); // 프로그램 구동 즉시 사용가능한 시간
	Ready_Timer(L"Timer_FPS60");// , FALSE);	// FPS 60으로 제한한 이후부터 사용가능한 시간

								// 프레임
	Ready_Frame(L"Frame60", 60.f);// , FALSE);


	//Ready_Proto(L"Proto_Buffer_TerrainTex", CTerrainTex::Create(m_pGraphicDev, VTXCNTX, VTXCNTZ, VTXITV));// , E_FAIL);
	Ready_Proto(L"Proto_Buffer_CubeTex", CCubeTex::Create(m_pGraphicDev));// , E_FAIL);
	Ready_Proto(L"Proto_Buffer_TerrainTex", CTerrainTex::Create(m_pGraphicDev, VTXCNTX, VTXCNTZ, VTXITV));// , E_FAIL);

	//Ready_Proto(L"Proto_Texture_Terrain", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Grass_%d.tga", TYPE_NORMAL, 2));// , E_FAIL);
	//Ready_Proto(L"Proto_Texture_Terrain2", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Terrain0.png", TYPE_NORMAL, 1));// , E_FAIL);
	//Ready_Proto(L"Proto_Texture_SkyBox", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/SkyBox/burger%d.dds", TYPE_CUBE, 4));// , E_FAIL);

	Ready_Proto(L"Proto_Calculator", CCalculator::Create(m_pGraphicDev));// , E_FAIL);


	Ready_Proto(L"Proto_Buffer_TriCol", CTriCol::Create(m_pGraphicDev));
	Ready_Proto(L"Proto_Buffer_RcCol", CRcCol::Create(m_pGraphicDev));// , E_FAIL);
	Ready_Proto(L"Proto_Buffer_RcTex", CRcTex::Create(m_pGraphicDev));// , E_FAIL);

	Ready_Proto(L"Proto_Transform", CTransform::Create(m_pGraphicDev));// , E_FAIL);





	Ready_Proto(L"Proto_Mesh_Bed", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Bed.X"));
	Ready_Proto(L"Proto_Mesh_Conveyor", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Conveyor.X"));
	Ready_Proto(L"Proto_Mesh_Desk1", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Desk1.X"));
	Ready_Proto(L"Proto_Mesh_Door3", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Door3.X"));
	Ready_Proto(L"Proto_Mesh_Door4", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Door4.X"));
	Ready_Proto(L"Proto_Mesh_DoorClearFin", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"DoorClearFin.X"));
	Ready_Proto(L"Proto_Mesh_DoorClearLeft", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"DoorClearLeft.X"));
	Ready_Proto(L"Proto_Mesh_DoorClearRight", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"DoorClearRight.X"));
	Ready_Proto(L"Proto_Mesh_Drawer1", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Drawer1.X"));
	Ready_Proto(L"Proto_Mesh_Drawer2", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Drawer2.X"));
	Ready_Proto(L"Proto_Mesh_Skeleton_Ball", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Skeleton_Ball.X"));
	Ready_Proto(L"Proto_Mesh_Table1", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Table1.X"));
	Ready_Proto(L"Proto_Mesh_Table2", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Table2.X"));
	Ready_Proto(L"Proto_Mesh_Table11", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Table11.X"));
	Ready_Proto(L"Proto_Mesh_Wall1", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Wall1.X"));
	Ready_Proto(L"Proto_Mesh_Wall2", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Wall2.X"));
	Ready_Proto(L"Proto_Mesh_Wall4", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Wall4.X"));
	Ready_Proto(L"Proto_Mesh_Wall6", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Wall6.X"));
	Ready_Proto(L"Proto_Mesh_Wall44", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Wall44.X"));
	Ready_Proto(L"Proto_Mesh_WallClear1", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"WallClear1.X"));
	Ready_Proto(L"Proto_Mesh_WallClear6", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"WallClear6.X"));
	Ready_Proto(L"Proto_Mesh_WallClear15", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"WallClear15.X"));
	//Ready_Proto(L"Proto_Texture_Player", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Player/Ma.jpg", TYPE_NORMAL));// , E_FAIL);

	/*Create_Management(&m_pManagementClass);
	m_pManagementClass->AddRef();

	m_pScene = CStage::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_pScene);
	m_pManagementClass->Set_Scene(m_pScene);*/

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
