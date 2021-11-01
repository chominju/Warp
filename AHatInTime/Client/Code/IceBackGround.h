#ifndef IceBackGround_h__
#define IceBackGround_h__

#include "GameObject.h"

BEGIN(Engine)

class CTerrainTex;
class CTexture;
class CTransform;
class CRenderer;
class COptimization;

END
class CIceBackGround : public CGameObject
{
private:
	explicit CIceBackGround(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CIceBackGround(const CIceBackGround& rhs);
	virtual ~CIceBackGround(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

	void Set_TerrainData(Terrain_Data terrainData);
	Terrain_Data Get_TerrainData() { return m_terrainData; }

	void Set_TextureComponent(const _tchar* pTextureProtoTag);


	CTerrainTex* Get_TerrainTex_Component() { return m_pBufferCom; }
	CTexture* Get_Texture_Component() { return m_pTextureCom; }
	CTransform* Get_Transform_Component() { return m_pTransformCom; }


private:
	HRESULT					Add_Component(void);
	HRESULT					SetUp_Material(void);

private:
	CTerrainTex*				m_pBufferCom = nullptr;
	CTexture*					m_pTextureCom = nullptr;
	CTransform*					m_pTransformCom = nullptr;
	CRenderer*					m_pRendererCom = nullptr;
	//COptimization*				m_pOptimizationCom = nullptr;

	INDEX32*					m_pIndex = nullptr;
	_ulong						m_dwTriCnt = 0;

	Terrain_Data				m_terrainData;


public:
	static CIceBackGround*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};


#endif // Terrain_h__