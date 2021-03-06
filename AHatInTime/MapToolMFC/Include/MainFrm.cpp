
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "MapToolMFC.h"

#include "MainFrm.h"
#include "MapToolMFCView.h"

#include "Tab.h"
#include "Tool_Stage.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
	//: m_pDeviceClass(CGraphicDev::GetInstance())
	//, m_pGraphicDev(m_pDeviceClass->Get_Device())
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("도구 모음을 만들지 못했습니다.\n");
	//	return -1;      // 만들지 못했습니다.
	//}

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("상태 표시줄을 만들지 못했습니다.\n");
	//	return -1;      // 만들지 못했습니다.
	//}
	//m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.cx = 1250 + 20 * 2;
	cs.cy = 600 + 63;

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	g_hWnd = m_hWnd;
	g_index = -1;
	Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass);

	m_pDeviceClass->AddRef();

	m_pGraphicDev = m_pDeviceClass->Get_Device();
	m_pGraphicDev->AddRef();

	// 폰트

	Ready_Font(m_pGraphicDev, L"Font_Default", L"바탕", 15, 20, FW_NORMAL);
	Ready_Font(m_pGraphicDev, L"Font_Jinji", L"궁서", 30, 30, FW_HEAVY);

	// InputDev

	Ready_InputDev(g_hInst, g_hWnd);


	RECT rcMain{};
	this->GetWindowRect(&rcMain);
	SetRect(&rcMain, 0, 0, rcMain.right - rcMain.left, rcMain.bottom - rcMain.top);
	// 	rcMain.right = rcMain.right - rcMain.left; 
	// 	rcMain.left = 0; 
	// 	rcMain.bottom = rcMain.bottom - rcMain.top; 
	// 	rcMain.top = 0;
	RECT rcView{};
	GetClientRect(&rcView);
	iGapX = rcMain.right - rcView.right; //1440 - 1420 = 20
	iGapY = rcMain.bottom - rcView.bottom;

	m_MainSplitter.CreateStatic(this, 1, 2);

	m_MainSplitter.CreateView(0, 0, RUNTIME_CLASS(CTab), CSize(450, WINCY + iGapY), pContext);
	m_MainSplitter.CreateView(0, 1, RUNTIME_CLASS(CMapToolMFCView), CSize(WINCX + iGapX, WINCY + iGapX), pContext);

	//m_MainSplitter.SetColumnInfo(1, 800, 600);

	//m_MainSplitter.SetColumnInfo(0, 800, 500);
	//m_MainSplitter.SetColumnInfo(1, 300, 150);
	//m_MainSplitter.SetRowInfo(0, 600, 300);


	return TRUE;
}
