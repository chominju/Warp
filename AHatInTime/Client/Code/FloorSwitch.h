#ifndef FloorSwitch_h__
#define FloorSwitch_h__

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
class CFloorSwitch : public CInteractionObject
{
private:
	explicit CFloorSwitch(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFloorSwitch(const CFloorSwitch& rhs);
	virtual ~CFloorSwitch(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

	void	IsCollisionBall();
	void	IsCollisionObject();

	void	Set_SwitchOption(int option) { m_switchOption = option; }
	int		Get_SwitchOption() { return m_switchOption; }

	_bool	Get_IsObjectColl() { return m_isObjectColl; }
private:
	virtual HRESULT			Add_Component(void);
	//_bool					Collision_ToObject(const _tchar* pLayerTag, const _tchar* pObjTag);

private:
//	CStaticMesh*			m_pMeshCom = nullptr;
//	CTransform*				m_pTransformCom = nullptr;
//	CRenderer*				m_pRendererCom = nullptr;
//	CCalculator*			m_pCalculatorCom = nullptr;
//	CCollider*				m_pColliderCom = nullptr;
	CGameObject*					m_targetBall;
	_bool							m_isBallColl;
	_bool							m_isObjectColl;
	int								m_switchOption;
	float							m_timer;

public:
	static CFloorSwitch*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Sword_h__
