#include "stdafx.h"
#include "Load_Manager.h"
#include "Static_Object.h"
#include "Terrain.h"
#include "IceBackGround.h"
#include "Export_Function.h"
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

	int i = 0;
	while (true)
	{
		i++;
		DWORD dwByte = 0;
		DWORD dwStringCount = 0;
		_tchar* szBuf = nullptr;

		Terrain_Data newTerrain_Data{};
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

		g_index++;

		if (i == 1)
		{
			FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Buffer_TerrainTex", CTerrainTex::Create(m_pGraphicDev, newTerrain_Data.m_cntX, newTerrain_Data.m_cntZ, VTXITV)), E_FAIL);
		}
		else if (i == 2)
		{
			FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Buffer_IceTerrainTex", CTerrainTex::Create(m_pGraphicDev, newTerrain_Data.m_cntX, newTerrain_Data.m_cntZ, VTXITV)), E_FAIL);
			newTerrain_Data.m_pos[INFO_POS].y += 0.2;
		}
		CTerrain* newTerrain = CTerrain::Create(m_pGraphicDev);
		newTerrain->Get_Transform_Component()->Set_Pos(newTerrain_Data.m_pos[INFO_POS].x, newTerrain_Data.m_pos[INFO_POS].y, newTerrain_Data.m_pos[INFO_POS].z);
		newTerrain->Get_Transform_Component()->Set_Rotation(newTerrain_Data.m_vAngle.x, newTerrain_Data.m_vAngle.y, newTerrain_Data.m_vAngle.z);
		newTerrain->Set_Index(newTerrain_Data.m_terrainIndex);
		newTerrain->Set_TextureComponent(newTerrain_Data.m_terrainTextureName);

		pLayer->Add_GameObject(L"Terrain", newTerrain);

	}
	CloseHandle(hFile);
	return S_OK;
}

HRESULT CLoad_Manager::Load_Static_Object_Data(const wstring & filePath, CLayer*		pLayer, LPDIRECT3DDEVICE9 m_pGraphicDev)
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

		Object_Data newObject_Data;
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
		CStatic_Objects* newObjects = CStatic_Objects::Create(m_pGraphicDev);
		newObjects->Get_Transform_Component()->Set_Pos(newObject_Data.m_pos[INFO_POS].x, newObject_Data.m_pos[INFO_POS].y, newObject_Data.m_pos[INFO_POS].z);
		newObjects->Get_Transform_Component()->Set_Rotation(newObject_Data.m_vAngle.x, newObject_Data.m_vAngle.y, newObject_Data.m_vAngle.z);
		newObjects->Get_Transform_Component()->Set_Scale(newObject_Data.m_vScale.x, newObject_Data.m_vScale.y, newObject_Data.m_vScale.z);
		newObjects->Set_Index(newObject_Data.m_objectIndex);

		newObjects->Set_Static_Objects_Data(newObject_Data);
		newObjects->Set_StaticMesh_Component(newObject_Data.m_objectTextureName);

		pLayer->Add_GameObject(L"Static_Object", newObjects);

	}
	CloseHandle(hFile);
	return S_OK;

}