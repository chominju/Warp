#include "stdafx.h"
#include "RightDoor.h"

#include "Export_Function.h"

CRightDoor::CRightDoor(LPDIRECT3DDEVICE9 pGraphicDev)
	: CInteractionObject(pGraphicDev)
	,m_isOpen(false)
	, m_isFloorSwitch(false)
{

}

CRightDoor::CRightDoor(const CRightDoor& rhs)
	: CInteractionObject(rhs)
{

}

CRightDoor::~CRightDoor(void)
{

}

HRESULT CRightDoor::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

Engine::_int CRightDoor::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	SetUp_OnTerrain();

	// 1번 문
	if (m_bSensorColl)
		m_isOpen = true;

	if (m_doorOption == 1 || m_doorOption == 3)
	{
		if (m_isOpen)
		{
			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, +80.f, fTimeDelta);

			_vec3 getPos;
			m_pTransformCom->Get_Info(INFO_POS, &getPos);
			if (getPos.z < 117)
			{
				m_isOpen = false;
				m_bDraw = false;
			}
		}
	}

	// 2번 문 
	if (m_doorOption == 2 && m_isFloorSwitch)
	{
		_vec3 getPos;
		m_pTransformCom->Get_Info(INFO_POS, &getPos);
		if (getPos.z >= 117)
		{
			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, +80.f, fTimeDelta);
		}
		else
			m_bDraw = false;


	}
	else if (m_doorOption == 2)
	{
		m_bDraw = true;
		_vec3 getPos;
		m_pTransformCom->Get_Info(INFO_POS, &getPos);
		if (getPos.z < m_firstPos.z)
		{
			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, -80.f, fTimeDelta);
		}

	}

	if (m_doorOption == 4 && m_isFloorSwitch)
	{
		_vec3 getPos;
		m_pTransformCom->Get_Info(INFO_POS, &getPos);
		if (getPos.z >= (m_firstPos.z - 2.5))
		{
			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, 80.f, fTimeDelta);
		}
		else
			m_bDraw = false;
	}
	else if (m_doorOption == 4)
	{
		m_bDraw = true;
		_vec3 getPos;
		m_pTransformCom->Get_Info(INFO_POS, &getPos);
		if (getPos.z < m_firstPos.z)
		{
			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, -80.f, fTimeDelta);
		}

	}

	if (m_doorOption == 5)
	{
		if (m_isFloorSwitch)
		{
				_vec3					m_vDir;
				m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
				m_pTransformCom->Move_Pos(&m_vDir, 80.f, fTimeDelta);

				_vec3 getPos;
				m_pTransformCom->Get_Info(INFO_POS, &getPos);
				if (getPos.x > 117)
				{
					m_isOpen = false;
					m_bDraw = false;
				}
		}

	}


	if (m_doorOption == 6)
	{
		if (m_isOpen)
		{
			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, 80.f, fTimeDelta);

			_vec3 getPos;
			m_pTransformCom->Get_Info(INFO_POS, &getPos);
			if (getPos.z < 182)
			{
				m_isOpen = false;
				m_bDraw = false;
			}
		}
	}

	if (m_doorOption == 7)
	{
		if (m_isFloorSwitch)
		{

			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, 80.f, fTimeDelta);

			_vec3 getPos;
			m_pTransformCom->Get_Info(INFO_POS, &getPos);
			if (getPos.z < 182)
			{
				m_isOpen = false;
				m_bDraw = false;
			}
		}
	}

	Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CRightDoor::Render_Object(void)
{
	if (false == m_bDraw)
		return;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

	m_pMeshCom->Render_Meshes();

	m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), m_pTransformCom->Get_WorldMatrix());
	m_pColliderSensorCom->Render_Collider(COLLTYPE(m_bSensorColl), m_pTransformCom->Get_WorldMatrix());
	
}


HRESULT CRightDoor::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// 메쉬
	pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(L"Proto_Mesh_DoorClearRight.x"));
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
	pComponent = m_pColliderSensorCom = CCollider::Create(m_pGraphicDev, m_pMeshCom->Get_VtxPos(), m_pMeshCom->Get_NumVtx(), m_pMeshCom->Get_VtxSize(), 70, 0, 50);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_SensorCollider", pComponent);

	return S_OK;

}


CRightDoor* CRightDoor::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRightDoor*	pInstance = new CRightDoor(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CRightDoor::Free(void)
{
	CGameObject::Free();
}
