// TerrainTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "TerrainTool.h"
#include "afxdialogex.h"


// CTerrainTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTerrainTool, CDialogEx)

CTerrainTool::CTerrainTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CTerrainTool::~CTerrainTool()
{
}

void CTerrainTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTerrainTool, CDialogEx)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CTerrainTool �޽��� ó�����Դϴ�.


void CTerrainTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnDropFiles(hDropInfo);
}
