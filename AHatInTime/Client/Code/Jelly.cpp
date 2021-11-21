#include "stdafx.h"
#include "Jelly.h"
#include "Player.h"
#include "SoundMgr.h"

#include "Export_Function.h"

CJelly::CJelly(LPDIRECT3DDEVICE9 pGraphicDev)
	: CInteractionObject(pGraphicDev)
	, m_speed(2.f)
{

}

CJelly::CJelly(const CJelly& rhs)
	: CInteractionObject(rhs)
{

}

CJelly::~CJelly(void)
{

}

HRESULT CJelly::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

Engine::_int CJelly::Update_Object(const _float& fTimeDelta)
{
	if (false == m_bDraw)
		return 0;

	CGameObject::Update_Object(fTimeDelta);

	SetUp_OnTerrain();

	if (m_bSensorColl)
	{
		if(m_bDraw)
			CSoundMgr::Get_Instance()->PlaySound(L"ItemEat.wav", CSoundMgr::PLAYER);
		auto getPlayer = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"Player_Layer")->begin();
		dynamic_cast<CPlayer*>(getPlayer->second)->Set_IsWrapSkillItem(true);
		m_bDraw = false;
	}


	Add_RenderGroup(RENDER_NONALPHA, this);
	
	return 0;
}

void CJelly::Render_Object(void)
{
	if (false == m_bDraw)
		return;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pMeshCom->Render_Meshes();

	m_pColliderSensorCom->Render_Collider(COLLTYPE(m_bSensorColl), m_pTransformCom->Get_WorldMatrix());
}

HRESULT CJelly::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// ¸Þ½¬
	pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(L"Proto_Mesh_Jelly.x"));
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
	pComponent = m_pColliderSensorCom = CCollider::Create(m_pGraphicDev, m_pMeshCom->Get_VtxPos(), m_pMeshCom->Get_NumVtx(), m_pMeshCom->Get_VtxSize(), -5, 0,-5);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_SensorCollider", pComponent);

	return S_OK;
}


CJelly* CJelly::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CJelly*	pInstance = new CJelly(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CJelly::Free(void)
{
	CGameObject::Free();
}
