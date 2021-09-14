// MeshTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "MeshTool.h"
#include "afxdialogex.h"


// CMeshTool 대화 상자입니다.

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


// CMeshTool 메시지 처리기입니다.


void CMeshTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnDropFiles(hDropInfo);
}
