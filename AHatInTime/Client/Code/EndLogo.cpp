#include "stdafx.h"
#include "EndLogo.h"
#include "Stage.h"
#include "EndBackGround.h"

#include "Export_Function.h"

CEndLogo::CEndLogo(LPDIRECT3DDEVICE9 pGraphicDev)
	: CScene(pGraphicDev)
{

}

CEndLogo::~CEndLogo(void)
{

}

HRESULT CEndLogo::Ready_Scene(void)
{
	FAILED_CHECK_RETURN(CScene::Ready_Scene(), E_FAIL);

	CSoundMgr::Get_Instance()->StopAll();
	FAILED_CHECK_RETURN(Ready_Resource(m_pGraphicDev), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Environment_Layer(L"Environment"), E_FAIL);

	return S_OK;
}

Engine::_int CEndLogo::Update_Scene(const _float& fTimeDelta)
{
	_int	iExit = CScene::Update_Scene(fTimeDelta);
	return iExit;
}

void CEndLogo::Render_Scene(void)
{
	// debug 용
	Render_Font(L"Font_Default", L"감사합니다", &_vec2(280.f, 250.f), D3DXCOLOR(0.f, 0.f, 0.f, 1.f));

}

HRESULT CEndLogo::Ready_Environment_Layer(const _tchar * pLayerTag)
{
	CLayer*		pLayer = CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	
	CGameObject*			pGameObject = nullptr;

	// background
	pGameObject = CEndBackGround::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"EndBackGround", pGameObject), E_FAIL);
	
	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CEndLogo::Ready_GameLogic_Layer(const _tchar * pLayerTag)
{
	return S_OK;
}

HRESULT CEndLogo::Ready_UI_Layer(const _tchar * pLayerTag)
{
	return S_OK;
}

CEndLogo* CEndLogo::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEndLogo*	pInstance = new CEndLogo(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
		Safe_Release(pInstance);

	return pInstance;
}

void CEndLogo::Free(void)
{
	CScene::Free();
}
HRESULT CEndLogo::Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FAILED_CHECK_RETURN(Ready_Proto(L"Proto_Texture_EndLogo", CTexture::Create(m_pGraphicDev, L"../../MapToolMFC/Bin/Resource3/UseStaticMesh/Loading.jpg", TYPE_NORMAL)), E_FAIL);
	return S_OK;
}
