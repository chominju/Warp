#ifndef Object_h__
#define Object_h__

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
class CObjects : public CGameObject
{
private:
	explicit CObjects(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CObjects(const CObjects& rhs);
	virtual ~CObjects(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

	void Set_ObjectData(Object_Data objectData);
	Object_Data Get_ObjectData() { return m_objectData; }

private:
	HRESULT					Add_Component(void);
	void					SetUp_OnTerrain(void);
	_bool					Collision_ToObject(const _tchar* pLayerTag, const _tchar* pObjTag);

public:
	CStaticMesh*			m_pMeshCom			= nullptr;
	CTransform*				m_pTransformCom		= nullptr;
	CRenderer*				m_pRendererCom		= nullptr;
	//CCalculator*			m_pCalculatorCom	= nullptr;
	//CCollider*				m_pColliderCom		= nullptr;
	//COptimization*			m_pOptimizationCom	= nullptr;

	Object_Data				m_objectData;

private:	
	
	_bool					m_bColl = false;
	_uint					m_iFlag;
	_bool					m_bDraw = false;


public:
	static CObjects*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Stone_h__
