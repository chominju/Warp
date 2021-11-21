#include "stdafx.h"
#include "OrderTile.h"
#include "Ball.h"
#include "Player.h"
#include "OrderTile_Manager.h"
#include "LeftDoor.h"
#include "RightDoor.h"
#include "SoundMgr.h"

#include "Export_Function.h"

_int COrderTile::m_orderTileIndex = -1;
_bool COrderTile::m_isEnd1 = false;
_bool COrderTile::m_isEnd2 = false;
_bool COrderTile::m_isFinish1 = false;
_bool COrderTile::m_isFinish2 = false;


COrderTile::COrderTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CInteractionObject(pGraphicDev)
	, m_speed(1.f)
	, m_tileNum(-1)
	, m_isStart1(false)
	, m_isStart2(false)
	, m_showTile(false)
	, m_timer(0.f)
	, m_check(false)
{

}

COrderTile::COrderTile(const COrderTile& rhs)
	: CInteractionObject(rhs)
{

}

COrderTile::~COrderTile(void)
{

}

HRESULT COrderTile::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

Engine::_int COrderTile::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	SetUp_OnTerrain();

	Add_RenderGroup(RENDER_NONALPHA, this);

	if (m_tileNum == 0)
	{
		if (m_bColl)
		{
			if (!m_isFinish1)
				m_isStart1 = true;
			else
				m_isStart2 = true;
		}
	}
	else
	{

	}

	if (!m_isFinish1)
	{
		if (m_isStart1)
		{
			m_timer += fTimeDelta;
			if (m_timer > 1.f)
			{
				m_orderTileIndex++;
				if (m_orderTileIndex < COrderTile_Manger::GetInstance()->Get_GameObjectOrder1Size())
				{
					auto object = COrderTile_Manger::GetInstance()->Get_GameObjectOrder1(m_orderTileIndex);
					dynamic_cast<COrderTile*>(object)->Set_ShowTile(true);
					dynamic_cast<COrderTile*>(object)->Sound_OrderTile();
					m_timer = 0.f;
					if (m_orderTileIndex > 0)
					{
						auto object = COrderTile_Manger::GetInstance()->Get_GameObjectOrder1(m_orderTileIndex - 1);
						dynamic_cast<COrderTile*>(object)->Set_ShowTile(false);
					}
				}
				else
				{
					auto object = COrderTile_Manger::GetInstance()->Get_GameObjectOrder1(m_orderTileIndex - 1);
					dynamic_cast<COrderTile*>(object)->Set_ShowTile(false);
					m_isStart1 = false;
					m_isEnd1 = true;
					m_orderTileIndex = -1;
					m_timer = 0.f;
				}
			}
		}

		if (m_isEnd1)
		{
			if (m_bColl)
			{
				if (!m_check)
				{
					m_check = true;
					m_orderTileIndex++;
					if (COrderTile_Manger::GetInstance()->IsSameOrder1(m_orderTileIndex, this))
					{
						Sound_OrderTile();
						m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSoundOn.jpg"));
					}
					else
					{
						m_isEnd1 = false;
						m_orderTileIndex = -1;
						m_timer = 0.f;
					}

					if (m_orderTileIndex == COrderTile_Manger::GetInstance()->Get_GameObjectOrder1Size() - 1)
					{
						m_isFinish1 = true;
						m_orderTileIndex = -1;
						m_timer = 0.f;
					}
				}
			}
			else
			{
				m_check = false;
				m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSound.jpg"));
			}
		}
		else
		{
			if (m_showTile)
				m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSoundOn.jpg"));
			else
				m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSound.jpg"));
		}
	}
	else
	{
		if (m_isStart2)
		{
			m_timer += fTimeDelta;
			if (m_timer > 1.f)
			{
				m_orderTileIndex++;
				if (m_orderTileIndex < COrderTile_Manger::GetInstance()->Get_GameObjectOrder2Size())
				{
					auto object = COrderTile_Manger::GetInstance()->Get_GameObjectOrder2(m_orderTileIndex);
					dynamic_cast<COrderTile*>(object)->Sound_OrderTile();
					dynamic_cast<COrderTile*>(object)->Set_ShowTile(true);
					m_timer = 0.f;
					if (m_orderTileIndex > 0)
					{
						auto object = COrderTile_Manger::GetInstance()->Get_GameObjectOrder2(m_orderTileIndex - 1);
						dynamic_cast<COrderTile*>(object)->Set_ShowTile(false);
					}
				}
				else
				{
					auto object = COrderTile_Manger::GetInstance()->Get_GameObjectOrder2(m_orderTileIndex - 1);
					dynamic_cast<COrderTile*>(object)->Set_ShowTile(false);
					m_isStart2 = false;
					m_isEnd2 = true;
					m_orderTileIndex = -1;
					m_timer = 0.f;
				}
			}
		}

		if (m_isEnd2)
		{
			if (m_bColl)
			{
				if (!m_check)
				{
					m_check = true;
					m_orderTileIndex++;
					if (COrderTile_Manger::GetInstance()->IsSameOrder2(m_orderTileIndex, this))
					{
						Sound_OrderTile();
						m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSoundOn.jpg"));
					}
					else
					{
						m_isEnd2 = false;
						m_orderTileIndex = -1;
						m_timer = 0.f;
					}

					if (m_orderTileIndex == COrderTile_Manger::GetInstance()->Get_GameObjectOrder2Size() - 1)
					{
						m_isFinish2 = true;
					}
				}
			}
			else
			{
				m_check = false;
				m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSound.jpg"));
			}
		}
		else
		{
			if (m_showTile)
				m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSoundOn.jpg"));
			else
				m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSound.jpg"));
		}
	}
	if (m_isFinish2)
	{
		auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");

		for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
		{
			if (iter->first == L"LeftDoor7")
				dynamic_cast<CLeftDoor*>(iter->second)->Set_FloorSwitch(true);

			if (iter->first == L"RightDoor7")
				dynamic_cast<CRightDoor*>(iter->second)->Set_FloorSwitch(true);
		}
	}

	return 0;
}

void COrderTile::Render_Object(void)
{
	if (false == m_bDraw)
		return;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pTextureCom->Render_Texture();

	m_pBufferCom->Render_Buffer();

	const _matrix* getTemp = m_pTransformCom->Get_WorldMatrix();
	_matrix newWorldMatrix = *getTemp;
	newWorldMatrix._11 = 0.05f;
	newWorldMatrix._12 = 0.f;
	newWorldMatrix._13 = 0.f;
	newWorldMatrix._14 = 0.f;
	newWorldMatrix._21 = 0.f;
	newWorldMatrix._22 = 0.05f;
	newWorldMatrix._23 = 0.f;
	newWorldMatrix._24 = 0.f;
	newWorldMatrix._31 = 0.f;
	newWorldMatrix._32 = 0.f;
	newWorldMatrix._33 = 0.05f;
	newWorldMatrix._34 = 0.f;

	newWorldMatrix._42 += 1;

	m_pSphereColliderCom->Render_SphereCollider(&newWorldMatrix);

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void COrderTile::Sound_OrderTile()
{
	if (m_tileNum == 1) // 위
	{
		CSoundMgr::Get_Instance()->PlaySound(L"OrderUp.ogg", CSoundMgr::PLAYER);
	}
	else if (m_tileNum == 2) // 아래
	{
		CSoundMgr::Get_Instance()->PlaySound(L"OrderDown.ogg", CSoundMgr::PLAYER);
	}
	else if (m_tileNum == 3) // 왼쪽
	{
		CSoundMgr::Get_Instance()->PlaySound(L"OrderLeft.ogg", CSoundMgr::PLAYER);
	}
	else if (m_tileNum == 4) // 오른쪽
	{
		CSoundMgr::Get_Instance()->PlaySound(L"OrderRight.ogg", CSoundMgr::PLAYER);
	}
}

HRESULT COrderTile::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_Buffer_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"TileSound.jpg"));
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

	// Calculator
	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(L"Proto_Calculator"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(L"Com_Calculator", pComponent);


	// Collider
	pComponent = m_pSphereColliderCom = CSphereCollider::Create(m_pGraphicDev, 20);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_SphereCollider", pComponent);

	return S_OK;
}


COrderTile* COrderTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	COrderTile*	pInstance = new COrderTile(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void COrderTile::Free(void)
{
	CGameObject::Free();
}
