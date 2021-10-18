#ifndef LeftDoor_h__
#define LeftDoor_h__

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
class CLeftDoor : public CInteractionObject
{
private:
	explicit CLeftDoor(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CLeftDoor(const CLeftDoor& rhs);
	virtual ~CLeftDoor(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

private:
	virtual HRESULT			Add_Component(void);
	//_bool					Collision_ToObject(const _tchar* pLayerTag, const _tchar* pObjTag);

private:
	_bool					isOpen;
//	CStaticMesh*			m_pMeshCom = nullptr;
//	CTransform*				m_pTransformCom = nullptr;
//	CRenderer*				m_pRendererCom = nullptr;
//	CCalculator*			m_pCalculatorCom = nullptr;
//	CCollider*				m_pColliderCom = nullptr;


public:
	static CLeftDoor*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Sword_h__
