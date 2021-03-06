#include "Layer.h"
#include "Engine_Macro.h"
#include "../Client/Code/Define.h"

USING(Engine)

Engine::CLayer::CLayer(void)
{

}

Engine::CLayer::~CLayer(void)
{

}

HRESULT Engine::CLayer::Add_GameObject(const _tchar* pObjTag, CGameObject* pInstance)
{
	if (nullptr == pInstance)
		return E_FAIL;

	m_mapObject.emplace(pObjTag, pInstance);
	m_vecObject.push_back(pInstance);

	return S_OK;
}

HRESULT Engine::CLayer::Ready_Layer(void)
{
	return S_OK;
}

int Engine::CLayer::Update_Layer(const _float& fTimeDelta)
{
	_int	iResult = 0;

	for (auto& iter : m_mapObject)
	{
		iResult = iter.second->Update_Object(fTimeDelta);

		if (iResult == SCENE_END)
			break;

		if (iResult & 0x8000000)
			return iResult;
		if (iter.second->Get_IsDie())
		{
			Safe_Release(iter.second);
			m_mapObject.erase(iter.first);
		}
		if (m_mapObject.size() == 0)
			break;
	}

	return iResult;
}

CLayer* Engine::CLayer::Create(void)
{
	CLayer*		pInstance = new CLayer;

	if (FAILED(pInstance->Ready_Layer()))
		Safe_Release(pInstance);

	return pInstance;
}

void Engine::CLayer::Free(void)
{
	for_each(m_mapObject.begin(), m_mapObject.end(), CDeleteMap());
	m_mapObject.clear();
}

CComponent* Engine::CLayer::Get_Component(const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID)
{
	auto	iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(pObjTag));

	if (iter == m_mapObject.end())
		return nullptr;

	return iter->second->Get_Component(pComponentTag, eID);
}

CGameObject * CLayer::Get_GameObject(const _tchar * mapTag, int index)
{
	auto	iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(mapTag));

	while (true)
	{
		if (iter == m_mapObject.end())
			return nullptr;

		if (iter->second->Get_Index() == index)
			return iter->second;
		else
			iter++;
	}
}

CGameObject* CLayer::Get_GameObjectVector(int index)
{
	int size = m_vecObject.size();
	for (int i = 0; i < size; i++)
	{
		if (index == m_vecObject[i]->Get_Index())
		{
			return m_vecObject[i];
		}
	}

	return nullptr;
}