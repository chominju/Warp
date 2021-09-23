#ifndef Texture_h__
#define Texture_h__

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CTextureDev : public CBase
{
private:
	explicit CTextureDev(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTextureDev(void);

public:
	HRESULT		Ready_Texture();

	LPD3DXSPRITE Get_Sprite() { return m_pSprite; }

	//void		Render_Texture();			// 출력할 폰트 색상


	void			Render_TextureBegin();
	void			Render_TextureEnd();

private:
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	LPD3DXSPRITE			m_pSprite;

public:
	static CTextureDev*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void);

};

END
#endif // Font_h__
