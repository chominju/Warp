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

	return S_OK;
}

Engine::_int CBall::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	SetUp_OnTerrain();

	_vec3	vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);


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

					check = true;
					break;
				}
				else
					check = false;
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
	
	return 0;
}

void CBall::Render_Object(void)
{
	if (false == m_bDraw)
		return;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

	
		m_pMeshCom->Render_Meshes();

	
		_matrix temp;
		D3DXMatrixIdentity(&temp);
		temp._11 = 0.05f;
		temp._22 = 0.05f;
		temp._33 = 0.05f;
		temp._41 = m_pTransformCom->Get_WorldMatrix()->_41;
		temp._42 = m_pTransformCom->Get_WorldMatrix()->_42;
		temp._43 = m_pTransformCom->Get_WorldMatrix()->_43;

		m_pColliderSensorCom->Render_Collider(COLLTYPE(m_bSensorColl), &temp);

}


HRESULT CBall::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// ¸Þ½¬
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

	return S_OK;

}

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
