// ColliderTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapToolMFC.h"
#include "ColliderTab.h"
#include "afxdialogex.h"


// CColliderTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CColliderTab, CDialogEx)

CColliderTab::CColliderTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CColliderTab::~CColliderTab()
{
}

void CColliderTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CColliderTab, CDialogEx)
END_MESSAGE_MAP()


// CColliderTab 메시지 처리기입니다.
