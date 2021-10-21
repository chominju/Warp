#ifndef Interaction_Object_h__
#define Interaction_Object_h__

#include "GameObject.h"
//#include "Define.h"

BEGIN(Engine)

class CStaticMesh;
class CTransform;
class CRenderer;
class CCalculator;
class CCollider;
class COptimization;

END
class CInteractionObject : public CGameObject
{
protected:
	explicit CInteractionObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CInteractionObject(const CInteractionObject& rhs);
	virtual ~CInteractionObject(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

	//void Set_Static_Objects_Data(Object_Data objectData);
	//Object_Data Get_Static_Objects_Data() { return m_objectData; }

	void Set_StaticMesh_Component(const _tchar* pTextureProtoTag);

	CStaticMesh* Get_StaticMesh_Component() { return m_pMeshCom; }
	CTransform* Get_Transform_Component() { return m_pTransformCom; }
	CCollider* Get_Collider_Component() { return m_pColliderCom; }
	CCollider* Get_ColliderSensor_Component() { return m_pColliderSensorCom; }

protected:
	virtual HRESULT			Add_Component(void);
	void					SetUp_OnTerrain(void);
	_bool					Collision_ToPlayer(const _tchar* pLayerTag, const _tchar* pObjTag);

protected:
	CStaticMesh*			m_pMeshCom			= nullptr;
	CTransform*				m_pTransformCom		= nullptr;
	CRenderer*				m_pRendererCom		= nullptr;
	CCalculator*			m_pCalculatorCom	= nullptr;
	CCollider*				m_pColliderCom		= nullptr;
	CCollider*				m_pColliderSensorCom = nullptr;
	//COptimization*			m_pOptimizationCom	= nullptr;

	//Object_Data				m_objectData;

private:	
	
	_uint					m_iFlag;


public:
	static CInteractionObject*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Stone_h__
