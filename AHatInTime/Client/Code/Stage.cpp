#include "stdafx.h"
#include "Stage.h"
#include "Load_Manager.h"
#include "LeftDoor.h"
#include "RightDoor.h"
#include "Ball.h"
#include "FloorSwitch.h"

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

	FAILED_CHECK_RETURN(Ready_Environment_Layer(L"Environment_Layer"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_GameLogic_Layer(L"GameLogic_Layer"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_StaticObject_Layer(L"StaticObject_Layer"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_InteractionObject_Layer(L"InteractionObject_Layer"), E_FAIL);
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
		wsprintf(m_szFPS, L"FPS : %d", m_dwRenderCnt);
		m_fTime = 0.f;
		m_dwRenderCnt = 0;
	}

	Render_Font(L"Font_Jinji", m_szFPS, &_vec2(400.f, 20.f), D3DXCOLOR(0.f, 0.f, 0.f, 1.f));

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

	//// SkyBox
	//pGameObject = CSkyBox::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"SkyBox", pGameObject), E_FAIL);



	

	
	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CStage::Ready_GameLogic_Layer(const _tchar * pLayerTag)
{
	CLayer*		pLayer = CLayer::Create();
	CLoad_Manager::Load_Terrain_Data(L"../Data/terrain5.dat" , pLayer,m_pGraphicDev);
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	
	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CStage::Ready_StaticObject_Layer(const _tchar * pLayerTag)
{
	CLayer*		pLayer = CLayer::Create();
	/*CLoad_Manager::Load_Static_Object_Data(L"../Data/mesh39.dat", pLayer, m_pGraphicDev);*/
	CLoad_Manager::Load_Static_Object_Data(L"../Data/mesh400.dat", pLayer, m_pGraphicDev);
	//CGameObject*			pGameObject = nullptr;

	//pGameObject = CLeftDoor::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LeftDoor", pGameObject), E_FAIL);
	
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	m_mapLayer.emplace(pLayerTag, pLayer);
}

HRESULT CStage::Ready_InteractionObject_Layer(const _tchar * pLayerTag)
{
	CLayer*		pLayer = CLayer::Create();
	CGameObject*			pGameObject = nullptr;

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
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"FloorSwitch", pGameObject), E_FAIL);


	
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	m_mapLayer.emplace(pLayerTag, pLayer);
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
	//CLayer*		pLayer = CLayer::Create();
	//NULL_CHECK_RETURN(pLayer, E_FAIL);

	//CGameObject*			pGameObject = nullptr;


	//// UI
	//pGameObject = CUI::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI", pGameObject), E_FAIL);


	//m_mapLayer.emplace(pLayerTag, pLayer);

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
