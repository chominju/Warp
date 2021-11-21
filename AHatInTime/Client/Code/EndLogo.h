#ifndef EndLogo_h__
#define EndLogo_h__

#include "Scene.h"
#include "Define.h"

class CEndLogo : public CScene
{
private:
	explicit CEndLogo(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CEndLogo(void);

public:
	virtual HRESULT Ready_Scene(void) override;
	virtual _int Update_Scene(const _float& fTimeDelta) override;
	virtual void Render_Scene(void) override;

private:
	HRESULT			Ready_Environment_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_GameLogic_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_UI_Layer(const _tchar* pLayerTag);

	HRESULT			Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev);

private:

public:
	static CEndLogo*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void);


};

#endif // EndLogo_h__
