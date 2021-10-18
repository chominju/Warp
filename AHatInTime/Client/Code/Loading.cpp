#include "stdafx.h"
#include "Loading.h"

#include "Export_Function.h"


CLoading::CLoading(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bFinish(false)
{
	m_pGraphicDev->AddRef();
	ZeroMemory(m_szLoading, sizeof(_tchar) * 256);
}

CLoading::~CLoading(void)
{

}

HRESULT CLoading::Ready_Loading(LOADINGID eID)
{
	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, Thread_Main, this, 0, NULL);

	m_eID = eID;

	return S_OK;
}

Engine::_uint CLoading::LoadingForStage(void)
{
	lstrcpy(m_szLoading, L"Texture Loading.................");
	// 버퍼
	//FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Buffer_TerrainTex", CTerrainTex::Create(m_pGraphicDev, VTXCNTX, VTXCNTZ, VTXITV)), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Buffer_CubeTex", CCubeTex::Create(m_pGraphicDev)), E_FAIL);
	
	// 텍스쳐
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Texture_Terrain", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Grass_%d.tga", TYPE_NORMAL, 2)), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Texture_Terrain2", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Terrain0.png", TYPE_NORMAL, 1)), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Texture_SkyBox", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/SkyBox/burger%d.dds", TYPE_CUBE, 4)), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Texture_Effect", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Explosion/Explosion%d.png", TYPE_NORMAL, 90)), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Texture_UI", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/hpbar.png", TYPE_NORMAL, 1)), E_FAIL);


	// 메쉬
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Tree", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource/Mesh/StaticMesh/Tree/", L"Tree01.X")), E_FAIL);
	//FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Stone",CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource/Mesh/StaticMesh/TombStone/", L"TombStone.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Navi", CNaviMesh::Create(m_pGraphicDev)), E_FAIL);

#pragma region PLAYER
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Sword", CStaticMesh::Create(m_pGraphicDev, L"../Bin/Resource/Mesh/StaticMesh/Sword/", L"Sword.X")), E_FAIL);
	//FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Player", CDynamicMesh::Create(m_pGraphicDev, L"../Bin/Resource/Mesh/DynamicMesh/PlayerXfile/", L"Player.X")), E_FAIL);
#pragma endregion PLAYER
		
	// 기타 등등
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Calculator", CCalculator::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Optimization", COptimization::Create(m_pGraphicDev, true, VTXCNTX, VTXCNTZ)), E_FAIL);


	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Stone", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"WallClear6.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_StaticMesh_Player", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/Mesh/DynamicMesh/Player/", L"Player.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Player", CDynamicMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/Mesh/DynamicMesh/Player/", L"Player.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Rectangle_White.jpg", CTexture::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/Texture/Terrain/Rectangle_White.jpg", TYPE_NORMAL, 1)), E_FAIL);
	//FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Transform", CTransform::Create(m_pGraphicDev)) , E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Bed.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Bed.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Box1.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Box1.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Box2.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Box2.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Box3.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Box3.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Box4.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Box4.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Box5.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Box5.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Box6.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Box6.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Clothrack.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Clothrack.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Conveyor1.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Conveyor1.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Conveyor2.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Conveyor2.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Desk1.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Desk1.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_DeskDeco1.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"DeskDeco1.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_DeskDeco2.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"DeskDeco2.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Door3.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Door3.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Door4.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Door4.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_DoorClearFin.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"DoorClearFin.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_DoorClearLeft.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"DoorClearLeft.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_DoorClearRight.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"DoorClearRight.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Drawer1.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Drawer1.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Drawer2.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Drawer2.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_GarbageBag.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"GarbageBag.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Handrail_Corner1.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Handrail_Corner1.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Handrail_Corner2.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Handrail_Corner2.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_HeavyMetal_Barrel.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"HeavyMetal_Barrel.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Maze_Wall1.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Maze_Wall1.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Maze_Wall3.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Maze_Wall3.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Maze_Wall4.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Maze_Wall4.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Maze_Wall5.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Maze_Wall5.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Pillar1.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Pillar1.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Pillar2.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Pillar2.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Pillar3.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Pillar3.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_SecurityCam1.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"SecurityCam1.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_SecurityCam2.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"SecurityCam2.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Skeleton_Ball.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Skeleton_Ball.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Table1.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Table1.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Table2.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Table2.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Table11.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Table11.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Wall1.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Wall1.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Wall2.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Wall2.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Wall4.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Wall4.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Wall6.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Wall6.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_Wall44.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"Wall44.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_WallClear_Corner1.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"WallClear_Corner1.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_WallClear_Corner2.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"WallClear_Corner2.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_WallClear_Corner3.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"WallClear_Corner3.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_WallClear1.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"WallClear1.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_WallClear6.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"WallClear6.X")), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Mesh_WallClear15.x", CStaticMesh::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/", L"WallClear15.X")), E_FAIL);


	m_bFinish = true;

	lstrcpy(m_szLoading, L"Loading Complete!!!!!!!!!!!!!!!!!!!!!!");


	return 0;
}

Engine::_uint CLoading::LoadingForBoss(void)
{
	// 수업상 정의한 코드

	return 0;
}

unsigned int CALLBACK CLoading::Thread_Main(void* pArg)
{
	CLoading*		pLoading = (CLoading*)pArg;

	_uint	iFlag = 0;

	EnterCriticalSection(pLoading->Get_Crt());

	switch (pLoading->Get_LoadingID())
	{
	case LOADING_STAGE:
		iFlag = pLoading->LoadingForStage();
		break;

	case LOADING_BOSS:
		iFlag = pLoading->LoadingForBoss();
		break;
	}

	LeaveCriticalSection(pLoading->Get_Crt());

	// _endthreadex(0);		리턴값이 0인 경우엔 _endthreadex함수가 자동 호출되어 문제가 없지만 그렇지 않은 경우에는 예외처리로 이 함수를 호출할 수 있도록 설계해야 한다.
	
	return iFlag;
}

CLoading* CLoading::Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADINGID eID)
{
	CLoading*	pInstance = new CLoading(pGraphicDev);

	if (FAILED(pInstance->Ready_Loading(eID)))
		Safe_Release(pInstance);

	return pInstance;
}

void CLoading::Free(void)
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_Crt);

	Safe_Release(m_pGraphicDev);

}

