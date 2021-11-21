#ifndef WarpSprite_h__
#define WarpSprite_h__

#include "GameObject.h"
#include "Define.h"
#include "InteractionObject.h"

BEGIN(Engine)

class CStaticMesh;
class CTransform;
class CRenderer;
class CCalculator;
class CCollider;
class CRcTex;
class CTexture;

END
class CWarpSprite : public CInteractionObject
{
private:
	explicit CWarpSprite(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CWarpSprite(const CWarpSprite& rhs);
	virtual ~CWarpSprite(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

private:
	virtual HRESULT			Add_Component(void);

private:

	_int					m_startIndex;
	_int					m_lastIndex;
	_float					m_timer;
public:
	static CWarpSprite*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // WarpSprite_h__
