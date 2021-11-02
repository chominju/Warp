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

	//void	IsCollisionBall();

private:
	virtual HRESULT			Add_Component(void);
	//_bool					Collision_ToObject(const _tchar* pLayerTag, const _tchar* pObjTag);

private:
	//CRcTex*					m_pBufferCom = nullptr;
	//CTexture*				m_pTextureCom = nullptr;
	//CTransform*				m_pTransformCom = nullptr;
	//CRenderer*				m_pRendererCom = nullptr;
	//CCalculator*			m_pCalculatorCom = nullptr;
	//CCollider*				m_pColliderCom = nullptr;

	_int					m_startIndex;
	_int					m_lastIndex;
	_float					m_timer;
public:
	static CWarpSprite*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Sword_h__
