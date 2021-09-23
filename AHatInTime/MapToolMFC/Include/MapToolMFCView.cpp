
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
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

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

		m_pManagementClass->Update_Scene(fTimeFPS60);

		m_pDeviceClass->Render_Begin(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));

		m_pManagementClass->Render_Scene(m_pGraphicDev);

		m_pDeviceClass->Render_End(m_hWnd);

	}
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
	CView::OnInitialUpdate();

	// Ÿ�̸�
	Ready_Timer(L"Timer_Immediate");// , FALSE); // ���α׷� ���� ��� ��밡���� �ð�
	Ready_Timer(L"Timer_FPS60");// , FALSE);	// FPS 60���� ������ ���ĺ��� ��밡���� �ð�

								// ������
	Ready_Frame(L"Frame60", 60.f);// , FALSE);


	Ready_Proto(L"Proto_Buffer_TerrainTex", CTerrainTex::Create(m_pGraphicDev, VTXCNTX, VTXCNTZ, VTXITV));// , E_FAIL);
	Ready_Proto(L"Proto_Buffer_CubeTex", CCubeTex::Create(m_pGraphicDev));// , E_FAIL);


	Ready_Proto(L"Proto_Texture_Terrain", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Grass_%d.tga", TYPE_NORMAL, 2));// , E_FAIL);
	Ready_Proto(L"Proto_Texture_Terrain2", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Terrain0.png", TYPE_NORMAL, 1));// , E_FAIL);
	Ready_Proto(L"Proto_Texture_SkyBox", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/SkyBox/burger%d.dds", TYPE_CUBE, 4));// , E_FAIL);

	Ready_Proto(L"Proto_Calculator", CCalculator::Create(m_pGraphicDev));// , E_FAIL);


	Ready_Proto(L"Proto_Buffer_TriCol", CTriCol::Create(m_pGraphicDev));
	Ready_Proto(L"Proto_Buffer_RcCol", CRcCol::Create(m_pGraphicDev));// , E_FAIL);
	Ready_Proto(L"Proto_Buffer_RcTex", CRcTex::Create(m_pGraphicDev));// , E_FAIL);

	Ready_Proto(L"Proto_Transform", CTransform::Create(m_pGraphicDev));// , E_FAIL);
	Ready_Proto(L"Proto_Mesh_Stone", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource/Mesh/StaticMesh/TombStone/", L"TombStone.X"));
	Ready_Proto(L"Proto_Texture_Player", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Player/Ma.jpg", TYPE_NORMAL));// , E_FAIL);

	Create_Management(&m_pManagementClass);
	m_pManagementClass->AddRef();

	m_pScene = CStage::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_pScene);
	m_pManagementClass->Set_Scene(m_pScene);

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}
