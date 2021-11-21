#include "stdafx.h"
#include "WrapSprite.h"
#include "Player.h"
#include "Ball.h"
#include "Player.h"
#include "OrderTile_Manager.h"

#include "Export_Function.h"

CWarpSprite::CWarpSprite(LPDIRECT3DDEVICE9 pGraphicDev)
	: CInteractionObject(pGraphicDev)
	, m_startIndex(0)
	, m_lastIndex(15)
	, m_timer(0.f)
{

}

CWarpSprite::CWarpSprite(const CWarpSprite& rhs)
	: CInteractionObject(rhs)
{

}

CWarpSprite::~CWarpSprite(void)
{

}

HRESULT CWarpSprite::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

Engine::_int CWarpSprite::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);
	m_timer += fTimeDelta;

	if (m_startIndex > m_lastIndex)
	{
		m_isDie = true;
		return 0;
	}
	if (m_timer > 0.02f)
	{
		_tchar temp[256];
		wsprintf(temp, L"WARPSTART_%d.tga", m_startIndex);
		m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(temp));
		m_startIndex++;
		m_timer = 0;
	}
	


	Add_RenderGroup(RENDER_NONALPHA, this);

	
	return 0;
}

void CWarpSprite::Render_Object(void)
{
	if (false == m_bDraw)
		return;
	
	const _matrix *temp = m_pTransformCom->Get_WorldMatrix();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0x00);

	m_pTextureCom->Render_Texture();

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

HRESULT CWarpSprite::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_Buffer_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"WARPSTART_0.tga"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Texture", pComponent);

	// Transform
	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
	m_pTransformCom->Set_Scale(2.f, 2.f, 2.f);
	m_pTransformCom->Set_Rotation(0.f, 0.f, 0.f);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	// renderer
	pComponent = m_pRendererCom = Get_Renderer();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->AddRef();
	m_mapComponent[ID_STATIC].emplace(L"Com_Renderer", pComponent);

	return S_OK;

}


CWarpSprite* CWarpSprite::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWarpSprite*	pInstance = new CWarpSprite(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CWarpSprite::Free(void)
{
	CGameObject::Free();
}
