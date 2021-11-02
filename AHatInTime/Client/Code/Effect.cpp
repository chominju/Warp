#include "stdafx.h"
#include "Effect.h"

#include "Export_Function.h"
#include "Management.h"
#include "Player.h"
CEffect::CEffect(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{

}

CEffect::CEffect(const CEffect& rhs)
	: CGameObject(rhs)
{

}

CEffect::~CEffect(void)
{

}

HRESULT CEffect::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//m_pTransformCom->Set_Pos(&_vec3(rand() % 50, 0.f, rand() % 50));
	auto player = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"Player_Layer")->begin();
	const _matrix * temp = dynamic_cast<CPlayer*>(player->second)->Get_Transform_Component()->Get_WorldMatrix();
	m_pTransformCom->Set_Pos(temp->_41, 3.f, temp->_43);
	return S_OK;
}

Engine::_int CEffect::Update_Object(const _float& fTimeDelta)
{

	m_fFrame += 90.f * fTimeDelta;

	if (m_fFrame > 90.f)
		m_fFrame = 0.f;


	CGameObject::Update_Object(fTimeDelta);
	
	_matrix		matWorld, matView, matBill;

	m_pTransformCom->Get_WorldMatrix(&matWorld);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixIdentity(&matBill);

	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, NULL, &matBill);

	// ���� �� �ڵ�� ������ ������ �ִ�.
	// ���� ��� = �� * �� * �� * �� * ��
	// �� = �� * ��(��(I)) -> ��(��^-1) * �� * �� 

	m_pTransformCom->Set_WorldMatrix(&(matBill * matWorld));

	_vec3 vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);

	Compute_ViewZ(&vPos);

	Add_RenderGroup(RENDER_ALPHA, this);

	return 0;
}

void CEffect::Render_Object(void)
{
	LPD3DXEFFECT	pEffect = m_pShaderCom->Get_EffectHandle();
	NULL_CHECK(pEffect);
	pEffect->AddRef();

	FAILED_CHECK_RETURN(SetUp_ConstantTable(pEffect), );

	_uint	iMaxPass = 0;

	pEffect->Begin(&iMaxPass, 0);	// 1. ���� ���̴� ������ ���� �ִ� pass�� ���� ��ȯ 2. �����ϴ� ��Ŀ� ���� flag ��(default ��)
	pEffect->BeginPass(0);

	m_pBufferCom->Render_Buffer();

	pEffect->EndPass();
	pEffect->End();

	Safe_Release(pEffect);


}

HRESULT CEffect::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_Buffer_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Buffer", pComponent);

	// texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_Texture_Effect"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Texture", pComponent);

	// Transform
	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	// renderer
	pComponent = m_pRendererCom = Get_Renderer();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->AddRef();
	m_mapComponent[ID_STATIC].emplace(L"Com_Renderer", pComponent);

	// Shader
	pComponent = m_pShaderCom = dynamic_cast<CShader*>(Clone_Proto(L"Proto_Shader_Effect"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Shader", pComponent);

	return S_OK;

}

HRESULT CEffect::SetUp_ConstantTable(LPD3DXEFFECT& pEffect)
{
	_matrix		matWorld, matView, matProj;

	m_pTransformCom->Get_WorldMatrix(&matWorld);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	m_pTextureCom->Set_Texture(pEffect, "g_BaseTexture", (_uint)m_fFrame);

	//Get_RenderTargetTexture(pEffect, L"Target_Depth", "g_DepthTexture");

	return S_OK;
}

CEffect* CEffect::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEffect*	pInstance = new CEffect(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CEffect::Free(void)
{
	CGameObject::Free();
}

