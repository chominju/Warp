#include "stdafx.h"
#include "FloorSwitch.h"
#include "LeftDoor.h"
#include "RightDoor.h"
#include "Ball.h"
#include "HeavyMetal_Barrel.h"

#include "Export_Function.h"

CFloorSwitch::CFloorSwitch(LPDIRECT3DDEVICE9 pGraphicDev)
	: CInteractionObject(pGraphicDev)
	, m_isBallColl(false)
	, m_isObjectColl(false)
	, m_timer(0.f)
{

}

CFloorSwitch::CFloorSwitch(const CFloorSwitch& rhs)
	: CInteractionObject(rhs)
{

}

CFloorSwitch::~CFloorSwitch(void)
{

}

HRESULT CFloorSwitch::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//m_pTransformCom->Set_Pos(89.f, 0.f, 126.f);
	//m_pTransformCom->Set_Rotation(0.f, 90.f, 0.f);
	//m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(60.f));

	return S_OK;
}

Engine::_int CFloorSwitch::Update_Object(const _float& fTimeDelta)
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

	m_timer += fTimeDelta;
	if (m_timer > 1.f)
	{
		if (m_switchOption == 1)
		{
			IsCollisionBall();
			if (m_bSensorColl || m_isBallColl)
			{
				auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");

				for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
				{
					if (iter->first == L"LeftDoor2")
						dynamic_cast<CLeftDoor*>(iter->second)->Set_FloorSwitch(true);

					if (iter->first == L"RightDoor2")
						dynamic_cast<CRightDoor*>(iter->second)->Set_FloorSwitch(true);
				}

			}
			else
			{
				auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");

				for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
				{
					if (iter->first == L"LeftDoor2")
						dynamic_cast<CLeftDoor*>(iter->second)->Set_FloorSwitch(false);

					if (iter->first == L"RightDoor2")
						dynamic_cast<CRightDoor*>(iter->second)->Set_FloorSwitch(false);
				}
			}
		}

		if (m_switchOption == 2 || m_switchOption == 3)
		{
			IsCollisionObject();

			auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");
			_bool Switch2 = false;
			_bool Switch3 = false;
			_bool Switch22 = false;
			_bool Switch33 = false;
			for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
			{
				if (iter->first == L"FloorSwitch2")
				{
					Switch2 = dynamic_cast<CFloorSwitch*>(iter->second)->Get_IsObjectColl();
					Switch22 = dynamic_cast<CFloorSwitch*>(iter->second)->Get_IsSensorColl();
				}

				if (iter->first == L"FloorSwitch3")
				{

					Switch3 = dynamic_cast<CFloorSwitch*>(iter->second)->Get_IsObjectColl();
					Switch33 = dynamic_cast<CFloorSwitch*>(iter->second)->Get_IsSensorColl();
				}
			}

			if ((Switch2 || Switch22) && (Switch3 || Switch33))
			{
				for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
				{
					if (iter->first == L"LeftDoor4")
						dynamic_cast<CLeftDoor*>(iter->second)->Set_FloorSwitch(true);

					if (iter->first == L"RightDoor4")
						dynamic_cast<CRightDoor*>(iter->second)->Set_FloorSwitch(true);
				}
			}
			else
			{
				for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
				{
					if (iter->first == L"LeftDoor4")
						dynamic_cast<CLeftDoor*>(iter->second)->Set_FloorSwitch(false);

					if (iter->first == L"RightDoor4")
						dynamic_cast<CRightDoor*>(iter->second)->Set_FloorSwitch(false);
				}
			}

		}



		/*if (isOpen)
		{
			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, -80.f, fTimeDelta);

			_vec3 getPos;
			m_pTransformCom->Get_Info(INFO_POS, &getPos);
			if (getPos.z > 123)
			{
				isOpen = false;
				m_bDraw = false;
			}
		}*/
	}
	return 0;
}

void CFloorSwitch::Render_Object(void)
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

		//// @@@@@@@@안보이게 주석
	m_pColliderSensorCom->Render_Collider(COLLTYPE(m_bSensorColl), m_pTransformCom->Get_WorldMatrix());

	//m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), m_pTransformCom->Get_NRotWorldMatrix());
}

void CFloorSwitch::IsCollisionBall()
{
	auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");

	for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
	{
		if (iter->first == L"Ball")
			m_targetBall = iter->second;
	}

	auto ballColl = dynamic_cast<CBall*>(m_targetBall)->Get_ColliderSensor_Component();
	if (m_pCalculatorCom->Collision_AABB(ballColl->Get_Min(), ballColl->Get_Max(), ballColl->Get_CollWorldMatrix(),
		m_pColliderSensorCom->Get_Min(), m_pColliderSensorCom->Get_Max(), m_pColliderSensorCom->Get_CollWorldMatrix()))
		m_isBallColl = true;
	else
		m_isBallColl = false;
}

void CFloorSwitch::IsCollisionObject()
{
	auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");

	for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
	{
		if (iter->first == L"HeavyMetal_Barrel1")
			m_targetBall = iter->second;
	}

	auto ballColl = dynamic_cast<CHeavyMetal_Barrel*>(m_targetBall)->Get_Collider_Component();
	if (m_pCalculatorCom->Collision_AABB(ballColl->Get_Min(), ballColl->Get_Max(), ballColl->Get_CollWorldMatrix(),
		m_pColliderSensorCom->Get_Min(), m_pColliderSensorCom->Get_Max(), m_pColliderSensorCom->Get_CollWorldMatrix()))
		m_isObjectColl = true;
	else
		m_isObjectColl = false;




	for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
	{
		if (iter->first == L"HeavyMetal_Barrel2")
			m_targetBall = iter->second;
	}

	ballColl = dynamic_cast<CHeavyMetal_Barrel*>(m_targetBall)->Get_Collider_Component();
	if (m_pCalculatorCom->Collision_AABB(ballColl->Get_Min(), ballColl->Get_Max(), ballColl->Get_CollWorldMatrix(),
		m_pColliderSensorCom->Get_Min(), m_pColliderSensorCom->Get_Max(), m_pColliderSensorCom->Get_CollWorldMatrix()))
		m_isObjectColl = true;
	if (!m_isObjectColl)
		m_isObjectColl = false;



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

HRESULT CFloorSwitch::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// 메쉬
	pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(L"Proto_Mesh_Floorswitch.x"));
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
	pComponent = m_pColliderSensorCom = CCollider::Create(m_pGraphicDev, m_pMeshCom->Get_VtxPos(), m_pMeshCom->Get_NumVtx(), m_pMeshCom->Get_VtxSize(),-30,0,-30);
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

CFloorSwitch* CFloorSwitch::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFloorSwitch*	pInstance = new CFloorSwitch(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CFloorSwitch::Free(void)
{
	CGameObject::Free();
}
