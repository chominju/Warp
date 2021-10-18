#include "stdafx.h"
#include "Player.h"

#include "Export_Function.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pushKey{false,false,false,false,}
	, m_isKeyStop{ false,false,false,false }
{

}

CPlayer::CPlayer(const CPlayer& rhs)
	: CGameObject(rhs)
{

}

CPlayer::~CPlayer(void)
{

}

HRESULT CPlayer::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	FAILED_CHECK_RETURN(CGameObject::Ready_Object(), E_FAIL);

	m_pTransformCom->Set_Scale(0.05f, 0.05f, 0.05f);
	m_pTransformCom->Set_Pos(78.f, 0.f, 120.f);
	m_pTransformCom->Set_Rotation(0.f, 0.f, 0.f);
	
	//m_pNaviCom->Set_CellIndex(1);
	m_pMeshCom->Set_AnimationIndex(11);

	return S_OK;
}

Engine::_int CPlayer::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);
	
	m_pCalculatorCom->Collision_StaticObject(m_pSphereColliderCom, m_pushKey, m_isKeyStop);
	m_pCalculatorCom->Collision_InteractionObject(m_pSphereColliderCom, m_pushKey, m_isKeyStop);
	//Collision_ToObject();
	//if (Collision_ToObject(/*L"StaticObject_Layer", L"Static_Object"*/))
	//{
	//	int a;
	//	m_isKeyStop[KEY_DOWN];
	//	m_isKeyStop[KEY_UP];
	//	m_isKeyStop[KEY_LEFT];
	//	m_isKeyStop[KEY_RIGHT];
	//	a = 10;
	//}
	//if (Collision_ToObject(/*L"StaticObject_Layer", L"Static_Object"*/))
	//{
	//	for (int i = 0; i < KEY_END; i++)
	//	{
	//		m_isKeyStop[i] = m_pushKey[i];
	//	}
	//}
	//else
	//{
	//	for (int i = 0; i < KEY_END; i++)
	//	{
	//		m_isKeyStop[i] = false;
	//	}
	//}

	SetUp_OnTerrain();

	Key_Input(fTimeDelta);

	m_pMeshCom->Play_Animation(fTimeDelta);

	Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CPlayer::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

	//m_pNaviCom->Render_NaviMesh();

	m_pMeshCom->Render_Meshes();

	const _matrix* getTemp = m_pTransformCom->Get_WorldMatrix();
	_matrix newWorldMatrix = *getTemp;
	newWorldMatrix._42 += 3;
	
	m_pSphereColliderCom->Render_SphereCollider(&newWorldMatrix/*m_pTransformCom->Get_WorldMatrix()*/);
}

HRESULT CPlayer::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// DynamicMesh
	pComponent = m_pMeshCom = dynamic_cast<CDynamicMesh*>(Clone_Proto(L"Proto_Mesh_Player"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Mesh", pComponent);

	//// NaviMesh
	//pComponent = m_pNaviCom = dynamic_cast<CNaviMesh*>(Clone_Proto(L"Proto_Mesh_Navi"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(L"Com_Navi", pComponent);

	// Transform
	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
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
	pComponent = m_pSphereColliderCom = CSphereCollider::Create(m_pGraphicDev, 30);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_SphereCollider", pComponent);

	return S_OK;

}

void CPlayer::Key_Input(const _float& fTimeDelta)
{
	//m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);


	//if (Get_DIKeyState(DIK_UP) & 0x80)
	//{
	//	_vec3	vPos, vDir;
	//	m_pTransformCom->Get_Info(INFO_POS, &vPos);
	//	m_pTransformCom->Get_Info(INFO_LOOK, &vDir);
	//	D3DXVec3Normalize(&vDir, &vDir);

	///*	m_pTransformCom->Set_Pos(&m_pNaviCom->Move_OnNaviMesh(&vPos, &(vDir *fTimeDelta * 5.f)));
	//	m_pMeshCom->Set_AnimationIndex(11);*/
	//}
	

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pTransformCom->Set_Rotation(0.f, 180.f, 0.f);
		m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		if (!m_isKeyStop[KEY_DOWN])
		{
			m_pTransformCom->Move_Pos(&m_vDir, +10.f, fTimeDelta);
			//m_isKeyStop[KEY_UP] = false;
		}
		m_pushKey[KEY_DOWN] = true;
		m_pushKey[KEY_UP] = false;
		m_pushKey[KEY_LEFT] = false;
		m_pushKey[KEY_RIGHT] = false;
		m_pMeshCom->Set_AnimationIndex(11);
	}
	//else
	//	m_pushKey[KEY_DOWN] = false;

	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pTransformCom->Set_Rotation(0.f, 0.f, 0.f);
		m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		if (!m_isKeyStop[KEY_UP])
		{
			m_pTransformCom->Move_Pos(&m_vDir, +10.f, fTimeDelta);
			//m_isKeyStop[KEY_DOWN] = false;
		}
		m_pushKey[KEY_DOWN] = false;
		m_pushKey[KEY_UP] = true;
		m_pushKey[KEY_LEFT] = false;
		m_pushKey[KEY_RIGHT] = false;
		m_pMeshCom->Set_AnimationIndex(11);
	}
	//else
	//	m_pushKey[KEY_UP] = false;

	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pTransformCom->Set_Rotation(0.f, -90.f, 0.f);
		m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		if (!m_isKeyStop[KEY_LEFT])
		{
			m_pTransformCom->Move_Pos(&m_vDir, +10.f, fTimeDelta);
			//m_isKeyStop[KEY_RIGHT] = false;
		}
		m_pushKey[KEY_DOWN] = false;
		m_pushKey[KEY_UP] = false;
		m_pushKey[KEY_LEFT] = true;
		m_pushKey[KEY_RIGHT] = false;
		m_pMeshCom->Set_AnimationIndex(11);
	}
	/*else
		m_pushKey[KEY_LEFT] = false;*/

	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pTransformCom->Set_Rotation(0.f, 90.f, 0.f);
		m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		if (!m_isKeyStop[KEY_RIGHT])
		{
			m_pTransformCom->Move_Pos(&m_vDir, +10.f, fTimeDelta);
			//m_isKeyStop[KEY_LEFT] = false;
		}
		m_pushKey[KEY_DOWN] = false;
		m_pushKey[KEY_UP] = false;
		m_pushKey[KEY_LEFT] = false;
		m_pushKey[KEY_RIGHT] = true;
		m_pMeshCom->Set_AnimationIndex(11);
	}	
	else
		m_pMeshCom->Set_AnimationIndex(23);
	//else
	//	m_pushKey[KEY_RIGHT] = false;

	//if(m_pushKey[0]|| m_pushKey[1]|| m_pushKey[2]|| m_pushKey[3])
	//	m_pTransformCom->Move_Pos(&m_vDir, +10.f, fTimeDelta);
	/*if (Get_DIMouseState(DIM_LB) & 0X80)
	{
		_vec3	vPos = PickUp_OnTerrain();

		m_pTransformCom->Move_PickingPos(&vPos, 10.f, fTimeDelta);
	}*/

	if (Get_DIMouseState(DIM_RB) & 0X80)
	{
		m_pMeshCom->Set_AnimationIndex(11);
	}

	if(true == m_pMeshCom->Is_AnimationsetFinish())
		m_pMeshCom->Set_AnimationIndex(11);
}

void CPlayer::SetUp_OnTerrain(void)
{
	_vec3	vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);

	CTerrainTex*		pTerrainBufferCom = dynamic_cast<CTerrainTex*>(Engine::Get_Component(L"GameLogic_Layer", L"Terrain", L"Com_Buffer", ID_STATIC));
	NULL_CHECK(pTerrainBufferCom);

	const _vec3*	ptPos = pTerrainBufferCom->Get_VtxPos();


	//_float		fHeight = m_pCalculatorCom->Compute_HeightOnTerrain(&vPos, pTerrainBufferCom->Get_VtxPos(), VTXCNTX, VTXCNTZ);

	//m_pTransformCom->Set_Pos(vPos.x, fHeight, vPos.z);
}

_bool CPlayer::Collision_ToObject(/*const _tchar * pLayerTag, const _tchar * pObjTag*/)
{
	/*CCollider*		pObjectColliderCom = dynamic_cast<CCollider*>(Engine::Get_Component(pLayerTag, pObjTag, L"Com_Collider", ID_STATIC));
	NULL_CHECK_RETURN(pObjectColliderCom, false);*/

	/*return m_pCalculatorCom->Collision_AABB(pPlayerColliderCom->Get_Min(), pPlayerColliderCom->Get_Max(), pPlayerColliderCom->Get_CollWorldMatrix(),
	m_pColliderCom->Get_Min(), m_pColliderCom->Get_Max(), m_pColliderCom->Get_CollWorldMatrix());*/

	return m_pCalculatorCom->Collision_StaticObject(/*pObjectColliderCom->Get_Min(), pObjectColliderCom->Get_Max(), pObjectColliderCom->Get_CollWorldMatrix(),*/
		m_pSphereColliderCom , m_pushKey,m_isKeyStop);

}

//Engine::_vec3 CPlayer::PickUp_OnTerrain(void)
//{
//	CTerrainTex*		pTerrainBufferCom = dynamic_cast<CTerrainTex*>(Engine::Get_Component(L"GameLogic", L"Terrain", L"Com_Buffer", ID_STATIC));
//	NULL_CHECK_RETURN(pTerrainBufferCom, _vec3());
//
//	CTransform*		pTerrainTransCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"GameLogic", L"Terrain", L"Com_Transform", ID_DYNAMIC));
//	NULL_CHECK_RETURN(pTerrainTransCom, _vec3());
//
//	_vec3 temp{};
//	return temp;
//	//return m_pCalculatorCom->Picking_OnTerrain(g_hWnd, pTerrainBufferCom, pTerrainTransCom);
//}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer*	pInstance = new CPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CPlayer::Free(void)
{
	CGameObject::Free();
}

