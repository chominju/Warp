#ifndef GraphicDev_h__
#define GraphicDev_h__

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CGraphicDev : public CBase 
{
	DECLARE_SINGLETON(CGraphicDev)

private:
	explicit CGraphicDev(void);
	virtual ~CGraphicDev(void);

public:
	LPDIRECT3DDEVICE9		Get_Device() { return m_pGraphicDev; }
	LPD3DXSPRITE Get_Sprite() { return m_sprite; }
	LPD3DXFONT Get_Font() { return m_font; }
public:
	HRESULT			Ready_GraphicDev(HWND hWnd, WINMODE eMode, 
									const _uint& iSizeX, 
									const _uint& iSizeY, 
									CGraphicDev** ppGraphicDev);

	void			Render_Begin(D3DXCOLOR Color);
	void			Render_End(HWND hWnd = NULL);

private:
	LPDIRECT3D9				m_pSDK;				// ��ġ�� �����ϴ� ����(�������� �ٺ� ��ü)
	LPDIRECT3DDEVICE9		m_pGraphicDev;		// �׸��� ��ġ�� ��Ʈ���ϴ� ��ü(m_pSDK�� ���ؼ��� ���� ����)

	LPD3DXSPRITE			m_sprite;
	LPD3DXFONT				m_font;

public:
	virtual		void		Free(void);
};

END
#endif // GraphicDev_h__
