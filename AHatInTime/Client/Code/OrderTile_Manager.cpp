#include "stdafx.h"
#include "Ball.h"
#include "Player.h"


#include "Export_Function.h"
#include "OrderTile_Manager.h"

IMPLEMENT_SINGLETON(COrderTile_Manger)


COrderTile_Manger::COrderTile_Manger()
	:m_currentIndex(0)
{
}

COrderTile_Manger::~COrderTile_Manger()
{
}
void COrderTile_Manger::Set_listOrder1(CGameObject * addObject)
{
	m_vecOrder1.push_back(addObject);
}
void COrderTile_Manger::Set_listOrder2(CGameObject * addObject)
{
	m_vecOrder2.push_back(addObject);
}
_bool COrderTile_Manger::IsSameOrder1(int vecNum, CGameObject * addObject)
{
	if (m_vecOrder1.size() <= vecNum)
		return false;

	if (addObject == m_vecOrder1[vecNum])
		return true;
	else
		return false;

}
_bool COrderTile_Manger::IsSameOrder2(int vecNum, CGameObject * addObject)
{
	if (m_vecOrder2.size() <= vecNum)
		return false;

	if (addObject == m_vecOrder2[vecNum])
		return true;
	else
		return false;
}
void COrderTile_Manger::Free(void)
{
	
}
