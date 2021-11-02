#include "stdafx.h"
#include "PlayerAim.h"
#include "Player.h"
#include "Ball.h"
#include "Player.h"
#include "OrderTile_Manager.h"

#include "Export_Function.h"

CPlayerAim::CPlayerAim(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{

}

CPlayerAim::CPlayerAim(const CPlayerAim& rhs)
	: CGameObject(rhs)
{

}

CPlayerAim::~CPlayerAim(void)
{

}

HRESULT CPlayerAim::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	//m_pTransformCom->Set_Pos(89.f, 0.f, 126.f);
	//m_pTransformCom->Set_Rotation(0.f, 90.f, 0.f);
	//m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(60.f));
	//m_pTransformCom->Set_Scale(2.f, 2.f, 2.f);
	return S_OK;
}

Engine::_int CPlayerAim::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);
	//	//CPlayer * getPlayer = CManagement::GetInstance()

	//SetUp_OnTerrain();

	//m_bColl
	//m_bColl = Collision_ToPlayer(L"Player_Layer", L"Player");

	//if (m_bColl)
	//{
	//	CManagement::GetInstance()->Get_Scene()->Get_MapLayer(L"Player_Layer", L"Player",0);
	//	//CPlayer * getPlayer = CManagement::GetInstance()
	//	// 플레이어 세팅
	//}

	_vec3	vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);

	//m_bDraw = m_pOptimizationCom->Isin_FrustumForObject(&vPos);

	Add_RenderGroup(RENDER_NONALPHA, this);


	/*if(m_bColl || m_showTile)
		m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSoundOn.jpg"));
	else
		m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSound.jpg"));*/
	//IsCollisionBall();

	//if (m_bSensorColl)
	//{
	//	auto getPlayer = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"Player_Layer")->begin();
	//	bool *getPlayerPush = dynamic_cast<CPlayer*>(getPlayer->second)->Get_PushKey();
	//	dynamic_cast<CPlayer*>(getPlayer->second)->Set_Speed(m_speed);
	//}
	
	return 0;
}

void CPlayerAim::Render_Object(void)
{
	if (false == m_bDraw)
		return;
	/*if (m_tileNum == 0)
		return;*/
	auto getPlayer = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"Player_Layer")->begin();
	//dynamic_cast<CPlayer*>(getPlayer->second)->Get_WrapSphereCollider()
	auto getMatrix = dynamic_cast<CPlayer*>(getPlayer->second)->Get_WrapSphereCollider()->Get_CollWorldMatrix();
	_matrix temp = *getMatrix;
	temp._11 = 1.0f;
	temp._22 = 1.5f;
	temp._33 = 1.5f;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &temp);
	//m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0x00);

	m_pTextureCom->Render_Texture();

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
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
//	// 메쉬
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

HRESULT CPlayerAim::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	//// 메쉬
	//pComponent = m_pMeshCom = dynamic_cast<CStaticMesh*>(Clone_Proto(L"Proto_Mesh_GarbageBag.x"));
	//NULL_CHECK_RETURN(pComponent);
	//Add_AddComponent(L"Com_Mesh", ID_DYNAMIC, pComponent);

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_Buffer_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"CircleAim.tga"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Texture", pComponent);

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

	return S_OK;

}


CPlayerAim* CPlayerAim::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayerAim*	pInstance = new CPlayerAim(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CPlayerAim::Free(void)
{
	CGameObject::Free();
}
