#include "Scene.h"

USING(Engine)

Engine::CScene::CScene(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev->AddRef();
}

Engine::CScene::~CScene(void)
{

}

CComponent * CScene::Get_Component(const _tchar * pLayerTag, 
									const _tchar * pObjTag, 
									const _tchar * pComponentTag,
									COMPONENTID eID)
{
	auto		iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTag_Finder(pLayerTag));

	if (iter == m_mapLayer.end())
		return nullptr;


	return iter->second->Get_Component(pObjTag, pComponentTag, eID);
}

void CScene::Add_LayerGameObject(const _tchar * pLayerTag, CLayer* layer , const _tchar * pObjectTag, CGameObject* gameObject)
{
	auto iter= find_if(m_mapLayer.begin(),m_mapLayer.end(), CTag_Finder(pLayerTag));

	if (iter == m_mapLayer.end())
		m_mapLayer.emplace(pLayerTag, layer);
	else
	{
		iter->second->Add_GameObject(pObjectTag , gameObject);
	}
		

}

CGameObject* CScene::Get_MapLayer(const _tchar * pLayerTag , const _tchar * pObjTag, int index)
{
	auto iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTag_Finder(pLayerTag));

	if (iter == m_mapLayer.end())
		return nullptr;
	else
	{
		return iter->second->Get_GameObjectVector(index);// Get_GameObject(pObjTag, index);// Get_GameObjectVector(index);
	}
}

multimap<const _tchar*, CGameObject*>* CScene::Get_Layer_GameObjects(const _tchar * pLayerTag)
{
	auto iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTag_Finder(pLayerTag));
	
	if (iter == m_mapLayer.end())
		return nullptr;
	else
	{
		return iter->second->Get_LayerObject();
	}
}

//CGameObject * CScene::Get_Player(const _tchar * pLayerTag, const _tchar * pObjTag)
//{
//	auto iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTag_Finder(pLayerTag));
//
//	if (iter == m_mapLayer.end())
//		return nullptr;
//	else
//	{
//		return iter->second->Get_GameObjectVector(index);// Get_GameObject(pObjTag, index);// Get_GameObjectVector(index);
//	}
//}

HRESULT Engine::CScene::Ready_Scene(void)
{
	return S_OK;
}

Engine::_int Engine::CScene::Update_Scene(const _float& fTimeDelta)
{
	_int iResult = 0;

	for (auto& iter : m_mapLayer)
	{
		iResult = iter.second->Update_Layer(fTimeDelta);

		if (iResult & 0x80000000)
			return iResult;

		if (iResult == 10)
			break;
	}
		
	return iResult;
}

void Engine::CScene::Render_Scene(void)
{

}

void Engine::CScene::Free(void)
{
	for_each(m_mapLayer.begin(), m_mapLayer.end(), CDeleteMap());
	m_mapLayer.clear();

	Safe_Release(m_pGraphicDev);
}

