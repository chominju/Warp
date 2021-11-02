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

	//m_pTransformCom->Set_Pos(89.f, 0.f, 126.f);
	//m_pTransformCom->Set_Rotation(0.f, 90.f, 0.f);
	//m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(60.f));

	return S_OK;
}

Engine::_int CRightDoor::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	SetUp_OnTerrain();

	//if (m_bColl)
	//	isOpen = true;

	//if (isOpen)
	//{
	//	_vec3					m_vDir;
	//	m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
	//	m_pTransformCom->Move_Pos(&m_vDir, +80.f, fTimeDelta);

	//	_vec3 getPos;
	//	m_pTransformCom->Get_Info(INFO_POS, &getPos);
	//	if (getPos.z < 117)
	//	{
	//		isOpen = false;
	//		m_bDraw = false;
	//	}
	//}
	////m_bColl = Collision_ToPlayer(L"Player_Layer", L"Player");

	////if (m_bColl)
	////{
	////	CManagement::GetInstance()->Get_Scene()->Get_MapLayer(L"Player_Layer", L"Player",0);
	////	//CPlayer * getPlayer = CManagement::GetInstance()
	////	// �÷��̾� ����
	////}

	//_vec3	vPos;
	//m_pTransformCom->Get_Info(INFO_POS, &vPos);

	////m_bDraw = m_pOptimizationCom->Isin_FrustumForObject(&vPos);

	// 1�� ��
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

	// 2�� �� 
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

	/*if (m_doorOption == 7)
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

	if (m_doorOption == 5)
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
	}*/

	Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CRightDoor::Render_Object(void)
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



	// @@@@@@@@�Ⱥ��̰� �ּ�
	m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), m_pTransformCom->Get_WorldMatrix());
	m_pColliderSensorCom->Render_Collider(COLLTYPE(m_bSensorColl), m_pTransformCom->Get_WorldMatrix());
	
	
	
	//m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), m_pTransformCom->Get_NRotWorldMatrix());
}

//void CLeftDoor::Set_StaticMesh_Component(const _tchar* pMeshProtoTag)
//{
//	// �޽�
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

HRESULT CRightDoor::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// �޽�
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
