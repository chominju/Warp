#include "Renderer.h"

USING(Engine)
IMPLEMENT_SINGLETON(CRenderer)

Engine::CRenderer::CRenderer(void)
{

}

Engine::CRenderer::~CRenderer(void)
{
	Free();
}
// �� �����Ӹ��� ���� �׷��� ����
void Engine::CRenderer::Add_RenderGroup(RENDERID eID, CGameObject* pGameObject)
{
	if (RENDER_END <= eID || nullptr == pGameObject)
		return;

	m_RenderGroup[eID].push_back(pGameObject);
	pGameObject->AddRef();
}
// ������ �����׷��� ���
void Engine::CRenderer::Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev)
{
	for (_uint i = 0; i < RENDER_END; ++i)
	{
		for (auto& iter : m_RenderGroup[i])
		{
			iter->Render_Object();
			Safe_Release(iter);		// ������ �ƴ�, ���۷��� ī��Ʈ ����
		}
		m_RenderGroup[i].clear();
	}

	/*Render_Priority(pGraphicDev);
	Render_Nonalpha(pGraphicDev);
	Render_Alpha(pGraphicDev);
	Render_UI(pGraphicDev);

	Clear_RenderGroup();*/
}

void Engine::CRenderer::Clear_RenderGroup(void)
{
	for (_uint i = 0; i < RENDER_END; ++i)
	{
		for_each(m_RenderGroup[i].begin(), m_RenderGroup[i].end(), CDeleteObj());
		m_RenderGroup[i].clear();
	}
}

void CRenderer::Render_Priority(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (auto& iter : m_RenderGroup[RENDER_PRIORITY])
		iter->Render_Object();

	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void CRenderer::Render_Nonalpha(LPDIRECT3DDEVICE9 & pGraphicDev)
{
}

void CRenderer::Render_Alpha(LPDIRECT3DDEVICE9 & pGraphicDev)
{
}

void CRenderer::Render_UI(LPDIRECT3DDEVICE9 & pGraphicDev)
{
}

void Engine::CRenderer::Free(void)
{
	Clear_RenderGroup();
}

