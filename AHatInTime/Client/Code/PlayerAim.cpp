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
	return S_OK;
}

Engine::_int CPlayerAim::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_NONALPHA, this);
	return 0;
}

void CPlayerAim::Render_Object(void)
{
	if (false == m_bDraw)
		return;
	auto getPlayer = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"Player_Layer")->begin();
	auto getMatrix = dynamic_cast<CPlayer*>(getPlayer->second)->Get_WrapSphereCollider()->Get_CollWorldMatrix();
	_matrix temp = *getMatrix;
	temp._11 = 1.0f;
	temp._22 = 1.5f;
	temp._33 = 1.5f;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &temp);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0x00);

	m_pTextureCom->Render_Texture();

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

HRESULT CPlayerAim::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

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
