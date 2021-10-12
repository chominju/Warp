#include "stdafx.h"
#include "Static_Object.h"

#include "Export_Function.h"

CStatic_Objects::CStatic_Objects(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_bDraw(true)
{

}

CStatic_Objects::CStatic_Objects(const CStatic_Objects& rhs)
	: CGameObject(rhs)
{

}

CStatic_Objects::~CStatic_Objects(void)
{

}

HRESULT CStatic_Objects::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(5.f, 0.f, 5.f);
	//m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(60.f));

	return S_OK;
}

Engine::_int CStatic_Objects::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	SetUp_OnTerrain();

	//m_bColl = Collision_ToObject(L"GameLogic", L"Player");

	_vec3	vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);

	//m_bDraw = m_pOptimizationCom->Isin_FrustumForObject(&vPos);

	Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CStatic_Objects::Render_Object(void)
{
	if (false == m_bDraw)
		return;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	
	if (!_tcscmp(m_objectData.m_objectTextureName , L"Proto_Mesh_WallClear6.x")||
		!_tcscmp(m_objectData.m_objectTextureName, L"Proto_Mesh_WallClear_Corner2.x") || 
		!_tcscmp(m_objectData.m_objectTextureName, L"Proto_Mesh_WallClear_Corner3.x") || 
		!_tcscmp(m_objectData.m_objectTextureName, L"Proto_Mesh_WallClear1.x") || 
		!_tcscmp(m_objectData.m_objectTextureName, L"Proto_Mesh_WallClear6.x") || 
		!_tcscmp(m_objectData.m_objectTextureName, L"Proto_Mesh_WallClear15.x"))
	{
		m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0xc0);

		//m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		m_pMeshCom->Render_Meshes();

		m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		//m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
	else
		m_pMeshCom->Render_Meshes();
	
	/*m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0xff);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);*/
	//m_pMeshCom->Render_Meshes();

	
	m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), m_pTransformCom->Get_WorldMatrix());

	//m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), m_pTransformCom->Get_NRotWorldMatrix());
}

void CStatic_Objects::Set_StaticMesh_Component(const _tchar* pMeshProtoTag)
{
	// ¸Þ½¬
	CComponent*			pComponent = nullptr;
	pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(pMeshProtoTag));
	NULL_CHECK_RETURN(pComponent);
	Add_AddComponent(L"Com_Mesh", ID_DYNAMIC, pComponent);

	pComponent = m_pColliderCom = CCollider::Create(m_pGraphicDev, m_pMeshCom->Get_VtxPos(), m_pMeshCom->Get_NumVtx(), m_pMeshCom->Get_VtxSize());
	NULL_CHECK_RETURN(pComponent);
	m_mapComponent[ID_STATIC].emplace(L"Com_Collider", pComponent);
}

void CStatic_Objects::Set_Static_Objects_Data(Object_Data objectData)
{
	_tcscpy_s(m_objectData.m_objectTextureName, _countof(m_objectData.m_objectTextureName), objectData.m_objectTextureName);

	m_objectData.m_pos[INFO_POS].x = objectData.m_pos[INFO_POS].x;
	m_objectData.m_pos[INFO_POS].y = objectData.m_pos[INFO_POS].y;
	m_objectData.m_pos[INFO_POS].z = objectData.m_pos[INFO_POS].z;

	m_objectData.m_vAngle.x = objectData.m_vAngle.x;
	m_objectData.m_vAngle.y = objectData.m_vAngle.y;
	m_objectData.m_vAngle.z = objectData.m_vAngle.z;

	m_objectData.m_vScale.x = objectData.m_vScale.x;
	m_objectData.m_vScale.y = objectData.m_vScale.y;
	m_objectData.m_vScale.z = objectData.m_vScale.z;

	m_objectData.m_objectIndex = objectData.m_objectIndex;
}

HRESULT CStatic_Objects::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

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

	//// Calculator
	//pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(L"Proto_Calculator"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_DYNAMIC].emplace(L"Com_Calculator", pComponent);

	// Collider
	/*pComponent = m_pColliderCom = CCollider::Create(m_pGraphicDev, m_pMeshCom->Get_VtxPos(), m_pMeshCom->Get_NumVtx(), m_pMeshCom->Get_VtxSize());
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Collider", pComponent);*/

	//// Optimization
	//pComponent = m_pOptimizationCom = dynamic_cast<COptimization*>(Clone_Proto(L"Proto_Optimization"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(L"Com_Optimization", pComponent);
	//
	return S_OK;

}

void CStatic_Objects::SetUp_OnTerrain(void)
{
	_vec3	vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);

	CTerrainTex*		pTerrainBufferCom = dynamic_cast<CTerrainTex*>(Engine::Get_Component(L"GameLogic", L"Terrain", L"Com_Buffer", ID_STATIC));
	NULL_CHECK(pTerrainBufferCom);

	const _vec3*	ptPos = pTerrainBufferCom->Get_VtxPos();


	//_float		fHeight = m_pCalculatorCom->Compute_HeightOnTerrain(&vPos, pTerrainBufferCom->Get_VtxPos(), VTXCNTX, VTXCNTZ);
	//m_pTransformCom->Set_Pos(vPos.x, fHeight, vPos.z);
	m_pTransformCom->Set_Pos(vPos.x, vPos.y, vPos.z);
}

Engine::_bool CStatic_Objects::Collision_ToObject(const _tchar* pLayerTag, const _tchar* pObjTag)
{
	CCollider*		pPlayerColliderCom = dynamic_cast<CCollider*>(Engine::Get_Component(pLayerTag, pObjTag, L"Com_Collider", ID_STATIC));
	NULL_CHECK_RETURN(pPlayerColliderCom, false);

	/*return m_pCalculatorCom->Collision_AABB(pPlayerColliderCom->Get_Min(), pPlayerColliderCom->Get_Max(), pPlayerColliderCom->Get_CollWorldMatrix(),
											m_pColliderCom->Get_Min(), m_pColliderCom->Get_Max(), m_pColliderCom->Get_CollWorldMatrix());*/

	return true;
	//return m_pCalculatorCom->Collision_OBB(pPlayerColliderCom->Get_Min(), pPlayerColliderCom->Get_Max(), pPlayerColliderCom->Get_CollWorldMatrix(),
	//	m_pColliderCom->Get_Min(), m_pColliderCom->Get_Max(), m_pColliderCom->Get_CollWorldMatrix());

}

CStatic_Objects* CStatic_Objects::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CStatic_Objects*	pInstance = new CStatic_Objects(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CStatic_Objects::Free(void)
{
	CGameObject::Free();
}

