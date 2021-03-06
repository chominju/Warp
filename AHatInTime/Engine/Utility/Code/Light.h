#ifndef Light_h__
#define Light_h__

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CLight : public CBase
{
private:
	explicit CLight(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLight(void);
	
private:
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	D3DLIGHT9			m_tLightInfo;
	_uint				m_iIndex;

public:
	HRESULT		Ready_Light(const D3DLIGHT9* pLightInfo, const _uint& iIndex);

public:
	static CLight*		Create(LPDIRECT3DDEVICE9 pGraphicDev, 
								const D3DLIGHT9* pLightInfo, 
								const _uint& iIndex);
	virtual void		Free(void);
};

END
#endif // Light_h__
