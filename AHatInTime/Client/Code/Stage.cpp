#include "stdafx.h"
#include "Stage.h"
#include "Load_Manager.h"
#include "LeftDoor.h"
#include "RightDoor.h"
#include "Ball.h"
#include "FloorSwitch.h"
#include "Conveyor.h"
#include "Maze.h"
#include "HeavyMetal_Barrel.h"
#include "EmptyObject.h"
#include "GarbageBag.h"
#include "Jelly.h"
#include "Computer.h"
#include "IceBackGround.h"
#include "OrderTile.h"
#include "Effect.h"
#include "OrderTile_Manager.h"
#include "EndSpace.h"
#include "BackGround.h"
#include "Player.h"
#include "Terrain.h"
#include "DynamicCamera.h"
#include "SkyBox.h"

#include "Export_Function.h"

CStage::CStage(LPDIRECT3DDEVICE9 pGraphicDev)
	: CScene(pGraphicDev)
{

}

CStage::~CStage(void)
{

}

HRESULT CStage::Ready_Scene(void)
{
	FAILED_CHECK_RETURN(CScene::Ready_Scene(), E_FAIL);

	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"StageBgm.ogg");

	FAILED_CHECK_RETURN(Ready_Environment_Layer(L"Environment_Layer"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_GameLogic_Layer(L"GameLogic_Layer"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_StaticObject_Layer(L"StaticObject_Layer"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_InteractionObject_Layer(L"InteractionObject_Layer"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_OrderTile_Layer(L"OrderTile_Layer"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Player_Layer(L"Player_Layer"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_UI_Layer(L"UI_Layer"), E_FAIL);

	FAILED_CHECK_RETURN(Ready_LightInfo(), E_FAIL);




	//m_pGraphicDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pGraphicDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);



	return S_OK;
}

Engine::_int CStage::Update_Scene(const _float& fTimeDelta)
{
	m_fTime += fTimeDelta;

	return CScene::Update_Scene(fTimeDelta);
}

void CStage::Render_Scene(void)
{
	// debug 용
	++m_dwRenderCnt;

	if (m_fTime >= 1.f)
	{
		m_fTime = 0.f;
		m_dwRenderCnt = 0;
	}
}

HRESULT CStage::Ready_Environment_Layer(const _tchar * pLayerTag)
{
	CLayer*		pLayer = CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	
	CGameObject*			pGameObject = nullptr;

	// DynamicCamera
	pGameObject = CDynamicCamera::Create(m_pGraphicDev, 
		&_vec3(75.f, 70.f, 60.f), &_vec3(75.f, 0.f, 120.f), &_vec3(0.f, 5.f, 0.f), 
		D3DXToRadian(30.f), (_float)WINCX / (_float)WINCY, 0.1f, 1000.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"DynamicCamera", pGameObject), E_FAIL);
	
	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CStage::Ready_GameLogic_Layer(const _tchar * pLayerTag)
{
	CLayer*		pLayer = CLayer::Create();
	CLoad_Manager::Load_Terrain_Data(L"../Data/terrain6.dat" , pLayer,m_pGraphicDev);
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CStage::Ready_StaticObject_Layer(const _tchar * pLayerTag)
{
	CLayer*		pLayer = CLayer::Create();
	
	CLoad_Manager::Load_Static_Object_Data(L"../Data/mesh416.dat", pLayer, m_pGraphicDev);

	NULL_CHECK_RETURN(pLayer, E_FAIL);

	m_mapLayer.emplace(pLayerTag, pLayer);
}

HRESULT CStage::Ready_InteractionObject_Layer(const _tchar * pLayerTag)
{
	CLayer*		pLayer = CLayer::Create();
	CGameObject*			pGameObject = nullptr;
#pragma region Room1
	// 1번문
	pGameObject = CLeftDoor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CLeftDoor*>(pGameObject)->Get_Transform_Component()->Set_Pos(89.f, -0.1f, 120.f);
	dynamic_cast<CLeftDoor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 180.f, 0.f);
	dynamic_cast<CLeftDoor*>(pGameObject)->Set_DoorOption(1);
	dynamic_cast<CLeftDoor*>(pGameObject)->Set_FirstPos(89.f, -0.1f, 120.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LeftDoor", pGameObject), E_FAIL);

	pGameObject = CRightDoor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CRightDoor*>(pGameObject)->Get_Transform_Component()->Set_Pos(89.f, -0.1f, 120.f);
	dynamic_cast<CRightDoor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 180.f, 0.f);
	dynamic_cast<CRightDoor*>(pGameObject)->Set_DoorOption(1);
	dynamic_cast<CRightDoor*>(pGameObject)->Set_FirstPos(89.f, -0.1f, 120.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"RightDoor", pGameObject), E_FAIL);

#pragma endregion

#pragma region Room2_Ball

	// 2번문
	pGameObject = CLeftDoor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CLeftDoor*>(pGameObject)->Get_Transform_Component()->Set_Pos(133.f, -0.1f, 120.f);
	dynamic_cast<CLeftDoor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 180.f, 0.f);
	dynamic_cast<CLeftDoor*>(pGameObject)->Set_DoorOption(2);
	dynamic_cast<CLeftDoor*>(pGameObject)->Set_FirstPos(133.f, -0.1f, 120.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LeftDoor2", pGameObject), E_FAIL);

	pGameObject = CRightDoor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CRightDoor*>(pGameObject)->Get_Transform_Component()->Set_Pos(133.f, -0.1f, 120.f);
	dynamic_cast<CRightDoor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 180.f, 0.f);
	dynamic_cast<CRightDoor*>(pGameObject)->Set_DoorOption(2);
	dynamic_cast<CRightDoor*>(pGameObject)->Set_FirstPos(133.f, -0.1f, 120.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"RightDoor2", pGameObject), E_FAIL);

	// 볼
	pGameObject = CBall::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CBall*>(pGameObject)->Get_Transform_Component()->Set_Pos(110.f, 2.5f, 117.f);
	dynamic_cast<CBall*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Ball", pGameObject), E_FAIL);

	// 바닥 스위치
	pGameObject = CFloorSwitch::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CFloorSwitch*>(pGameObject)->Get_Transform_Component()->Set_Pos(118.f, 0.f, 128.f);
	dynamic_cast<CFloorSwitch*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	dynamic_cast<CFloorSwitch*>(pGameObject)->Set_SwitchOption(1);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"FloorSwitch1", pGameObject), E_FAIL);



#pragma endregion

#pragma region Room3_Conveyor

	//// 3번문
	pGameObject = CLeftDoor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CLeftDoor*>(pGameObject)->Get_Transform_Component()->Set_Pos(152.f, -0.1f, 120.f);
	dynamic_cast<CLeftDoor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 180.f, 0.f);
	dynamic_cast<CLeftDoor*>(pGameObject)->Set_DoorOption(3);
	dynamic_cast<CLeftDoor*>(pGameObject)->Set_FirstPos(152.f, -0.1f, 120.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LeftDoor3", pGameObject), E_FAIL);

	pGameObject = CRightDoor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CRightDoor*>(pGameObject)->Get_Transform_Component()->Set_Pos(152.f, -0.1f, 120.f);
	dynamic_cast<CRightDoor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 180.f, 0.f);
	dynamic_cast<CRightDoor*>(pGameObject)->Set_DoorOption(3);
	dynamic_cast<CRightDoor*>(pGameObject)->Set_FirstPos(152.f, -0.1f, 120.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"RightDoor3", pGameObject), E_FAIL);

	// 컨베이너1
	pGameObject = CConveyor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CConveyor*>(pGameObject)->Get_Transform_Component()->Set_Pos(137.f, 0.f, 120.f);
	dynamic_cast<CConveyor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 90.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Conveyor1", pGameObject), E_FAIL);

	// 컨베이너2
	pGameObject = CConveyor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CConveyor*>(pGameObject)->Get_Transform_Component()->Set_Pos(143.5f, 0.f, 120.f);
	dynamic_cast<CConveyor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 90.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Conveyor2", pGameObject), E_FAIL);

#pragma endregion

#pragma region Room4_Maze

	// 미로
	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(162.1f, 0.f, 139.f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze1", pGameObject), E_FAIL);
	
	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(162.1f, 0.f, 135.9f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze2", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(162.1f, 0.f, 132.8f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze3", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(162.1f, 0.f, 129.7f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze4", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(162.1f, 0.f, 120.f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze5", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(162.1f, 0.f, 116.9f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze6", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(162.1f, 0.f, 113.8f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze7", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(162.1f, 0.f, 110.7f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze8", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(162.1f, 0.f, 107.6f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze9", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(165.2f, 0.f, 107.6f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze10", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(168.3f, 0.f, 107.6f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze11", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(171.4f, 0.f, 107.6f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze12", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(174.5f, 0.f, 107.6f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze13", pGameObject), E_FAIL);
	
	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(174.5f, 0.f, 110.7f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze14", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(174.5f, 0.f, 113.8f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze15", pGameObject), E_FAIL);


	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(171.4f, 0.f, 107.6f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze16", pGameObject), E_FAIL);


	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(168.3f, 0.f, 107.6f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze17", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(171.4f, 0.f, 104.5f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze18", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(171.4f, 0.f, 101.4f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze19", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(174.5f, 0.f, 101.4f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze20", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(191.5f, 0.f, 113.5f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze21", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(191.5f, 0.f, 110.4f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze22", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(191.5f, 0.f, 107.3f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze23", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(182.7f, 0.f, 106.3f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze24", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(182.7f, 0.f, 103.2f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze25", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(182.7f, 0.f, 100.1f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze26", pGameObject), E_FAIL);

	pGameObject = CMaze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Pos(182.7f, 0.f, 97.f);
	dynamic_cast<CMaze*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 90.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MoveMaze27", pGameObject), E_FAIL);

	pGameObject = CJelly::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CJelly*>(pGameObject)->Get_Transform_Component()->Set_Pos(188.f, 0.f, 102.f);
	dynamic_cast<CJelly*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Jelly", pGameObject), E_FAIL);

#pragma endregion

#pragma region Room5_ObjectMove

	//// 4번문
	pGameObject = CLeftDoor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CLeftDoor*>(pGameObject)->Get_Transform_Component()->Set_Pos(161.f, -0.1f, 151.f);
	dynamic_cast<CLeftDoor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 180.f, 0.f);
	dynamic_cast<CLeftDoor*>(pGameObject)->Set_DoorOption(4);
	dynamic_cast<CLeftDoor*>(pGameObject)->Set_FirstPos(161.f, -0.1f, 151.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LeftDoor4", pGameObject), E_FAIL);

	pGameObject = CRightDoor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CRightDoor*>(pGameObject)->Get_Transform_Component()->Set_Pos(161.f, -0.1f, 151.f);
	dynamic_cast<CRightDoor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 180.f, 0.f);
	dynamic_cast<CRightDoor*>(pGameObject)->Set_DoorOption(4);
	dynamic_cast<CRightDoor*>(pGameObject)->Set_FirstPos(161.f, -0.1f, 151.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"RightDoor4", pGameObject), E_FAIL);

	pGameObject = CHeavyMetal_Barrel::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CHeavyMetal_Barrel*>(pGameObject)->Get_Transform_Component()->Set_Pos(175.f, 0.f, 130.f);
	dynamic_cast<CHeavyMetal_Barrel*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"HeavyMetal_Barrel1", pGameObject), E_FAIL);

	pGameObject = CHeavyMetal_Barrel::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CHeavyMetal_Barrel*>(pGameObject)->Get_Transform_Component()->Set_Pos(182.7f, 0.f, 154.f);
	dynamic_cast<CHeavyMetal_Barrel*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"HeavyMetal_Barrel2", pGameObject), E_FAIL);


	// 바닥 스위치
	pGameObject = CFloorSwitch::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CFloorSwitch*>(pGameObject)->Get_Transform_Component()->Set_Pos(190.f, 0.f, 153.f);
	dynamic_cast<CFloorSwitch*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	dynamic_cast<CFloorSwitch*>(pGameObject)->Set_SwitchOption(2);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"FloorSwitch2", pGameObject), E_FAIL);


	// 바닥 스위치
	pGameObject = CFloorSwitch::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CFloorSwitch*>(pGameObject)->Get_Transform_Component()->Set_Pos(176.f, 0.f, 124.f);
	dynamic_cast<CFloorSwitch*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	dynamic_cast<CFloorSwitch*>(pGameObject)->Set_SwitchOption(3);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"FloorSwitch3", pGameObject), E_FAIL);

#pragma endregion

#pragma region Room7_Road

	// 빙판 위 장애물
	pGameObject = CGarbageBag::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Pos(127.f, 0.f, 188.f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Scale(0.07f, 0.07, 0.06f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CGarbageBag00", pGameObject), E_FAIL);

	// 빙판 위 장애물
	pGameObject = CGarbageBag::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Pos(132.f, 0.f, 188.f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Scale(0.07f, 0.07, 0.06f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CGarbageBag000", pGameObject), E_FAIL);

	// 빙판 위 장애물
	pGameObject = CGarbageBag::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Pos(137.f, 0.f, 188.f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Scale(0.07f, 0.07, 0.06f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CGarbageBag0000", pGameObject), E_FAIL);

#pragma endregion

#pragma region Room6_Order

	//// 6번문
	pGameObject = CLeftDoor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CLeftDoor*>(pGameObject)->Get_Transform_Component()->Set_Pos(107.f, -0.1f, 185.f);
	dynamic_cast<CLeftDoor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 180.f, 0.f);
	dynamic_cast<CLeftDoor*>(pGameObject)->Set_DoorOption(6);
	dynamic_cast<CLeftDoor*>(pGameObject)->Set_FirstPos(107.f, -0.1f, 185.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LeftDoor6", pGameObject), E_FAIL);

	pGameObject = CRightDoor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CRightDoor*>(pGameObject)->Get_Transform_Component()->Set_Pos(107.f, -0.1f, 185.f);
	dynamic_cast<CRightDoor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 180.f, 0.f);
	dynamic_cast<CRightDoor*>(pGameObject)->Set_DoorOption(6);
	dynamic_cast<CRightDoor*>(pGameObject)->Set_FirstPos(107.f, -0.1f, 185.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"RightDoor6", pGameObject), E_FAIL);

#pragma endregion

#pragma region Room7_Frozen
	
	//// 7번문
	pGameObject = CLeftDoor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CLeftDoor*>(pGameObject)->Get_Transform_Component()->Set_Pos(120.9f, -0.1f, 185.f);
	dynamic_cast<CLeftDoor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 180.f, 0.f);
	dynamic_cast<CLeftDoor*>(pGameObject)->Set_DoorOption(7);
	dynamic_cast<CLeftDoor*>(pGameObject)->Set_FirstPos(120.9f, -0.1f, 185.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LeftDoor7", pGameObject), E_FAIL);

	pGameObject = CRightDoor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CRightDoor*>(pGameObject)->Get_Transform_Component()->Set_Pos(120.9f, -0.1f, 185.f);
	dynamic_cast<CRightDoor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 180.f, 0.f);
	dynamic_cast<CRightDoor*>(pGameObject)->Set_DoorOption(7);
	dynamic_cast<CRightDoor*>(pGameObject)->Set_FirstPos(120.9f, -0.1f, 185.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"RightDoor7", pGameObject), E_FAIL);

	// 빙판
	pGameObject = CEmptyObject::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CEmptyObject*>(pGameObject)->Get_Transform_Component()->Set_Pos(167.f, 0.f, 187.f);
	dynamic_cast<CEmptyObject*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"FrozenLoad", pGameObject), E_FAIL);

	// 빙판 위 장애물
	pGameObject = CGarbageBag::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Pos(197.f, 0.f, 195.f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Scale(0.07f, 0.07, 0.07f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CGarbageBag1", pGameObject), E_FAIL);

	pGameObject = CGarbageBag::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Pos(180.f, 0.f, 190.f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Scale(0.07f, 0.07, 0.07f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CGarbageBag2", pGameObject), E_FAIL);

	pGameObject = CGarbageBag::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Pos(185.f, 0.f, 165.f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Scale(0.07f, 0.07, 0.07f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CGarbageBag3", pGameObject), E_FAIL);

	pGameObject = CGarbageBag::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Pos(185.f, 0.f, 210.f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Scale(0.07f, 0.07, 0.07f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CGarbageBag4", pGameObject), E_FAIL);

	pGameObject = CGarbageBag::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Pos(170.f, 0.f, 200.f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Scale(0.07f, 0.07, 0.07f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CGarbageBag5", pGameObject), E_FAIL);

	pGameObject = CGarbageBag::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Pos(175.f, 0.f, 175.f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Scale(0.07f, 0.07, 0.07f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CGarbageBag6", pGameObject), E_FAIL);

	pGameObject = CGarbageBag::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Pos(150.f, 0.f, 178.f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Scale(0.07f, 0.07, 0.07f);
	dynamic_cast<CGarbageBag*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CGarbageBag7", pGameObject), E_FAIL);

	// 도착하는 물건
	pGameObject = CComputer::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CComputer*>(pGameObject)->Get_Transform_Component()->Set_Pos(157.f, 0.f, 200.f);
	dynamic_cast<CComputer*>(pGameObject)->Get_Transform_Component()->Set_Scale(0.05f, 0.05f, 0.05f);
	dynamic_cast<CComputer*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 180.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Computer", pGameObject), E_FAIL);

#pragma endregion

#pragma region Last

	//// 마지막 문
	pGameObject = CLeftDoor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CLeftDoor*>(pGameObject)->Get_Transform_Component()->Set_Pos(114.f, -0.1f, 192.5f);
	dynamic_cast<CLeftDoor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 90.f, 0.f);
	dynamic_cast<CLeftDoor*>(pGameObject)->Set_DoorOption(5);
	dynamic_cast<CLeftDoor*>(pGameObject)->Set_FirstPos(114.f, -0.1f, 150.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LeftDoor5", pGameObject), E_FAIL);

	pGameObject = CRightDoor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CRightDoor*>(pGameObject)->Get_Transform_Component()->Set_Pos(114.f, -0.1f, 192.5f);
	dynamic_cast<CRightDoor*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 90.f, 0.f);
	dynamic_cast<CRightDoor*>(pGameObject)->Set_DoorOption(5);
	dynamic_cast<CRightDoor*>(pGameObject)->Set_FirstPos(114.f, -0.1f, 192.5f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"RightDoor5", pGameObject), E_FAIL);

	// 빙판
	pGameObject = CEndSpace::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CEndSpace*>(pGameObject)->Get_Transform_Component()->Set_Pos(110.f, 0.f, 228.f);
	dynamic_cast<CEndSpace*>(pGameObject)->Get_Transform_Component()->Set_Rotation(0.f, 0.f, 0.f);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Ending", pGameObject), E_FAIL);


#pragma endregion

	NULL_CHECK_RETURN(pLayer, E_FAIL);

	m_mapLayer.emplace(pLayerTag, pLayer);
}

HRESULT CStage::Ready_OrderTile_Layer(const _tchar * pLayerTag)
{
	CLayer*		pLayer = CLayer::Create();
	CGameObject*			pGameObject = nullptr;
	CGameObject*			pGameObject1 = nullptr;
	CGameObject*			pGameObject2 = nullptr;
	CGameObject*			pGameObject3 = nullptr;
	CGameObject*			pGameObject4 = nullptr;


	// 가운데 발판
	pGameObject = COrderTile::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<COrderTile*>(pGameObject)->Get_Transform_Component()->Set_Pos(68.f, 0.2f, 185.f);
	dynamic_cast<COrderTile*>(pGameObject)->Get_Transform_Component()->Set_Scale(2.f, 2.f, 2.f);
	dynamic_cast<COrderTile*>(pGameObject)->Get_Transform_Component()->Set_Rotation(90.f, 0.f, 0.f);
	dynamic_cast<COrderTile*>(pGameObject)->Set_TileNum(0);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"OrderTile0", pGameObject), E_FAIL);

	// 맨위 발판
	pGameObject1 = COrderTile::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<COrderTile*>(pGameObject1)->Get_Transform_Component()->Set_Pos(68.f, 0.2f, 195.f);
	dynamic_cast<COrderTile*>(pGameObject1)->Get_Transform_Component()->Set_Scale(2.f, 2.f, 2.f);
	dynamic_cast<COrderTile*>(pGameObject1)->Get_Transform_Component()->Set_Rotation(90.f, 0.f, 0.f);
	dynamic_cast<COrderTile*>(pGameObject1)->Set_TileNum(1);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"OrderTile1", pGameObject1), E_FAIL);

	// 맨아래 발판
	pGameObject2 = COrderTile::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<COrderTile*>(pGameObject2)->Get_Transform_Component()->Set_Pos(68.f, 0.2f, 175.f);
	dynamic_cast<COrderTile*>(pGameObject2)->Get_Transform_Component()->Set_Scale(2.f, 2.f, 2.f);
	dynamic_cast<COrderTile*>(pGameObject2)->Get_Transform_Component()->Set_Rotation(90.f, 0.f, 0.f);
	dynamic_cast<COrderTile*>(pGameObject2)->Set_TileNum(2);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"OrderTile2", pGameObject2), E_FAIL);

	// 맨왼쪽 발판
	pGameObject3 = COrderTile::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<COrderTile*>(pGameObject3)->Get_Transform_Component()->Set_Pos(58.f, 0.2f, 185.f);
	dynamic_cast<COrderTile*>(pGameObject3)->Get_Transform_Component()->Set_Scale(2.f, 2.f, 2.f);
	dynamic_cast<COrderTile*>(pGameObject3)->Get_Transform_Component()->Set_Rotation(90.f, 0.f, 0.f);
	dynamic_cast<COrderTile*>(pGameObject3)->Set_TileNum(3);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"OrderTile3", pGameObject3), E_FAIL);

	// 맨오른쪽 발판
	pGameObject4 = COrderTile::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<COrderTile*>(pGameObject4)->Get_Transform_Component()->Set_Pos(78.f, 0.2f, 185.f);
	dynamic_cast<COrderTile*>(pGameObject4)->Get_Transform_Component()->Set_Scale(2.f, 2.f, 2.f);
	dynamic_cast<COrderTile*>(pGameObject4)->Get_Transform_Component()->Set_Rotation(90.f, 0.f, 0.f);
	dynamic_cast<COrderTile*>(pGameObject4)->Set_TileNum(4);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"OrderTile4", pGameObject4), E_FAIL);

	NULL_CHECK_RETURN(pLayer, E_FAIL);

	m_mapLayer.emplace(pLayerTag, pLayer);

	COrderTile_Manger::GetInstance()->Set_listOrder1(pGameObject1);
	COrderTile_Manger::GetInstance()->Set_listOrder1(pGameObject2);
	COrderTile_Manger::GetInstance()->Set_listOrder1(pGameObject3);
	COrderTile_Manger::GetInstance()->Set_listOrder1(pGameObject4);

	COrderTile_Manger::GetInstance()->Set_listOrder2(pGameObject3);
	COrderTile_Manger::GetInstance()->Set_listOrder2(pGameObject1);
	COrderTile_Manger::GetInstance()->Set_listOrder2(pGameObject3);
	COrderTile_Manger::GetInstance()->Set_listOrder2(pGameObject2);
	COrderTile_Manger::GetInstance()->Set_listOrder2(pGameObject4);


}

HRESULT CStage::Ready_Player_Layer(const _tchar * pLayerTag)
{
	CLayer*		pLayer = CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*			pGameObject = nullptr;

	pGameObject = CPlayer::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Player", pGameObject), E_FAIL);


	m_mapLayer.emplace(pLayerTag, pLayer);
}

HRESULT CStage::Ready_UI_Layer(const _tchar * pLayerTag)
{
	return S_OK;
}

HRESULT CStage::Ready_LightInfo(void)
{
	D3DLIGHT9			tLightInfo;
	ZeroMemory(&tLightInfo, sizeof(D3DLIGHT9));

	tLightInfo.Type = D3DLIGHT_DIRECTIONAL;
	tLightInfo.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Direction = _vec3(1.f, -1.f, 1.f);

	FAILED_CHECK_RETURN(Ready_Light(m_pGraphicDev, &tLightInfo, 0), E_FAIL);

	return S_OK;
}

void CStage::Create_Maze(const _tchar * pLayerTag)
{
}

CStage* CStage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CStage*	pInstance = new CStage(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
		Safe_Release(pInstance);

	return pInstance;
}

void CStage::Free(void)
{
	CScene::Free();
}
