#include "stdafx.h"
#include "EmptyObject.h"
#include "Ball.h"
#include "Player.h"

#include "Export_Function.h"

CEmptyObject::CEmptyObject(LPDIRECT3DDEVICE9 pGraphicDev)
	: CInteractionObject(pGraphicDev)
	, m_speed(2.f)
{

}

CEmptyObject::CEmptyObject(const CEmptyObject& rhs)
	: CInteractionObject(rhs)
{

}

CEmptyObject::~CEmptyObject(void)
{

}

HRESULT CEmptyObject::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	return S_OK;
}

Engine::_int CEmptyObject::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	SetUp_OnTerrain();

	Add_RenderGroup(RENDER_NONALPHA, this);

	// 플레이어랑 충돌했을 때
	auto getPlayer = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"Player_Layer")->begin();
	if (m_bSensorColl)
	{
		dynamic_cast<CPlayer*>(getPlayer->second)->Set_IsFrozenRoadOn(true);
	}
	else
	{
		dynamic_cast<CPlayer*>(getPlayer->second)->Set_IsFrozenRoadOn(false);
	}
	
	return 0;
}

void CEmptyObject::Render_Object(void)
{
	if (false == m_bDraw)
		return;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

	m_pColliderSensorCom->Render_Collider(COLLTYPE(m_bSensorColl), m_pTransformCom->Get_WorldMatrix());
}


HRESULT CEmptyObject::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// 메쉬
	pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(L"Proto_Mesh_Wall1.x"));
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

	// SensorCollider
	_vec3* temp;
	//temp
	pComponent = m_pColliderSensorCom = CCollider::Create(m_pGraphicDev, m_pMeshCom->Get_VtxPos(), 4/*m_pMeshCom->Get_NumVtx()*/, m_pMeshCom->Get_VtxSize(), 540, 0, 425);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_SensorCollider", pComponent);

	return S_OK;

}


CEmptyObject* CEmptyObject::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEmptyObject*	pInstance = new CEmptyObject(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CEmptyObject::Free(void)
{
	CGameObject::Free();
}
