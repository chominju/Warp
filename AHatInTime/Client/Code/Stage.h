#ifndef Stage_h__
#define Stage_h__

#include "Scene.h"
#include "Define.h"

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
	HRESULT			Ready_StaticObject_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_InteractionObject_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_OrderTile_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_Player_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_UI_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_LightInfo(void);

	void			Create_Maze(const _tchar* pLayerTag);

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
