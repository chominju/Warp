#include "stdafx.h"
#include "HeavyMetal_Barrel.h"
#include "Ball.h"
#include "Player.h"

#include "Export_Function.h"

CHeavyMetal_Barrel::CHeavyMetal_Barrel(LPDIRECT3DDEVICE9 pGraphicDev)
	: CInteractionObject(pGraphicDev)
	, m_speed(10.f)
	, m_isSound(false)
{

}

CHeavyMetal_Barrel::CHeavyMetal_Barrel(const CHeavyMetal_Barrel& rhs)
	: CInteractionObject(rhs)
{

}

CHeavyMetal_Barrel::~CHeavyMetal_Barrel(void)
{

}

HRESULT CHeavyMetal_Barrel::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_isObject_PlayerHide = true;

	return S_OK;
}

Engine::_int CHeavyMetal_Barrel::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	SetUp_OnTerrain();

	_vec3	vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);

	Add_RenderGroup(RENDER_NONALPHA, this);

	if (m_isObject_PlayerWarpMove)
	{
		if (!m_isObject_PlayerWarpMoveFirst)
		{
			auto getPlayer = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"Player_Layer")->begin();
			dynamic_cast<CPlayer*>(getPlayer->second)->Get_Transform_Component()->Get_Info(INFO_LOOK, &m_vDir);
			auto playerLastKey = dynamic_cast<CPlayer*>(getPlayer->second)->Get_LastPushKey();
			D3DXVec3Normalize(&m_vDir, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, 200, fTimeDelta);

			m_pTransformCom->Update_Component(fTimeDelta);
			m_isObject_PlayerWarpMoveFirst = true;
		}
		else
		{
			if (!m_pCalculatorCom->Collision_Object_StaticObject(m_pColliderCom))
			{
				if (!m_isSound)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"Button.ogg", CSoundMgr::PLAYER);
					m_isSound = true;
				}
				
				m_pTransformCom->Move_Pos(&m_vDir, m_speed, fTimeDelta);
			}
			else
			{
				m_isSound = false;
				m_isObject_PlayerWarpMove = false;
				m_isObject_PlayerWarpMoveFirst = false;
			}
		}
	}
	return 0;
}

void CHeavyMetal_Barrel::Render_Object(void)
{
	if (false == m_bDraw)
		return;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

		m_pMeshCom->Render_Meshes();

		m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), m_pTransformCom->Get_WorldMatrix());
}

HRESULT CHeavyMetal_Barrel::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// ¸Þ½¬
	pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(L"Proto_Mesh_HeavyMetal_Barrel.x"));
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

	return S_OK;

}


CHeavyMetal_Barrel* CHeavyMetal_Barrel::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHeavyMetal_Barrel*	pInstance = new CHeavyMetal_Barrel(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CHeavyMetal_Barrel::Free(void)
{
	CGameObject::Free();
}
