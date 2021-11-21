#ifndef Conveyor_h__
#define Conveyor_h__

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
class CConveyor : public CInteractionObject
{
private:
	explicit CConveyor(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CConveyor(const CConveyor& rhs);
	virtual ~CConveyor(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

	//void	IsCollisionBall();

private:
	virtual HRESULT			Add_Component(void);

private:
	CGameObject*					m_targetBall;
	_float							m_speed;

public:
	static CConveyor*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Conveyor_h__
