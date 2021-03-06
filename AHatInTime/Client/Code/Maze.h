#ifndef Maze_h__
#define Maze_h__

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
class CMaze : public CInteractionObject
{
private:
	explicit CMaze(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMaze(const CMaze& rhs);
	virtual ~CMaze(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

	void	Set_FirstPos(float x, float y, float z) { m_firstPos.x = x; m_firstPos.y = y; m_firstPos.z = z; }

private:
	virtual HRESULT			Add_Component(void);

private:
	_bool					m_isMove;
	_bool					m_isFloorSwitch;

	int						m_doorOption;
	_vec3					m_firstPos;

public:
	static CMaze*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Maze_h__
