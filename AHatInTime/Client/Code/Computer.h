#ifndef Computer_h__
#define Computer_h__

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
class CComputer : public CInteractionObject
{
private:
	explicit CComputer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CComputer(const CComputer& rhs);
	virtual ~CComputer(void);

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
	static CComputer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Computer_h__
