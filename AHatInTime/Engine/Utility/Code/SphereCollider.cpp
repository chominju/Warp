#include "SphereCollider.h"

USING(Engine)

Engine::CSphereCollider::CSphereCollider(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev)
	//, m_pVB(nullptr)
	//, m_pIB(nullptr)	
{
	D3DXMatrixIdentity(&m_matCollWorld);
}

Engine::CSphereCollider::CSphereCollider(const CSphereCollider& rhs)
	: CComponent(rhs)	
	//, m_vMin(rhs.m_vMin)
	//, m_vMax(rhs.m_vMax)
	, m_matCollWorld(rhs.m_matCollWorld)
{
//#ifdef _DEBUG
//	m_pVB = rhs.m_pVB;
//	m_pVB->AddRef();
//	m_pIB = rhs.m_pIB;
//	m_pIB->AddRef();
//
//	for (_ulong i = 0; i < COL_END; ++i)
//	{
//		m_pTexture[i] = rhs.m_pTexture[i];
//		m_pTexture[i]->AddRef();
//	}
//	
//#endif
}

Engine::CSphereCollider::~CSphereCollider(void)
{

}

CSphereCollider* Engine::CSphereCollider::Create(LPDIRECT3DDEVICE9 pGraphicDev, int radius/*, const _vec3* pPos, const _ulong& dwNumVtx, const _ulong& dwVtxSize*/)
{
	CSphereCollider*	pInstance = new CSphereCollider(pGraphicDev);

	if (FAILED(pInstance->Ready_SphereCollider(radius/*pPos, dwNumVtx, dwVtxSize*/)))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CSphereCollider::Clone(void)
{
	return new CSphereCollider(*this);
}

void Engine::CSphereCollider::Free(void)
{
//#ifdef _DEBUG
//	Safe_Release(m_pIB);
//	Safe_Release(m_pVB);
//
//	if (false == m_bClone)
//	{
//		for (_ulong i = 0; i < COL_END; ++i)
//			Safe_Release(m_pTexture[i]);
//	}
//#endif
	CComponent::Free();

}

HRESULT Engine::CSphereCollider::Ready_SphereCollider(int radius/*const _vec3* pPos, const _ulong& dwNumVtx, const _ulong& dwVtxSize*/)
{
	m_radius = radius;
	//D3DXComputeBoundingBox(pPos, dwNumVtx, sizeof(_vec3), &m_vMin, &m_vMax);
	D3DXCreateSphere(m_pGraphicDev, m_radius, 10, 10, &m_pSphereMesh, NULL);

	return S_OK;
}

void Engine::CSphereCollider::Render_SphereCollider(/*COLLTYPE eType, *//*const*/ _matrix* pColliderMatrix)
{
	m_matCollWorld = *pColliderMatrix;

#ifdef _DEBUG
	//m_pGraphicDev->SetTransform(D3DTS_WORLD, pColliderMatrix);
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//m_pSphereMesh->DrawSubset(0);
	///*m_pGraphicDev->SetTexture(0, m_pTexture[eType]);

	//m_pGraphicDev->SetStreamSource(0, m_pVB, 0, sizeof(VTXCUBE));
	//m_pGraphicDev->SetFVF(FVF_CUBE);
	//m_pGraphicDev->SetIndices(m_pIB);*/
	////m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
#endif
}

/*



*/