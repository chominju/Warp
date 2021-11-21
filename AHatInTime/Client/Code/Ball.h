#ifndef Ball_h__
#define Ball_h__

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
class CBall : public CInteractionObject
{
private:
	explicit CBall(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBall(const CBall& rhs);
	virtual ~CBall(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

private:
	virtual HRESULT			Add_Component(void);

private:
	_bool					isBall;
	_bool					m_isFirstColl;
	_bool					m_firstPushKey[KEY_END];
	_float					m_speed;
	_float					m_angle[2];

public:
	static CBall*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Ball_h__
