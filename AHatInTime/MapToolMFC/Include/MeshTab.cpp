// MeshTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapToolMFC.h"
#include "MeshTab.h"
#include "afxdialogex.h"


// CMeshTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMeshTab, CDialogEx)

CMeshTab::CMeshTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CMeshTab::~CMeshTab()
{
}

void CMeshTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMeshTab, CDialogEx)
END_MESSAGE_MAP()


// CMeshTab 메시지 처리기입니다.
