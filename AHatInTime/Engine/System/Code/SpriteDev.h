#ifndef SpriteDev_h__
#define SpriteDev_h__

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CSpriteDev : public CBase
{
private:
	explicit CSpriteDev(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSpriteDev(void);

public:
	LPD3DXSPRITE Get_Sprite() { return m_pSprite; }
	HRESULT		Ready_Sprite();

	void		Render_BeginSprite(D3DXCOLOR Color);
	void		Render_EndSprite(HWND hWnd = NULL);
private:
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	LPD3DXSPRITE			m_pSprite;

public:
	static CSpriteDev*		Create(LPDIRECT3DDEVICE9 pGraphicDev);			// ±½±â

private:
	virtual void Free(void);

};

END
#endif // Font_h__
