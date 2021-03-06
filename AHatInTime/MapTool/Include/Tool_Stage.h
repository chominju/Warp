#ifndef Stage_h__
#define Stage_h__

#include "Scene.h"
#include "Tool_Define.h"
//#include "Player.h"
//#include "Monster.h"

#include "Tool_Terrain2.h"
#include "Tool_DynamicCamera2.h"
//#include "SkyBox.h"

#include "Tool_Stone.h"
//#include "Sword.h"

class CStage : public CScene
{
private:
	explicit CStage(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CStage(void);

public:
	virtual HRESULT Ready_Scene(void) override;
	virtual _int Update_Scene(const _float& fTimeDelta) override;
	virtual void Render_Scene(void) override;

private:
	HRESULT			Ready_Environment_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_GameLogic_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_UI_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_LightInfo(void);

private:
	_ulong			m_dwRenderCnt = 0;
	_tchar			m_szFPS[256];
	_float			m_fTime = 0.f;

public:
	static CStage*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void);


};

#endif // Stage_h__
