#ifndef MainApp_h__
#define MainApp_h__

#include "Define.h"
#include "Base.h"
#include "Engine_Define.h"
#include "Export_Function.h"


BEGIN(Engine)

class CGraphicDev;
class CManagement;

END

class CMainApp : public CBase
{
private:						
	explicit CMainApp(void);	
	virtual ~CMainApp(void);


public:
	HRESULT				Ready_MainApp(void);
	int					Update_MainApp(const float& fTimeDelta);
	void				Render_MainApp(void);

private:
	HRESULT					SetUp_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev);
	HRESULT					Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, CManagement** ppManagementClass);

private:
	CGraphicDev*			m_pDeviceClass = nullptr;
	LPDIRECT3DDEVICE9		m_pGraphicDev = nullptr;
	CManagement*			m_pManagementClass = nullptr;

	CTriCol*				m_pBuffer = nullptr;

public:
	static CMainApp*		Create(void);	
	virtual void			Free(void);		

};

#endif // MainApp_h__


