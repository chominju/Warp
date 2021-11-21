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
class CRcTex;
class CTexture;

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
	CSphereCollider* Get_WrapSphereCollider() { return m_pWrapSphereColliderCom; }
	_bool*		Get_PushKey() { return m_pushKey; }
	_bool*		Get_LastPushKey() { return m_lastPushKey; }

	_float					Get_Speed() { return m_speed; }
	void					Set_Speed(_float speed) { m_speed = speed; }
	void					Reset_Speed() { m_speed = m_firstSpeed; }

	_bool					Get_IsConveyor() { return m_isConveyor; }
	void					Set_IsConveyor(_bool conveyor) { m_isConveyor = conveyor; }

	_bool					Get_IsFrozenRoadOn() { return m_isFrozenRoadOn; }
	void					Set_IsFrozenRoadOn(_bool frozenRoad) { m_isFrozenRoadOn = frozenRoad; }
	_bool					Get_IsWrapSkillItem() { return m_isWrapSkillItem; }
	void					Set_IsWrapSkillItem(_bool wrapSkill) { m_isWrapSkillItem = wrapSkill; }

	_bool					Get_IsCollComputer() { return m_isColl_Computer; }
	void					Set_IsCollComputer(_bool isCollComputer) { m_isColl_Computer = isCollComputer; }

private:
	HRESULT					Add_Component(void);
	void					Key_Input(const _float& fTimeDelta);
	void					SetUp_OnTerrain(void);

private:
	CStaticMesh*			m_pStatic_MeshCom = nullptr;
	CDynamicMesh*			m_pMeshCom = nullptr;
	CTransform*				m_pTransformCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CCollider*				m_pColliderCom = nullptr;
	CSphereCollider*		m_pSphereColliderCom = nullptr;
	CSphereCollider*		m_pWrapSphereColliderCom = nullptr;

	CCalculator*			m_pCalculatorCom = nullptr;
	_vec3					m_vDir;

	_bool					m_pushKey[KEY_END];					// ���� ������ �ִ� Ű
	_bool					m_lastPushKey[KEY_END];				// ���������� ������ Ű(������ ������)
	_bool					m_isKeyStop[KEY_END];				// �̵��� �ȵǴ� Ű
	_bool					m_isConveyor;						// �����̳� ���� �ִ���
	_bool					m_isWrapSkillItem;					// ���� �����ϰ� �ϴ� �������� �Ծ�����
	_bool					m_isWrapable;						// ������ ��������(�浹üũȮ��)
	_bool					m_isWrapKeyable;					// ����Ű�� ��������(Q)
	_bool					m_isHideObject;						// ������Ʈ �ȿ� ������
	_bool					m_isHideObjectAble;					// ������Ʈ �ȿ� �����ִ���
	_bool					m_isFrozenRoadOn;					// ���� ���� �ִ���
	_bool					m_isFrozenRoadWalk;					// ���� ���� �Ȱ��ִ���
	_bool					m_isColl_StaticObject;				// static ������Ʈ�� �浹 ������
	_bool					m_isColl_InteractionObject;			// interaction ������Ʈ�� �浹 ������
	_bool					m_isColl_Computer;

	_float					m_startTime;						
	_float					m_speed;
	_float					m_firstSpeed;

	CGameObject*			m_hideObjectAble;					// ���� ���� �� �ִ� ������Ʈ
	CGameObject*			m_hideObject;						// ���� ���� ������Ʈ
	CGameObject*			m_FrozenObject;						// ���� ������Ʈ

	CGameObject*			m_playerAim;
public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Player_h__
