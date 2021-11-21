#include "stdafx.h"
#include "Player.h"
#include "PlayerAim.h"
#include "InteractionObject.h"
#include "EmptyObject.h"
#include "Export_Function.h"
#include "LeftDoor.h"
#include "RightDoor.h"
#include "WrapSprite.h"
#include "Effect.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pushKey{ false,false,false,false, }
	, m_isKeyStop{ false,false,false,false }
	, m_startTime(0.f)
	, m_speed(10.f)
	, m_firstSpeed(m_speed)
	, m_isConveyor(false)
	, m_isWrapable(true)
	, m_isWrapKeyable(true)
	, m_isHideObject(false)
	, m_isHideObjectAble(false)
	, m_hideObjectAble(nullptr)
	, m_hideObject(nullptr)
	, m_isFrozenRoadOn(false)
	, m_isFrozenRoadWalk(false)
	, m_isColl_StaticObject(false)
	, m_isColl_InteractionObject(false)
	, m_isWrapSkillItem(false)
	, m_isColl_Computer(false)
{

}

CPlayer::CPlayer(const CPlayer& rhs)
	: CGameObject(rhs)
{

}

CPlayer::~CPlayer(void)
{

}

HRESULT CPlayer::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	FAILED_CHECK_RETURN(CGameObject::Ready_Object(), E_FAIL);

	m_pTransformCom->Set_Scale(0.05f, 0.05f, 0.05f);
	m_pTransformCom->Set_Pos(78.f, 0.f, 120.f);
	m_pTransformCom->Set_Rotation(0.f, 0.f, 0.f);
	m_pMeshCom->Set_AnimationIndex(11);

	return S_OK;
}

Engine::_int CPlayer::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);
	m_startTime += fTimeDelta;
	if (m_startTime > 1.f)
	{
		_vec3 getPlayerRot;
		m_pTransformCom->Get_Rotation(&getPlayerRot);
		m_pCalculatorCom->Collision_InteractionObjectSensor(m_pColliderCom->Get_Min(), m_pColliderCom->Get_Max(), m_pColliderCom->Get_CollWorldMatrix(), getPlayerRot);
		m_pCalculatorCom->Collision_StaticObject(m_pSphereColliderCom, m_pushKey, m_isKeyStop);
		m_isColl_InteractionObject = m_pCalculatorCom->Collision_InteractionObject(m_pSphereColliderCom, m_pushKey, m_isKeyStop);


		_bool isWarp_interationObj;
		_bool isWarp_staticObj;
		isWarp_interationObj =m_pCalculatorCom->Collision_Warp_InteractionObject(m_pWrapSphereColliderCom , &m_isHideObjectAble , m_hideObjectAble);
		isWarp_staticObj =m_pCalculatorCom->Collision_Warp_StaticObject(m_pWrapSphereColliderCom);
		m_pCalculatorCom->Collision_OrderTile(m_pSphereColliderCom);
		
		if((isWarp_interationObj==false ||(isWarp_interationObj==true && m_isHideObjectAble ==true))&&isWarp_staticObj==false)
			m_isWrapable = true;
		else
			m_isWrapable = false;

		if (m_hideObjectAble == nullptr)
		{
			int a;
		}
	}

	SetUp_OnTerrain();

	auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");
	for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
	{
		if (!_tcscmp(iter->first, L"FrozenLoad"))
			m_FrozenObject = iter->second;

	}

	Key_Input(fTimeDelta);

	m_pMeshCom->Play_Animation(fTimeDelta);

	Add_RenderGroup(RENDER_NONALPHA, this);
	if (m_isWrapSkillItem)
		m_playerAim->Update_Object(fTimeDelta);
	return 0;
}

void CPlayer::Render_Object(void)
{
	if (m_bDraw)
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
		m_pMeshCom->Render_Meshes();

		const _matrix* getTemp = m_pTransformCom->Get_WorldMatrix();
		_matrix newWorldMatrix = *getTemp;
		newWorldMatrix._42 += 3;

		m_pSphereColliderCom->Render_SphereCollider(&newWorldMatrix);
		m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), m_pTransformCom->Get_WorldMatrix());

	}

	const _matrix* getTemp2 = m_pTransformCom->Get_WorldMatrix();
	_matrix newWorldMatrix2 = *getTemp2;
	newWorldMatrix2._42 += 3;

	if (m_lastPushKey[KEY_DOWN])
		newWorldMatrix2._43 -= 10;
	if (m_lastPushKey[KEY_UP])
		newWorldMatrix2._43 += 10;
	if (m_lastPushKey[KEY_LEFT])
		newWorldMatrix2._41 -= 10;
	if (m_lastPushKey[KEY_RIGHT])
		newWorldMatrix2._41 += 10;

	m_pWrapSphereColliderCom->Render_SphereCollider(&newWorldMatrix2/*m_pTransformCom->Get_WorldMatrix()*/);
	if (m_isWrapSkillItem)
		m_playerAim->Render_Object();
}

HRESULT CPlayer::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// 메쉬
	pComponent = m_pStatic_MeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(L"Proto_StaticMesh_Player"));
	NULL_CHECK_RETURN(pComponent);
	Add_AddComponent(L"Com_StaticMesh", ID_DYNAMIC, pComponent);

	pComponent = m_pColliderCom = CCollider::Create(m_pGraphicDev, m_pStatic_MeshCom->Get_VtxPos(), m_pStatic_MeshCom->Get_NumVtx(), m_pStatic_MeshCom->Get_VtxSize());
	NULL_CHECK_RETURN(pComponent);
	m_mapComponent[ID_STATIC].emplace(L"Com_Collider", pComponent);

	// DynamicMesh
	pComponent = m_pMeshCom = dynamic_cast<CDynamicMesh*>(Clone_Proto(L"Proto_Mesh_Player"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Mesh", pComponent);

	// Transform
	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
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
	pComponent = m_pSphereColliderCom = CSphereCollider::Create(m_pGraphicDev, 30);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_SphereCollider", pComponent);

	// WarpCollider
	pComponent = m_pWrapSphereColliderCom = CSphereCollider::Create(m_pGraphicDev, 30);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_WrapSphereCollider", pComponent);

	m_playerAim = CPlayerAim::Create(m_pGraphicDev);
	return S_OK;

}

void CPlayer::Key_Input(const _float& fTimeDelta)
{
	if (!m_isFrozenRoadOn) // 빙판위가 아닐때
	{
		if (m_isHideObject)	// 물체에 숨었을 때
		{
			if (GetAsyncKeyState('W') & 0x8000)	// W를 눌렀을 때
			{
				dynamic_cast<CInteractionObject*>(m_hideObject)->Set_IsObject_PlayerWarpMove(true);
				m_isHideObject = false;
				m_bDraw = true;
			}
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_pTransformCom->Set_Rotation(0.f, 180.f, 0.f);
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			D3DXVec3Normalize(&m_vDir, &m_vDir);
			if (!m_isKeyStop[KEY_DOWN] && !m_isHideObject)
			{
				m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
			}
			m_pushKey[KEY_DOWN] = true;
			m_pushKey[KEY_UP] = false;
			m_pushKey[KEY_LEFT] = false;
			m_pushKey[KEY_RIGHT] = false;

			m_lastPushKey[KEY_DOWN] = true;
			m_lastPushKey[KEY_UP] = false;
			m_lastPushKey[KEY_LEFT] = false;
			m_lastPushKey[KEY_RIGHT] = false;
			m_pMeshCom->Set_AnimationIndex(11);
		}

		else if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_pTransformCom->Set_Rotation(0.f, 0.f, 0.f);
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			D3DXVec3Normalize(&m_vDir, &m_vDir);
			if (!m_isKeyStop[KEY_UP] && !m_isHideObject)
			{
				m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
			}
			m_pushKey[KEY_DOWN] = false;
			m_pushKey[KEY_UP] = true;
			m_pushKey[KEY_LEFT] = false;
			m_pushKey[KEY_RIGHT] = false;

			m_lastPushKey[KEY_DOWN] = false;
			m_lastPushKey[KEY_UP] = true;
			m_lastPushKey[KEY_LEFT] = false;
			m_lastPushKey[KEY_RIGHT] = false;
			m_pMeshCom->Set_AnimationIndex(11);
		}

		else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_pTransformCom->Set_Rotation(0.f, -90.f, 0.f);
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			D3DXVec3Normalize(&m_vDir, &m_vDir);
			if (!m_isKeyStop[KEY_LEFT] && !m_isHideObject)
			{
				m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
			}
			m_pushKey[KEY_DOWN] = false;
			m_pushKey[KEY_UP] = false;
			m_pushKey[KEY_LEFT] = true;
			m_pushKey[KEY_RIGHT] = false;

			m_lastPushKey[KEY_DOWN] = false;
			m_lastPushKey[KEY_UP] = false;
			m_lastPushKey[KEY_LEFT] = true;
			m_lastPushKey[KEY_RIGHT] = false;
			m_pMeshCom->Set_AnimationIndex(11);
		}

		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_pTransformCom->Set_Rotation(0.f, 90.f, 0.f);
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			D3DXVec3Normalize(&m_vDir, &m_vDir);
			if (!m_isKeyStop[KEY_RIGHT] && !m_isHideObject)
			{
				m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
			}
			m_pushKey[KEY_DOWN] = false;
			m_pushKey[KEY_UP] = false;
			m_pushKey[KEY_LEFT] = false;
			m_pushKey[KEY_RIGHT] = true;

			m_lastPushKey[KEY_DOWN] = false;
			m_lastPushKey[KEY_UP] = false;
			m_lastPushKey[KEY_LEFT] = false;
			m_lastPushKey[KEY_RIGHT] = true;
			m_pMeshCom->Set_AnimationIndex(11);
		}
		else
		{
			m_pushKey[KEY_DOWN] = false;
			m_pushKey[KEY_UP] = false;
			m_pushKey[KEY_LEFT] = false;
			m_pushKey[KEY_RIGHT] = false;
			if (m_pMeshCom->Get_AnimationIndex() == 10)
			{
				if (true == m_pMeshCom->Is_AnimationsetFinish())
					m_pMeshCom->Set_AnimationIndex(23);
			}
			else
				m_pMeshCom->Set_AnimationIndex(23);
		}

		if (m_isWrapable && m_isWrapSkillItem)
		{
			if (GetAsyncKeyState('Q') & 0x8000)
			{
				if (m_isWrapKeyable)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"Player_Warp.ogg", CSoundMgr::PLAYER);
					if (!m_isHideObject)
					{
						CLayer*		pLayer = CLayer::Create();
						CWarpSprite* newWarpSprite = CWarpSprite::Create(m_pGraphicDev);
						const _matrix* playerWorld = m_pTransformCom->Get_WorldMatrix();
						newWarpSprite->Get_Transform_Component()->Set_Pos(playerWorld->_41, 5.f, playerWorld->_43);

						pLayer->Add_GameObject(L"WarpSprite", newWarpSprite);
						CManagement::GetInstance()->Get_Scene()->Add_LayerGameObject(L"Effect_Layer", pLayer, L"WarpSprite", newWarpSprite);
					}

					m_isWrapKeyable = false;
					if (m_isHideObjectAble)
					{
						m_bDraw = false;
						m_isHideObject = true;

						const _matrix * getWorld = dynamic_cast<CInteractionObject*>(m_hideObjectAble)->Get_Transform_Component()->Get_WorldMatrix();// Get_CollWorldMatrix();
						_vec3 temp;
						m_pTransformCom->Get_Info(INFO_POS, &temp);
						m_pTransformCom->Set_Pos(getWorld->_41, temp.y, getWorld->_43);
						m_pMeshCom->Set_AnimationIndex(10);
						m_hideObject = m_hideObjectAble;

					}
					else
					{
						m_bDraw = true;
						m_isHideObject = false;
						const _matrix * getWorld = m_pWrapSphereColliderCom->Get_CollWorldMatrix();
						_vec3 temp;
						m_pTransformCom->Get_Info(INFO_POS, &temp);
						m_pTransformCom->Set_Pos(getWorld->_41, temp.y, getWorld->_43);
						m_pMeshCom->Set_AnimationIndex(10);
					}
				}
			}
			else
				m_isWrapKeyable = true;
		}
		else
			m_isWrapKeyable = true;
	}
	else
	{
		CCollider* getSensorColl = dynamic_cast<CEmptyObject*>(m_FrozenObject)->Get_ColliderSensor_Component();

		const _vec3 * pDestMin = dynamic_cast<CCollider*>(getSensorColl)->Get_Min();
		const _vec3 * pDestMax = dynamic_cast<CCollider*>(getSensorColl)->Get_Max();
		const _matrix * pDestWorld = dynamic_cast<CCollider*>(getSensorColl)->Get_CollWorldMatrix();
		_vec3		vDestMin, vDestMax;

		D3DXVec3TransformCoord(&vDestMin, pDestMin, pDestWorld);
		D3DXVec3TransformCoord(&vDestMax, pDestMax, pDestWorld);

		_vec3 temp = vDestMin;
		if (vDestMax.x < vDestMin.x)
		{
			vDestMin.x = vDestMax.x;
			vDestMax.x = temp.x;
		}

		if (vDestMax.y < vDestMin.y)
		{
			vDestMin.y = vDestMax.y;
			vDestMax.y = temp.y;
		}

		if (vDestMax.z < vDestMin.z)
		{
			vDestMin.z = vDestMax.z;
			vDestMax.z = temp.z;
		}

		_vec3 playerPos;
		m_pTransformCom->Get_Info(INFO_POS, &playerPos);

		Set_Speed(m_firstSpeed * 2);
		if (!m_isFrozenRoadWalk)	// 걷고 있지 않을 때
		{
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				m_pTransformCom->Set_Rotation(0.f, 180.f, 0.f);
				m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
				D3DXVec3Normalize(&m_vDir, &m_vDir);
				if (!m_isKeyStop[KEY_DOWN] && !m_isHideObject)
				{
					if (vDestMin.z < playerPos.z)
					{
						m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
					}
				}
				m_pushKey[KEY_DOWN] = true;
				m_pushKey[KEY_UP] = false;
				m_pushKey[KEY_LEFT] = false;
				m_pushKey[KEY_RIGHT] = false;

				m_lastPushKey[KEY_DOWN] = true;
				m_lastPushKey[KEY_UP] = false;
				m_lastPushKey[KEY_LEFT] = false;
				m_lastPushKey[KEY_RIGHT] = false;
				m_pMeshCom->Set_AnimationIndex(11);
				m_isFrozenRoadWalk = true;
			}

			else if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				m_pTransformCom->Set_Rotation(0.f, 0.f, 0.f);
				m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
				D3DXVec3Normalize(&m_vDir, &m_vDir);
				if (!m_isKeyStop[KEY_UP] && !m_isHideObject)
				{
					if (vDestMax.z > playerPos.z)
					{
						m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
					}
				}
				m_pushKey[KEY_DOWN] = false;
				m_pushKey[KEY_UP] = true;
				m_pushKey[KEY_LEFT] = false;
				m_pushKey[KEY_RIGHT] = false;

				m_lastPushKey[KEY_DOWN] = false;
				m_lastPushKey[KEY_UP] = true;
				m_lastPushKey[KEY_LEFT] = false;
				m_lastPushKey[KEY_RIGHT] = false;
				m_pMeshCom->Set_AnimationIndex(11);
				m_isFrozenRoadWalk = true;
			}

			else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				m_pTransformCom->Set_Rotation(0.f, -90.f, 0.f);
				m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
				D3DXVec3Normalize(&m_vDir, &m_vDir);
				if (!m_isKeyStop[KEY_LEFT] && !m_isHideObject)
				{
					if (vDestMin.x < playerPos.x)
					{
						m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
					}
				}
				m_pushKey[KEY_DOWN] = false;
				m_pushKey[KEY_UP] = false;
				m_pushKey[KEY_LEFT] = true;
				m_pushKey[KEY_RIGHT] = false;

				m_lastPushKey[KEY_DOWN] = false;
				m_lastPushKey[KEY_UP] = false;
				m_lastPushKey[KEY_LEFT] = true;
				m_lastPushKey[KEY_RIGHT] = false;
				m_pMeshCom->Set_AnimationIndex(11);
				m_isFrozenRoadWalk = true;
			}

			else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				m_pTransformCom->Set_Rotation(0.f, 90.f, 0.f);
				m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
				D3DXVec3Normalize(&m_vDir, &m_vDir);
				if (!m_isKeyStop[KEY_RIGHT] && !m_isHideObject)
				{
					if (vDestMax.x > playerPos.x)
					{
						m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
					}
				}
				m_pushKey[KEY_DOWN] = false;
				m_pushKey[KEY_UP] = false;
				m_pushKey[KEY_LEFT] = false;
				m_pushKey[KEY_RIGHT] = true;

				m_lastPushKey[KEY_DOWN] = false;
				m_lastPushKey[KEY_UP] = false;
				m_lastPushKey[KEY_LEFT] = false;
				m_lastPushKey[KEY_RIGHT] = true;
				m_pMeshCom->Set_AnimationIndex(11);
				m_isFrozenRoadWalk = true;
			}
			else
			{
				m_pushKey[KEY_DOWN] = false;
				m_pushKey[KEY_UP] = false;
				m_pushKey[KEY_LEFT] = false;
				m_pushKey[KEY_RIGHT] = false;
				m_pMeshCom->Set_AnimationIndex(23);
			}

			if (Get_DIMouseState(DIM_RB) & 0X80)
			{
				m_pMeshCom->Set_AnimationIndex(11);
			}

			if (true == m_pMeshCom->Is_AnimationsetFinish())
				m_pMeshCom->Set_AnimationIndex(11);
		}
		else	// 걷고 있을 때 장애물 없을 때 까지 쭉 걷기
		{
				if (m_lastPushKey[KEY_DOWN])
				{
					if (vDestMin.z < playerPos.z)
					{
						if (!m_isKeyStop[KEY_DOWN] && !m_isHideObject)
						{
							m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
							D3DXVec3Normalize(&m_vDir, &m_vDir);
							m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
						}
						else
						{
							m_pMeshCom->Set_AnimationIndex(23);
							m_isFrozenRoadWalk = false;
						}
					}
					else
					{
						m_pMeshCom->Set_AnimationIndex(23);
						m_isFrozenRoadWalk = false;
					}
				}
				else if (m_lastPushKey[KEY_UP])
				{
					if (vDestMax.z > playerPos.z)
					{
						if (!m_isKeyStop[KEY_UP] && !m_isHideObject)
						{
							m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
							D3DXVec3Normalize(&m_vDir, &m_vDir);
							m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
						}
						else
						{
							m_pMeshCom->Set_AnimationIndex(23);
							m_isFrozenRoadWalk = false;
						}
					}
					else
					{
						m_pMeshCom->Set_AnimationIndex(23);
						m_isFrozenRoadWalk = false;
					}
				}
				else if (m_lastPushKey[KEY_LEFT])
				{
					if (vDestMin.x < playerPos.x)
					{
						if (!m_isKeyStop[KEY_LEFT] && !m_isHideObject)
						{
							m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
							D3DXVec3Normalize(&m_vDir, &m_vDir);
							m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
						}
						else
						{
							m_pMeshCom->Set_AnimationIndex(23);
							m_isFrozenRoadWalk = false;
						}
					}
					else if (vDestMin.x > playerPos.x && (playerPos.z < 190 && playerPos.z>180))
					{
						m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
						D3DXVec3Normalize(&m_vDir, &m_vDir);
						m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
					}
					else
					{
						m_pMeshCom->Set_AnimationIndex(23);
						m_isFrozenRoadWalk = false;
					}
				}
				else if (m_lastPushKey[KEY_RIGHT])
				{
					if (vDestMax.x > playerPos.x)
					{
						if (!m_isKeyStop[KEY_RIGHT] && !m_isHideObject)
						{
							m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
							D3DXVec3Normalize(&m_vDir, &m_vDir);
							m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
						}
						else
						{
							m_pMeshCom->Set_AnimationIndex(23);
							m_isFrozenRoadWalk = false;
						}
					}
					else
					{
						m_pMeshCom->Set_AnimationIndex(23);
						m_isFrozenRoadWalk = false;
						Reset_Speed();
					}
				}
		}
	}

	if (m_isColl_Computer)		// 컴퓨터와 상호작용 될 때
	{
		if (GetAsyncKeyState('G') & 0x8000)	// G를 눌렀을 때
		{
			auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");
			for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
			{
				for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
				{
					if (iter->first == L"LeftDoor5")
						dynamic_cast<CLeftDoor*>(iter->second)->Set_FloorSwitch(true);

					if (iter->first == L"RightDoor5")
						dynamic_cast<CRightDoor*>(iter->second)->Set_FloorSwitch(true);
				}
			}
		}
	}
}

void CPlayer::SetUp_OnTerrain(void)
{
	CTerrainTex*		pTerrainBufferCom = dynamic_cast<CTerrainTex*>(Engine::Get_Component(L"GameLogic_Layer", L"Terrain", L"Com_Buffer", ID_STATIC));
	NULL_CHECK(pTerrainBufferCom);
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer*	pInstance = new CPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CPlayer::Free(void)
{
	CGameObject::Free();
}

