#ifndef RightDoor_h__
#define RightDoor_h__

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
class CRightDoor : public CInteractionObject
{
private:
	explicit CRightDoor(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRightDoor(const CRightDoor& rhs);
	virtual ~CRightDoor(void);

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

private:
	_bool					m_isOpen;
	_bool					m_isFloorSwitch;
	int						m_doorOption;
	_vec3					m_firstPos;

public:
	static CRightDoor*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // RightDoor_h__
