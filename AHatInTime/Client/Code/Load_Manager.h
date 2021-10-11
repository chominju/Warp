#ifndef Load_Manager_h__
#define Load_Manager_h__

#include "Define.h"
#include "Export_Function.h"

class CLoad_Manager
{
private:
	CLoad_Manager();
	~CLoad_Manager();
public:
	static HRESULT Load_Terrain_Data(const wstring& filePath, CLayer*	pLayer,LPDIRECT3DDEVICE9 m_pGraphicDev);
	static HRESULT Load_Static_Object_Data(const wstring & filePath, CLayer*		pLayer,LPDIRECT3DDEVICE9 m_pGraphicDev);
	//static HRESULT Load_Terrain_Data(const _tchar * filePath, const _tchar * pLayerTag, LPDIRECT3DDEVICE9* m_pGraphicDev);
	//static HRESULT Load_Static_Object_Data(const _tchar*  filePath, const _tchar*  pLayerTag, LPDIRECT3DDEVICE9* m_pGraphicDev);
	//static HRESULT Load_Navi_Mesh_Data(const wstring& filePath);

};

#endif // Load_Manager_h__
