// TerrainTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "TerrainTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "Tool_Terrain.h"


// CTerrainTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTerrainTool, CDialogEx)

CTerrainTool::CTerrainTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_posX(0)
	, m_posY(0)
	, m_posZ(0)
	, m_rotX(0)
	, m_rotY(0)
	, m_rotZ(0)
	, m_countX(2)
	, m_countZ(2)
	, m_pDeviceClass(CGraphicDev::GetInstance())
	, m_pGraphicDev(CGraphicDev::GetInstance()->Get_Device())
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
	DDX_Control(pDX, IDC_LIST2, m_addList);

	DDX_Text(pDX, IDC_EDIT1, m_posX);
	DDX_Text(pDX, IDC_EDIT2, m_posY);
	DDX_Text(pDX, IDC_EDIT3, m_posZ);
	DDX_Text(pDX, IDC_EDIT4, m_rotX);
	DDX_Text(pDX, IDC_EDIT5, m_rotY);
	DDX_Text(pDX, IDC_EDIT6, m_rotZ);
	DDX_Text(pDX, IDC_EDIT7, m_countX);
	DDX_Text(pDX, IDC_EDIT8, m_countZ);
}


BEGIN_MESSAGE_MAP(CTerrainTool, CDialogEx)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CTerrainTool::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON3, &CTerrainTool::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON4, &CTerrainTool::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON5, &CTerrainTool::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON1, &CTerrainTool::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON2, &CTerrainTool::OnBnClickedButtonLoad)
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
	m_textureListIndex = m_textureListBox.GetCurSel();


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
	

	CTexture* getTexture = dynamic_cast<CTexture*>(Clone_Proto(m_textureNameVector[m_textureListIndex]));
	if (nullptr == getTexture)
		return;

	m_pDeviceClass->Render_Begin(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.f));
	
	auto textureTemp = getTexture->Get_TextureInfo(m_textureNameVector[m_textureListIndex].operator LPCWSTR());

	D3DXMATRIX matScale, matTrans, matWorld;
	float ratioX = float(WINCX) / textureTemp->imageInfo.Width;
	float ratioY = float(WINCY) / textureTemp->imageInfo.Height;
	D3DXMatrixScaling(&matScale, ratioX, ratioY, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX / 2, WINCY / 2, 0.f);
	matWorld = matScale * matTrans;

	float centerX = textureTemp->imageInfo.Width >> 1;
	float centerY = textureTemp->imageInfo.Height >> 1;







	//getTexture->Render_Texture();
	//getTexture->Get_TextureInfo(m_textureName[index].operator LPCWSTR())->texture;
	m_pDeviceClass->Get_Sprite()->SetTransform(&matWorld);
	m_pDeviceClass->Get_Sprite()->Draw(textureTemp->texture, nullptr, &D3DXVECTOR3(centerX, centerY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

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
	CString relativePath = wstrRelativePath;

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
		m_textureNameVector.push_back(cData);
		CString pathFull = relativePath +"\\"+ cData;

		CTexture * instance = CTexture::Create(m_pGraphicDev, pathFull, TYPE_NORMAL, 1);
		instance->Insert_Texture(m_pGraphicDev, pathFull.operator LPCWSTR(), m_textureNameVector[i].operator LPCWSTR());
		Ready_Proto(m_textureNameVector[i], instance/*CTexture::Create(m_pGraphicDev, pathFull, TYPE_NORMAL, 1)*/);// , E_FAIL);
		m_textureListBox.AddString(cData);
		i++;
	}


	//Ready_Proto(L"Proto_Buffer_TerrainTex", CTerrainTex::Create(m_pGraphicDev, VTXCNTX, VTXCNTZ, VTXITV));// , E_FAIL);

	//Ready_Proto(L"Proto_Texture_Player", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Player/Ma.jpg", TYPE_NORMAL));// , E_FAIL);
	//Ready_Proto(L"Proto_Texture_Logo", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Logo/sana.jpg", TYPE_NORMAL));//, E_FAIL);
	//Ready_Proto(L"Proto_Transform", CTransform::Create(m_pGraphicDev));// , E_FAIL);

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


void CTerrainTool::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*CTexture* getTexture = dynamic_cast<CTexture*>(Clone_Proto(m_textureNameVector[m_textureListIndex]));
	if (nullptr == getTexture)
		return;*/

	CComponent*			pComponent = nullptr;

	// texture
	CTerrain * newTerrain = CTerrain::Create(m_pGraphicDev);
	pComponent = newTerrain->m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(m_textureNameVector[m_textureListIndex]));;
	newTerrain->Add_MapComponent(pComponent, ID_STATIC, L"Com_Texture");

	// buffer
	Ready_Proto(L"Proto_Buffer_TerrainTex", CTerrainTex::Create(m_pGraphicDev, m_countX, m_countZ, VTXITV));// , E_FAIL);
	pComponent = newTerrain->m_pBufferCom = dynamic_cast<CTerrainTex*>(Clone_Proto(L"Proto_Buffer_TerrainTex"));
	newTerrain->m_pBufferCom->Set_Index(m_countX,m_countZ);
	newTerrain->Add_MapComponent(pComponent, ID_STATIC, L"Com_Buffer");
	//newTerrain->m_pIndex = new INDEX32[newTerrain->m_pBufferCom->Get_TriCnt()];

	// Transform
	pComponent = newTerrain->m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
	newTerrain->Add_MapComponent(pComponent, ID_DYNAMIC, L"Com_Transform");

	// renderer
	pComponent = newTerrain->m_pRendererCom = Get_Renderer();
	pComponent->AddRef();
	newTerrain->Add_MapComponent(pComponent, ID_STATIC, L"Com_Renderer");

	//// Optimization
	//pComponent = newTerrain->m_pOptimizationCom = dynamic_cast<COptimization*>(Clone_Proto(L"Proto_Optimization"));
	//newTerrain->Add_MapComponent(pComponent,ID_STATIC,L"Com_Optimization");
	
	m_addList.AddString(m_textureNameVector[m_textureListIndex]);
	m_addTextureVector.push_back(newTerrain);

	m_pDeviceClass->Render_Begin(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.f));

	auto textureTemp = getTexture->Get_TextureInfo(m_textureNameVector[m_textureListIndex].operator LPCWSTR());

	D3DXMATRIX matScale, matTrans, matWorld;
	float ratioX = float(WINCX) / textureTemp->imageInfo.Width;
	float ratioY = float(WINCY) / textureTemp->imageInfo.Height;
	D3DXMatrixScaling(&matScale, ratioX, ratioY, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX / 2, WINCY / 2, 0.f);
	matWorld = matScale * matTrans;

	float centerX = textureTemp->imageInfo.Width >> 1;
	float centerY = textureTemp->imageInfo.Height >> 1;







	//getTexture->Render_Texture();
	//getTexture->Get_TextureInfo(m_textureName[index].operator LPCWSTR())->texture;
	m_pDeviceClass->Get_Sprite()->SetTransform(&matWorld);
	m_pDeviceClass->Get_Sprite()->Draw(textureTemp->texture, nullptr, &D3DXVECTOR3(centerX, centerY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	//CGraphicDev::GetInstance()->Get_Device()->SetTexture(0, getTexture);
	m_pDeviceClass->Render_End(m_pictureControl.m_hWnd);
	//CGraphic_Device::Get_Instance()->Render_End(m_picture.m_hWnd);
	UpdateData(FALSE);


}


void CTerrainTool::OnBnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTerrainTool::OnBnClickedButtonApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTerrainTool::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTerrainTool::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
