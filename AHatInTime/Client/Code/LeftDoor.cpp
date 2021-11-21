#include "stdafx.h"
#include "LeftDoor.h"
#include "SoundMgr.h"

#include "Export_Function.h"

CLeftDoor::CLeftDoor(LPDIRECT3DDEVICE9 pGraphicDev)
	: CInteractionObject(pGraphicDev)
	, m_isOpen(false)
	, m_isFloorSwitch(false)
	, m_isSound(false)
	, m_isBackSound(true)
{

}

CLeftDoor::CLeftDoor(const CLeftDoor& rhs)
	: CInteractionObject(rhs)
{

}

CLeftDoor::~CLeftDoor(void)
{

}

HRESULT CLeftDoor::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

Engine::_int CLeftDoor::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	SetUp_OnTerrain();

	Add_RenderGroup(RENDER_NONALPHA, this);
	 
	// 1번 문
	if (m_bSensorColl)
		m_isOpen = true;

	if (m_doorOption == 1 || m_doorOption == 3)
	{
		if (m_isOpen)
		{
			if(!m_isSound)
				CSoundMgr::Get_Instance()->PlaySound(L"Door_Open.ogg", CSoundMgr::PLAYER);
			m_isSound = true;
			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, -80.f, fTimeDelta);

			_vec3 getPos;
			m_pTransformCom->Get_Info(INFO_POS, &getPos);
			if (getPos.z > 123)
			{
				m_isOpen = false;
				m_bDraw = false;
			}
		}
	}

	// 2번 문 
	if (m_doorOption == 2 && m_isFloorSwitch)
	{
		if (!m_isSound)
			CSoundMgr::Get_Instance()->PlaySound(L"Door_Open.ogg", CSoundMgr::PLAYER);
		m_isSound = true;
		m_isBackSound = false;

		_vec3 getPos;
		m_pTransformCom->Get_Info(INFO_POS, &getPos);
		if (getPos.z <= 123)
		{
		_vec3					m_vDir;
		m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
		m_pTransformCom->Move_Pos(&m_vDir, -80.f, fTimeDelta);
		}
		else
			m_bDraw = false;


	}
	else if(m_doorOption==2)
	{
		if (!m_isBackSound)
			CSoundMgr::Get_Instance()->PlaySound(L"Door_Open.ogg", CSoundMgr::PLAYER);
		m_isSound = false;
		m_isBackSound = true;

		m_bDraw = true;
		_vec3 getPos;
		m_pTransformCom->Get_Info(INFO_POS, &getPos);
		if (getPos.z > m_firstPos.z)
		{
			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, 80.f, fTimeDelta);
		}

	}

	if (m_doorOption == 4 && m_isFloorSwitch)
	{
		if (!m_isSound)
			CSoundMgr::Get_Instance()->PlaySound(L"Door_Open.ogg", CSoundMgr::PLAYER);
		m_isSound = true;
		m_isBackSound = false;

		_vec3 getPos;
		m_pTransformCom->Get_Info(INFO_POS, &getPos);
		if (getPos.z <= (m_firstPos.z +2.5))
		{
			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, -80.f, fTimeDelta);
		}
		else
			m_bDraw = false;
	}
	else if (m_doorOption == 4)
	{
		if (!m_isBackSound)
			CSoundMgr::Get_Instance()->PlaySound(L"Door_Open.ogg", CSoundMgr::PLAYER);
		m_isSound = false;
		m_isBackSound = true;

		m_bDraw = true;
		_vec3 getPos;
		m_pTransformCom->Get_Info(INFO_POS, &getPos);
		if (getPos.z > m_firstPos.z)
		{
			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, 80.f, fTimeDelta);
		}

	}


	if (m_doorOption == 5)
	{
		if (m_isFloorSwitch)
		{
			if (!m_isSound)
				CSoundMgr::Get_Instance()->PlaySound(L"Door_Open.ogg", CSoundMgr::PLAYER);
			m_isSound = true;

			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, -80.f, fTimeDelta);

			_vec3 getPos;
			m_pTransformCom->Get_Info(INFO_POS, &getPos);
			if (getPos.x < 111)
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
			if (!m_isSound)
				CSoundMgr::Get_Instance()->PlaySound(L"Door_Open.ogg", CSoundMgr::PLAYER);
			m_isSound = true;

			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, -80.f, fTimeDelta);

			_vec3 getPos;
			m_pTransformCom->Get_Info(INFO_POS, &getPos);
			if (getPos.z > 188)
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
			if (!m_isSound)
				CSoundMgr::Get_Instance()->PlaySound(L"Door_Open.ogg", CSoundMgr::PLAYER);
			m_isSound = true;

			_vec3					m_vDir;
			m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
			m_pTransformCom->Move_Pos(&m_vDir, -80.f, fTimeDelta);

			_vec3 getPos;
			m_pTransformCom->Get_Info(INFO_POS, &getPos);
			if (getPos.z > 188)
			{
				m_isOpen = false;
				m_bDraw = false;
			}
		}
	}





	return 0;
}

void CLeftDoor::Render_Object(void)
{
	if (false == m_bDraw)
		return;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

	m_pMeshCom->Render_Meshes();

	m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), m_pTransformCom->Get_WorldMatrix());
	m_pColliderSensorCom->Render_Collider(COLLTYPE(m_bSensorColl), m_pTransformCom->Get_WorldMatrix());

}



HRESULT CLeftDoor::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// 메쉬
	pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(L"Proto_Mesh_DoorClearLeft.x"));
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
	pComponent = m_pColliderSensorCom = CCollider::Create(m_pGraphicDev, m_pMeshCom->Get_VtxPos(), m_pMeshCom->Get_NumVtx(), m_pMeshCom->Get_VtxSize(),70, 0, 50);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_SensorCollider", pComponent);

	return S_OK;
}

CLeftDoor* CLeftDoor::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLeftDoor*	pInstance = new CLeftDoor(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CLeftDoor::Free(void)
{
	CGameObject::Free();
}
