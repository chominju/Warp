#ifndef EndBackGround_h__
#define EndBackGround_h__

#include "GameObject.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;
class CRenderer;

END
class CEndBackGround : public CGameObject
{
private:
	explicit CEndBackGround(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CEndBackGround(const CEndBackGround& rhs);
	virtual ~CEndBackGround(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

private:
	HRESULT					Add_Component(void);

private:
	CRcTex*					m_pBufferCom = nullptr;
	CTexture*				m_pTextureCom = nullptr;
	CTransform*				m_pTransformCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;

public:
	static CEndBackGround*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // BackGround_h__
