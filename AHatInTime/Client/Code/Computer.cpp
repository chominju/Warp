#include "stdafx.h"
#include "Computer.h"
#include "Ball.h"
#include "Player.h"

#include "Export_Function.h"

CComputer::CComputer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CInteractionObject(pGraphicDev)
	, m_speed(2.f)
{

}

CComputer::CComputer(const CComputer& rhs)
	: CInteractionObject(rhs)
{

}

CComputer::~CComputer(void)
{

}

HRESULT CComputer::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	//m_pTransformCom->Set_Pos(89.f, 0.f, 126.f);
	//m_pTransformCom->Set_Rotation(0.f, 90.f, 0.f);
	//m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(60.f));

	return S_OK;
}

Engine::_int CComputer::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	SetUp_OnTerrain();
	//m_bColl
	//m_bColl = Collision_ToPlayer(L"Player_Layer", L"Player");

	//if (m_bColl)
	//{
	//	CManagement::GetInstance()->Get_Scene()->Get_MapLayer(L"Player_Layer", L"Player",0);
	//	//CPlayer * getPlayer = CManagement::GetInstance()
	//	// �÷��̾� ����
	//}

	_vec3	vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);

	//m_bDraw = m_pOptimizationCom->Isin_FrustumForObject(&vPos);

	Add_RenderGroup(RENDER_NONALPHA, this);

	//IsCollisionBall();

	//if (m_bSensorColl)
	//{
	//	auto getPlayer = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"Player_Layer")->begin();
	//	bool *getPlayerPush = dynamic_cast<CPlayer*>(getPlayer->second)->Get_PushKey();
	//	dynamic_cast<CPlayer*>(getPlayer->second)->Set_Speed(m_speed);
	//}
	
	return 0;
}

void CComputer::Render_Object(void)
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


		//const _matrix* getWorldMatrix = m_pTransformCom->Get_WorldMatrix();
		//_matrix getWorldMatrixTemp = *getWorldMatrix;
		//getWorldMatrixTemp._41 -= 5;
		//m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), &getWorldMatrixTemp);

		// @@@@@@@@�Ⱥ��̰� �ּ�
		m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), m_pTransformCom->Get_WorldMatrix());

	//m_pColliderCom->Render_Collider(COLLTYPE(m_bColl), m_pTransformCom->Get_NRotWorldMatrix());
}

//void CConveyor::IsCollisionBall()
//{
//	auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");
//
//	for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
//	{
//		if (iter->first == L"Ball")
//			m_targetBall = iter->second;
//	}
//
//	auto ballColl = dynamic_cast<CBall*>(m_targetBall)->Get_ColliderSensor_Component();
//	if (m_pCalculatorCom->Collision_AABB(ballColl->Get_Min(), ballColl->Get_Max(), ballColl->Get_CollWorldMatrix(),
//		m_pColliderSensorCom->Get_Min(), m_pColliderSensorCom->Get_Max(), m_pColliderSensorCom->Get_CollWorldMatrix()))
//		m_isBallColl = true;
//	else
//		m_isBallColl = false;
//}

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

HRESULT CComputer::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// �޽�
	pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(L"Proto_Mesh_Computer.x"));
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

	//// Optimization
	//pComponent = m_pOptimizationCom = dynamic_cast<COptimization*>(Clone_Proto(L"Proto_Optimization"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(L"Com_Optimization", pComponent);
	//
	return S_OK;

}


CComputer* CComputer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CComputer*	pInstance = new CComputer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CComputer::Free(void)
{
	CGameObject::Free();
}