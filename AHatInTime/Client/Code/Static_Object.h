#ifndef Static_Objects_h__
#define Static_Objects_h__

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
class CStatic_Objects : public CGameObject
{
private:
	explicit CStatic_Objects(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CStatic_Objects(const CStatic_Objects& rhs);
	virtual ~CStatic_Objects(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

	void Set_Static_Objects_Data(Object_Data objectData);
	Object_Data Get_Static_Objects_Data() { return m_objectData; }

	void Set_StaticMesh_Component(const _tchar* pTextureProtoTag);

	CStaticMesh* Get_StaticMesh_Component() { return m_pMeshCom; }
	CTransform* Get_Transform_Component() { return m_pTransformCom; }

private:
	HRESULT					Add_Component(void);
	void					SetUp_OnTerrain(void);
	_bool					Collision_ToObject(const _tchar* pLayerTag, const _tchar* pObjTag);

private:
	CStaticMesh*			m_pMeshCom			= nullptr;
	CTransform*				m_pTransformCom		= nullptr;
	CRenderer*				m_pRendererCom		= nullptr;
	//CCalculator*			m_pCalculatorCom	= nullptr;
	CCollider*				m_pColliderCom		= nullptr;
	//COptimization*			m_pOptimizationCom	= nullptr;

	Object_Data				m_objectData;

private:	
	
	_bool					m_bColl = false;
	_uint					m_iFlag;
	_bool					m_bDraw = false;


public:
	static CStatic_Objects*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Stone_h__
