#include "stdafx.h"
#include "Conveyor.h"
#include "LeftDoor.h"
#include "RightDoor.h"
#include "Ball.h"
#include "Player.h"

#include "Export_Function.h"

CConveyor::CConveyor(LPDIRECT3DDEVICE9 pGraphicDev)
	: CInteractionObject(pGraphicDev)
	, m_speed(2.f)
{

}

CConveyor::CConveyor(const CConveyor& rhs)
	: CInteractionObject(rhs)
{

}

CConveyor::~CConveyor(void)
{

}

HRESULT CConveyor::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

Engine::_int CConveyor::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	SetUp_OnTerrain();

	_vec3	vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);

	Add_RenderGroup(RENDER_NONALPHA, this);

	if (m_bSensorColl)
	{
		auto getPlayer = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"Player_Layer")->begin();
		bool *getPlayerPush = dynamic_cast<CPlayer*>(getPlayer->second)->Get_PushKey();
		_vec3					m_vDir={ -1,0,0 };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		dynamic_cast<CPlayer*>(getPlayer->second)->Get_Transform_Component()->Move_Pos(&m_vDir, m_speed, fTimeDelta);
		dynamic_cast<CPlayer*>(getPlayer->second)->Set_Speed(6);
	}
	
	return 0;
}

void CConveyor::Render_Object(void)
{
	if (false == m_bDraw)
		return;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
		m_pMeshCom->Render_Meshes();

	m_pColliderSensorCom->Render_Collider(COLLTYPE(m_bSensorColl), m_pTransformCom->Get_WorldMatrix());
}


HRESULT CConveyor::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// ¸Þ½¬
	pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(L"Proto_Mesh_Conveyor1.x"));
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
	pComponent = m_pColliderSensorCom = CCollider::Create(m_pGraphicDev, m_pMeshCom->Get_VtxPos(), m_pMeshCom->Get_NumVtx(), m_pMeshCom->Get_VtxSize(),-40,0,-10);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_SensorCollider", pComponent);

	return S_OK;

}


CConveyor* CConveyor::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CConveyor*	pInstance = new CConveyor(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CConveyor::Free(void)
{
	CGameObject::Free();
}
