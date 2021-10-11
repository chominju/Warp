#include "stdafx.h"
#include "Load_Manager.h"
#include "Static_Object.h"
#include "Terrain.h"
#include "Export_Function.h"
//#include "afxdialogex.h"
#include <fstream>
#include <string.h>

CLoad_Manager::CLoad_Manager()
{
}

CLoad_Manager::~CLoad_Manager()
{
}

HRESULT CLoad_Manager::Load_Terrain_Data(const wstring & filePath , CLayer*		pLayer, LPDIRECT3DDEVICE9 m_pGraphicDev)
{
	HANDLE hFile = CreateFile(filePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	g_index = -1;

	while (true)
	{
		DWORD dwByte = 0;
		DWORD dwStringCount = 0;
		_tchar* szBuf = nullptr;

		Terrain_Data newTerrain_Data;
		//Terrain_Data tile;
		//tile = new Tile_Info;
		ReadFile(hFile, &dwStringCount, sizeof(DWORD), &dwByte, nullptr);
		if (0 == dwByte)
			break;

		szBuf = new _tchar[dwStringCount];
		ReadFile(hFile, szBuf, dwStringCount, &dwByte, nullptr);
		
		_tcscpy_s(newTerrain_Data.m_terrainTextureName, _countof(newTerrain_Data.m_terrainTextureName), szBuf);
		Safe_Delete_Array(szBuf);

		ReadFile(hFile, &newTerrain_Data.m_terrainIndex, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &newTerrain_Data.m_cntX, sizeof(_ulong), &dwByte, nullptr);
		ReadFile(hFile, &newTerrain_Data.m_cntZ, sizeof(_ulong), &dwByte, nullptr);
		ReadFile(hFile, &newTerrain_Data.m_pos[INFO_POS].x, sizeof(float), &dwByte, nullptr);
		ReadFile(hFile, &newTerrain_Data.m_pos[INFO_POS].y, sizeof(float), &dwByte, nullptr);
		ReadFile(hFile, &newTerrain_Data.m_pos[INFO_POS].z, sizeof(float), &dwByte, nullptr);
		ReadFile(hFile, &newTerrain_Data.m_vAngle.x, sizeof(float), &dwByte, nullptr);
		ReadFile(hFile, &newTerrain_Data.m_vAngle.y, sizeof(float), &dwByte, nullptr);
		ReadFile(hFile, &newTerrain_Data.m_vAngle.z, sizeof(float), &dwByte, nullptr);

		CTexture* getTexture = dynamic_cast<CTexture*>(Clone_Proto(newTerrain_Data.m_terrainTextureName));
		if (nullptr == getTexture)
			return E_FAIL;

		g_index++;
		//CComponent*			pComponent = nullptr;
		CTerrain* newTerrain = CTerrain::Create(m_pGraphicDev);
		newTerrain->Get_Transform_Component()->Set_Pos(newTerrain_Data.m_pos[INFO_POS].x, newTerrain_Data.m_pos[INFO_POS].y, newTerrain_Data.m_pos[INFO_POS].z);
		newTerrain->Get_Transform_Component()->Set_Rotation(newTerrain_Data.m_vAngle.x, newTerrain_Data.m_vAngle.y, newTerrain_Data.m_vAngle.z);
		newTerrain->Get_TerrainTex_Component()->Reset_Buffer(newTerrain_Data.m_cntX, newTerrain_Data.m_cntZ);
		newTerrain->Set_Index(newTerrain_Data.m_terrainIndex);
		newTerrain->Set_TextureComponent(newTerrain_Data.m_terrainTextureName);

		pLayer->Add_GameObject(L"Terrain", newTerrain);

		//CLayer*		pLayer = CLayer::Create();
		////pLayer->Add_GameObject(L"Terrain",newTerrain);
		//CManagement::GetInstance()->Get_Scene()->Add_LayerGameObject(L"GameLogic", pLayer, L"Terrain", newTerrain);

	/*	newStatic_Object->m_pTransformCom->Set_Pos(newTerrain_Data.m_pos[INFO_POS].x, newTerrain_Data.m_pos[INFO_POS].y, newTerrain_Data.m_pos[INFO_POS].z);
		newStatic_Object->m_pTransformCom->Set_Rotation(newTerrain_Data.m_vAngle.x, newTerrain_Data.m_vAngle.y, newTerrain_Data.m_vAngle.z);
		newStatic_Object->m_pBufferCom->Reset_Buffer(newTerrain_Data.m_cntX, newTerrain_Data.m_cntZ);
		newStatic_Object->Set_Index(newTerrain_Data.m_terrainIndex);*/

		//m_addTextrueIndexVector.push_back(newTerrain_Data.m_terrainIndex);

		//// 텍스쳐
		//pComponent = newStatic_Object->m_pTextureCom = getTexture;
		//newStatic_Object->Add_AddComponent(L"Com_Texture", ID_STATIC, pComponent);

		/*newObject = new

		CGameObject* object;
		switch (terrain.objectKey)
		{
		case SCENE_OBJECT_ID::TILE:
		object = new CTile;
		object->Set_RenderID(RENDER_ID::RENDER_TILE);
		dynamic_cast<CTerrain*>(object)->Set_Terrain_Info(tile);
		dynamic_cast<CTerrain*>(object)->Set_Info_Pos();
		if (dynamic_cast<CTerrain*>(object)->Get_Terrain_Info().drawID == 1)
		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJECT_ID::RESPAWN_TILE, object);
		else
		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJECT_ID::SCENE_TILE, object);
		break;

		case SCENE_OBJECT_ID::BOX:
		object = new CBox;
		dynamic_cast<CTerrain*>(object)->Set_Terrain_Info(tile);
		dynamic_cast<CTerrain*>(object)->Set_Info_Pos();
		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJECT_ID::OBEJCT, object);
		break;

		case SCENE_OBJECT_ID::WALL:
		object = new CWall;
		dynamic_cast<CTerrain*>(object)->Set_Terrain_Info(tile);
		dynamic_cast<CTerrain*>(object)->Set_Info_Pos();
		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJECT_ID::OBEJCT, object);
		break;
		default:
		break;
		};*/
	}
	CloseHandle(hFile);
	return S_OK;
}

HRESULT CLoad_Manager::Load_Static_Object_Data(const wstring & filePath, CLayer*		pLayer, LPDIRECT3DDEVICE9 m_pGraphicDev)
{
	//CGameObject_Manager::Get_Instance()->Reset_Object(OBJECT_ID::SCENE_TILE);
	//CGameObject_Manager::Get_Instance()->Reset_Object(OBJECT_ID::OBEJCT);

	HANDLE hFile = CreateFile(filePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	g_index = -1;

	while (true)
	{
		DWORD dwByte = 0;
		DWORD dwStringCount = 0;
		_tchar* szBuf = nullptr;

		Object_Data newObject_Data;
		//Terrain_Data tile;
		//tile = new Tile_Info;
		ReadFile(hFile, &dwStringCount, sizeof(DWORD), &dwByte, nullptr);
		if (0 == dwByte)
			break;

		szBuf = new _tchar[dwStringCount];
		ReadFile(hFile, szBuf, dwStringCount, &dwByte, nullptr);

		_tcscpy_s(newObject_Data.m_objectTextureName, _countof(newObject_Data.m_objectTextureName), szBuf);
		Safe_Delete_Array(szBuf);

		ReadFile(hFile, &newObject_Data.m_objectIndex, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &newObject_Data.m_pos[INFO_POS].x, sizeof(float), &dwByte, nullptr);
		ReadFile(hFile, &newObject_Data.m_pos[INFO_POS].y, sizeof(float), &dwByte, nullptr);
		ReadFile(hFile, &newObject_Data.m_pos[INFO_POS].z, sizeof(float), &dwByte, nullptr);
		ReadFile(hFile, &newObject_Data.m_vAngle.x, sizeof(float), &dwByte, nullptr);
		ReadFile(hFile, &newObject_Data.m_vAngle.y, sizeof(float), &dwByte, nullptr);
		ReadFile(hFile, &newObject_Data.m_vAngle.z, sizeof(float), &dwByte, nullptr);
		ReadFile(hFile, &newObject_Data.m_vScale.x, sizeof(float), &dwByte, nullptr);
		ReadFile(hFile, &newObject_Data.m_vScale.y, sizeof(float), &dwByte, nullptr);
		ReadFile(hFile, &newObject_Data.m_vScale.z, sizeof(float), &dwByte, nullptr);

		g_index++;
		//	CComponent*			pComponent = nullptr;
		CStatic_Objects* newObjects = CStatic_Objects::Create(m_pGraphicDev);
		newObjects->Get_Transform_Component()->Set_Pos(newObject_Data.m_pos[INFO_POS].x, newObject_Data.m_pos[INFO_POS].y, newObject_Data.m_pos[INFO_POS].z);
		newObjects->Get_Transform_Component()->Set_Rotation(newObject_Data.m_vAngle.x, newObject_Data.m_vAngle.y, newObject_Data.m_vAngle.z);
		newObjects->Get_Transform_Component()->Set_Scale(newObject_Data.m_vScale.x, newObject_Data.m_vScale.y, newObject_Data.m_vScale.z);
		newObjects->Set_Index(newObject_Data.m_objectIndex);

		newObjects->Set_Static_Objects_Data(newObject_Data);
		newObjects->Set_StaticMesh_Component(newObject_Data.m_objectTextureName);

		pLayer->Add_GameObject(L"Static_Object", newObjects);

		//// 메쉬
		//pComponent = newObjects->Get_StaticMesh_Component() = dynamic_cast<CStaticMesh*>(Clone_Proto(newObject_Data.m_objectTextureName));
		//newObjects->Add_AddComponent(L"Com_Mesh", ID_DYNAMIC, pComponent);

		//pComponent = newObjects->m_pColliderCom = CCollider::Create(m_pGraphicDev, newObjects->m_pMeshCom->Get_VtxPos(), newObjects->m_pMeshCom->Get_NumVtx(), newObjects->m_pMeshCom->Get_VtxSize());
		//newObjects->Add_AddComponent(L"Com_Collider", ID_DYNAMIC, pComponent);


		/*	m_addMeshList.AddString(newObject_Data.m_objectTextureName);
		m_addMeshVector.push_back(newObjects);*/

		//CLayer*		pLayer = CLayer::Create();
		////pLayer->Add_GameObject(L"Terrain",newTerrain);
		//CManagement::GetInstance()->Get_Scene()->Add_LayerGameObject(L"GameLogic", pLayer, L"StaticMesh", newObjects);
	}
	CloseHandle(hFile);
	return S_OK;

}

//CLoad_Manager::LoadTextureData("../Data/ResoureList.txt");
//CLoad_Manager::LoadTerrainData(L"../Data/testMap2.dat");
//CLoad_Manager::LoadTerrainData(L"../Data/TerrainData.dat");
//CLoad_Manager::LoadItemData(L"../Data/ItemData.dat");

//// 	LoadTileData_Terrain(L"../Data/TerrainData.dat");
//HRESULT CLoad_Manager::Load_Terrain_Data(const _tchar*  filePath , const _tchar * pLayerTag/*,LPDIRECT3DDEVICE9* m_pGraphicDev*/)
//{
//	//CGameObject_Manager::Get_Instance()->Reset_Object(OBJECT_ID::SCENE_TILE);
//	//CGameObject_Manager::Get_Instance()->Reset_Object(OBJECT_ID::OBEJCT);
//
//	//HANDLE hFile = CreateFile(filePath/*.c_str()*/, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
//	//if (INVALID_HANDLE_VALUE == hFile)
//	//	return E_FAIL;
//
//	//g_index = -1;
//
//	//while (true)
//	//{
//	//	DWORD dwByte = 0;
//	//	DWORD dwStringCount = 0;
//	//	_tchar* szBuf = nullptr;
//
//	//	Terrain_Data newTerrain_Data;
//	//	//Terrain_Data tile;
//	//	//tile = new Tile_Info;
//	//	ReadFile(hFile, &dwStringCount, sizeof(DWORD), &dwByte, nullptr);
//	//	if (0 == dwByte)
//	//		break;
//
//	//	szBuf = new _tchar[dwStringCount];
//	//	ReadFile(hFile, szBuf, dwStringCount, &dwByte, nullptr);
//	//	
//	//	_tcscpy_s(newTerrain_Data.m_terrainTextureName, _countof(newTerrain_Data.m_terrainTextureName), szBuf);
//	//	Safe_Delete_Array(szBuf);
//
//	//	ReadFile(hFile, &newTerrain_Data.m_terrainIndex, sizeof(int), &dwByte, nullptr);
//	//	ReadFile(hFile, &newTerrain_Data.m_cntX, sizeof(_ulong), &dwByte, nullptr);
//	//	ReadFile(hFile, &newTerrain_Data.m_cntZ, sizeof(_ulong), &dwByte, nullptr);
//	//	ReadFile(hFile, &newTerrain_Data.m_pos[INFO_POS].x, sizeof(float), &dwByte, nullptr);
//	//	ReadFile(hFile, &newTerrain_Data.m_pos[INFO_POS].y, sizeof(float), &dwByte, nullptr);
//	//	ReadFile(hFile, &newTerrain_Data.m_pos[INFO_POS].z, sizeof(float), &dwByte, nullptr);
//	//	ReadFile(hFile, &newTerrain_Data.m_vAngle.x, sizeof(float), &dwByte, nullptr);
//	//	ReadFile(hFile, &newTerrain_Data.m_vAngle.y, sizeof(float), &dwByte, nullptr);
//	//	ReadFile(hFile, &newTerrain_Data.m_vAngle.z, sizeof(float), &dwByte, nullptr);
//
//	//	CTexture* getTexture = dynamic_cast<CTexture*>(Clone_Proto(newTerrain_Data.m_terrainTextureName));
//	//	if (nullptr == getTexture)
//	//		return;
//
//	//	g_index++;
//	//	//CComponent*			pComponent = nullptr;
//	//	CTerrain* newTerrain = CTerrain::Create(*m_pGraphicDev);
//	//	newTerrain->Get_Transform_Component()->Set_Pos(newTerrain_Data.m_pos[INFO_POS].x, newTerrain_Data.m_pos[INFO_POS].y, newTerrain_Data.m_pos[INFO_POS].z);
//	//	newTerrain->Get_Transform_Component()->Set_Rotation(newTerrain_Data.m_vAngle.x, newTerrain_Data.m_vAngle.y, newTerrain_Data.m_vAngle.z);
//	//	newTerrain->Get_TerrainTex_Component()->Reset_Buffer(newTerrain_Data.m_cntX, newTerrain_Data.m_cntZ);
//	//	newTerrain->Set_Index(newTerrain_Data.m_terrainIndex);
//	//	newTerrain->Set_TextureComponent(newTerrain_Data.m_terrainTextureName);
//
//	//	CLayer*		pLayer = CLayer::Create();
//	//	//pLayer->Add_GameObject(L"Terrain",newTerrain);
//	//	CManagement::GetInstance()->Get_Scene()->Add_LayerGameObject(pLayerTag, pLayer, L"Terrain", newTerrain);
//
//	///*	newStatic_Object->m_pTransformCom->Set_Pos(newTerrain_Data.m_pos[INFO_POS].x, newTerrain_Data.m_pos[INFO_POS].y, newTerrain_Data.m_pos[INFO_POS].z);
//	//	newStatic_Object->m_pTransformCom->Set_Rotation(newTerrain_Data.m_vAngle.x, newTerrain_Data.m_vAngle.y, newTerrain_Data.m_vAngle.z);
//	//	newStatic_Object->m_pBufferCom->Reset_Buffer(newTerrain_Data.m_cntX, newTerrain_Data.m_cntZ);
//	//	newStatic_Object->Set_Index(newTerrain_Data.m_terrainIndex);*/
//
//	//	//m_addTextrueIndexVector.push_back(newTerrain_Data.m_terrainIndex);
//
//	//	//// 텍스쳐
//	//	//pComponent = newStatic_Object->m_pTextureCom = getTexture;
//	//	//newStatic_Object->Add_AddComponent(L"Com_Texture", ID_STATIC, pComponent);
//
//	//	/*newObject = new
//
//	//	CGameObject* object;
//	//	switch (terrain.objectKey)
//	//	{
//	//	case SCENE_OBJECT_ID::TILE:
//	//	object = new CTile;
//	//	object->Set_RenderID(RENDER_ID::RENDER_TILE);
//	//	dynamic_cast<CTerrain*>(object)->Set_Terrain_Info(tile);
//	//	dynamic_cast<CTerrain*>(object)->Set_Info_Pos();
//	//	if (dynamic_cast<CTerrain*>(object)->Get_Terrain_Info().drawID == 1)
//	//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJECT_ID::RESPAWN_TILE, object);
//	//	else
//	//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJECT_ID::SCENE_TILE, object);
//	//	break;
//
//	//	case SCENE_OBJECT_ID::BOX:
//	//	object = new CBox;
//	//	dynamic_cast<CTerrain*>(object)->Set_Terrain_Info(tile);
//	//	dynamic_cast<CTerrain*>(object)->Set_Info_Pos();
//	//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJECT_ID::OBEJCT, object);
//	//	break;
//
//	//	case SCENE_OBJECT_ID::WALL:
//	//	object = new CWall;
//	//	dynamic_cast<CTerrain*>(object)->Set_Terrain_Info(tile);
//	//	dynamic_cast<CTerrain*>(object)->Set_Info_Pos();
//	//	CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJECT_ID::OBEJCT, object);
//	//	break;
//	//	default:
//	//	break;
//	//	};*/
//	//}
//	//CloseHandle(hFile);
//	return S_OK;
//}
//
//HRESULT CLoad_Manager::Load_Static_Object_Data(const _tchar*  filePath, const _tchar*  pLayerTag, LPDIRECT3DDEVICE9* m_pGraphicDev)
//{
//	//CGameObject_Manager::Get_Instance()->Reset_Object(OBJECT_ID::SCENE_TILE);
//	//CGameObject_Manager::Get_Instance()->Reset_Object(OBJECT_ID::OBEJCT);
//
//	HANDLE hFile = CreateFile(filePath/* .c_str()*/, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
//	if (INVALID_HANDLE_VALUE == hFile)
//		return E_FAIL;
//
//	g_index = -1;
//
//	while (true)
//	{
//		DWORD dwByte = 0;
//		DWORD dwStringCount = 0;
//		_tchar* szBuf = nullptr;
//
//		Object_Data newObject_Data;
//		//Terrain_Data tile;
//		//tile = new Tile_Info;
//		ReadFile(hFile, &dwStringCount, sizeof(DWORD), &dwByte, nullptr);
//		if (0 == dwByte)
//			break;
//
//		szBuf = new _tchar[dwStringCount];
//		ReadFile(hFile, szBuf, dwStringCount, &dwByte, nullptr);
//
//		_tcscpy_s(newObject_Data.m_objectTextureName, _countof(newObject_Data.m_objectTextureName), szBuf);
//		Safe_Delete_Array(szBuf);
//
//		ReadFile(hFile, &newObject_Data.m_objectIndex, sizeof(int), &dwByte, nullptr);
//		ReadFile(hFile, &newObject_Data.m_pos[INFO_POS].x, sizeof(float), &dwByte, nullptr);
//		ReadFile(hFile, &newObject_Data.m_pos[INFO_POS].y, sizeof(float), &dwByte, nullptr);
//		ReadFile(hFile, &newObject_Data.m_pos[INFO_POS].z, sizeof(float), &dwByte, nullptr);
//		ReadFile(hFile, &newObject_Data.m_vAngle.x, sizeof(float), &dwByte, nullptr);
//		ReadFile(hFile, &newObject_Data.m_vAngle.y, sizeof(float), &dwByte, nullptr);
//		ReadFile(hFile, &newObject_Data.m_vAngle.z, sizeof(float), &dwByte, nullptr);
//		ReadFile(hFile, &newObject_Data.m_vScale.x, sizeof(float), &dwByte, nullptr);
//		ReadFile(hFile, &newObject_Data.m_vScale.y, sizeof(float), &dwByte, nullptr);
//		ReadFile(hFile, &newObject_Data.m_vScale.z, sizeof(float), &dwByte, nullptr);
//
//		g_index++;
//	//	CComponent*			pComponent = nullptr;
//		CStatic_Objects* newObjects = CStatic_Objects::Create(*m_pGraphicDev);
//		newObjects->Get_Transform_Component()->Set_Pos(newObject_Data.m_pos[INFO_POS].x, newObject_Data.m_pos[INFO_POS].y, newObject_Data.m_pos[INFO_POS].z);
//		newObjects->Get_Transform_Component()->Set_Rotation(newObject_Data.m_vAngle.x, newObject_Data.m_vAngle.y, newObject_Data.m_vAngle.z);
//		newObjects->Get_Transform_Component()->Set_Scale(newObject_Data.m_vScale.x, newObject_Data.m_vScale.y, newObject_Data.m_vScale.z);
//		newObjects->Set_Index(newObject_Data.m_objectIndex);
//
//		newObjects->Set_Static_Objects_Data(newObject_Data);
//		newObjects->Set_StaticMesh_Component(newObject_Data.m_objectTextureName);
//
//		//// 메쉬
//		//pComponent = newObjects->Get_StaticMesh_Component() = dynamic_cast<CStaticMesh*>(Clone_Proto(newObject_Data.m_objectTextureName));
//		//newObjects->Add_AddComponent(L"Com_Mesh", ID_DYNAMIC, pComponent);
//
//		//pComponent = newObjects->m_pColliderCom = CCollider::Create(m_pGraphicDev, newObjects->m_pMeshCom->Get_VtxPos(), newObjects->m_pMeshCom->Get_NumVtx(), newObjects->m_pMeshCom->Get_VtxSize());
//		//newObjects->Add_AddComponent(L"Com_Collider", ID_DYNAMIC, pComponent);
//
//
//	/*	m_addMeshList.AddString(newObject_Data.m_objectTextureName);
//		m_addMeshVector.push_back(newObjects);*/
//
//		CLayer*		pLayer = CLayer::Create();
//		//pLayer->Add_GameObject(L"Terrain",newTerrain);
//		CManagement::GetInstance()->Get_Scene()->Add_LayerGameObject(pLayerTag, pLayer, L"StaticMesh", newObjects);
//	}
//	CloseHandle(hFile);
//	return S_OK;
//
//}

//HRESULT CLoad_Manager::LoadItemData(const wstring & filePath)
//{
//	HANDLE file = CreateFile(filePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
//	if (INVALID_HANDLE_VALUE == file)
//		return E_FAIL;
//
//	while (true)
//	{
//		DWORD byte = 0;
//
//		Item_Info item;
//		//tile = new Tile_Info;
//		ReadFile(file, &item, sizeof(Item_Info), &byte, nullptr);
//		if (0 == byte)
//			break;
//
//		CGameObject_Manager::Get_Instance()->Add_ItemData(item);
//	}
//	CloseHandle(file);
//	return S_OK;
//}
