// MeshTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapToolMFC.h"
#include "MeshTab.h"
#include "afxdialogex.h"
#include "MapToolMFCView.h"
#include "MainFrm.h"
#include "FileInfo.h"
#include "Tool_Object.h"


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
	, m_sizeX(0)
	, m_sizeY(0)
	, m_sizeZ(0)
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
	DDX_Text(pDX, IDC_EDIT7, m_sizeX);
	DDX_Text(pDX, IDC_EDIT8, m_sizeY);
	DDX_Text(pDX, IDC_EDIT9, m_sizeZ);
}


BEGIN_MESSAGE_MAP(CMeshTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CMeshTab::OnBnClickedButtonAdd)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMeshTab::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMeshTab::OnBnClickedButtonApply)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMeshTab::OnLbnSelchangeListAdd)
	//ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMeshTab::OnTvnSelchangedTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMeshTab::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_BUTTON5, &CMeshTab::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON6, &CMeshTab::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CMeshTab 메시지 처리기입니다.


BOOL CMeshTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitTreeCtrl();

	CMainFrame* main = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	m_mfcView = dynamic_cast<CMapToolMFCView*>(main->m_MainSplitter.GetPane(0, 1));
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
	CString strPosX, strPosY, strPosZ;

	GetDlgItemText(IDC_EDIT1, strPosX);
	m_posX = _tstof(strPosX);

	GetDlgItemText(IDC_EDIT2, strPosY);
	m_posY = _tstof(strPosY);

	GetDlgItemText(IDC_EDIT3, strPosZ);
	m_posZ = _tstof(strPosZ);

	CString strRotX, strRotY, strRotZ;

	GetDlgItemText(IDC_EDIT4, strRotX);
	m_rotX = _tstof(strRotX);

	GetDlgItemText(IDC_EDIT5, strRotY);
	m_rotY = _tstof(strRotY);

	GetDlgItemText(IDC_EDIT6, strRotZ);
	m_rotZ = _tstof(strRotZ);



	CString strSizeX, strSizeY, strSizeZ;

	GetDlgItemText(IDC_EDIT7, strSizeX);
	m_sizeX = _tstof(strSizeX);

	GetDlgItemText(IDC_EDIT8, strSizeY);
	m_sizeY = _tstof(strSizeY);

	GetDlgItemText(IDC_EDIT9, strSizeZ);
	m_sizeZ = _tstof(strSizeZ);

	Object_Data objectData;
	objectData.m_pos[INFO_POS].x = m_posX;
	objectData.m_pos[INFO_POS].y = m_posY;
	objectData.m_pos[INFO_POS].z = m_posZ;
	objectData.m_vAngle.x = m_rotX;
	objectData.m_vAngle.y = m_rotY;
	objectData.m_vAngle.z = m_rotZ;
	objectData.m_vScale.x = m_sizeX;
	objectData.m_vScale.y = m_sizeY;
	objectData.m_vScale.z = m_sizeZ;


	CLayer*		pLayer = CLayer::Create();
	CObjects*			pObjects = CObjects::Create(m_pGraphicDev);
	CComponent*			pComponent = nullptr;

	g_index++;

	CString m_name = L"Proto_Mesh_";
	m_name = m_name + m_meshNameVector[m_meshListIndex];

	_tcscpy_s(objectData.m_objectTextureName, _countof(objectData.m_objectTextureName), m_name);
	
	// StaticMesh
	pComponent = pObjects->m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(m_name));
	pObjects->Add_AddComponent(L"Com_Mesh", ID_DYNAMIC, pComponent);

	pComponent = pObjects->m_pColliderCom = CCollider::Create(m_pGraphicDev, pObjects->m_pMeshCom->Get_VtxPos(), pObjects->m_pMeshCom->Get_NumVtx(), pObjects->m_pMeshCom->Get_VtxSize());
	pObjects->Add_AddComponent(L"Com_Collider", ID_DYNAMIC,pComponent);


	pObjects->Set_Index(g_index);
	objectData.m_objectIndex = g_index;
	pObjects->Set_ObjectData(objectData);
	

	pLayer->Add_GameObject(m_meshNameVector[m_meshListIndex], pObjects);
	CManagement::GetInstance()->Get_Scene()->Add_LayerGameObject(L"GameLogic", pLayer, L"StaticMesh", pObjects);

	m_addMeshList.AddString(m_meshNameVector[m_meshListIndex]);

	m_meshIndexVector.push_back(g_index);
	m_addMeshVector.push_back(pObjects);


	m_mfcView->Render_View();
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
	Object_Data tempObjectData;

	if (m_addMeshVector.size() == 0 /*|| m_addListIndex==NULL*/)
		return;

	CString strPosX, strPosY, strPosZ;

	GetDlgItemText(IDC_EDIT1, strPosX);
	m_posX = _tstof(strPosX);

	GetDlgItemText(IDC_EDIT2, strPosY);
	m_posY = _tstof(strPosY);

	GetDlgItemText(IDC_EDIT3, strPosZ);
	m_posZ = _tstof(strPosZ);

	CString strRotX, strRotY, strRotZ;

	GetDlgItemText(IDC_EDIT4, strRotX);
	m_rotX = _tstof(strRotX);

	GetDlgItemText(IDC_EDIT5, strRotY);
	m_rotY = _tstof(strRotY);

	GetDlgItemText(IDC_EDIT6, strRotZ);
	m_rotZ = _tstof(strRotZ);



	CString strSizeX, strSizeY, strSizeZ;

	GetDlgItemText(IDC_EDIT7, strSizeX);
	m_sizeX = _tstof(strSizeX);

	GetDlgItemText(IDC_EDIT8, strSizeY);
	m_sizeY = _tstof(strSizeY);

	GetDlgItemText(IDC_EDIT9, strSizeZ);
	m_sizeZ = _tstof(strSizeZ);

	//  m_pMeshCom
	//	m_pTransformCom
	//	m_pRendererCom

	CGameObject* getObject = CManagement::GetInstance()->Get_Scene()->Get_MapLayer(L"GameLogic", m_meshNameVector[m_meshListIndex],m_meshIndexVector[m_addMeshListIndex]);
	dynamic_cast<CObjects*>(getObject)->m_pTransformCom->Set_Pos(m_posX, m_posY, m_posZ);

	dynamic_cast<CObjects*>(getObject)->m_pTransformCom->Set_Rotation(m_rotX, m_rotY, m_rotZ);

	dynamic_cast<CObjects*>(getObject)->m_pTransformCom->Set_Scale(m_sizeX, m_sizeY, m_sizeZ);

	Object_Data getObjectData = dynamic_cast<CObjects*>(getObject)->Get_ObjectData();

	tempObjectData.m_pos[INFO_POS].x = m_posX;
	tempObjectData.m_pos[INFO_POS].y = m_posY;
	tempObjectData.m_pos[INFO_POS].z = m_posZ;
	tempObjectData.m_vAngle.x = m_rotX;
	tempObjectData.m_vAngle.y = m_rotY;
	tempObjectData.m_vAngle.z = m_rotZ;
	tempObjectData.m_vScale.x = m_sizeX;
	tempObjectData.m_vScale.y = m_sizeY;
	tempObjectData.m_vScale.z = m_sizeZ;
	tempObjectData.m_objectIndex = getObjectData.m_objectIndex;
	_tcscpy_s(tempObjectData.m_objectTextureName, _countof(tempObjectData.m_objectTextureName), getObjectData.m_objectTextureName);

	dynamic_cast<CObjects*>(getObject)->Set_ObjectData(tempObjectData);

	m_mfcView->Render_View();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMeshTab::OnLbnSelchangeListAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_addMeshListIndex = m_addMeshList.GetCurSel();
	//m_addMeshList.str
	CGameObject* getObject = CManagement::GetInstance()->Get_Scene()->Get_MapLayer(L"GameLogic", L"StaticMesh", m_meshIndexVector[m_addMeshListIndex]);

	_vec3 pos, rot, size;
	dynamic_cast<CObjects*>(getObject)->m_pTransformCom->Get_Info(INFO_POS, &pos);
	m_posX = pos.x;
	m_posY = pos.y;
	m_posZ = pos.z;
	dynamic_cast<CObjects*>(getObject)->m_pTransformCom->Get_Rotation(&rot);
	m_rotX = rot.x;
	m_rotY = rot.y;
	m_rotZ = rot.z;
	dynamic_cast<CObjects*>(getObject)->m_pTransformCom->Get_Scale(&size);
	m_sizeX = size.x;
	m_sizeY = size.y;
	m_sizeZ = size.z;

	UpdateData(FALSE);
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
	CString pathSelectedX;

	HTREEITEM hParentItem = hSelected; // 현재 선택된 아이템을 첫번째 시작으로 한다.
	while (hParentItem != NULL)
	{ // 최상의 부모가 없을 때 까지
		pathSelected = _T("\\") + pathSelected;
		pathSelected = m_tree.GetItemText(hParentItem) + pathSelected;
		hParentItem = m_tree.GetParentItem(hParentItem);
	}

	CString temp = L"..\\Bin\\";

	// 완성된 경로의 뒤에 "*.*"를 붙여주어서 최종으로 선택된 아이템의 경로를 완성한다.
	pathSelectedX = temp + pathSelected + _T("*.X");
	pathSelected = temp + pathSelected + _T("*.*");

	// 1.2.2.1.2 CFileFind를 이용하여 읽어온 경로의 파일 또는 폴더를 찾는다.
	CFileFind finder;
	CFileFind finderX;
	BOOL bWorking = finder.FindFile(pathSelected);
	BOOL bWorkingX = finderX.FindFile(pathSelectedX);


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
		m_meshList.ResetContent();// DeleteAllItems();
	}
	//  2.2 트리뷰에서 선택한 아이템의 하위폴더와 파일을 ListView에 보여준다.
	bWorking = finder.FindFile(pathSelected);
	while (bWorking)
	{
		while (bWorkingX)
		{
			bWorkingX = finderX.FindNextFile();
			if (finderX.IsDots())
				continue;

			CString ttemp2 = finderX.GetFileName();

			m_meshList.AddString(finderX.GetFileName());// InsertItem(1, finder.GetFileName());
			m_meshNameVector.push_back(finderX.GetFileName());
		}
		bWorking = finder.FindNextFile();

		if (finder.IsDots()) 
			continue;

		CString ttemp = finder.GetFileName();

		//m_meshList.AddString(finder.GetFileName());// InsertItem(1, finder.GetFileName());

	}
	//  -----------------------------------------------------------------------------------
	*pResult = 0;
}


void CMeshTab::InitTreeCtrl()
{
	HTREEITEM hItem = m_tree.InsertItem(_T("Resource3", hItem));

	//  1.1.1 CFileFind를 이용하여 "C:\\*.*"의 파일 또는 폴더를 찾는다.
	//CFileFind finder;

	//CString path = _T("D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource3\\*.*");
	//CString wstrRelativePath = L"";
	//wstrRelativePath = CFileInfo::ConvertRelativePath(path);
	//CString relativePath = wstrRelativePath;

	//BOOL bWorking = finder.FindFile(/*_T(*//*"D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource2\\*.*"*/relativePath/*)*/);
	//  1.1.2 C드라이브의 모든 파일을 하나씩 검사하면서 폴더만 Tree의 아이템으로 삽입한다.
	//while (bWorking)
	//{
	//	//   1.1.2.1 "C:\\*.*"의 NextFile(C드라이브의 첫번째)부터 아래 검사를 시작한다.
	//	bWorking = finder.FindNextFile();

	//	if (finder.IsDots())
	//		continue;
	//	//   1.1.2.2 현재 검사하고 있는 것이 Directory일 경우만 Tree의 아이템으로 삽입한다.
	//	if (finder.IsDirectory())
	//	{
	//		m_tree.InsertItem(finder.GetFileName(), hItem);
	//	}
	//}
	////  1.1.3 삽입한 모든 트리아이템을 보이도록 한다.
	m_tree.EnsureVisible(hItem);
}


void CMeshTab::OnBnClickedButtonSave()
{
	m_mfcView->m_isUpdate = false;

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
		{
			m_mfcView->m_isUpdate = true;
			m_mfcView->OnDraw();
			return;
		}

		DWORD dwByte = 0;
		DWORD dwStringSize = 0;
		for (auto& pObjects : m_addMeshVector)
		{
			Object_Data temp = pObjects->Get_ObjectData();
			dwStringSize = (_tcslen(temp.m_objectTextureName) + 1) * sizeof(wchar_t);
			WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, temp.m_objectTextureName, dwStringSize, &dwByte, nullptr);
			WriteFile(hFile, &temp.m_objectIndex, sizeof(int), &dwByte, nullptr);

			WriteFile(hFile, &temp.m_pos[INFO_POS].x, sizeof(float), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_pos[INFO_POS].y, sizeof(float), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_pos[INFO_POS].z, sizeof(float), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_vAngle.x, sizeof(float), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_vAngle.y, sizeof(float), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_vAngle.z, sizeof(float), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_vScale.x, sizeof(float), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_vScale.y, sizeof(float), &dwByte, nullptr);
			WriteFile(hFile, &temp.m_vScale.z, sizeof(float), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}

	m_mfcView->m_isUpdate = true;
	m_mfcView->OnDraw();
}


void CMeshTab::OnBnClickedButtonLoad()
{
	m_mfcView->m_isUpdate = false;

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

	m_addMeshVector.clear();

	if (IDOK == dlg.DoModal())
	{
		CString filePath = dlg.GetPathName();
		HANDLE hFile = CreateFile(filePath.GetString(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			m_mfcView->m_isUpdate = true;
			m_mfcView->OnDraw();
			return;
		}
		DWORD dwByte = 0;
		DWORD dwStringCount = 0;
		m_meshIndexVector.clear();
		_tchar* szBuf = nullptr;
		while (true)
		{
			Object_Data tempObjectData;
			ReadFile(hFile, &dwStringCount, sizeof(DWORD), &dwByte, nullptr);
			if (0 == dwByte)
				break;
			szBuf = new _tchar[dwStringCount];
			ReadFile(hFile, szBuf, dwStringCount, &dwByte, nullptr);

			_tcscpy_s(tempObjectData.m_objectTextureName, _countof(tempObjectData.m_objectTextureName), szBuf);
			Safe_Delete_Array(szBuf);

			ReadFile(hFile, &tempObjectData.m_objectIndex, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &tempObjectData.m_pos[INFO_POS].x, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &tempObjectData.m_pos[INFO_POS].y, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &tempObjectData.m_pos[INFO_POS].z, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &tempObjectData.m_vAngle.x, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &tempObjectData.m_vAngle.y, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &tempObjectData.m_vAngle.z, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &tempObjectData.m_vScale.x, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &tempObjectData.m_vScale.y, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &tempObjectData.m_vScale.z, sizeof(float), &dwByte, nullptr);

			g_index++;
			CComponent*			pComponent = nullptr;
			CObjects* newObjects = CObjects::Create(m_pGraphicDev);
			newObjects->m_pTransformCom->Set_Pos(tempObjectData.m_pos[INFO_POS].x, tempObjectData.m_pos[INFO_POS].y, tempObjectData.m_pos[INFO_POS].z);
			newObjects->m_pTransformCom->Set_Rotation(tempObjectData.m_vAngle.x, tempObjectData.m_vAngle.y, tempObjectData.m_vAngle.z);
			newObjects->m_pTransformCom->Set_Scale(tempObjectData.m_vScale.x, tempObjectData.m_vScale.y, tempObjectData.m_vScale.z);
			newObjects->Set_Index(tempObjectData.m_objectIndex);

			m_meshIndexVector.push_back(tempObjectData.m_objectIndex);
			newObjects->Set_ObjectData(tempObjectData);

			// 메쉬
			pComponent = newObjects->m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(tempObjectData.m_objectTextureName));
			newObjects->Add_AddComponent(L"Com_Mesh", ID_DYNAMIC, pComponent);

			pComponent = newObjects->m_pColliderCom = CCollider::Create(m_pGraphicDev, newObjects->m_pMeshCom->Get_VtxPos(), newObjects->m_pMeshCom->Get_NumVtx(), newObjects->m_pMeshCom->Get_VtxSize());
			newObjects->Add_AddComponent(L"Com_Collider", ID_DYNAMIC, pComponent);


			m_addMeshList.AddString(tempObjectData.m_objectTextureName);
			m_addMeshVector.push_back(newObjects);

			CLayer*		pLayer = CLayer::Create();
			//pLayer->Add_GameObject(L"Terrain",newTerrain);
			CManagement::GetInstance()->Get_Scene()->Add_LayerGameObject(L"GameLogic", pLayer, L"StaticMesh", newObjects);
		}
		m_mfcView->Render_View();
	}

	m_mfcView->m_isUpdate = true;
	m_mfcView->OnDraw();
}
