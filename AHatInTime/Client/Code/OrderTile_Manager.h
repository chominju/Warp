#ifndef OrderTileManager_h__
#define OrderTileManager_h__

#include "GameObject.h"
#include "Define.h"
#include "InteractionObject.h"

BEGIN(Engine)

class CStaticMesh;
class CTransform;
class CRenderer;
class CCalculator;
class CCollider;

END
class COrderTile_Manger
{
private:
	DECLARE_SINGLETON(COrderTile_Manger)
	COrderTile_Manger();
	~COrderTile_Manger();

public:


	void	Set_listOrder1(CGameObject* addObject);
	void	Set_listOrder2(CGameObject* addObject);

	_int	Get_CurrentIndex() { return m_currentIndex; }
	void	Reset_CurrentIndex() { m_currentIndex = 0; }
	_bool	IsSameOrder1(int vecNum , CGameObject* addObject);
	_bool	IsSameOrder2(int vecNum, CGameObject* addObject);

	CGameObject* Get_GameObjectOrder1(_int index) { return m_vecOrder1[index]; }
	CGameObject* Get_GameObjectOrder2(_int index) { return m_vecOrder2[index]; }

	_int	Get_GameObjectOrder1Size() { return m_vecOrder1.size(); }
	_int	Get_GameObjectOrder2Size() { return m_vecOrder2.size(); }

private:

	vector<CGameObject*> m_vecOrder1;
	vector<CGameObject*> m_vecOrder2;

	vector<CGameObject*> m_vecPlayerPush;

	_int				m_currentIndex;


private:


public:

private:
	virtual void		Free(void);
};


#endif // OrderTileManager_h__
