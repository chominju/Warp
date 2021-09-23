#ifndef Texture_h__
#define Texture_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTexture : public CComponent
{
private:
	explicit CTexture(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTexture(const CTexture& rhs);
	virtual ~CTexture(void);

public:
	HRESULT			Ready_Texture(const _tchar* pPath, TEXTUREID eType, const _uint& iCnt);
	void			Render_Texture(const _uint& iIndex = 0);

	HRESULT Insert_Texture(LPDIRECT3DDEVICE9 pGraphicDev, const wstring & filePath, const wstring & stateKey = L"", const DWORD & count = 0);
	const Texture_Info* Get_TextureInfo(const wstring & stateKey = L"", const DWORD & index = 0);

private:
	vector<IDirect3DBaseTexture9*>		m_vecTexture;	

public:
	virtual CComponent*		Clone(void);
	static CTexture*		Create(LPDIRECT3DDEVICE9 pGraphicDev, 
									const _tchar* pPath, 
									TEXTUREID eType, 
									const _uint& iCnt = 1);
	
	Texture_Info m_textureInfo;
	virtual void			Free(void);
};

END
#endif // Texture_h__