#include "SpriteDev.h"

USING(Engine)

Engine::CSpriteDev::CSpriteDev(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_pSprite(nullptr)
{
	m_pGraphicDev->AddRef();
}

Engine::CSpriteDev::~CSpriteDev(void)
{

}

HRESULT Engine::CSpriteDev::Ready_Sprite()
{
	FAILED_CHECK_RETURN(D3DXCreateSprite(m_pGraphicDev, &m_pSprite), E_FAIL);

	return S_OK;
}

void CSpriteDev::Render_BeginSprite(D3DXCOLOR Color)
{
	m_pGraphicDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, Color, 1.f, 0);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CSpriteDev::Render_EndSprite(HWND hWnd)
{
	m_pSprite->End();
	m_pGraphicDev->Present(NULL, NULL, hWnd, NULL);
}

CSpriteDev* Engine::CSpriteDev::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSpriteDev*	pInstance = new CSpriteDev(pGraphicDev);

	if (FAILED(pInstance->Ready_Sprite()))
	{
		MSG_BOX("Font Create Failed");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

void Engine::CSpriteDev::Free(void)
{
	Engine::Safe_Release(m_pSprite);
	Engine::Safe_Release(m_pGraphicDev);
}

