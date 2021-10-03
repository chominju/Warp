// TerrainTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapToolMFC.h"
#include "TerrainTab.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "Tool_Terrain.h"

// CTerrainTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTerrainTab, CDialogEx)

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
	, m_countX(2)
	, m_countZ(2)
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
	DDX_Control(pDX, IDC_TREE, m_tree);
}


BEGIN_MESSAGE_MAP(CTerrainTab, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &CTerrainTab::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON3, &CTerrainTab::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON4, &CTerrainTab::OnBnClickedButtonDelete)
	ON_LBN_SELCHANGE(IDC_LIST2, &CTerrainTab::OnLbnSelchangeListAdd)
	ON_BN_CLICKED(IDC_BUTTON1, &CTerrainTab::OnBnClickedButtonApply)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, &CTerrainTab::OnTvnSelchangedTree)
END_MESSAGE_MAP()


// CTerrainTab �޽��� ó�����Դϴ�.


void CTerrainTab::OnLbnSelchangeList1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
	InitTreeCtrl();
	// 1.1 C����̺��� ��������� TreeView�� �����ش�.
	//HTREEITEM hItem = m_tree.InsertItem(_T("D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource2", hItem));

	////  1.1.1 CFileFind�� �̿��Ͽ� "C:\\*.*"�� ���� �Ǵ� ������ ã�´�.
	//CFileFind finder;
	//BOOL bWorking = finder.FindFile(_T("D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource2\\*.*"));
	////  1.1.2 C����̺��� ��� ������ �ϳ��� �˻��ϸ鼭 ������ Tree�� ���������� �����Ѵ�.
	//while (bWorking) {
	//	//   1.1.2.1 "C:\\*.*"�� NextFile(C����̺��� ù��°)���� �Ʒ� �˻縦 �����Ѵ�.
	//	bWorking = finder.FindNextFile();
	//	//   1.1.2.2 ���� �˻��ϰ� �ִ� ���� Directory�� ��츸 Tree�� ���������� �����Ѵ�.
	//	if (finder.IsDirectory()) {
	//		m_tree.InsertItem(finder.GetFileName(), hItem);
	//	}
	//}
	////  1.1.3 ������ ��� Ʈ���������� ���̵��� �Ѵ�.
	//m_tree.EnsureVisible(hItem);

	//HTREEITEM hItem = m_tree.InsertItem(_T("D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource2", hItem));

	//CFileFind finder;
	//CString path = _T("D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource2\\*.*");
	//bool isWorking = finder.FindFile(path);

	//while (isWorking)
	//{
	//	isWorking = finder.FindNextFileW();

	//	if (finder.IsDirectory() || finder.IsDots())
	//		continue;

	//	cData = finder.GetFileName();
	//	/*_tchar * str = (wchar_t*)(const wchar_t*)cData;*/
	//	m_textureNameVector.push_back(cData);
	//	CString pathFull = relativePath + "\\" + cData;

	//	CTexture * instance = CTexture::Create(m_pGraphicDev, pathFull, TYPE_NORMAL, 1);
	//	instance->Insert_Texture(m_pGraphicDev, pathFull.operator LPCWSTR(), m_textureNameVector[i].operator LPCWSTR());
	//	Ready_Proto(m_textureNameVector[i], instance/*CTexture::Create(m_pGraphicDev, pathFull, TYPE_NORMAL, 1)*/);// , E_FAIL);
	//	m_textureListBox.AddString(cData);
	//	i++;
	//}






	m_spriteDev = CSpriteDev::Create(m_pGraphicDev);
	
	//CString path = _T("..\\Bin\Resource2\\Textures\\Terrain");
	CString path = _T("D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource2\\Textures\\Terrain");
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

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CTerrainTab::OnBnClickedButtonAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	g_index++;

	// Ʈ������
	CTerrain* newTerrain = CTerrain::Create(m_pGraphicDev);
	pComponent = newTerrain->m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
	newTerrain->m_pTransformCom->Set_Pos(m_posX, m_posY, m_posZ);
	newTerrain->Set_Index(g_index);

	m_addTextrueIndexVector.push_back(g_index);

	if (m_rotX)
		newTerrain->m_pTransformCom->Rotation(ROT_X, m_rotX);
	if (m_rotY)
		newTerrain->m_pTransformCom->Rotation(ROT_Y, m_rotY);
	if (m_rotZ)
		newTerrain->m_pTransformCom->Rotation(ROT_Z, m_rotZ);
	newTerrain->Add_Component(L"Com_Transform", ID_DYNAMIC, pComponent);


	
	// �ؽ���
	pComponent = newTerrain->m_pTextureCom = getTexture;
	newTerrain->Add_Component(L"Com_Texture", ID_STATIC, pComponent);

	// renderer
	pComponent = newTerrain->m_pRendererCom = Get_Renderer();
	pComponent->AddRef();
	newTerrain->Add_Component(L"Com_Renderer", ID_STATIC, pComponent);

	// buffer
	//Ready_Proto(L"Proto_Buffer_TerrainTex", CTerrainTex::Create(m_pGraphicDev, m_countX, m_countZ, VTXITV));// , E_FAIL);
	pComponent = newTerrain->m_pBufferCom = dynamic_cast<CTerrainTex*>(Clone_Proto(L"Proto_Buffer_TerrainTex"));
	newTerrain->Add_Component(L"Com_Buffer", ID_STATIC, pComponent);

	m_addTextureList.AddString(m_textureNameVector[m_textureListIndex]);
	m_addTextureVector.push_back(newTerrain);

	CLayer*		pLayer = CLayer::Create();
	//pLayer->Add_GameObject(L"Terrain",newTerrain);
	CManagement::GetInstance()->Get_Scene()->Add_LayerGameObject(L"GameLogic", pLayer, L"Terrain", newTerrain);
	

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	//m_addTextureVector[m_addListIndex]->m_pTransformCom->Set_Pos(m_posX, m_posY, m_posY);
	//
	//m_addTextureVector[m_addListIndex]->m_pTransformCom->Rotation(ROT_X, m_rotX);

	//m_addTextureVector[m_addListIndex]->m_pTransformCom->Rotation(ROT_Y, m_rotY);

	//m_addTextureVector[m_addListIndex]->m_pTransformCom->Rotation(ROT_Z, m_rotZ);
	//
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}



void CTerrainTab::InitTreeCtrl()
{
	HTREEITEM hItem = m_tree.InsertItem(_T("Resource2", hItem));

	//  1.1.1 CFileFind�� �̿��Ͽ� "C:\\*.*"�� ���� �Ǵ� ������ ã�´�.
	CFileFind finder;

	CString path = _T("D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource2\\*.*");
	CString wstrRelativePath = L"";
	wstrRelativePath = CFileInfo::ConvertRelativePath(path);
	CString relativePath = wstrRelativePath;

	BOOL bWorking = finder.FindFile(/*_T(*//*"D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource2\\*.*"*/wstrRelativePath/*)*/);
	//  1.1.2 C����̺��� ��� ������ �ϳ��� �˻��ϸ鼭 ������ Tree�� ���������� �����Ѵ�.
	while (bWorking) 
	{
		//   1.1.2.1 "C:\\*.*"�� NextFile(C����̺��� ù��°)���� �Ʒ� �˻縦 �����Ѵ�.
		bWorking = finder.FindNextFile();

		if (finder.IsDots())
			continue;
		//   1.1.2.2 ���� �˻��ϰ� �ִ� ���� Directory�� ��츸 Tree�� ���������� �����Ѵ�.
		if (finder.IsDirectory()) 
		{
			m_tree.InsertItem(finder.GetFileName(), hItem);
		}
	}
	//  1.1.3 ������ ��� Ʈ���������� ���̵��� �Ѵ�.
	m_tree.EnsureVisible(hItem);
}


void CTerrainTab::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	// 1.2 TreeView�� ������ ���콺�� Ŭ���ϸ�, �������� ����� TreeView�� �����ش�.
	HTREEITEM hSelected = pNMTreeView->itemNew.hItem; // ���� ������ ������


													  // (������ ���� ���� ����)
													  // 1.2.2.1 ���õ� �������� ���� ����� Ʈ����Ʈ�ѿ� �߰��Ѵ�.
													  // 1.2.2.1.1 ���õ� �������� ��θ� �о�´�. 

	CString pathSelected; //�������� ���� ��� pathSelected�� �����Ѵ�.


	HTREEITEM hParentItem = hSelected; // ���� ���õ� �������� ù��° �������� �Ѵ�.
	while (hParentItem != NULL)
	{ // �ֻ��� �θ� ���� �� ����
		pathSelected = _T("\\") + pathSelected;
		pathSelected = m_tree.GetItemText(hParentItem) + pathSelected;
		hParentItem = m_tree.GetParentItem(hParentItem);
	}

	CString temp = L"..\\Bin\\";

	// �ϼ��� ����� �ڿ� "*.*"�� �ٿ��־ �������� ���õ� �������� ��θ� �ϼ��Ѵ�.
	pathSelected = temp+ pathSelected + _T("*.*");

	// 1.2.2.1.2 CFileFind�� �̿��Ͽ� �о�� ����� ���� �Ǵ� ������ ã�´�.
	CFileFind finder;
	BOOL bWorking = finder.FindFile(pathSelected);

	// 1.2.1 ������ �������� �������� �ִ��� ������ �˻��Ѵ�.
	// 1.2.2 ���õ� ���� ���� ���, 
	//       => �ش� �������� GetItemData()�� 0���� �ʱ�ȭ �Ǿ�����.
	if (m_tree.GetItemData(hSelected) == 0)
	{
		// 1.2.2.1.3 ������ �������� ��������� �ϳ��� �˻��ϸ鼭 ������ ��츸 Tree ���������� �����Ѵ�. (. or ..�� ����)
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (finder.IsDots())
				continue;
			if (finder.IsDirectory()) 
			{
				m_tree.InsertItem(finder.GetFileName(), hSelected);
			}


		}

		// 1.2.2.2 �ش� �������� ���õ� ���� ������ SetItemData() �Լ��� ǥ���Ѵ�.
		m_tree.SetItemData(hSelected, 1);

		// 1.2.3 ���õ� ���� �ִ� ���, �ƹ� �۾��� ���� �ʴ´�. (�̹� ���� ����� Ʈ���� �߰��Ǿ� �����Ƿ�)
		// 1.2.4 ���±��� ������ Ʈ���������� TreeView�� �������� �Ѵ�.
		m_tree.EnsureVisible(hSelected);
	}

	//  �߰� �� �ڵ�------------------------------------------------------------------------
	//  2.1 TreeView�� ������ ���콺�� Ŭ���ϸ�, ListCtrl�� ����ִ� �������� ����.
	if (pNMTreeView->itemNew.hItem != pNMTreeView->itemOld.hItem)
	{
		m_textureListBox.ResetContent();// DeleteAllItems();
	}
	//  2.2 Ʈ���信�� ������ �������� ���������� ������ ListView�� �����ش�.
	bWorking = finder.FindFile(pathSelected);
	while (bWorking) {
		bWorking = finder.FindNextFile();
		if (finder.IsDots()) continue;

		CString ttemp = finder.GetFileName();
		m_textureListBox.AddString(finder.GetFileName());// InsertItem(1, finder.GetFileName());

	}
	//  -----------------------------------------------------------------------------------
	*pResult = 0;
}
