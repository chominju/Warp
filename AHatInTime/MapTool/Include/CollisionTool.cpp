// CollisionTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "CollisionTool.h"
#include "afxdialogex.h"


// CCollisionTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCollisionTool, CDialogEx)

CCollisionTool::CCollisionTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CCollisionTool::~CCollisionTool()
{
}

void CCollisionTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCollisionTool, CDialogEx)
END_MESSAGE_MAP()


// CCollisionTool �޽��� ó�����Դϴ�.