// MeshTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "MeshTool.h"
#include "afxdialogex.h"


// CMeshTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMeshTool, CDialogEx)

CMeshTool::CMeshTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CMeshTool::~CMeshTool()
{
}

void CMeshTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMeshTool, CDialogEx)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CMeshTool �޽��� ó�����Դϴ�.


void CMeshTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnDropFiles(hDropInfo);
}
