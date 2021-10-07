
// MapToolMFCView.cpp : CMapToolMFCView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMapToolMFCView ����/�Ҹ�

CMapToolMFCView::CMapToolMFCView()
	:m_pDeviceClass(CGraphicDev::GetInstance())
	, m_pGraphicDev(CGraphicDev::GetInstance()->Get_Device())
	, m_isUpdate(true)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_pManagementClass = CManagement::GetInstance();
	m_pManagementClass->AddRef();
}

CMapToolMFCView::~CMapToolMFCView()
{
}

BOOL CMapToolMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMapToolMFCView �׸���

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
	if (m_isUpdate)
		Invalidate(FALSE);

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMapToolMFCView �μ�

BOOL CMapToolMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMapToolMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMapToolMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMapToolMFCView ����

#ifdef _DEBUG
void CMapToolMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMapToolMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapToolMFCDoc* CMapToolMFCView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapToolMFCDoc)));
	return (CMapToolMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapToolMFCView �޽��� ó����


void CMapToolMFCView::OnInitialUpdate()
{

	// Ÿ�̸�
	Ready_Timer(L"Timer_Immediate");// , FALSE); // ���α׷� ���� ��� ��밡���� �ð�
	Ready_Timer(L"Timer_FPS60");// , FALSE);	// FPS 60���� ������ ���ĺ��� ��밡���� �ð�

								// ������
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





	Ready_Proto(L"Proto_Mesh_Bed.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Bed.X"));
	Ready_Proto(L"Proto_Mesh_Conveyor.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Conveyor.X"));
	Ready_Proto(L"Proto_Mesh_Desk1.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Desk1.X"));
	Ready_Proto(L"Proto_Mesh_Door3.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Door3.X"));
	Ready_Proto(L"Proto_Mesh_Door4.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Door4.X"));
	Ready_Proto(L"Proto_Mesh_DoorClearFin.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"DoorClearFin.X"));
	Ready_Proto(L"Proto_Mesh_DoorClearLeft.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"DoorClearLeft.X"));
	Ready_Proto(L"Proto_Mesh_DoorClearRight.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"DoorClearRight.X"));
	Ready_Proto(L"Proto_Mesh_Drawer1.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Drawer1.X"));
	Ready_Proto(L"Proto_Mesh_Drawer2.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Drawer2.X"));
	Ready_Proto(L"Proto_Mesh_Skeleton_Ball.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Skeleton_Ball.X"));
	Ready_Proto(L"Proto_Mesh_Table1.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Table1.X"));
	Ready_Proto(L"Proto_Mesh_Table2.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Table2.X"));
	Ready_Proto(L"Proto_Mesh_Table11.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Table11.X"));
	Ready_Proto(L"Proto_Mesh_Wall1.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Wall1.X"));
	Ready_Proto(L"Proto_Mesh_Wall2.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Wall2.X"));
	Ready_Proto(L"Proto_Mesh_Wall4.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Wall4.X"));
	Ready_Proto(L"Proto_Mesh_Wall6.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Wall6.X"));
	Ready_Proto(L"Proto_Mesh_Wall44.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"Wall44.X"));
	Ready_Proto(L"Proto_Mesh_WallClear1.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"WallClear1.X"));
	Ready_Proto(L"Proto_Mesh_WallClear6.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"WallClear6.X"));
	Ready_Proto(L"Proto_Mesh_WallClear15.x", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource3/UseStaticMesh/", L"WallClear15.X"));
	
	CView::OnInitialUpdate();
	//Ready_Proto(L"Proto_Texture_Player", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Player/Ma.jpg", TYPE_NORMAL));// , E_FAIL);

	/*Create_Management(&m_pManagementClass);
	m_pManagementClass->AddRef();

	m_pScene = CStage::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_pScene);
	m_pManagementClass->Set_Scene(m_pScene);*/

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


void CMapToolMFCView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

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
}

void CMapToolMFCView::Render_View()
{
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
}
