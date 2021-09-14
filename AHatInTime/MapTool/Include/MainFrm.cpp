
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "MapTool.h"

#include "MainFrm.h"

#include "MapToolView.h"
#include "Form.h"

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

	//도구모음
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

	cs.cx = 1250 + 20*2;
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
	//if (FAILED(m_MainSplitter.CreateStatic(this, 1, 2)))
	//{
	//	AfxMessageBox(_T("Failed to create static splitter"));
	//	return FALSE;
	//}

	//if (FAILED(m_MainSplitter.CreateView(0, 0, RUNTIME_CLASS(CForm), CSize(400, 600), pContext)))
	//{
	//	AfxMessageBox(_T("Failed to first pane splitter"));
	//	return FALSE;
	//}

	//if (FAILED(m_MainSplitter.CreateView(0, 1, RUNTIME_CLASS(CMapToolView), CSize(100,600), pContext)))
	//{
	//	AfxMessageBox(_T("Failed to second pane splitter"));
	//	return FALSE;
	//}

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

	m_MainSplitter.CreateView(0, 0, RUNTIME_CLASS(CForm), CSize(450, 600 + iGapY), pContext);
	m_MainSplitter.CreateView(0, 1, RUNTIME_CLASS(CMapToolView), CSize(800 + iGapX, 600+iGapX), pContext);

	//m_MainSplitter.SetColumnInfo(1, 800, 600);

	//m_MainSplitter.SetColumnInfo(0, 800, 500);
	//m_MainSplitter.SetColumnInfo(1, 300, 150);
	//m_MainSplitter.SetRowInfo(0, 600, 300);

	return TRUE;

}
