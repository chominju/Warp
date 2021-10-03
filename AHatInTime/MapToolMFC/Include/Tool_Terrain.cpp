#include "stdafx.h"
#include "Tool_Terrain.h"

#include "Export_Function.h"

CTerrain::CTerrain(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{

}

CTerrain::CTerrain(const CTerrain& rhs)
	: CGameObject(rhs)
{

}

CTerrain::~CTerrain(void)
{

}

HRESULT CTerrain::Ready_Object(void)
{
	//FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	FAILED_CHECK_RETURN(CGameObject::Ready_Object(), E_FAIL);

	return S_OK;
}

Engine::_int CTerrain::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	Add_RenderGroup(RENDER_PRIORITY, this);

	return 0;
}

void CTerrain::Render_Object(void)
{
	if(m_pTransformCom)
		m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	if (m_pTextureCom)
		m_pTextureCom->Render_Texture();

	FAILED_CHECK_RETURN(SetUp_Material(), );

	if (m_pBufferCom)
		m_pBufferCom->Render_Buffer();

	//m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//HRESULT CTerrain::Add_Component(void)
//{
//	CComponent*			pComponent = nullptr;
//
//	// buffer
//	pComponent = m_pBufferCom = dynamic_cast<CTerrainTex*>(Clone_Proto(L"Proto_Buffer_TerrainTex"));
//	NULL_CHECK_RETURN(pComponent, E_FAIL);
//	m_mapComponent[ID_STATIC].emplace(L"Com_Buffer", pComponent);
//	
//	// texture
//	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_Texture_Terrain"));
//	NULL_CHECK_RETURN(pComponent, E_FAIL);
//	m_mapComponent[ID_STATIC].emplace(L"Com_Texture", pComponent);
//
//	// Transform
//	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
//	NULL_CHECK_RETURN(pComponent, E_FAIL);
//	m_mapComponent[ID_DYNAMIC].emplace(L"Com_Transform", pComponent);
//
//	// renderer
//	pComponent = m_pRendererCom = Get_Renderer();
//	NULL_CHECK_RETURN(pComponent, E_FAIL);
//	pComponent->AddRef();
//	m_mapComponent[ID_STATIC].emplace(L"Com_Renderer", pComponent);
//	
//	return S_OK;
//}

HRESULT CTerrain::SetUp_Material(void)
{
	D3DMATERIAL9		tMtrl;
	ZeroMemory(&tMtrl, sizeof(D3DMATERIAL9));

	tMtrl.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrl.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrl.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.f);
	tMtrl.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
	tMtrl.Power = 0.f;

	m_pGraphicDev->SetMaterial(&tMtrl);

	return S_OK;
}

CTerrain* CTerrain::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrain*	pInstance = new CTerrain(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CTerrain::Free(void)
{
	CGameObject::Free();
}

