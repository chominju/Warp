#ifndef GameObject_h__
#define GameObject_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CGameObject : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CGameObject(const CGameObject& rhs);
	virtual ~CGameObject(void);

public:
	CComponent*		Get_Component(const _tchar* pComponentTag, COMPONENTID eID);
	_float			Get_ViewZ(void) { return m_fViewZ; }
	void			Add_AddComponent(const _tchar* pComponentTag, COMPONENTID eID, CComponent* component);

	void			Set_Index(int index) { m_index = index; }
	int				Get_Index() { return m_index; }
	void			Set_IsColl(_bool coll) { m_bColl = coll; }
	void			Set_IsSensorColl(_bool sensorColl) { m_bSensorColl = sensorColl; }

	void			Set_StopPlayer(KEY keyType, bool stopPlayer) { m_stopPlayer[keyType] = stopPlayer; }
	void			Set_StopPlayer(_bool stopPlayer[]);
	void			Reset_StopPlayer();
	_bool*			Get_StopPlayer() { return m_stopPlayer; }

	void			Set_Draw(_bool setDraw) { m_bDraw = setDraw; }
	_bool			Get_Draw() { return m_bDraw; }

public:
	virtual		HRESULT		Ready_Object(void);
	virtual		_int		Update_Object(const _float& fTimeDelta);
	virtual		void		Render_Object(void);

public:
	void					Compute_ViewZ(const _vec3* pPos);
		
protected:
	LPDIRECT3DDEVICE9					m_pGraphicDev;
	map<const _tchar*, CComponent*>		m_mapComponent[ID_END];
	_float								m_fViewZ;
	int									m_index;
	_bool								m_bColl;
	_bool								m_bSensorColl;
	_bool								m_bDraw;
	_bool								m_stopPlayer[KEY_END];

private:
	CComponent*			Find_Component(const _tchar* pComponentTag, COMPONENTID eID);

public:
	virtual void	Free(void);

};

END
#endif // GameObject_h__
