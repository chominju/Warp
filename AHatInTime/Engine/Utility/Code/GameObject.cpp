#include "GameObject.h"

USING(Engine)

Engine::CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bColl(false)
	, m_bDraw(true)
	, m_bSensorColl(false)
	, m_stopPlayer{ false,false ,false ,false }
	, m_isDie(false)
{
	m_pGraphicDev->AddRef();
}

Engine::CGameObject::CGameObject(const CGameObject& rhs)
	: m_pGraphicDev(rhs.m_pGraphicDev)
{
	m_pGraphicDev->AddRef();
}

Engine::CGameObject::~CGameObject(void)
{

}

void CGameObject::Set_StopPlayer(_bool stopPlayer[])
{
	for (int i = 0; i < KEY_END; i++)
		m_stopPlayer[i] = stopPlayer[i];
}

void CGameObject::Reset_StopPlayer()
{
	for (int i = 0; i < KEY_END; i++)
		m_stopPlayer[i] = false;
}

HRESULT Engine::CGameObject::Ready_Object(void)
{
	return S_OK;
}

Engine::_int Engine::CGameObject::Update_Object(const _float& fTimeDelta)
{
	for (auto& iter : m_mapComponent[ID_DYNAMIC])
	{
		iter.second->Update_Component(fTimeDelta);
	}

	return 0;
}

void Engine::CGameObject::Render_Object(void)
{

}

void Engine::CGameObject::Free(void)
{
	for (_uint i = 0; i < ID_END; ++i)
	{
		for_each(m_mapComponent[i].begin(), m_mapComponent[i].end(), CDeleteMap());
		m_mapComponent[i].clear();
	}

	Safe_Release(m_pGraphicDev);
}

CComponent* Engine::CGameObject::Find_Component(const _tchar* pComponentTag, COMPONENTID eID)
{

	auto	iter = find_if(m_mapComponent[eID].begin(), m_mapComponent[eID].end(), CTag_Finder(pComponentTag));

	if (iter == m_mapComponent[eID].end())
		return nullptr;

	return iter->second;
}

CComponent* Engine::CGameObject::Get_Component(const _tchar* pComponentTag, COMPONENTID eID)
{
	CComponent*		pComponent = Find_Component(pComponentTag, eID);

	if (nullptr == pComponent)
		return nullptr;

	return pComponent;
}

void CGameObject::Add_AddComponent(const _tchar * pComponentTag, COMPONENTID eID, CComponent * component)
{
	CComponent*		pComponent = Find_Component(pComponentTag, eID);

	if (nullptr == pComponent)
		m_mapComponent[eID].emplace(pComponentTag, component);
}

void Engine::CGameObject::Compute_ViewZ(const _vec3* pPos)
{
	_matrix		matView;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);

	_vec3	vCamPos;

	memcpy(&vCamPos, &matView._41, sizeof(_vec3));

	m_fViewZ = D3DXVec3Length(&(vCamPos - *pPos));

}

