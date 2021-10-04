// MeshTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapToolMFC.h"
#include "MeshTab.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "Tool_Stone.h"
#include "Tool_Stone.h"


// CMeshTab 대화 상자입니다.

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


// CMeshTab 메시지 처리기입니다.


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
	//CString relativePath = wstrRelativePath;				// 상대경로
	//CString relativePath2 = relativePath;					
	//relativePath2.Insert(relativePath2.GetLength(), L"\\"); // 폴더명//까지만
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
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//CTexture* getTexture = dynamic_cast<CTexture*>(Clone_Proto(m_textureNameVector[m_textureListIndex]));
	//if (nullptr == getTexture)
	//	return;

	//CComponent*			pComponent = nullptr;

	//// 트랜스폼
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



	//// 텍스쳐
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMeshTab::OnLbnSelchangeListAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_addMeshListIndex = m_addMeshList.GetCurSel();
}


void CMeshTab::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	// 1.2 TreeView의 폴더를 마우스로 클릭하면, 하위폴더 목록을 TreeView에 보여준다.
	HTREEITEM hSelected = pNMTreeView->itemNew.hItem; // 현재 선택한 아이템


													  // (나중을 위해 먼저 실행)
													  // 1.2.2.1 선택된 아이템의 하위 목록을 트리컨트롤에 추가한다.
													  // 1.2.2.1.1 선택된 아이템의 경로를 읽어온다. 

	CString pathSelected; //최종으로 얻어올 경로 pathSelected를 선언한다.


	HTREEITEM hParentItem = hSelected; // 현재 선택된 아이템을 첫번째 시작으로 한다.
	while (hParentItem != NULL)
	{ // 최상의 부모가 없을 때 까지
		pathSelected = _T("\\") + pathSelected;
		pathSelected = m_tree.GetItemText(hParentItem) + pathSelected;
		hParentItem = m_tree.GetParentItem(hParentItem);
	}

	CString temp = L"..\\Bin\\";

	// 완성된 경로의 뒤에 "*.*"를 붙여주어서 최종으로 선택된 아이템의 경로를 완성한다.
	pathSelected = temp + pathSelected + _T("*.*");

	// 1.2.2.1.2 CFileFind를 이용하여 읽어온 경로의 파일 또는 폴더를 찾는다.
	CFileFind finder;
	BOOL bWorking = finder.FindFile(pathSelected);

	// 1.2.1 선택한 아이템이 선택적이 있는지 없는지 검사한다.
	// 1.2.2 선택된 적이 없는 경우, 
	//       => 해당 아이템의 GetItemData()는 0으로 초기화 되어있음.
	if (m_tree.GetItemData(hSelected) == 0)
	{
		// 1.2.2.1.3 선택한 아이템의 하위목록을 하나씩 검사하면서 폴더의 경우만 Tree 아이템으로 삽입한다. (. or ..는 예외)
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

		// 1.2.2.2 해당 아이템은 선택된 적이 있음을 SetItemData() 함수로 표시한다.
		m_tree.SetItemData(hSelected, 1);

		// 1.2.3 선택된 적이 있는 경우, 아무 작업도 하지 않는다. (이미 하위 목록은 트리에 추가되어 있으므로)
		// 1.2.4 여태까지 삽입한 트리아이템을 TreeView에 보여지게 한다.
		m_tree.EnsureVisible(hSelected);
	}

	//  추가 된 코드------------------------------------------------------------------------
	//  2.1 TreeView의 폴더를 마우스로 클릭하면, ListCtrl에 담겨있던 아이템을 비운다.
	if (pNMTreeView->itemNew.hItem != pNMTreeView->itemOld.hItem)
	{
		//m_textureListBox.ResetContent();// DeleteAllItems();
	}
	//  2.2 트리뷰에서 선택한 아이템의 하위폴더와 파일을 ListView에 보여준다.
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

	//  1.1.1 CFileFind를 이용하여 "C:\\*.*"의 파일 또는 폴더를 찾는다.
	CFileFind finder;

	CString path = _T("D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource3\\*.*");
	CString wstrRelativePath = L"";
	wstrRelativePath = CFileInfo::ConvertRelativePath(path);
	CString relativePath = wstrRelativePath;

	BOOL bWorking = finder.FindFile(/*_T(*//*"D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource2\\*.*"*/wstrRelativePath/*)*/);
	//  1.1.2 C드라이브의 모든 파일을 하나씩 검사하면서 폴더만 Tree의 아이템으로 삽입한다.
	while (bWorking)
	{
		//   1.1.2.1 "C:\\*.*"의 NextFile(C드라이브의 첫번째)부터 아래 검사를 시작한다.
		bWorking = finder.FindNextFile();

		if (finder.IsDots())
			continue;
		//   1.1.2.2 현재 검사하고 있는 것이 Directory일 경우만 Tree의 아이템으로 삽입한다.
		if (finder.IsDirectory())
		{
			m_tree.InsertItem(finder.GetFileName(), hItem);
		}
	}
	//  1.1.3 삽입한 모든 트리아이템을 보이도록 한다.
	m_tree.EnsureVisible(hItem);
}
