#include "stdafx.h"
#include "Maze.h"

#include "Export_Function.h"

CMaze::CMaze(LPDIRECT3DDEVICE9 pGraphicDev)
	: CInteractionObject(pGraphicDev)
	, m_isMove(false)
	, m_isFloorSwitch(false)
{

}

CMaze::CMaze(const CMaze& rhs)
	: CInteractionObject(rhs)
{

}

CMaze::~CMaze(void)
{

}

HRESULT CMaze::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

Engine::_int CMaze::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	SetUp_OnTerrain();

	Add_RenderGroup(RENDER_NONALPHA, this);
	 
	// 1번 문
	if (!m_bSensorColl)
	{
		m_bDraw = true;
		_vec3 getPos;
		m_pTransformCom->Get_Info(INFO_POS, &getPos);
		if (getPos.y < -6.5f)
		{
			m_isMove = false;
		}
		else
		{
			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_RIGHT, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, -200.f, fTimeDelta);
		}
	}
	else
	{
		m_bDraw = true;
		
		_vec3 getPos;
		m_pTransformCom->Get_Info(INFO_POS, &getPos);
		if (getPos.y > 1.5f)
		{
			m_isMove = false;
		}
		else
		{
			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_RIGHT, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, +200.f, fTimeDelta);
		}
	}

	return 0;
}

void CMaze::Render_Object(void)
{
	if (false == m_bDraw)
		return;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

		m_pMeshCom->Render_Meshes();

	m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), m_pTransformCom->Get_WorldMatrix());
	m_pColliderSensorCom->Render_Collider(COLLTYPE(m_bSensorColl), m_pTransformCom->Get_WorldMatrix());

}

HRESULT CMaze::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// 메쉬
	pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(L"Proto_Mesh_Maze_Wall1.x"));
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
	pComponent = m_pColliderCom = CCollider::Create(m_pGraphicDev, m_pMeshCom->Get_VtxPos(), m_pMeshCom->Get_NumVtx(), m_pMeshCom->Get_VtxSize(),0,0,0);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Collider", pComponent);

	// SensorCollider
	pComponent = m_pColliderSensorCom = CCollider::Create(m_pGraphicDev, m_pMeshCom->Get_VtxPos(), m_pMeshCom->Get_NumVtx(), m_pMeshCom->Get_VtxSize(),50, 80, 80);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_SensorCollider", pComponent);

	return S_OK;

}

CMaze* CMaze::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMaze*	pInstance = new CMaze(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CMaze::Free(void)
{
	CGameObject::Free();
}
