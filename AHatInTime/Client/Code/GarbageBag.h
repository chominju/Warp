#ifndef GarbageBag_h__
#define GarbageBag_h__

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
class CGarbageBag : public CInteractionObject
{
private:
	explicit CGarbageBag(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CGarbageBag(const CGarbageBag& rhs);
	virtual ~CGarbageBag(void);

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
	static CGarbageBag*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // GarbageBag_h__
