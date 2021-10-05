// TerrainTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapToolMFC.h"
#include "TerrainTab.h"
#include "afxdialogex.h"
#include "MapToolMFCView.h"
#include "MainFrm.h"
#include "FileInfo.h"
#include "Tool_Terrain.h"

// CTerrainTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTerrainTab, CDialogEx)

//CTerrainTab::CTerrainTab()
//{
//
//}

CTerrainTab::CTerrainTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_pDeviceClass(CGraphicDev::GetInstance())
	, m_pGraphicDev(CGraphicDev::GetInstance()->Get_Device())
	, m_pManagementClass(CManagement::GetInstance())
	, m_posX(0)
	, m_posY(0)
	, m_rotX(0)
	, m_rotY(0)
	, m_rotZ(0)
	, m_countX(129)
	, m_countZ(129)
	, m_posZ(0)
{

}

CTerrainTab::~CTerrainTab()
{
}

void CTerrainTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_textureListBox);
	DDX_Control(pDX, IDC_LIST2, m_addTextureList);
	DDX_Control(pDX, IDC_PICTURE, m_pictureControl);
	DDX_Text(pDX, IDC_EDIT1, m_posX);
	DDX_Text(pDX, IDC_EDIT2, m_posY);
	DDX_Text(pDX, IDC_EDIT4, m_rotX);
	DDX_Text(pDX, IDC_EDIT5, m_rotY);
	DDX_Text(pDX, IDC_EDIT6, m_rotZ);
	DDX_Text(pDX, IDC_EDIT7, m_countX);
	DDX_Text(pDX, IDC_EDIT8, m_countZ);
	DDX_Text(pDX, IDC_EDIT3, m_posZ);
}


BEGIN_MESSAGE_MAP(CTerrainTab, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &CTerrainTab::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON3, &CTerrainTab::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON4, &CTerrainTab::OnBnClickedButtonDelete)
	ON_LBN_SELCHANGE(IDC_LIST2, &CTerrainTab::OnLbnSelchangeListAdd)
	ON_BN_CLICKED(IDC_BUTTON1, &CTerrainTab::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON2, &CTerrainTab::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON5, &CTerrainTab::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CTerrainTab 메시지 처리기입니다.


void CTerrainTab::OnLbnSelchangeList1()
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

	m_spriteDev->Render_BeginSprite(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));

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
	
	m_spriteDev->Get_Sprite()->SetTransform(&matWorld);
	m_spriteDev->Get_Sprite()->Draw(textureTemp->texture, nullptr, &D3DXVECTOR3(centerX, centerY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	//CGraphicDev::GetInstance()->Get_Device()->SetTexture(0, getTexture);
	m_spriteDev->Render_EndSprite(m_pictureControl.m_hWnd);
	//CGraphic_Device::Get_Instance()->Render_End(m_picture.m_hWnd);

	UpdateData(FALSE);
}


BOOL CTerrainTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_spriteDev = CSpriteDev::Create(m_pGraphicDev);
	
	//CString path = _T("..\\Bin\Resource2\\Textures\\Terrain");
	CString path = _T("D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource3\\Texture\\Terrain");
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
		CString pathFull = relativePath + "\\" + cData;

		CTexture * instance = CTexture::Create(m_pGraphicDev, pathFull, TYPE_NORMAL, 1);
		instance->Insert_Texture(m_pGraphicDev, pathFull.operator LPCWSTR(), m_textureNameVector[i].operator LPCWSTR());
		Ready_Proto(m_textureNameVector[i], instance/*CTexture::Create(m_pGraphicDev, pathFull, TYPE_NORMAL, 1)*/);// , E_FAIL);
		m_textureListBox.AddString(cData);
		i++;
	}

	CMainFrame* main = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	m_mfcView = dynamic_cast<CMapToolMFCView*>(main->m_MainSplitter.GetPane(0, 1));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTerrainTab::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTexture* getTexture = dynamic_cast<CTexture*>(Clone_Proto(m_textureNameVector[m_textureListIndex]));
	if (nullptr == getTexture)
		return;

	m_posX = GetDlgItemInt(IDC_EDIT1);
	m_posY = GetDlgItemInt(IDC_EDIT2);

	m_rotX = GetDlgItemInt(IDC_EDIT4);
	m_rotY = GetDlgItemInt(IDC_EDIT5);
	m_rotZ = GetDlgItemInt(IDC_EDIT6);

	m_countX = GetDlgItemInt(IDC_EDIT7);
	m_countX = GetDlgItemInt(IDC_EDIT8);

	CComponent*			pComponent = nullptr;
	Terrain_Data terrainData;
	terrainData.m_pos[INFO_POS].x = m_posX;
	terrainData.m_pos[INFO_POS].y = m_posY;
	terrainData.m_pos[INFO_POS].z = m_posZ;
	terrainData.m_vAngle.x = m_rotX;
	terrainData.m_vAngle.y = m_rotY;
	terrainData.m_vAngle.z = m_rotZ;
	terrainData.m_cntX = m_countX;
	terrainData.m_cntZ = m_countZ;
	_tcscpy_s(terrainData.m_terrainTextureName, _countof(terrainData.m_terrainTextureName), m_textureNameVector[m_textureListIndex]);


	g_index++;

	// 트랜스폼
	CTerrain* newTerrain = CTerrain::Create(m_pGraphicDev);
	/*pComponent = newTerrain->m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
	newTerrain->m_pTransformCom->Set_Pos(m_posX, m_posY, m_posZ);*/
	newTerrain->Set_Index(g_index);
	terrainData.m_terrainIndex = g_index;


	m_addTextrueIndexVector.push_back(g_index);

	/*if (m_rotX)
		newTerrain->m_pTransformCom->Rotation(ROT_X, m_rotX);
	if (m_rotY)
		newTerrain->m_pTransformCom->Rotation(ROT_Y, m_rotY);
	if (m_rotZ)
		newTerrain->m_pTransformCom->Rotation(ROT_Z, m_rotZ);
	newTerrain->Add_AddComponent(L"Com_Transform", ID_DYNAMIC, pComponent);*/


	
	// 텍스쳐
	pComponent = newTerrain->m_pTextureCom = getTexture;
	newTerrain->Add_AddComponent(L"Com_Texture", ID_STATIC, pComponent);

	//// renderer
	//pComponent = newTerrain->m_pRendererCom = Get_Renderer();
	//pComponent->AddRef();
	//newTerrain->Add_AddComponent(L"Com_Renderer", ID_STATIC, pComponent);

	//// buffer
	////Ready_Proto(L"Proto_Buffer_TerrainTex", CTerrainTex::Create(m_pGraphicDev, m_countX, m_countZ, VTXITV));// , E_FAIL);
	//pComponent = newTerrain->m_pBufferCom = dynamic_cast<CTerrainTex*>(Clone_Proto(L"Proto_Buffer_TerrainTex"));
	//newTerrain->Add_AddComponent(L"Com_Buffer", ID_STATIC, pComponent);

	newTerrain->Set_TerrainData(terrainData);

	m_addTextureList.AddString(m_textureNameVector[m_textureListIndex]);
	m_addTextureVector.push_back(newTerrain);

	CLayer*		pLayer = CLayer::Create();
	//pLayer->Add_GameObject(L"Terrain",newTerrain);
	CManagement::GetInstance()->Get_Scene()->Add_LayerGameObject(L"GameLogic", pLayer, L"Terrain", newTerrain);
	
	m_mfcView->Render_View();

	//D3DXMATRIX matScale, matTrans, matWorld;
	//float ratioX = float(WINCX) / textureTemp->imageInfo.Width;
	//float ratioY = float(WINCY) / textureTemp->imageInfo.Height;
	//D3DXMatrixScaling(&matScale, ratioX, ratioY, 0.f);
	//D3DXMatrixTranslation(&matTrans, WINCX / 2, WINCY / 2, 0.f);
	//matWorld = matScale * matTrans;

	//float centerX = textureTemp->imageInfo.Width >> 1;
	//float centerY = textureTemp->imageInfo.Height >> 1;







	////getTexture->Render_Texture();
	////getTexture->Get_TextureInfo(m_textureName[index].operator LPCWSTR())->texture;
	//m_pDeviceClass->Get_Sprite()->SetTransform(&matWorld);
	//m_pDeviceClass->Get_Sprite()->Draw(textureTemp->texture, nullptr, &D3DXVECTOR3(centerX, centerY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	////CGraphicDev::GetInstance()->Get_Device()->SetTexture(0, getTexture);
	//m_pDeviceClass->Render_End(m_pictureControl.m_hWnd);
	////CGraphic_Device::Get_Instance()->Render_End(m_picture.m_hWnd);
	//UpdateData(FALSE);
}


void CTerrainTab::OnBnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CTerrainTab::CreateTerrain()
{
}


void CTerrainTab::OnLbnSelchangeListAdd()
{
	UpdateData(TRUE);

	m_addListIndex = m_addTextureList.GetCurSel();

	CGameObject* getObject = CManagement::GetInstance()->Get_Scene()->Get_MapLayer(L"GameLogic", L"Terrain", m_addTextrueIndexVector[m_addListIndex]);
	_vec3 pos, rot;
	dynamic_cast<CTerrain*>(getObject)->m_pTransformCom->Get_Info(INFO_POS, &pos);
	m_posX = pos.x;
	m_posY = pos.y;
	m_posZ = pos.z;
	dynamic_cast<CTerrain*>(getObject)->m_pTransformCom->Get_Rotation(&rot);
	m_rotX = rot.x;
	m_rotY = rot.y;
	m_rotZ = rot.z;

	m_countX = dynamic_cast<CTerrain*>(getObject)->m_pBufferCom->Get_CntX();
	m_countZ = dynamic_cast<CTerrain*>(getObject)->m_pBufferCom->Get_CntZ();
	
	UpdateData(FALSE);
	//m_addTextureVector[m_addListIndex]->m_pTransformCom->Set_Pos(m_posX, m_posY, m_posY);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTerrainTab::OnBnClickedButtonApply()
{
	if (m_addTextureVector.size() == 0 /*|| m_addListIndex==NULL*/)
		return;

	m_posX = GetDlgItemInt(IDC_EDIT1);
	m_posY = GetDlgItemInt(IDC_EDIT2);
	m_posZ = GetDlgItemInt(IDC_EDIT3);

	m_rotX = GetDlgItemInt(IDC_EDIT4);
	m_rotY = GetDlgItemInt(IDC_EDIT5);
	m_rotZ = GetDlgItemInt(IDC_EDIT6);

	m_countX = GetDlgItemInt(IDC_EDIT7);
	m_countZ = GetDlgItemInt(IDC_EDIT8);

	CGameObject* getObject = CManagement::GetInstance()->Get_Scene()->Get_MapLayer(L"GameLogic",L"Terrain", m_addTextrueIndexVector[m_addListIndex]);
	dynamic_cast<CTerrain*>(getObject)->m_pTransformCom->Set_Pos(m_posX, m_posY, m_posZ);

	dynamic_cast<CTerrain*>(getObject)->m_pTransformCom->Rotation(ROT_X, m_rotX);

	dynamic_cast<CTerrain*>(getObject)->m_pTransformCom->Rotation(ROT_Y, m_rotY);

	dynamic_cast<CTerrain*>(getObject)->m_pTransformCom->Rotation(ROT_Z, m_rotZ);

	dynamic_cast<CTerrain*>(getObject)->m_pBufferCom->Reset_Buffer(m_countX, m_countZ);

	m_mfcView->Render_View();

	//m_addTextureVector[m_addListIndex]->m_pTransformCom->Set_Pos(m_posX, m_posY, m_posY);
	//
	//m_addTextureVector[m_addListIndex]->m_pTransformCom->Rotation(ROT_X, m_rotX);

	//m_addTextureVector[m_addListIndex]->m_pTransformCom->Rotation(ROT_Y, m_rotY);

	//m_addTextureVector[m_addListIndex]->m_pTransformCom->Rotation(ROT_Z, m_rotZ);
	//
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTerrainTab::OnBnClickedButtonSave()
{
	CString m_strPath;
	CStdioFile file;
	// CFile file;
	CFileException ex;

	CFileDialog Dlg(FALSE,
		L"dat",
		L"*.dat",
		OFN_OVERWRITEPROMPT,
		L"Data File(*.dat) | *.dat||",
		this);

	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (Dlg.DoModal())
	{
		CString wstrFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD dwByte = 0;
		DWORD dwStringSize = 0;
		for (auto& pTerrain : m_addTextureVector)
		{
			Terrain_Data temp = pTerrain->Get_TerrainData();
			dwStringSize = (_tcslen(temp.m_terrainTextureName) + 1)* sizeof(wchar_t);
			WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, temp.m_terrainTextureName, dwStringSize, &dwByte, nullptr);
			WriteFile(hFile, &temp.m_terrainIndex, sizeof(int), &dwByte, nullptr);

			WriteFile(hFile, &temp.m_cntX, sizeof(_ulong), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_cntZ, sizeof(_ulong), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_pos[INFO_POS].x, sizeof(float), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_pos[INFO_POS].y, sizeof(float), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_pos[INFO_POS].z, sizeof(float), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_vAngle.x, sizeof(float), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_vAngle.y, sizeof(float), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_vAngle.z, sizeof(float), &dwByte, nullptr);
			

			//WriteFile(file, &temp, sizeof(Terrain_Data), &dwByte, nullptr);



		/*	dwStringSize = sizeof(wchar_t) * (rPair.second->strName.GetLength() + 1);
			WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, rPair.second->strName.GetString(), dwStringSize, &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->iAtt, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->iDef, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->byItem, sizeof(BYTE), &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->byJop, sizeof(BYTE), &dwByte, nullptr);*/
		}

		CloseHandle(hFile);
	}






	////// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CFileDialog dig(FALSE, // 다른이름으로 저장. 만약 TRUE 파일 열기. 
	//	L"dat",// 디폴트 확장자 
	//	L"*.dat",// 디폴트 파일 이름 
	//	OFN_OVERWRITEPROMPT);// 덮어쓸때 경고 메시지 띄어주겠다. 
	//TCHAR szCurDir[MAX_PATH]{};
	//GetCurrentDirectory(MAX_PATH, szCurDir);
	////D:\박병건\118C\D2D\Framework_v1
	//PathRemoveFileSpec(szCurDir);
	//lstrcat(szCurDir, L"\\Data");
	//dig.m_ofn.lpstrInitialDir = szCurDir;
	//if (IDOK == dig.DoModal())
	//{
	//	CString filePath = dig.GetPathName();
	//	HANDLE file = CreateFile(filePath.GetString(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	//	if (INVALID_HANDLE_VALUE == file)
	//		return;

	//	DWORD byte = 0;
	//	for (auto& pTile : m_addTextureVector)
	//		WriteFile(file, pTile, sizeof(CTerrain), &byte, nullptr);

	//	CloseHandle(file);
	//}

}





void CTerrainTab::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog dlg(TRUE, // 다른이름으로 저장. 만약 TRUE 파일 열기. 
		L"dat",// 디폴트 확장자 
		L"*.dat",// 디폴트 파일 이름 
		OFN_OVERWRITEPROMPT);// 덮어쓸때 경고 메시지 띄어주겠다. 
	TCHAR szCurDir[MAX_PATH]{};
	GetCurrentDirectory(MAX_PATH, szCurDir);
	//D:\박병건\118C\D2D\Framework_v1
	PathRemoveFileSpec(szCurDir);
	lstrcat(szCurDir, L"\\Data");
	dlg.m_ofn.lpstrInitialDir = szCurDir;

	m_addTextureVector.clear();

	if (IDOK == dlg.DoModal())
	{
		CString filePath = dlg.GetPathName();
		HANDLE hFile = CreateFile(filePath.GetString(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;
		DWORD dwByte = 0;
		DWORD dwStringCount = 0;
		g_index = -1;
		m_addTextrueIndexVector.clear();
		_tchar* szBuf = nullptr;
		while (true)
		{
			//Terrain_Data* temp=new Terrain_Data;
			//terrain = CTerrain::Create(m_pGraphicDev);
			//ReadFile(hFile, temp, sizeof(Terrain_Data), &dwByte, nullptr);
			//terrain->Set_TerrainData(temp);

			Terrain_Data tempTerrainData;
			ReadFile(hFile, &dwStringCount, sizeof(DWORD), &dwByte, nullptr);
			if (0 == dwByte)
				break;
			szBuf = new _tchar[dwStringCount];
			ReadFile(hFile, szBuf, dwStringCount, &dwByte, nullptr);

			_tcscpy_s(tempTerrainData.m_terrainTextureName, _countof(tempTerrainData.m_terrainTextureName), szBuf);
			Safe_Delete_Array(szBuf);

			ReadFile(hFile, &tempTerrainData.m_terrainIndex, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &tempTerrainData.m_cntX, sizeof(_ulong), &dwByte, nullptr);
			ReadFile(hFile, &tempTerrainData.m_cntZ, sizeof(_ulong), &dwByte, nullptr);
			ReadFile(hFile, &tempTerrainData.m_pos[INFO_POS].x, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &tempTerrainData.m_pos[INFO_POS].y, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &tempTerrainData.m_pos[INFO_POS].z, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &tempTerrainData.m_vAngle.x, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &tempTerrainData.m_vAngle.y, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &tempTerrainData.m_vAngle.z, sizeof(float), &dwByte, nullptr);


			CTexture* getTexture = dynamic_cast<CTexture*>(Clone_Proto(tempTerrainData.m_terrainTextureName));
			if (nullptr == getTexture)
				return;

			g_index++;
			CComponent*			pComponent = nullptr;
			CTerrain* newTerrain = CTerrain::Create(m_pGraphicDev);
			newTerrain->m_pTransformCom->Set_Pos(tempTerrainData.m_pos[INFO_POS].x, tempTerrainData.m_pos[INFO_POS].y, tempTerrainData.m_pos[INFO_POS].z);
			newTerrain->m_pTransformCom->Rotation(ROT_X, tempTerrainData.m_vAngle.x);
			newTerrain->m_pTransformCom->Rotation(ROT_Y, tempTerrainData.m_vAngle.y);
			newTerrain->m_pTransformCom->Rotation(ROT_Z, tempTerrainData.m_vAngle.z);
			newTerrain->m_pBufferCom->Reset_Buffer(tempTerrainData.m_cntX, tempTerrainData.m_cntZ);
			newTerrain->Set_Index(tempTerrainData.m_terrainIndex);

			m_addTextrueIndexVector.push_back(g_index);

			// 텍스쳐
			pComponent = newTerrain->m_pTextureCom = getTexture;
			newTerrain->Add_AddComponent(L"Com_Texture", ID_STATIC, pComponent);

			//// renderer
			//pComponent = newTerrain->m_pRendererCom = Get_Renderer();
			//pComponent->AddRef();
			//newTerrain->Add_AddComponent(L"Com_Renderer", ID_STATIC, pComponent);

			//// buffer
			////Ready_Proto(L"Proto_Buffer_TerrainTex", CTerrainTex::Create(m_pGraphicDev, m_countX, m_countZ, VTXITV));// , E_FAIL);
			//pComponent = newTerrain->m_pBufferCom = dynamic_cast<CTerrainTex*>(Clone_Proto(L"Proto_Buffer_TerrainTex"));
			//newTerrain->Add_AddComponent(L"Com_Buffer", ID_STATIC, pComponent);

			newTerrain->Set_TerrainData(tempTerrainData);

			m_addTextureList.AddString(m_textureNameVector[m_textureListIndex]);
			m_addTextureVector.push_back(newTerrain);

			CLayer*		pLayer = CLayer::Create();
			//pLayer->Add_GameObject(L"Terrain",newTerrain);
			CManagement::GetInstance()->Get_Scene()->Add_LayerGameObject(L"GameLogic", pLayer, L"Terrain", newTerrain);


			//ReadFile(hFile, &pUnitInfo->iAtt, sizeof(int), &dwByte, nullptr);
			//ReadFile(hFile, &pUnitInfo->iDef, sizeof(int), &dwByte, nullptr);
			//ReadFile(hFile, &pUnitInfo->byJob, sizeof(BYTE), &dwByte, nullptr);
			//ReadFile(hFile, &pUnitInfo->byItem, sizeof(BYTE), &dwByte, nullptr);

			//m_mapUnitInfo.emplace(pUnitInfo->wstrName, pUnitInfo);
			//m_ListBox.AddString(pUnitInfo->wstrName);


			//if (0 == dwByte)
			//{
			//	Safe_Release(terrain);
			//	break;
			//}
		}
		m_mfcView->Render_View();
	}
}
