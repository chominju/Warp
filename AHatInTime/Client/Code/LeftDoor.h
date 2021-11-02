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

	void	Set_DoorOption(int option) { m_doorOption = option; }
	int		Get_DoorOption() { return m_doorOption; }

	void	Set_FirstPos(float x, float y, float z) { m_firstPos.x = x; m_firstPos.y = y; m_firstPos.z = z; }

	void	Set_FloorSwitch(bool floorSwitch) { m_isFloorSwitch = floorSwitch; }
	_bool	Get_FloorSwitch() { return m_isFloorSwitch; }

private:
	virtual HRESULT			Add_Component(void);
	//_bool					Collision_ToObject(const _tchar* pLayerTag, const _tchar* pObjTag);

private:
	_bool					m_isOpen;
	_bool					m_isFloorSwitch;

//	CStaticMesh*			m_pMeshCom = nullptr;
//	CTransform*				m_pTransformCom = nullptr;
//	CRenderer*				m_pRendererCom = nullptr;
//	CCalculator*			m_pCalculatorCom = nullptr;
//	CCollider*				m_pColliderCom = nullptr;
	int						m_doorOption;
	_vec3					m_firstPos;

	_bool					m_isSound;
	_bool					m_isBackSound;

public:
	static CLeftDoor*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Sword_h__
