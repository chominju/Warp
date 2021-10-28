#include "stdafx.h"
#include "Player.h"
#include "InteractionObject.h"
#include "EmptyObject.h"
#include "Export_Function.h"

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
	, m_isWrapSkillItem(true)
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
	//빙판맵
	//m_pTransformCom->Set_Pos(120.f, 0.f, 180.f);
	//물체미는맵
	//m_pTransformCom->Set_Pos(180.f, 0.f, 150.f);
	//기존위치
	m_pTransformCom->Set_Pos(78.f, 0.f, 120.f);

	m_pTransformCom->Set_Rotation(0.f, 0.f, 0.f);
	
	//m_pNaviCom->Set_CellIndex(1);
	m_pMeshCom->Set_AnimationIndex(11);

	return S_OK;
}

Engine::_int CPlayer::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	m_startTime += fTimeDelta;
	if (m_startTime > 1.f)
	{
		_vec3 playerRot;
		m_pTransformCom->Get_Rotation(&playerRot);
		m_pCalculatorCom->Collision_InteractionObjectSensor(m_pColliderCom->Get_Min(), m_pColliderCom->Get_Max(), m_pColliderCom->Get_CollWorldMatrix(), playerRot);
		/*m_isColl_StaticObject = */m_pCalculatorCom->Collision_StaticObject(m_pSphereColliderCom, m_pushKey, m_isKeyStop);
		m_isColl_InteractionObject = m_pCalculatorCom->Collision_InteractionObject(m_pSphereColliderCom, m_pushKey, m_isKeyStop);


		_bool temp1;
		_bool temp2;
		temp1 =m_pCalculatorCom->Collision_Warp_InteractionObject(m_pWrapSphereColliderCom , &m_isHideObjectAble , m_hideObjectAble);
		temp2 =m_pCalculatorCom->Collision_Warp_StaticObject(m_pWrapSphereColliderCom);
		if((temp1==false ||(temp1==true && m_isHideObjectAble ==true))&&temp2==false)
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
	//Add_RenderGroup(RENDER_PLAYER, this);
	return 0;
}

void CPlayer::Render_Object(void)
{
	if (m_bDraw)
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

		//m_pNaviCom->Render_NaviMesh();

		m_pMeshCom->Render_Meshes();

		const _matrix* getTemp = m_pTransformCom->Get_WorldMatrix();
		_matrix newWorldMatrix = *getTemp;
		newWorldMatrix._42 += 3;

		// @@@@@@@@안보이게 주석
		m_pSphereColliderCom->Render_SphereCollider(&newWorldMatrix/*m_pTransformCom->Get_WorldMatrix()*/);
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

	//// NaviMesh
	//pComponent = m_pNaviCom = dynamic_cast<CNaviMesh*>(Clone_Proto(L"Proto_Mesh_Navi"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(L"Com_Navi", pComponent);

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
				/*if (m_lastPushKey[KEY_DOWN])
				{
				}
				else if(m_lastPushKey[KEY_UP])
				{

				}
				else if (m_lastPushKey[KEY_LEFT])
				{

				}
				else if(m_lastPushKey[KEY_RIGHT])*/
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
				//m_isKeyStop[KEY_UP] = false;
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
		//else
		//	m_pushKey[KEY_DOWN] = false;

		else if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_pTransformCom->Set_Rotation(0.f, 0.f, 0.f);
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			D3DXVec3Normalize(&m_vDir, &m_vDir);
			if (!m_isKeyStop[KEY_UP] && !m_isHideObject)
			{
				m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
				//m_isKeyStop[KEY_DOWN] = false;
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
		//else
		//	m_pushKey[KEY_UP] = false;

		else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_pTransformCom->Set_Rotation(0.f, -90.f, 0.f);
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			D3DXVec3Normalize(&m_vDir, &m_vDir);
			if (!m_isKeyStop[KEY_LEFT] && !m_isHideObject)
			{
				m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
				//m_isKeyStop[KEY_RIGHT] = false;
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
		/*else
			m_pushKey[KEY_LEFT] = false;*/

		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_pTransformCom->Set_Rotation(0.f, 90.f, 0.f);
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			D3DXVec3Normalize(&m_vDir, &m_vDir);
			if (!m_isKeyStop[KEY_RIGHT] && !m_isHideObject)
			{
				m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
				//m_isKeyStop[KEY_LEFT] = false;
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
		//else
		//	m_pushKey[KEY_RIGHT] = false;

		//if(m_pushKey[0]|| m_pushKey[1]|| m_pushKey[2]|| m_pushKey[3])
		//	m_pTransformCom->Move_Pos(&m_vDir, +10.f, fTimeDelta);
		/*if (Get_DIMouseState(DIM_LB) & 0X80)
		{
			_vec3	vPos = PickUp_OnTerrain();

			m_pTransformCom->Move_PickingPos(&vPos, 10.f, fTimeDelta);
		}*/

		//if (Get_DIMouseState(DIM_RB) & 0X80)
		//{
		//	m_pMeshCom->Set_AnimationIndex(11);
		//}

		//if (true == m_pMeshCom->Is_AnimationsetFinish())
		//	m_pMeshCom->Set_AnimationIndex(11);
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
					//m_isKeyStop[KEY_UP] = false;
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
			//else
			//	m_pushKey[KEY_DOWN] = false;

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
					//m_isKeyStop[KEY_DOWN] = false;
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
			//else
			//	m_pushKey[KEY_UP] = false;

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
					//m_isKeyStop[KEY_RIGHT] = false;
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
			/*else
			m_pushKey[KEY_LEFT] = false;*/

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
					//m_isKeyStop[KEY_LEFT] = false;
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
			//if (!m_isColl_StaticObject && !m_isColl_InteractionObject)
			//{
			//	
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

			/*}
			else
			{
				m_pMeshCom->Set_AnimationIndex(23);
				m_isFrozenRoadWalk = false;
			}*/
			/*else
			{
				m_pMeshCom->Set_AnimationIndex(23);
				m_isFrozenRoadWalk = false;
			}*/
		}
	}
}

void CPlayer::SetUp_OnTerrain(void)
{
	_vec3	vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);

	CTerrainTex*		pTerrainBufferCom = dynamic_cast<CTerrainTex*>(Engine::Get_Component(L"GameLogic_Layer", L"Terrain", L"Com_Buffer", ID_STATIC));
	NULL_CHECK(pTerrainBufferCom);

	const _vec3*	ptPos = pTerrainBufferCom->Get_VtxPos();


	//_float		fHeight = m_pCalculatorCom->Compute_HeightOnTerrain(&vPos, pTerrainBufferCom->Get_VtxPos(), VTXCNTX, VTXCNTZ);

	//m_pTransformCom->Set_Pos(vPos.x, fHeight, vPos.z);
}

_bool CPlayer::Collision_ToObject(/*const _tchar * pLayerTag, const _tchar * pObjTag*/)
{
	/*CCollider*		pObjectColliderCom = dynamic_cast<CCollider*>(Engine::Get_Component(pLayerTag, pObjTag, L"Com_Collider", ID_STATIC));
	NULL_CHECK_RETURN(pObjectColliderCom, false);*/

	/*return m_pCalculatorCom->Collision_AABB(pPlayerColliderCom->Get_Min(), pPlayerColliderCom->Get_Max(), pPlayerColliderCom->Get_CollWorldMatrix(),
	m_pColliderCom->Get_Min(), m_pColliderCom->Get_Max(), m_pColliderCom->Get_CollWorldMatrix());*/

	return m_pCalculatorCom->Collision_StaticObject(/*pObjectColliderCom->Get_Min(), pObjectColliderCom->Get_Max(), pObjectColliderCom->Get_CollWorldMatrix(),*/
		m_pSphereColliderCom , m_pushKey,m_isKeyStop);

}

//Engine::_vec3 CPlayer::PickUp_OnTerrain(void)
//{
//	CTerrainTex*		pTerrainBufferCom = dynamic_cast<CTerrainTex*>(Engine::Get_Component(L"GameLogic", L"Terrain", L"Com_Buffer", ID_STATIC));
//	NULL_CHECK_RETURN(pTerrainBufferCom, _vec3());
//
//	CTransform*		pTerrainTransCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"GameLogic", L"Terrain", L"Com_Transform", ID_DYNAMIC));
//	NULL_CHECK_RETURN(pTerrainTransCom, _vec3());
//
//	_vec3 temp{};
//	return temp;
//	//return m_pCalculatorCom->Picking_OnTerrain(g_hWnd, pTerrainBufferCom, pTerrainTransCom);
//}

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

