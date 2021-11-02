#ifndef OrderTile_h__
#define OrderTile_h__

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
class COrderTile : public CInteractionObject
{
private:
	explicit COrderTile(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit COrderTile(const COrderTile& rhs);
	virtual ~COrderTile(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

	void	Set_TileNum(_int num) { m_tileNum = num; }
	_int	Get_TileNum() { return m_tileNum; }

	void	Set_ShowTile(_bool showTile) { m_showTile = showTile; }
	_bool	Get_ShowTile() { return m_showTile; }

	void	Sound_OrderTile();
	//void	IsCollisionBall();

private:
	virtual HRESULT			Add_Component(void);
	//_bool					Collision_ToObject(const _tchar* pLayerTag, const _tchar* pObjTag);

private:
//	CStaticMesh*			m_pMeshCom = nullptr;
//	CTransform*				m_pTransformCom = nullptr;
//	CRenderer*				m_pRendererCom = nullptr;
//	CCalculator*			m_pCalculatorCom = nullptr;
//	CCollider*				m_pColliderCom = nullptr;
	_float							m_speed;
	_int							m_tileNum;
	_bool							m_isStart1;
	_bool							m_isStart2;
	static	_bool							m_isEnd1;
	static	_bool							m_isEnd2;

	static	_bool							m_isFinish1;
	static	_bool							m_isFinish2;
	_bool							m_showTile;
	_float							m_timer;

	_bool							m_check;
static	_int						m_orderTileIndex;

public:
	static COrderTile*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Sword_h__
