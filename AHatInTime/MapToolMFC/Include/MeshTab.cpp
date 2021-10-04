// MeshTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapToolMFC.h"
#include "MeshTab.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "Tool_Stone.h"
#include "Tool_Stone.h"


// CMeshTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMeshTab, CDialogEx)

CMeshTab::CMeshTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_pDeviceClass(CGraphicDev::GetInstance())
	, m_pGraphicDev(CGraphicDev::GetInstance()->Get_Device())
	, m_pManagementClass(CManagement::GetInstance())
	, m_posX(0)
	, m_posY(0)
	, m_posZ(0)
	, m_rotX(0)
	, m_rotY(0)
	, m_rotZ(0)
{

}

CMeshTab::~CMeshTab()
{
}

void CMeshTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_meshList);
	DDX_Control(pDX, IDC_LIST2, m_addMeshList);
	DDX_Text(pDX, IDC_EDIT1, m_posX);
	DDX_Text(pDX, IDC_EDIT2, m_posY);
	DDX_Text(pDX, IDC_EDIT3, m_posZ);
	DDX_Text(pDX, IDC_EDIT4, m_rotX);
	DDX_Text(pDX, IDC_EDIT5, m_rotY);
	DDX_Text(pDX, IDC_EDIT6, m_rotZ);
	//DDX_Control(pDX, IDC_TREE1, m_tree);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}


BEGIN_MESSAGE_MAP(CMeshTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CMeshTab::OnBnClickedButtonAdd)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMeshTab::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMeshTab::OnBnClickedButtonApply)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMeshTab::OnLbnSelchangeListAdd)
	//ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMeshTab::OnTvnSelchangedTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMeshTab::OnTvnSelchangedTree1)
END_MESSAGE_MAP()


// CMeshTab �޽��� ó�����Դϴ�.


BOOL CMeshTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitTreeCtrl();
	//m_spriteDev = CSpriteDev::Create(m_pGraphicDev);

	////CString path = _T("..\\Bin\Resource2\\Textures\\Terrain");
	//CString path = _T("D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource2\\Meshes\\StaticMeshTemp");
	////CString path = _T("D:\\Jusin\\AHatInTime\\AHatInTime\\MapTool\\Bin\\Resource2\\Textures\\Terrain");
	//CString wstrRelativePath = L"";
	//wstrRelativePath = CFileInfo::ConvertRelativePath(path);
	//CString relativePath = wstrRelativePath;				// �����
	//CString relativePath2 = relativePath;					
	//relativePath2.Insert(relativePath2.GetLength(), L"\\"); // ������//������
	//CFileFind finder;
	//int size = path.GetLength();
	//path.Insert(size, L"\\*.X");

	//bool isWorking = finder.FindFile(path);
	//CString cData;
	//int i = 0;
	//while (isWorking)
	//{
	//	isWorking = finder.FindNextFileW();

	//	if (finder.IsDirectory() || finder.IsDots())
	//		continue;

	//	cData = finder.GetFileName();
	//	/*_tchar * str = (wchar_t*)(const wchar_t*)cData;*/
	//	m_meshNameVector.push_back(cData);
	//	CString pathFull = relativePath + "\\" + cData;

	//	//CStaticMesh * instance = CStaticMesh::Create(m_pGraphicDev, relativePath2, cData);
	//	Ready_Proto(m_meshNameVector[i], CStaticMesh::Create(m_pGraphicDev, relativePath2, cData));


	//	//CTexture * instance = CTexture::Create(m_pGraphicDev, pathFull, TYPE_NORMAL, 1);
	//	//instance->Insert_Texture(m_pGraphicDev, pathFull.operator LPCWSTR(), m_meshNameVector[i].operator LPCWSTR());
	//	//Ready_Proto(m_meshNameVector[i], instance/*CTexture::Create(m_pGraphicDev, pathFull, TYPE_NORMAL, 1)*/);// , E_FAIL);
	//	m_meshList.AddString(cData);
	//	i++;
	//}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMeshTab::OnBnClickedButtonAdd()
{

	m_posX = GetDlgItemInt(IDC_EDIT1);
	m_posY = GetDlgItemInt(IDC_EDIT2);

	m_rotX = GetDlgItemInt(IDC_EDIT4);
	m_rotY = GetDlgItemInt(IDC_EDIT5);
	m_rotZ = GetDlgItemInt(IDC_EDIT6);

	g_index++;

	CLayer*		pLayer = CLayer::Create();
	CGameObject*			pGameObject = nullptr;
	// Stone
	pGameObject = CStone::Create(m_pGraphicDev);
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->Add_GameObject(L"Stone", pGameObject);
	pGameObject->Set_Index(g_index);
	CManagement::GetInstance()->Get_Scene()->Add_LayerGameObject(L"GameLogic", pLayer, L"Stone", pGameObject);

	m_addMeshList.AddString(m_meshNameVector[m_meshListIndex]);

	m_meshIndexVector.push_back(g_index);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//CTexture* getTexture = dynamic_cast<CTexture*>(Clone_Proto(m_textureNameVector[m_textureListIndex]));
	//if (nullptr == getTexture)
	//	return;

	//CComponent*			pComponent = nullptr;

	//// Ʈ������
	//CTerrain* newTerrain = CTerrain::Create(m_pGraphicDev);
	//pComponent = newTerrain->m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
	//newTerrain->m_pTransformCom->Set_Pos(m_posX, m_posY, m_posZ);

	//if (m_rotX)
	//	newTerrain->m_pTransformCom->Rotation(ROT_X, m_rotX);
	//if (m_rotY)
	//	newTerrain->m_pTransformCom->Rotation(ROT_Y, m_rotY);
	//if (m_rotZ)
	//	newTerrain->m_pTransformCom->Rotation(ROT_Z, m_rotZ);
	//newTerrain->Add_Component(L"Com_Transform", ID_DYNAMIC, pComponent);



	//// �ؽ���
	//pComponent = newTerrain->m_pTextureCom = getTexture;
	//newTerrain->Add_Component(L"Com_Texture", ID_STATIC, pComponent);

	//// renderer
	//pComponent = newTerrain->m_pRendererCom = Get_Renderer();
	//pComponent->AddRef();
	//newTerrain->Add_Component(L"Com_Renderer", ID_STATIC, pComponent);

	//// buffer
	//Ready_Proto(L"Proto_Buffer_TerrainTex", CTerrainTex::Create(m_pGraphicDev, m_countX, m_countZ, VTXITV));// , E_FAIL);
	//pComponent = newTerrain->m_pBufferCom = dynamic_cast<CTerrainTex*>(Clone_Proto(L"Proto_Buffer_TerrainTex"));
	//newTerrain->Add_Component(L"Com_Buffer", ID_STATIC, pComponent);

	//m_addTextureList.AddString(m_textureNameVector[m_textureListIndex]);
	//m_addTextureVector.push_back(newTerrain);

	//CLayer*		pLayer = CLayer::Create();
	//pLayer->Add_GameObject(L"Terrain", newTerrain);
	//CManagement::GetInstance()->Get_Scene()->Add_LayerGameObject(L"GameLogic", pLayer, L"Terrain", newTerrain);



	//CComponent*			pComponent = nullptr;

	//// StaticMesh
	//pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(L"Proto_Mesh_Stone"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(L"Com_Mesh", pComponent);

	//// Transform
	//pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	//// renderer
	//pComponent = m_pRendererCom = Get_Renderer();
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//pComponent->AddRef();
	//m_mapComponent[ID_STATIC].emplace(L"Com_Renderer", pComponent);

	//// Calculator
	//pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(L"Proto_Calculator"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_DYNAMIC].emplace(L"Com_Calculator", pComponent);

	//// Collider
	//pComponent = m_pColliderCom = CCollider::Create(m_pGraphicDev, m_pMeshCom->Get_VtxPos(), m_pMeshCom->Get_NumVtx(), m_pMeshCom->Get_VtxSize());
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(L"Com_Collider", pComponent);

	//// Optimization
	//pComponent = m_pOptimizationCom = dynamic_cast<COptimization*>(Clone_Proto(L"Proto_Optimization"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(L"Com_Optimization", pComponent);





}


void CMeshTab::OnLbnSelchangeList1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	m_meshListIndex = m_meshList.GetCurSel();

	UpdateData(FALSE);
}


void CMeshTab::OnBnClickedButtonApply()
{
	if (m_meshNameVector.size() == 0 /*|| m_addListIndex==NULL*/)
		return;

	m_posX = GetDlgItemInt(IDC_EDIT1);
	m_posY = GetDlgItemInt(IDC_EDIT2);
	m_posZ = GetDlgItemInt(IDC_EDIT3);

	m_rotX = GetDlgItemInt(IDC_EDIT4);
	m_rotY = GetDlgItemInt(IDC_EDIT5);
	m_rotZ = GetDlgItemInt(IDC_EDIT6);


	//  m_pMeshCom
	//	m_pTransformCom
	//	m_pRendererCom

	CGameObject* getObject = CManagement::GetInstance()->Get_Scene()->Get_MapLayer(L"GameLogic", L"Stone",m_meshIndexVector[m_addMeshListIndex]);
	dynamic_cast<CStone*>(getObject)->m_pTransformCom->Set_Pos(m_posX, m_posY, m_posZ);

	dynamic_cast<CStone*>(getObject)->m_pTransformCom->Rotation(ROT_X, m_rotX);

	dynamic_cast<CStone*>(getObject)->m_pTransformCom->Rotation(ROT_Y, m_rotY);

	dynamic_cast<CStone*>(getObject)->m_pTransformCom->Rotation(ROT_Z, m_rotZ);

	//m_addTextureVector[m_addListIndex]->m_pTransformCom->Set_Pos(m_posX, m_posY, m_posY);
	//
	//m_addTextureVector[m_addListIndex]->m_pTransformCom->Rotation(ROT_X, m_rotX);

	//m_addTextureVector[m_addListIndex]->m_pTransformCom->Rotation(ROT_Y, m_rotY);

	//m_addTextureVector[m_addListIndex]->m_pTransformCom->Rotation(ROT_Z, m_rotZ);
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMeshTab::OnLbnSelchangeListAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_addMeshListIndex = m_addMeshList.GetCurSel();
}


void CMeshTab::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
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
	pathSelected = temp + pathSelected + _T("*.*");

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
		//m_textureListBox.ResetContent();// DeleteAllItems();
	}
	//  2.2 Ʈ���信�� ������ �������� ���������� ������ ListView�� �����ش�.
	bWorking = finder.FindFile(pathSelected);
	while (bWorking) {
		bWorking = finder.FindNextFile();
		if (finder.IsDots()) continue;

		CString ttemp = finder.GetFileName();
		//m_textureListBox.AddString(finder.GetFileName());// InsertItem(1, finder.GetFileName());

	}
	//  -----------------------------------------------------------------------------------
	*pResult = 0;
}


void CMeshTab::InitTreeCtrl()
{
	HTREEITEM hItem = m_tree.InsertItem(_T("Resource3", hItem));

	//  1.1.1 CFileFind�� �̿��Ͽ� "C:\\*.*"�� ���� �Ǵ� ������ ã�´�.
	CFileFind finder;

	CString path = _T("D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource3\\*.*");
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
