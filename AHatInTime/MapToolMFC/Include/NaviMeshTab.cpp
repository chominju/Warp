// NaviMeshTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapToolMFC.h"
#include "NaviMeshTab.h"
#include "afxdialogex.h"


// CNaviMeshTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CNaviMeshTab, CDialogEx)

CNaviMeshTab::CNaviMeshTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

CNaviMeshTab::~CNaviMeshTab()
{
}

void CNaviMeshTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNaviMeshTab, CDialogEx)
END_MESSAGE_MAP()


// CNaviMeshTab 메시지 처리기입니다.
