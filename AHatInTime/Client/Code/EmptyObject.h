#ifndef EmptyObject_h__
#define EmptyObject_h__

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
class CEmptyObject : public CInteractionObject
{
private:
	explicit CEmptyObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CEmptyObject(const CEmptyObject& rhs);
	virtual ~CEmptyObject(void);

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
	static CEmptyObject*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // EmptyObject_h__
