#ifndef Jelly_h__
#define Jelly_h__

#include "GameObject.h"
#include "Define.h"
#include "InteractionObject.h"

BEGIN(Engine)

class CStaticMesh;
class CTransform;
class CRenderer;
class CCalculator;
class CCollider;

END
class CJelly : public CInteractionObject
{
private:
	explicit CJelly(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CJelly(const CJelly& rhs);
	virtual ~CJelly(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

private:
	virtual HRESULT			Add_Component(void);

private:
	CGameObject*					m_targetBall;
	_float							m_speed;

public:
	static CJelly*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Jelly_h__
