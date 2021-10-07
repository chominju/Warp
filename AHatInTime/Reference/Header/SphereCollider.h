#ifndef Sphere_Collider_h__
#define Sphere_Collider_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CSphereCollider : public CComponent
{
private:
	explicit CSphereCollider(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSphereCollider(const CSphereCollider& rhs);
	virtual ~CSphereCollider(void);

public:
	const _matrix*			Get_CollWorldMatrix(void) { return &m_matCollWorld; }
	const _vec3*			Get_Min(void) { return &m_vMin; }
	const _vec3*			Get_Max(void) { return &m_vMax; }

public:
	HRESULT			Ready_Collider(const _vec3* pPos, const _ulong& dwNumVtx, const _ulong& dwVtxSize);
	void			Render_Collider(COLLTYPE eType, const _matrix* pColliderMatrix);

private:
	_vec3						m_vMin, m_vMax;

#ifdef _DEBUG
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;
	LPDIRECT3DTEXTURE9			m_pTexture[COL_END];
#endif

	_matrix						m_matCollWorld;

public:
	static CSphereCollider*	Create(LPDIRECT3DDEVICE9 pGraphicDev,
		const _vec3* pPos,
		const _ulong& dwNumVtx,
		const _ulong& dwVtxSize);

	virtual CComponent* Clone(void);
	virtual void Free(void);
};

END
#endif // Collider_h__