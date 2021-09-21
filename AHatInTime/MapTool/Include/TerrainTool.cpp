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
	DDX_Control(pDX, IDC_PICTURE, m_pictureControl);
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


	//CString fileName;
	//m_textureListBox.GetText(index, fileName);



	//int i = 0;
	//for (; i < fileName.GetLength(); ++i)
	//{
	//	if (isdigit(fileName[i]))
	//		break;
	//}
	//fileName.Delete(0, i);
	//m_drawID = _ttoi(fileName.GetString());
	

	CTexture* getTexture = dynamic_cast<CTexture*>(Clone_Proto(m_textureName[index]));
	if (nullptr == getTexture)
		return;

	m_pDeviceClass->Render_Begin(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.f));
	
	getTexture->Render_Texture();


	//CGraphicDev::GetInstance()->Get_Device()->SetTexture(0, getTexture);
	m_pDeviceClass->Render_End(m_pictureControl.m_hWnd);
	//CGraphic_Device::Get_Instance()->Render_End(m_picture.m_hWnd);
	UpdateData(FALSE);
}


BOOL CTerrainTool::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	//CString path = _T("..\\Bin\Resource2\\Textures\\Terrain");
	CString path = _T("D:\\Jusin\\AHatInTime\\AHatInTime\\MapTool\\Bin\\Resource2\\Textures\\Terrain");
	CString wstrRelativePath = L"";
	wstrRelativePath = CFileInfo::ConvertRelativePath(path);
	CString temp = wstrRelativePath;

	CFileFind finder;	
	int size = path.GetLength();
	path.Insert(size, L"\\*.*");

	bool isWorking = finder.FindFile(path);
	CString cData;
	int i = 0;
	while (isWorking)
	{
		isWorking = finder.FindNextFileW();
		
		if (finder.IsDirectory() || finder.IsDots())
			continue;

		cData = finder.GetFileName();
		/*_tchar * str = (wchar_t*)(const wchar_t*)cData;*/
		m_textureName.push_back(cData);
		CString temp2 = temp +"\\"+ cData;
		Ready_Proto(m_textureName[i], CTexture::Create(m_pGraphicDev, temp2, TYPE_NORMAL, 1));// , E_FAIL);
		m_textureListBox.AddString(cData);
		i++;
	}


	// 텍스쳐
	//Ready_Proto(L"Proto_Texture_Terrain", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Grass_%d.tga", TYPE_NORMAL, 2));// , E_FAIL);
	//Ready_Proto(L"Proto_Texture_Terrain2", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Terrain0.png", TYPE_NORMAL, 1));// , E_FAIL);
	//Ready_Proto(L"Proto_Texture_SkyBox", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/SkyBox/burger%d.dds", TYPE_CUBE, 4));// , E_FAIL);


	//Ready_Proto(L"Proto_Texture_Terrain", CTexture::Create(m_pGraphicDev, L"../Bin/Resource2/Textures/Terrain/Black%d.tga", TYPE_NORMAL, 2));// , E_FAIL);
	//Ready_Proto(L"Proto_Texture_Terrain2", CTexture::Create(m_pGraphicDev, L"../Bin/Resource2/Textures/Terrain/Terrain0.png", TYPE_NORMAL, 1));// , E_FAIL);
	//Ready_Proto(L"Proto_Texture_SkyBox", CTexture::Create(m_pGraphicDev, L"../Bin/Resource2/Textures/SkyBox/burger%d.dds", TYPE_CUBE, 4));// , E_FAIL);


	//Ready_Proto(L"Proto_Mesh_Stone", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource2/Meshes/Scene_Boss/Static/Mafia_Theatre/", L"Mafia_Theatre.X"));// , E_FAIL);
	//Ready_Proto(L"Proto_Mesh_Sword", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource2/Mesh/StaticMesh/Sword/", L"Sword.X"));// , E_FAIL);
	//Ready_Proto(L"Proto_Mesh_Player", CDynamicMesh::Create(m_pGraphicDev, L"../Bin/Resource2/Mesh/DynamicMesh/PlayerXfile/", L"Player.X"));// , E_FAIL);


	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
