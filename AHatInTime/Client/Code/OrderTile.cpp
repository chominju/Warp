#include "stdafx.h"
#include "OrderTile.h"
#include "Ball.h"
#include "Player.h"
#include "OrderTile_Manager.h"
#include "LeftDoor.h"
#include "RightDoor.h"
#include "SoundMgr.h"

#include "Export_Function.h"

_int COrderTile::m_orderTileIndex = -1;
_bool COrderTile::m_isEnd1 = false;
_bool COrderTile::m_isEnd2 = false;
_bool COrderTile::m_isFinish1 = false;
_bool COrderTile::m_isFinish2 = false;


COrderTile::COrderTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CInteractionObject(pGraphicDev)
	, m_speed(1.f)
	, m_tileNum(-1)
	, m_isStart1(false)
	, m_isStart2(false)
	, m_showTile(false)
	, m_timer(0.f)
	, m_check(false)
	/*,m_orderTileIndex(-1)*/
{

}

COrderTile::COrderTile(const COrderTile& rhs)
	: CInteractionObject(rhs)
{

}

COrderTile::~COrderTile(void)
{

}

HRESULT COrderTile::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	//m_pTransformCom->Set_Pos(89.f, 0.f, 126.f);
	//m_pTransformCom->Set_Rotation(0.f, 90.f, 0.f);
	//m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(60.f));

	return S_OK;
}

Engine::_int COrderTile::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	SetUp_OnTerrain();
	//m_bColl
	//m_bColl = Collision_ToPlayer(L"Player_Layer", L"Player");

	//if (m_bColl)
	//{
	//	CManagement::GetInstance()->Get_Scene()->Get_MapLayer(L"Player_Layer", L"Player",0);
	//	//CPlayer * getPlayer = CManagement::GetInstance()
	//	// 플레이어 세팅
	//}

	_vec3	vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);

	//m_bDraw = m_pOptimizationCom->Isin_FrustumForObject(&vPos);

	Add_RenderGroup(RENDER_NONALPHA, this);

	if (m_tileNum == 0)
	{
		if (m_bColl)
		{
			if (!m_isFinish1)
				m_isStart1 = true;
			else
				m_isStart2 = true;
		}
	}
	else
	{

	}

	if (!m_isFinish1)
	{
		if (m_isStart1)
		{
			m_timer += fTimeDelta;
			if (m_timer > 1.f)
			{
				m_orderTileIndex++;
				if (m_orderTileIndex < COrderTile_Manger::GetInstance()->Get_GameObjectOrder1Size())
				{
					auto object = COrderTile_Manger::GetInstance()->Get_GameObjectOrder1(m_orderTileIndex);
					dynamic_cast<COrderTile*>(object)->Set_ShowTile(true);
					dynamic_cast<COrderTile*>(object)->Sound_OrderTile();
					m_timer = 0.f;
					if (m_orderTileIndex > 0)
					{
						auto object = COrderTile_Manger::GetInstance()->Get_GameObjectOrder1(m_orderTileIndex - 1);
						dynamic_cast<COrderTile*>(object)->Set_ShowTile(false);
					}
				}
				else
				{
					auto object = COrderTile_Manger::GetInstance()->Get_GameObjectOrder1(m_orderTileIndex - 1);
					dynamic_cast<COrderTile*>(object)->Set_ShowTile(false);
					m_isStart1 = false;
					m_isEnd1 = true;
					m_orderTileIndex = -1;
					m_timer = 0.f;
				}
			}
		}

		if (m_isEnd1)
		{
			if (m_bColl)
			{
				if (!m_check)
				{
					m_check = true;
					m_orderTileIndex++;
					if (COrderTile_Manger::GetInstance()->IsSameOrder1(m_orderTileIndex, this))
					{
						Sound_OrderTile();
						m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSoundOn.jpg"));
					}
					else
					{
						m_isEnd1 = false;
						m_orderTileIndex = -1;
						m_timer = 0.f;
					}

					if (m_orderTileIndex == COrderTile_Manger::GetInstance()->Get_GameObjectOrder1Size() - 1)
					{
						m_isFinish1 = true;
						m_orderTileIndex = -1;
						m_timer = 0.f;
					}
				}
			}
			else
			{
				m_check = false;
				m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSound.jpg"));
			}
		}
		else
		{
			if (m_showTile)
				m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSoundOn.jpg"));
			else
				m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSound.jpg"));
		}
	}
	else
	{
		if (m_isStart2)
		{
			m_timer += fTimeDelta;
			if (m_timer > 1.f)
			{
				m_orderTileIndex++;
				if (m_orderTileIndex < COrderTile_Manger::GetInstance()->Get_GameObjectOrder2Size())
				{
					auto object = COrderTile_Manger::GetInstance()->Get_GameObjectOrder2(m_orderTileIndex);
					dynamic_cast<COrderTile*>(object)->Sound_OrderTile();
					dynamic_cast<COrderTile*>(object)->Set_ShowTile(true);
					m_timer = 0.f;
					if (m_orderTileIndex > 0)
					{
						auto object = COrderTile_Manger::GetInstance()->Get_GameObjectOrder2(m_orderTileIndex - 1);
						dynamic_cast<COrderTile*>(object)->Set_ShowTile(false);
					}
				}
				else
				{
					auto object = COrderTile_Manger::GetInstance()->Get_GameObjectOrder2(m_orderTileIndex - 1);
					dynamic_cast<COrderTile*>(object)->Set_ShowTile(false);
					m_isStart2 = false;
					m_isEnd2 = true;
					m_orderTileIndex = -1;
					m_timer = 0.f;
				}
			}
		}

		if (m_isEnd2)
		{
			if (m_bColl)
			{
				if (!m_check)
				{
					m_check = true;
					m_orderTileIndex++;
					if (COrderTile_Manger::GetInstance()->IsSameOrder2(m_orderTileIndex, this))
					{
						Sound_OrderTile();
						m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSoundOn.jpg"));
					}
					else
					{
						m_isEnd2 = false;
						m_orderTileIndex = -1;
						m_timer = 0.f;
					}

					if (m_orderTileIndex == COrderTile_Manger::GetInstance()->Get_GameObjectOrder2Size() - 1)
					{
						m_isFinish2 = true;
					}
				}
			}
			else
			{
				m_check = false;
				m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSound.jpg"));
			}
		}
		else
		{
			if (m_showTile)
				m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSoundOn.jpg"));
			else
				m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSound.jpg"));
		}
	}
	if (m_isFinish2)
	{
		auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");

		for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
		{
			if (iter->first == L"LeftDoor7")
				dynamic_cast<CLeftDoor*>(iter->second)->Set_FloorSwitch(true);

			if (iter->first == L"RightDoor7")
				dynamic_cast<CRightDoor*>(iter->second)->Set_FloorSwitch(true);
		}
	}
	/*if(m_bColl || m_showTile)
		m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSoundOn.jpg"));
	else
		m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSound.jpg"));*/
	//IsCollisionBall();

	//if (m_bSensorColl)
	//{
	//	auto getPlayer = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"Player_Layer")->begin();
	//	bool *getPlayerPush = dynamic_cast<CPlayer*>(getPlayer->second)->Get_PushKey();
	//	dynamic_cast<CPlayer*>(getPlayer->second)->Set_Speed(m_speed);
	//}
	
	return 0;
}

void COrderTile::Render_Object(void)
{
	if (false == m_bDraw)
		return;
	/*if (m_tileNum == 0)
		return;*/
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pTextureCom->Render_Texture();

	m_pBufferCom->Render_Buffer();

	const _matrix* getTemp = m_pTransformCom->Get_WorldMatrix();
	_matrix newWorldMatrix = *getTemp;
	newWorldMatrix._11 = 0.05f;
	newWorldMatrix._12 = 0.f;
	newWorldMatrix._13 = 0.f;
	newWorldMatrix._14 = 0.f;
	newWorldMatrix._21 = 0.f;
	newWorldMatrix._22 = 0.05f;
	newWorldMatrix._23 = 0.f;
	newWorldMatrix._24 = 0.f;
	newWorldMatrix._31 = 0.f;
	newWorldMatrix._32 = 0.f;
	newWorldMatrix._33 = 0.05f;
	newWorldMatrix._34 = 0.f;

	newWorldMatrix._42 += 1;

	m_pSphereColliderCom->Render_SphereCollider(&newWorldMatrix);

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//void CConveyor::IsCollisionBall()
//{
//	auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");
//
//	for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
//	{
//		if (iter->first == L"Ball")
//			m_targetBall = iter->second;
//	}
//
//	auto ballColl = dynamic_cast<CBall*>(m_targetBall)->Get_ColliderSensor_Component();
//	if (m_pCalculatorCom->Collision_AABB(ballColl->Get_Min(), ballColl->Get_Max(), ballColl->Get_CollWorldMatrix(),
//		m_pColliderSensorCom->Get_Min(), m_pColliderSensorCom->Get_Max(), m_pColliderSensorCom->Get_CollWorldMatrix()))
//		m_isBallColl = true;
//	else
//		m_isBallColl = false;
//}

//void CLeftDoor::Set_StaticMesh_Component(const _tchar* pMeshProtoTag)
//{
//	// 메쉬
//	CComponent*			pComponent = nullptr;
//	pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(pMeshProtoTag));
//	NULL_CHECK_RETURN(pComponent);
//	Add_AddComponent(L"Com_Mesh", ID_DYNAMIC, pComponent);
//
//	pComponent = m_pColliderCom = CCollider::Create(m_pGraphicDev, m_pMeshCom->Get_VtxPos(), m_pMeshCom->Get_NumVtx(), m_pMeshCom->Get_VtxSize());
//	NULL_CHECK_RETURN(pComponent);
//	m_mapComponent[ID_STATIC].emplace(L"Com_Collider", pComponent);
//}

//void CInteractionObject::Set_Static_Objects_Data(Object_Data objectData)
//{
//	_tcscpy_s(m_objectData.m_objectTextureName, _countof(m_objectData.m_objectTextureName), objectData.m_objectTextureName);
//
//	m_objectData.m_pos[INFO_POS].x = objectData.m_pos[INFO_POS].x;
//	m_objectData.m_pos[INFO_POS].y = objectData.m_pos[INFO_POS].y;
//	m_objectData.m_pos[INFO_POS].z = objectData.m_pos[INFO_POS].z;
//
//	m_objectData.m_vAngle.x = objectData.m_vAngle.x;
//	m_objectData.m_vAngle.y = objectData.m_vAngle.y;
//	m_objectData.m_vAngle.z = objectData.m_vAngle.z;
//
//	m_objectData.m_vScale.x = objectData.m_vScale.x;
//	m_objectData.m_vScale.y = objectData.m_vScale.y;
//	m_objectData.m_vScale.z = objectData.m_vScale.z;
//
//	m_objectData.m_objectIndex = objectData.m_objectIndex;
//}

void COrderTile::Sound_OrderTile()
{
	if (m_tileNum == 1) // 위
	{
		CSoundMgr::Get_Instance()->PlaySound(L"OrderUp.ogg", CSoundMgr::PLAYER);
	}
	else if (m_tileNum == 2) // 아래
	{
		CSoundMgr::Get_Instance()->PlaySound(L"OrderDown.ogg", CSoundMgr::PLAYER);
	}
	else if (m_tileNum == 3) // 왼쪽
	{
		CSoundMgr::Get_Instance()->PlaySound(L"OrderLeft.ogg", CSoundMgr::PLAYER);
	}
	else if (m_tileNum == 4) // 오른쪽
	{
		CSoundMgr::Get_Instance()->PlaySound(L"OrderRight.ogg", CSoundMgr::PLAYER);
	}
}

HRESULT COrderTile::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	//// 메쉬
	//pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(L"Proto_Mesh_GarbageBag.x"));
	//NULL_CHECK_RETURN(pComponent);
	//Add_AddComponent(L"Com_Mesh", ID_DYNAMIC, pComponent);

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_Buffer_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSound.jpg"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Texture", pComponent);

	// Transform
	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
	m_pTransformCom->Set_Scale(0.05f, 0.05f, 0.05f);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	// renderer
	pComponent = m_pRendererCom = Get_Renderer();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->AddRef();
	m_mapComponent[ID_STATIC].emplace(L"Com_Renderer", pComponent);

	// Calculator
	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(L"Proto_Calculator"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(L"Com_Calculator", pComponent);


	// Collider
	pComponent = m_pSphereColliderCom = CSphereCollider::Create(m_pGraphicDev, 20);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_SphereCollider", pComponent);

	//// Collider
	//pComponent = m_pColliderCom = CCollider::Create(m_pGraphicDev, m_pMeshCom->Get_VtxPos(), m_pMeshCom->Get_NumVtx(), m_pMeshCom->Get_VtxSize(),0,0,0);
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(L"Com_Collider", pComponent);

	//// Optimization
	//pComponent = m_pOptimizationCom = dynamic_cast<COptimization*>(Clone_Proto(L"Proto_Optimization"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(L"Com_Optimization", pComponent);
	//
	return S_OK;

}


COrderTile* COrderTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	COrderTile*	pInstance = new COrderTile(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void COrderTile::Free(void)
{
	CGameObject::Free();
}
