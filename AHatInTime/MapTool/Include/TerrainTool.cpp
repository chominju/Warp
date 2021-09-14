// TerrainTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "TerrainTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"



// CTerrainTool 대화 상자입니다.

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
	DDX_Control(pDX, IDC_LIST1, m_textureListBox);
}


BEGIN_MESSAGE_MAP(CTerrainTool, CDialogEx)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CTerrainTool::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// CTerrainTool 메시지 처리기입니다.


void CTerrainTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	int size = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	TCHAR szBuf[MAX_PATH] = L"";
	CString relativePath;
	for (int i = 0; i < size; ++i)
	{
		DragQueryFile(hDropInfo, i, szBuf, MAX_PATH);
		relativePath = CFileInfo::ConvertRelativePath(szBuf);
		CString fileNameAndExtension = PathFindFileName(szBuf);
		TCHAR szFileName[MAX_PATH]{};
		lstrcpy(szFileName, fileNameAndExtension.GetString());

		PathRemoveExtension(szFileName);

		if (m_textureListBox.IsWindowVisible())
			m_textureListBox.AddString(szFileName);
	}
	m_textureListBox.SetHorizontalExtent(500);
	UpdateData(FALSE);

	CDialogEx::OnDropFiles(hDropInfo);
}


void CTerrainTool::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	int index = m_textureListBox.GetCurSel();
	CString fileName;
	m_textureListBox.GetText(index, fileName);
	int i = 0;
	for (; i < fileName.GetLength(); ++i)
	{
		if (isdigit(fileName[i]))
			break;
	}
	fileName.Delete(0, i);
	m_drawID = _ttoi(fileName.GetString());

	/*CGraphic_Device::Get_Instance()->Render_Begin();
	const Texture_Info * textureInfo = CTexture_Manager::Get_Instance()->Get_TextureInfo_Manager(L"Terrain", L"Tile", m_drawID);
	if (nullptr == textureInfo)
		return;

	D3DXMATRIX matScale, matTrans, matWorld;
	float ratioX = float(WINCX) / textureInfo->imageInfo.Width;
	float ratioY = float(WINCY) / textureInfo->imageInfo.Height;
	D3DXMatrixScaling(&matScale, ratioX, ratioY, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX / 2, WINCY / 2, 0.f);
	matWorld = matScale * matTrans;


	float centerX = textureInfo->imageInfo.Width >> 1;
	float centerY = textureInfo->imageInfo.Height >> 1;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(textureInfo->texture, nullptr, &D3DXVECTOR3(centerX, centerY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	CGraphic_Device::Get_Instance()->Render_End(m_picture.m_hWnd);*/
	UpdateData(FALSE);
}
