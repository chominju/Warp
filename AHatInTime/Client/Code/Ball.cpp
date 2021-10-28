#include "stdafx.h"
#include "Ball.h"
#include "Player.h"


#include "Export_Function.h"

CBall::CBall(LPDIRECT3DDEVICE9 pGraphicDev)
	: CInteractionObject(pGraphicDev)
	, isBall(false)
	, m_firstPushKey{ false,false,false,false }
	, m_isFirstColl(false)
	, m_speed(3.f)
	, m_angle{0.f,0.f}
{

}

CBall::CBall(const CBall& rhs)
	: CInteractionObject(rhs)
{

}

CBall::~CBall(void)
{

}

HRESULT CBall::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//m_pTransformCom->Set_Pos(89.f, 0.f, 126.f);
	//m_pTransformCom->Set_Rotation(0.f, 90.f, 0.f);
	//m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(60.f));

	return S_OK;
}

Engine::_int CBall::Update_Object(const _float& fTimeDelta)
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

	bool check=false;
	if (m_bSensorColl)
	{
		auto getPlayer = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"Player_Layer")->begin();
	 	bool *getPlayerPush =  dynamic_cast<CPlayer*>(getPlayer->second)->Get_PushKey();
		dynamic_cast<CPlayer*>(getPlayer->second)->Set_Speed(m_speed);
		if (!m_isFirstColl)
		{
			m_isFirstColl = true;
			for (int i = 0; i < KEY_END; i++)
			{
				m_firstPushKey[i] = getPlayerPush[i];
			}
		}
		//if (getPlayerPush[0])// 아래
		//{
		//	m_pTransformCom->Set_Rotation(0.f, 180.f, 0.f);
		//}
		//if (getPlayerPush[1])//위
		//{
		//	m_pTransformCom->Set_Rotation(0.f, 0.f, 0.f);
		//}
		//if (getPlayerPush[2])//왼쪽
		//{
		//	m_pTransformCom->Set_Rotation(0.f, -90.f, 0.f);
		//}
		//if (getPlayerPush[3])//오른쪽
		//{
		//	m_pTransformCom->Set_Rotation(0.f, 90.f, 0.f);
		//}
			
			for (int i = 0; i < KEY_END; i++)
			{
				if (getPlayerPush[i] && m_firstPushKey[i])
				{
					if (i == 0)
					{
						m_angle[1] += 1.f;
					}
					else if (i == 1)
					{
						m_angle[1] -= 1.f;
					}
					else if (i == 2)
					{
						m_angle[0] += 1.f;
					}
					else
					{
						m_angle[0] -= 1.f;
					}
					m_pTransformCom->Set_Rotation(m_angle[1], 0.f, m_angle[0]);
		_vec3					m_vDir;
		dynamic_cast<CPlayer*>(getPlayer->second)->Get_Transform_Component()->Get_Info(INFO_LOOK, &m_vDir);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
					//_vec3					m_vDir;
					//m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
					//D3DXVec3Normalize(&m_vDir, &m_vDir);
					//m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
					////m_pTransformCom->Set_Rotation(m_angle[0], m_angle[1], 0.f);
					check = true;
					break;
				}
				else
					check = false;
				/*			break;
						case KEY_UP:
							if (getPlayerPush[i]&& m_firstPushKey[i])
							{
								_vec3					m_vDir;
								m_pTransformCom->Set_Rotation(0.f, 0.f, 0.f);
								m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
								D3DXVec3Normalize(&m_vDir, &m_vDir);
								m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
							}
							else
								dynamic_cast<CPlayer*>(getPlayer->second)->Reset_Speed();
							break;
						case KEY_LEFT:
							if (getPlayerPush[i]&& m_firstPushKey[i])
							{
								_vec3					m_vDir;
								m_pTransformCom->Set_Rotation(0.f, -90.f, 0.f);
								m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
								D3DXVec3Normalize(&m_vDir, &m_vDir);
								m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
							}
							else
								dynamic_cast<CPlayer*>(getPlayer->second)->Reset_Speed();
							break;
						case KEY_RIGHT:
							if (getPlayerPush[i]&& m_firstPushKey[i])
							{
								_vec3					m_vDir;
								m_pTransformCom->Set_Rotation(0.f, 90.f, 0.f);
								m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
								D3DXVec3Normalize(&m_vDir, &m_vDir);
								m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
							}
							else
								dynamic_cast<CPlayer*>(getPlayer->second)->Reset_Speed();
						default:
							break;
						}*/
			}
		if(!check)
			dynamic_cast<CPlayer*>(getPlayer->second)->Reset_Speed();
	}
	else
	{
		auto getPlayer = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"Player_Layer")->begin();
		bool *getPlayerPush = dynamic_cast<CPlayer*>(getPlayer->second)->Get_PushKey();
		dynamic_cast<CPlayer*>(getPlayer->second)->Reset_Speed();

		m_isFirstColl = false;
		for (int i = 0; i < KEY_END; i++)
		{
			m_firstPushKey[i] = false;
		}
	}
		//isOpen = true;

	//if (isOpen)
	//{
		//_vec3					m_vDir;
		//m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
		//m_pTransformCom->Move_Pos(&m_vDir, -80.f, fTimeDelta);

		//_vec3 getPos;
		//m_pTransformCom->Get_Info(INFO_POS, &getPos);
		//if (getPos.z > 123)
		//{
		//	//isOpen = false;
		//	m_bDraw = false;
		//}
	//}
	return 0;
}

void CBall::Render_Object(void)
{
	if (false == m_bDraw)
		return;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

	//if (!_tcscmp(m_objectData.m_objectTextureName, L"Proto_Mesh_WallClear6.x") ||
	//	!_tcscmp(m_objectData.m_objectTextureName, L"Proto_Mesh_WallClear_Corner2.x") ||
	//	!_tcscmp(m_objectData.m_objectTextureName, L"Proto_Mesh_WallClear_Corner3.x") ||
	//	!_tcscmp(m_objectData.m_objectTextureName, L"Proto_Mesh_WallClear1.x") ||
	//	!_tcscmp(m_objectData.m_objectTextureName, L"Proto_Mesh_WallClear6.x") ||
	//	!_tcscmp(m_objectData.m_objectTextureName, L"Proto_Mesh_WallClear15.x"))
	//{
	//	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0xc0);

	//	//m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//	m_pMeshCom->Render_Meshes();

	//	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//	//m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//}
	//else
		m_pMeshCom->Render_Meshes();

	/*m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0xff);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);*/
	//m_pMeshCom->Render_Meshes();


		//const _matrix* getWorldMatrix = m_pTransformCom->Get_WorldMatrix();
		//_matrix getWorldMatrixTemp = *getWorldMatrix;
		//getWorldMatrixTemp._41 -= 5;
		//m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), &getWorldMatrixTemp);

		// @@@@@@@@안보이게 주석
		_matrix temp;
		D3DXMatrixIdentity(&temp);
		temp._11 = 0.05f;// m_pTransformCom->Get_WorldMatrix()->_11;
		temp._22 = 0.05f;// m_pTransformCom->Get_WorldMatrix()->_22;
		temp._33 = 0.05f;//m_pTransformCom->Get_WorldMatrix()->_33;
		temp._41 = m_pTransformCom->Get_WorldMatrix()->_41;
		temp._42 = m_pTransformCom->Get_WorldMatrix()->_42;
		temp._43 = m_pTransformCom->Get_WorldMatrix()->_43;

		m_pColliderSensorCom->Render_Collider(COLLTYPE(m_bSensorColl), &temp/* m_pTransformCom->Get_WorldMatrix()*/);

	//m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), m_pTransformCom->Get_NRotWorldMatrix());
}

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

HRESULT CBall::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// 메쉬
	pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(L"Proto_Mesh_Skeleton_Ball.x"));
	NULL_CHECK_RETURN(pComponent);
	Add_AddComponent(L"Com_Mesh", ID_DYNAMIC, pComponent);

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
	pComponent = m_pColliderSensorCom = CCollider::Create(m_pGraphicDev, m_pMeshCom->Get_VtxPos(), m_pMeshCom->Get_NumVtx(), m_pMeshCom->Get_VtxSize(),0,0,0);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_SensorCollider", pComponent);

	//// Optimization
	//pComponent = m_pOptimizationCom = dynamic_cast<COptimization*>(Clone_Proto(L"Proto_Optimization"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(L"Com_Optimization", pComponent);
	//
	return S_OK;

}

//void CLeftDoor::SetUp_OnTerrain(void)
//{
//	_vec3	vPos;
//	m_pTransformCom->Get_Info(INFO_POS, &vPos);
//
//	CTerrainTex*		pTerrainBufferCom = dynamic_cast<CTerrainTex*>(Engine::Get_Component(L"GameLogic_Layer", L"Terrain", L"Com_Buffer", ID_STATIC));
//	NULL_CHECK(pTerrainBufferCom);
//
//	const _vec3*	ptPos = pTerrainBufferCom->Get_VtxPos();
//
//
//	//_float		fHeight = m_pCalculatorCom->Compute_HeightOnTerrain(&vPos, pTerrainBufferCom->Get_VtxPos(), VTXCNTX, VTXCNTZ);
//	//m_pTransformCom->Set_Pos(vPos.x, fHeight, vPos.z);
//	m_pTransformCom->Set_Pos(vPos.x, vPos.y, vPos.z);
//}

CBall* CBall::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBall*	pInstance = new CBall(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CBall::Free(void)
{
	CGameObject::Free();
}
