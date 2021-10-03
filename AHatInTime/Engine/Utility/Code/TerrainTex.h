#ifndef TerrainTex_h__
#define TerrainTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTerrainTex : public CVIBuffer
{
private:
	explicit CTerrainTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerrainTex(const CTerrainTex& rhs);
	virtual ~CTerrainTex(void);

public:
	const _vec3*			Get_VtxPos(void) const { return m_pPos; }
	
	// �� �Լ��� ���̸��� �ػ󵵿� ������ ������ ��ġ�ϴٴ� ���� �Ͽ� ����ϴ� �ڵ�
	_ulong			Get_VtxCntX(void) const { return m_iH.biWidth; }
	_ulong			Get_VtxCntZ(void) const { return m_iH.biHeight; }

	_ulong			Get_CntX(void) const { return m_cntX; }
	_ulong			Get_CntZ(void) const { return m_cntZ; }
	
	void			Copy_Index(INDEX32* pIndex, const _ulong& dwTriCnt);
public:
	HRESULT Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	virtual void Render_Buffer(void) override;

	void Reset_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ);

private:
	HANDLE					m_hFile;
	BITMAPFILEHEADER		m_fH;
	BITMAPINFOHEADER		m_iH;
	_vec3*					m_pPos = nullptr;
	_ulong					m_cntX;
	_ulong					m_cntZ;

public:
	static CTerrainTex*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv = 1);
	virtual CComponent*	Clone(void);
private:
	virtual void Free(void) override;

};

END
#endif // TerrainTex_h__
