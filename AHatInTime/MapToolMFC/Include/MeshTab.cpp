// MeshTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapToolMFC.h"
#include "MeshTab.h"
#include "afxdialogex.h"
#include "MapToolMFCView.h"
#include "MainFrm.h"
#include "FileInfo.h"
#include "Tool_Object.h"


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


// CMeshTab �޽��� ó�����Դϴ�.


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


	//m_posX = GetDlgItemInt(IDC_EDIT1);
	//m_posY = GetDlgItemInt(IDC_EDIT2);

	//m_rotX = GetDlgItemInt(IDC_EDIT4);
	//m_rotY = GetDlgItemInt(IDC_EDIT5);
	//m_rotZ = GetDlgItemInt(IDC_EDIT6);


	CLayer*		pLayer = CLayer::Create();
	CObjects*			pObjects = CObjects::Create(m_pGraphicDev);
	CComponent*			pComponent = nullptr;

	g_index++;

	CString m_name = L"Proto_Mesh_";
	m_name = m_name + m_meshNameVector[m_meshListIndex];

	// StaticMesh
	pComponent = pObjects->m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(m_name));
	pObjects->Add_AddComponent(L"Com_Mesh", ID_DYNAMIC, pComponent);

	pObjects->Set_Index(g_index);
	pLayer->Add_GameObject(m_meshNameVector[m_meshListIndex], pObjects);
	CManagement::GetInstance()->Get_Scene()->Add_LayerGameObject(L"GameLogic", pLayer, L"StaticMesh", pObjects);

	m_addMeshList.AddString(m_meshNameVector[m_meshListIndex]);

	m_meshIndexVector.push_back(g_index);

	m_mfcView->Render_View();
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

	//m_posX = GetDlgItemInt(IDC_EDIT1);
	//m_posY = GetDlgItemInt(IDC_EDIT2);
	//m_posZ = GetDlgItemInt(IDC_EDIT3);

	//m_rotX = GetDlgItemInt(IDC_EDIT4);
	//m_rotY = GetDlgItemInt(IDC_EDIT5);
	//m_rotZ = GetDlgItemInt(IDC_EDIT6);

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

	m_mfcView->Render_View();
	//  m_pMeshCom
	//	m_pTransformCom
	//	m_pRendererCom

	CGameObject* getObject = CManagement::GetInstance()->Get_Scene()->Get_MapLayer(L"GameLogic", m_meshNameVector[m_meshListIndex],m_meshIndexVector[m_addMeshListIndex]);
	dynamic_cast<CObjects*>(getObject)->m_pTransformCom->Set_Pos(m_posX, m_posY, m_posZ);

	dynamic_cast<CObjects*>(getObject)->m_pTransformCom->Rotation(ROT_X, m_rotX);

	dynamic_cast<CObjects*>(getObject)->m_pTransformCom->Rotation(ROT_Y, m_rotY);

	dynamic_cast<CObjects*>(getObject)->m_pTransformCom->Rotation(ROT_Z, m_rotZ);

	dynamic_cast<CObjects*>(getObject)->m_pTransformCom->Set_Scale(m_sizeX, m_sizeY, m_sizeZ);
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

	// 1.2 TreeView�� ������ ���콺�� Ŭ���ϸ�, �������� ����� TreeView�� �����ش�.
	HTREEITEM hSelected = pNMTreeView->itemNew.hItem; // ���� ������ ������


													  // (������ ���� ���� ����)
													  // 1.2.2.1 ���õ� �������� ���� ����� Ʈ����Ʈ�ѿ� �߰��Ѵ�.
													  // 1.2.2.1.1 ���õ� �������� ��θ� �о�´�. 

	CString pathSelected; //�������� ���� ��� pathSelected�� �����Ѵ�.
	CString pathSelectedX;

	HTREEITEM hParentItem = hSelected; // ���� ���õ� �������� ù��° �������� �Ѵ�.
	while (hParentItem != NULL)
	{ // �ֻ��� �θ� ���� �� ����
		pathSelected = _T("\\") + pathSelected;
		pathSelected = m_tree.GetItemText(hParentItem) + pathSelected;
		hParentItem = m_tree.GetParentItem(hParentItem);
	}

	CString temp = L"..\\Bin\\";

	// �ϼ��� ����� �ڿ� "*.*"�� �ٿ��־ �������� ���õ� �������� ��θ� �ϼ��Ѵ�.
	pathSelectedX = temp + pathSelected + _T("*.X");
	pathSelected = temp + pathSelected + _T("*.*");

	// 1.2.2.1.2 CFileFind�� �̿��Ͽ� �о�� ����� ���� �Ǵ� ������ ã�´�.
	CFileFind finder;
	CFileFind finderX;
	BOOL bWorking = finder.FindFile(pathSelected);
	BOOL bWorkingX = finderX.FindFile(pathSelectedX);


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
		m_meshList.ResetContent();// DeleteAllItems();
	}
	//  2.2 Ʈ���信�� ������ �������� ���������� ������ ListView�� �����ش�.
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

	//  1.1.1 CFileFind�� �̿��Ͽ� "C:\\*.*"�� ���� �Ǵ� ������ ã�´�.
	//CFileFind finder;

	//CString path = _T("D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource3\\*.*");
	//CString wstrRelativePath = L"";
	//wstrRelativePath = CFileInfo::ConvertRelativePath(path);
	//CString relativePath = wstrRelativePath;

	//BOOL bWorking = finder.FindFile(/*_T(*//*"D:\\Jusin\\AHatInTime\\AHatInTime\\MapToolMFC\\Bin\\Resource2\\*.*"*/relativePath/*)*/);
	//  1.1.2 C����̺��� ��� ������ �ϳ��� �˻��ϸ鼭 ������ Tree�� ���������� �����Ѵ�.
	//while (bWorking)
	//{
	//	//   1.1.2.1 "C:\\*.*"�� NextFile(C����̺��� ù��°)���� �Ʒ� �˻縦 �����Ѵ�.
	//	bWorking = finder.FindNextFile();

	//	if (finder.IsDots())
	//		continue;
	//	//   1.1.2.2 ���� �˻��ϰ� �ִ� ���� Directory�� ��츸 Tree�� ���������� �����Ѵ�.
	//	if (finder.IsDirectory())
	//	{
	//		m_tree.InsertItem(finder.GetFileName(), hItem);
	//	}
	//}
	////  1.1.3 ������ ��� Ʈ���������� ���̵��� �Ѵ�.
	m_tree.EnsureVisible(hItem);
}


void CMeshTab::OnBnClickedButtonSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMeshTab::OnBnClickedButtonLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
