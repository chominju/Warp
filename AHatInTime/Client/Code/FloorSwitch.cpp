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
	return S_OK;
}

Engine::_int CFloorSwitch::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	SetUp_OnTerrain();

	_vec3	vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);

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
	}
	return 0;
}

void CFloorSwitch::Render_Object(void)
{
	if (false == m_bDraw)
		return;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

		m_pMeshCom->Render_Meshes();

	
	m_pColliderSensorCom->Render_Collider(COLLTYPE(m_bSensorColl), m_pTransformCom->Get_WorldMatrix());

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


HRESULT CFloorSwitch::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// ¸Þ½¬
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

	
	return S_OK;

}

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
