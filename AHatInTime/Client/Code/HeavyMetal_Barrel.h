#ifndef HeavyMetal_Barrel_h__
#define HeavyMetal_Barrel_h__

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
class CHeavyMetal_Barrel : public CInteractionObject
{
private:
	explicit CHeavyMetal_Barrel(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CHeavyMetal_Barrel(const CHeavyMetal_Barrel& rhs);
	virtual ~CHeavyMetal_Barrel(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

private:
	virtual HRESULT			Add_Component(void);

private:

	CGameObject*					m_targetBall;
	_float							m_speed;
	_bool							m_isSound;
public:
	static CHeavyMetal_Barrel*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // HeavyMetal_Barrel_h__
