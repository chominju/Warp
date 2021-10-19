#ifndef Player_h__
#define Player_h__

#include "GameObject.h"
#include "Define.h"

BEGIN(Engine)

class CDynamicMesh;
class CTransform;
class CRenderer;
class CCalculator;
class CCollider;
class CNaviMesh;
class CSphereCollider;
class CStaticMesh;

END
class CPlayer : public CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPlayer(const CPlayer& rhs);
	virtual ~CPlayer(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

	CTransform* Get_Transform_Component() { return m_pTransformCom; }

	_bool*		Get_PushKey() { return m_pushKey; }

	_float					Get_Speed() { return m_speed; }
	void					Set_Speed(_float speed) { m_speed = speed; }
	void					Reset_Speed() { m_speed = m_firstSpeed; }

private:
	HRESULT					Add_Component(void);
	void					Key_Input(const _float& fTimeDelta);
	void					SetUp_OnTerrain(void);
	//_vec3					PickUp_OnTerrain(void);

	_bool					Collision_ToObject(/*const _tchar* pLayerTag, const _tchar* pObjTag*/);

private:
	CStaticMesh*			m_pStatic_MeshCom = nullptr;
	CDynamicMesh*			m_pMeshCom = nullptr;
	//CNaviMesh*				m_pNaviCom = nullptr;
	CTransform*				m_pTransformCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CCollider*				m_pColliderCom = nullptr;
	CSphereCollider*		m_pSphereColliderCom = nullptr;

	CCalculator*			m_pCalculatorCom = nullptr;
	_vec3					m_vDir;

	_bool					m_pushKey[KEY_END];
	_bool					m_isKeyStop[KEY_END];
	_float					m_startTime;
	_float					m_speed;
	_float					m_firstSpeed;
public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Player_h__
