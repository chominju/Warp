#include "Calculator.h"
#include "TerrainTex.h"
#include "Transform.h"
#include "SphereCollider.h"
#include "..\Client\Code\Static_Object.h"
#include "..\Client\Code\InteractionObject.h"
#include "StaticMesh.h"
#include "Management.h"
#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "Collider.h"
#include <tchar.h>

USING(Engine)

Engine::CCalculator::CCalculator(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev)
{

}

Engine::CCalculator::CCalculator(const CCalculator& rhs)
	:CComponent(rhs)
{

}

Engine::CCalculator::~CCalculator(void)
{

}

HRESULT Engine::CCalculator::Ready_Calculator(void)
{
	//D3DXPLANE		Plane;

	//// 평면을 이루는 정점의 위치를 넣어주면 평면의 ABCD를 만들어주는 함수
	// D3DXPlaneFromPoints()

	 // 평면의 방정식

	
	

	 // x,y,z는 평면 위에 놓여있는 정점의 좌표
	 // a, b, c, d는 평면과 직각을 이루는 법선의 방향성

	return S_OK;
}

Engine::_float Engine::CCalculator::Compute_HeightOnTerrain(const _vec3* pPos, 
															const _vec3* pTerrainVtxPos, 
															const _ulong& dwCntX, 
															const _ulong& dwCntZ, 
															const _ulong& dwVtxItv)
{
	_ulong	dwIndex = _ulong(pPos->z / dwVtxItv) * dwCntX + _ulong(pPos->x / dwVtxItv);

	_float	fRatioX = (pPos->x - pTerrainVtxPos[dwIndex + dwCntX].x) / dwVtxItv;
	_float	fRatioZ = (pTerrainVtxPos[dwIndex + dwCntX].z - pPos->z) / dwVtxItv;;


	D3DXPLANE		Plane;


	// 오른쪽 위
	if (fRatioX > fRatioZ)
	{
		D3DXPlaneFromPoints(&Plane, &pTerrainVtxPos[dwIndex + dwCntX], 
									&pTerrainVtxPos[dwIndex + dwCntX + 1], 
									&pTerrainVtxPos[dwIndex + 1]);
	}
	else
	{
		D3DXPlaneFromPoints(&Plane, &pTerrainVtxPos[dwIndex + dwCntX],
									&pTerrainVtxPos[dwIndex + 1],
									&pTerrainVtxPos[dwIndex]);
	}
	// ax + by + cz + d = 0->y = ?
	// by = -ax - cz - d
	// y =(-ax - cz - d) / b

	return ((-Plane.a * pPos->x - Plane.c * pPos->z - Plane.d) / Plane.b);
}

Engine::CCalculator* Engine::CCalculator::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCalculator*	pInstance = new CCalculator(pGraphicDev);

	if (FAILED(pInstance->Ready_Calculator()))
		Safe_Release(pInstance);

	return pInstance;
}

void Engine::CCalculator::Free(void)
{
	CComponent::Free();
}

Engine::CComponent* Engine::CCalculator::Clone(void)
{
	return new CCalculator(*this);
}

Engine::_vec3 Engine::CCalculator::Picking_OnTerrain(HWND hWnd,
	const CTerrainTex* pTerrainBufferCom,
	const CTransform* pTerrainTransCom)
{
	POINT	ptMouse = {};

	GetCursorPos(&ptMouse);

	ScreenToClient(hWnd, &ptMouse);

	_vec3		vMousePos;

	D3DVIEWPORT9		ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));

	m_pGraphicDev->GetViewport(&ViewPort);

	// 뷰포트 영역의 좌표를 투영 영역의 좌표로 변환
	vMousePos.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
	vMousePos.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f;
	vMousePos.z = 0.f;

	// 투영 상태의 마우스를 뷰스페이스 상태로 변환
	_matrix		matProj;

	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, NULL, &matProj);
	D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matProj);

	// 뷰스페이스 상태의 마우스를 월드 영역으로 변환
	_vec3		vRayPos, vRayDir;

	vRayPos = _vec3(0.f, 0.f, 0.f);
	vRayDir = vMousePos - vRayPos;

	_matrix		matView;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

	// 월드 상태에서 로컬 영역까지 변환
	_matrix		matWorld;
	pTerrainTransCom->Get_WorldMatrix(&matWorld);
	D3DXMatrixInverse(&matWorld, NULL, &matWorld);

	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matWorld);

	_ulong		dwVtxCntX = pTerrainBufferCom->Get_VtxCntX();
	_ulong		dwVtxCntZ = pTerrainBufferCom->Get_VtxCntZ();

	const _vec3*		pTerrainVtx = pTerrainBufferCom->Get_VtxPos();

	_float		fU, fV, fDist;

	_ulong		dwVtxIdx[3];

	for (_ulong i = 0; i < dwVtxCntZ - 1; ++i)
	{
		for (_ulong j = 0; j < dwVtxCntX - 1; ++j)
		{
			_ulong	dwIndex = i * dwVtxCntX + j;

			// 오른쪽 위

			dwVtxIdx[0] = dwIndex + dwVtxCntX;
			dwVtxIdx[1] = dwIndex + dwVtxCntX + 1;
			dwVtxIdx[2] = dwIndex + 1;

			if(D3DXIntersectTri(&pTerrainVtx[dwVtxIdx[1]], 
								&pTerrainVtx[dwVtxIdx[2]],
								&pTerrainVtx[dwVtxIdx[0]], 
								&vRayPos, 
								&vRayDir,
								&fU, &fV, &fDist))
			{
				return _vec3(pTerrainVtx[dwVtxIdx[1]].x + (pTerrainVtx[dwVtxIdx[0]].x - pTerrainVtx[dwVtxIdx[1]].x) * fU,
							0.f,
							pTerrainVtx[dwVtxIdx[1]].z + (pTerrainVtx[dwVtxIdx[2]].z - pTerrainVtx[dwVtxIdx[1]].z) * fV);
			}
			
			// 왼쪽 아래
			dwVtxIdx[0] = dwIndex + dwVtxCntX;
			dwVtxIdx[1] = dwIndex + 1;
			dwVtxIdx[2] = dwIndex;

			if (D3DXIntersectTri(&pTerrainVtx[dwVtxIdx[2]],
								&pTerrainVtx[dwVtxIdx[0]],
								&pTerrainVtx[dwVtxIdx[1]],
								&vRayPos,
								&vRayDir,
								&fU, &fV, &fDist))
			{
				return _vec3(pTerrainVtx[dwVtxIdx[2]].x + (pTerrainVtx[dwVtxIdx[1]].x - pTerrainVtx[dwVtxIdx[2]].x) * fU,
							0.f,
							pTerrainVtx[dwVtxIdx[2]].z + (pTerrainVtx[dwVtxIdx[0]].z - pTerrainVtx[dwVtxIdx[2]].z) * fV);
			}
		}
	}

	return _vec3();
}

Engine::_bool Engine::CCalculator::Collision_InteractionObjectSensor(const _vec3* pDestMin,
													const _vec3* pDestMax, 
													const _matrix* pDestWorld, _vec3 playerRot)
{
	auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");

	int distNum = 4;

	m_collision_StaticObjectCurrnet.clear();
	m_collision_StaticObjectCompare.clear();

	for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
	{
	bool isCollisionX = true;
	bool isCollisionY = true;
	bool isCollisionZ = true;
		if (!iter->second->Get_Draw())
			continue;
		CCollider* getSensorColl = dynamic_cast<CInteractionObject*>(iter->second)->Get_ColliderSensor_Component();

		if (getSensorColl == nullptr)
			continue;

		_vec3		vDestMin, vDestMax, vSourMin, vSourMax;
		_float		fMin, fMax;

		D3DXVec3TransformCoord(&vDestMin, pDestMin, pDestWorld);
		D3DXVec3TransformCoord(&vDestMax, pDestMax, pDestWorld);

		D3DXVec3TransformCoord(&vSourMin, getSensorColl->Get_Min(), getSensorColl->Get_CollWorldMatrix());
		D3DXVec3TransformCoord(&vSourMax, getSensorColl->Get_Max(), getSensorColl->Get_CollWorldMatrix());

		_vec3 temp = vDestMin;
		if (vDestMax.x < vDestMin.x)
		{
			vDestMin.x = vDestMax.x;
			vDestMax.x = temp.x;
		}

		if (vDestMax.z < vDestMin.z)
		{
			vDestMin.z = vDestMax.z;
			vDestMax.z = temp.z;
		}

		_vec3 temp2 = vSourMin;
		if (vSourMax.x < vSourMin.x)
		{
			vSourMin.x = vSourMax.x;
			vSourMax.x = temp2.x;
		}

		if (vSourMax.z < vSourMin.z)
		{
			vSourMin.z = vSourMax.z;
			vSourMax.z = temp2.z;
		}

		// x축에서 바라봤을 때
		fMin = max(vDestMin.x, vSourMin.x);
		fMax = min(vDestMax.x, vSourMax.x);

		if (fMax < fMin)
			isCollisionX = false;

		//// y축에서 바라봤을 때

		//fMin = max(vDestMin.y, vSourMin.y);
		//fMax = min(vDestMax.y, vSourMax.y);

		//if (fMax < fMin)
		//	isCollisionY = false;

		// z축에서 바라봤을 때

		fMin = max(vDestMin.z, vSourMin.z);
		fMax = min(vDestMax.z, vSourMax.z);

		if (fMax < fMin)
			isCollisionZ = false;

		if (isCollisionX&&isCollisionY&&isCollisionZ)
			iter->second->Set_IsSensorColl(true);
		else
			iter->second->Set_IsSensorColl(false);
	}

	return true;
}


Engine::_bool Engine::CCalculator::Collision_AABB(const _vec3* pDestMin,
	const _vec3* pDestMax,
	const _matrix* pDestWorld,
	const _vec3* pSourMin,
	const _vec3* pSourMax,
	const _matrix* pSourWorld)
{
	_vec3		vDestMin, vDestMax, vSourMin, vSourMax;
	_float		fMin, fMax;

	D3DXVec3TransformCoord(&vDestMin, pDestMin, pDestWorld);
	D3DXVec3TransformCoord(&vDestMax, pDestMax, pDestWorld);

	D3DXVec3TransformCoord(&vSourMin, pSourMin, pSourWorld);
	D3DXVec3TransformCoord(&vSourMax, pSourMax, pSourWorld);

	// x축에서 바라봤을 때
	_vec3 temp = vDestMin;
	if (vDestMax.x < vDestMin.x)
	{
		vDestMin.x = vDestMax.x;
		vDestMax.x = temp.x;
	}

	if (vDestMax.z < vDestMin.z)
	{
		vDestMin.z = vDestMax.z;
		vDestMax.z = temp.z;
	}

	fMin = max(vDestMin.x, vSourMin.x);
	fMax = min(vDestMax.x, vSourMax.x);

	if (fMax < fMin)
		return false;

	// y축에서 바라봤을 때

	fMin = max(vDestMin.y, vSourMin.y);
	fMax = min(vDestMax.y, vSourMax.y);

	if (fMax < fMin)
		return false;

	// z축에서 바라봤을 때

	fMin = max(vDestMin.z, vSourMin.z);
	fMax = min(vDestMax.z, vSourMax.z);

	if (fMax < fMin)
		return false;

	return true;
}

//_bool CCalculator::Collision_StaticObject_AABB(const _vec3 * pDestMin, const _vec3 * pDestMax, const _matrix * pDestWorld, _vec3 playerRot)
//{
//	auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"StaticObject_Layer");
//
//	bool isCollisionX = true;
//	bool isCollisionY = true;
//	bool isCollisionZ = true;
//	int distNum = 4;
//
//	m_collisionCGameObjectCurrnet.clear();
//	m_collisionCGameObjectCompare.clear();
//
//	for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
//	{
//		if (!iter->second->Get_Draw())
//			continue;
//		CCollider* getColl = dynamic_cast<CInteractionObject*>(iter->second)->Get_Collider_Component();
//
//		_vec3		vDestMin, vDestMax, vSourMin, vSourMax;
//		_float		fMin, fMax;
//
//		D3DXVec3TransformCoord(&vDestMin, pDestMin, pDestWorld);
//		D3DXVec3TransformCoord(&vDestMax, pDestMax, pDestWorld);
//
//		D3DXVec3TransformCoord(&vSourMin, getColl->Get_Min(), getColl->Get_CollWorldMatrix());
//		D3DXVec3TransformCoord(&vSourMax, getColl->Get_Max(), getColl->Get_CollWorldMatrix());
//
//		// x축에서 바라봤을 때
//		_vec3 temp = vDestMin;
//		if (vDestMax.x < vDestMin.x)
//		{
//			vDestMin.x = vDestMax.x;
//			vDestMax.x = temp.x;
//		}
//
//		if (vDestMax.z < vDestMin.z)
//		{
//			vDestMin.z = vDestMax.z;
//			vDestMax.z = temp.z;
//		}
//
//		fMin = max(vDestMin.x, vSourMax.x);
//		fMax = min(vDestMax.x, vSourMin.x);
//
//		if (fMax < fMin)
//			isCollisionX = false;
//
//		//// y축에서 바라봤을 때
//
//		//fMin = max(vDestMin.y, vSourMin.y);
//		//fMax = min(vDestMax.y, vSourMax.y);
//
//		//if (fMax < fMin)
//		//	isCollisionY = false;
//
//		// z축에서 바라봤을 때
//
//		fMin = max(vDestMin.z, vSourMax.z);
//		fMax = min(vDestMax.z, vSourMin.z);
//
//		if (fMax < fMin)
//			isCollisionZ = false;
//
//		if (isCollisionX&&isCollisionY&&isCollisionZ)
//			iter->second->Set_IsColl(true);
//		else
//			iter->second->Set_IsColl(false);
//	}
//
//	return true;
//}

_bool CCalculator::Collision_OBB(const _vec3 * pDestMin, const _vec3 * pDestMax, 
									const _matrix * pDestWorld, 
									const _vec3 * pSourMin, const _vec3 * pSourMax, 
									const _matrix * pSourWorld)
{
	OBB		tObb[2];
	ZeroMemory(tObb, sizeof(OBB) * 2);

	Set_Point(&tObb[0], pDestMin, pDestMax);
	Set_Point(&tObb[1], pSourMin, pSourMax);

	for (_uint i = 0; i < 8; ++i)
	{
		D3DXVec3TransformCoord(&tObb[0].vPoint[i], &tObb[0].vPoint[i], pDestWorld);
		D3DXVec3TransformCoord(&tObb[1].vPoint[i], &tObb[1].vPoint[i], pSourWorld);
	}

	D3DXVec3TransformCoord(&tObb[0].vCenter, &tObb[0].vCenter, pDestWorld);
	D3DXVec3TransformCoord(&tObb[1].vCenter, &tObb[1].vCenter, pSourWorld);

	for (_uint i = 0; i < 2; ++i)
		Set_Axis(&tObb[i]);

	_float	fDistance[3];		// 0번 : 첫 번째 obb의 중점에서 각 면을 향해 뻗어 나가는 벡터들을 각 축의 투영한 길이의 합
								// 1번 : 두 번째 obb의 중점에서 각 면을 향해 뻗어 나가는 벡터들을 각 축의 투영한 길이의 합
								// 2번 : 0번 obb의 중점에서 1번 obb의 중점으로 향하는 방향 벡터를 각 축의 투영한 길이의 합

	for (_int i = 0; i < 2; ++i)
	{
		for (_int j = 0; j < 3; ++j)
		{
			fDistance[0] = fabs(D3DXVec3Dot(&tObb[0].vProjAxis[0], &tObb[i].vAxis[j])) +
						   fabs(D3DXVec3Dot(&tObb[0].vProjAxis[1], &tObb[i].vAxis[j])) +
						   fabs(D3DXVec3Dot(&tObb[0].vProjAxis[2], &tObb[i].vAxis[j]));

			fDistance[1] = fabs(D3DXVec3Dot(&tObb[1].vProjAxis[0], &tObb[i].vAxis[j])) +
							fabs(D3DXVec3Dot(&tObb[1].vProjAxis[1], &tObb[i].vAxis[j])) +
							fabs(D3DXVec3Dot(&tObb[1].vProjAxis[2], &tObb[i].vAxis[j]));

			fDistance[2] = fabs(D3DXVec3Dot(&(tObb[1].vCenter - tObb[0].vCenter), &tObb[i].vAxis[j]));
				
			if (fDistance[2] > fDistance[0] + fDistance[1])
				return false;
		}
	}
	
	return true;
}

_bool CCalculator::Collision_StaticObject(/*const _vec3 * pDestMin, const _vec3 * pDestMax, const _matrix * pDestWorld,*/ CSphereCollider * playerCollider, _bool pushKey[], _bool isKeyStop[])
{
	auto getStaticObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"StaticObject_Layer");

	bool isCollision = false;
	int distNum = 4;

	m_collision_StaticObjectCurrnet.clear();
	m_collision_StaticObjectCompare.clear();

	for (auto iter = getStaticObject->begin(); iter != getStaticObject->end(); iter++)
	{
		if (!_tcscmp(dynamic_cast<CStatic_Objects*>(iter->second)->Get_Static_Objects_Data().m_objectTextureName, L"Proto_Mesh_DoorClearFin.x"))
			continue;
		CComponent* getComponent = iter->second->Get_Component(L"Com_Collider", ID_STATIC);
		const _vec3 * pDestMin = dynamic_cast<CCollider*>(getComponent)->Get_Min();
		const _vec3 * pDestMax = dynamic_cast<CCollider*>(getComponent)->Get_Max();
		const _matrix * pDestWorld = dynamic_cast<CCollider*>(getComponent)->Get_CollWorldMatrix();
		_vec3		vDestMin, vDestMax;
		_float		fMin, fMax;
		float dist = 0.f;

		D3DXVec3TransformCoord(&vDestMin, pDestMin, pDestWorld);
		D3DXVec3TransformCoord(&vDestMax, pDestMax, pDestWorld);

		// test
		_vec3 temp = vDestMin;
		if (vDestMax.x < vDestMin.x)
		{
			vDestMin.x = vDestMax.x;
			vDestMax.x = temp.x;
		}

		if (vDestMax.y < vDestMin.y)
		{
			vDestMin.y = vDestMax.y;
			vDestMax.y = temp.y;
		}

		if (vDestMax.z < vDestMin.z)
		{
			vDestMin.z = vDestMax.z;
			vDestMax.z = temp.z;
		}


		// x축에서 바라봤을 때

		const _matrix *playerMatrix = playerCollider->Get_CollWorldMatrix();
		_matrix		matWorld;
		D3DXMatrixInverse(&matWorld, NULL, playerMatrix);
		float ridius = playerCollider->Get_Radius();
		_vec3 objectVec3 = { pDestWorld->_41, pDestWorld->_42 , pDestWorld->_43 };
		_vec3 playerVec3 = { playerMatrix->_41, 0.f ,playerMatrix->_43 };

		float playerObjectDist = D3DXVec3Length(&(objectVec3 - playerVec3));


		float x = max(vDestMin.x, min(playerVec3.x, vDestMax.x));
		float y = max(vDestMin.y, min(playerVec3.y, vDestMax.y));
		float z = max(vDestMin.z, min(playerVec3.z, vDestMax.z));

		// this is the same as isPointInsideSphere
		float distance = sqrt((x - playerVec3.x) * (x - playerVec3.x) +
			(y - playerVec3.y) * (y - playerVec3.y) +
			(z - playerVec3.z) * (z - playerVec3.z));

		float radius = playerCollider->Get_Radius();
		//radius = sqrt(radius);

		int sensor = 2;
		/*if (!_tcscmp(dynamic_cast<CStatic_Objects*>(iter->second)->Get_Static_Objects_Data().m_objectTextureName, L"Proto_Mesh_Maze_Wall1.x"))
			sensor = 5;*/

		if (distance < sensor)
		{
			iter->second->Set_IsColl(true);
			isCollision = true;

			//iter->second->Set_StopPlayer(pushKey);
			m_collision_StaticObjectCurrnet.push_back(iter->second);
		}
		else
			iter->second->Set_IsColl(false);
	}

	bool isVecPush = false;
	bool isDifferent = false;

	// 지금 현재 충돌체크 갯수
	int vecSize = m_collision_StaticObjectCurrnet.size();

	// 이전 충돌체크 충돌체크 갯수
	int vecSizeAfter = m_collision_StaticObjectPrev.size();

	if (vecSize == 1 && vecSizeAfter == 2)
	{
		int i;
		i = 10;
	}

	// 현재 <= 이전
	if (vecSize <= vecSizeAfter)
	{
		for (int i = 0; i < vecSizeAfter; i++)
		{
			isVecPush = false;
			for (int j = 0; j < vecSize; j++)
			{
				if (m_collision_StaticObjectCurrnet[j] == m_collision_StaticObjectPrev[i])
					isVecPush = true;
			}
			if (!isVecPush)
				m_collision_StaticObjectCompare.push_back(m_collision_StaticObjectPrev[i]);
		}

		int compareLength = m_collision_StaticObjectCompare.size();
		for (int i = 0; i < compareLength; i++)
		{
			bool * getStopPlayer = m_collision_StaticObjectCompare[i]->Get_StopPlayer();
			for (int j = 0; j < KEY_END; j++)
			{
				if (getStopPlayer[j])
					isKeyStop[j] = false;
			}
			m_collision_StaticObjectCompare[i]->Reset_StopPlayer();
		}

	}
	// 현재 > 이전
	else
	{
		for (int i = 0; i < vecSize; i++)
		{
			isVecPush = false;
			for (int j = 0; j < vecSizeAfter; j++)
			{
				if (m_collision_StaticObjectCurrnet[i] == m_collision_StaticObjectPrev[j])
					isVecPush = true;
			}
			if (!isVecPush)
				m_collision_StaticObjectCompare.push_back(m_collision_StaticObjectCurrnet[i]);
		}

		int compareLength = m_collision_StaticObjectCompare.size();
		for (int i = 0; i < compareLength; i++)
		{
			m_collision_StaticObjectCompare[i]->Set_StopPlayer(pushKey);
			for (int j = 0; j < KEY_END; j++)
			{
				if (pushKey[j])
					isKeyStop[j] = true;
			}
		}
	}

	for (int i = 0; i < vecSize; i++)
	{
		auto stopPlayer = m_collision_StaticObjectCurrnet[i]->Get_StopPlayer();
		for (int j = 0; j < KEY_END; j++)
		{
			if (stopPlayer[j])
				isKeyStop[j] = true;
		}
	}

	m_collision_StaticObjectPrev.clear();
	for (int i = 0; i < vecSize; i++)
		m_collision_StaticObjectPrev.push_back(m_collision_StaticObjectCurrnet[i]);
	/*{
		bool * getStopPlayer = m_collisionCGameObjectCurrnet[i]->Get_StopPlayer();
		for (int i = 0; i < KEY_END; i++)
		{
			if (getStopPlayer[i])
				isKeyStop[i] = true;
		}
		m_collisionCGameObjectPrev.push_back(m_collisionCGameObjectCurrnet[i]);
	}*/
	if (m_collision_StaticObjectCompare.size())
		return true;
	else
		return false;
}

_bool CCalculator::Collision_InteractionObject(CSphereCollider * playerCollider, _bool pushKey[], _bool isKeyStop[])
{
	auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");

	bool isCollision = false;
	int distNum = 4;

	m_collision_InteractionObjectCurrnet.clear();
	m_collision_InteractionObjectCompare.clear();

	for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
	{
		CCollider* getSensorColl = dynamic_cast<CInteractionObject*>(iter->second)->Get_Collider_Component();
		if (getSensorColl == nullptr)
			continue;
		if (!iter->second->Get_Draw())
			continue;
		const _vec3 * pDestMin = dynamic_cast<CCollider*>(getSensorColl)->Get_Min();
		const _vec3 * pDestMax = dynamic_cast<CCollider*>(getSensorColl)->Get_Max();
		const _matrix * pDestWorld = dynamic_cast<CCollider*>(getSensorColl)->Get_CollWorldMatrix();
		_vec3		vDestMin, vDestMax;
		_float		fMin, fMax;
		float dist = 0.f;

		D3DXVec3TransformCoord(&vDestMin, pDestMin, pDestWorld);
		D3DXVec3TransformCoord(&vDestMax, pDestMax, pDestWorld);


		// test
		_vec3 temp = vDestMin;
		if (vDestMax.x < vDestMin.x)
		{
			vDestMin.x = vDestMax.x;
			vDestMax.x = temp.x;
		}

		if (vDestMax.y < vDestMin.y)
		{
			vDestMin.y = vDestMax.y;
			vDestMax.y = temp.y;
		}

		if (vDestMax.z < vDestMin.z)
		{
			vDestMin.z = vDestMax.z;
			vDestMax.z = temp.z;
		}



		// x축에서 바라봤을 때

		const _matrix *playerMatrix = playerCollider->Get_CollWorldMatrix();
		_matrix		matWorld;
		D3DXMatrixInverse(&matWorld, NULL, playerMatrix);
		float ridius = playerCollider->Get_Radius();
		_vec3 objectVec3 = { pDestWorld->_41, pDestWorld->_42 , pDestWorld->_43 };
		_vec3 playerVec3 = { playerMatrix->_41, 0.f ,playerMatrix->_43 };

		float playerObjectDist = D3DXVec3Length(&(objectVec3 - playerVec3));


		float x = max(vDestMin.x, min(playerVec3.x, vDestMax.x));
		float y = max(vDestMin.y, min(playerVec3.y, vDestMax.y));
		float z = max(vDestMin.z, min(playerVec3.z, vDestMax.z));

		// this is the same as isPointInsideSphere
		float distance = sqrt((x - playerVec3.x) * (x - playerVec3.x) +
			(y - playerVec3.y) * (y - playerVec3.y) +
			(z - playerVec3.z) * (z - playerVec3.z));

		float radius = playerCollider->Get_Radius();
		//radius = sqrt(radius);

		int sensor = 2;

		if (distance < sensor)
		{
			iter->second->Set_IsColl(true);
			isCollision = true;

			//iter->second->Set_StopPlayer(pushKey);
			m_collision_InteractionObjectCurrnet.push_back(iter->second);
		}
		else
			iter->second->Set_IsColl(false);
	}

	bool isVecPush = false;
	bool isDifferent = false;

	// 지금 현재 충돌체크 갯수
	int vecSize = m_collision_InteractionObjectCurrnet.size();

	// 이전 충돌체크 충돌체크 갯수
	int vecSizeAfter = m_collision_InteractionObjectPrev.size();

	if (vecSize == 1 && vecSizeAfter == 2)
	{
		int i;
		i = 10;
	}

	// 현재 <= 이전
	if (vecSize <= vecSizeAfter)
	{
		for (int i = 0; i < vecSizeAfter; i++)
		{
			isVecPush = false;
			for (int j = 0; j < vecSize; j++)
			{
				if (m_collision_InteractionObjectCurrnet[j] == m_collision_InteractionObjectPrev[i])
					isVecPush = true;
			}
			if (!isVecPush)
				m_collision_InteractionObjectCompare.push_back(m_collision_InteractionObjectPrev[i]);
		}

		int compareLength = m_collision_InteractionObjectCompare.size();
		for (int i = 0; i < compareLength; i++)
		{
			bool * getStopPlayer = m_collision_InteractionObjectCompare[i]->Get_StopPlayer();
			for (int j = 0; j < KEY_END; j++)
			{
				if (getStopPlayer[j])
					isKeyStop[j] = false;
			}
			m_collision_InteractionObjectCompare[i]->Reset_StopPlayer();
		}

	}
	// 현재 > 이전
	else
	{
		for (int i = 0; i < vecSize; i++)
		{
			isVecPush = false;
			for (int j = 0; j < vecSizeAfter; j++)
			{
				if (m_collision_InteractionObjectCurrnet[i] == m_collision_InteractionObjectPrev[j])
					isVecPush = true;
			}
			if (!isVecPush)
				m_collision_InteractionObjectCompare.push_back(m_collision_InteractionObjectCurrnet[i]);
		}

		int compareLength = m_collision_InteractionObjectCompare.size();
		for (int i = 0; i < compareLength; i++)
		{
			m_collision_InteractionObjectCompare[i]->Set_StopPlayer(pushKey);
			for (int j = 0; j < KEY_END; j++)
			{
				if (pushKey[j])
					isKeyStop[j] = true;
			}
		}
	}

	for (int i = 0; i < vecSize; i++)
	{
		auto stopPlayer = m_collision_InteractionObjectCurrnet[i]->Get_StopPlayer();
		for (int j = 0; j < KEY_END; j++)
		{
			if (stopPlayer[j])
				isKeyStop[j] = true;
		}
	}

	m_collision_InteractionObjectPrev.clear();
	for (int i = 0; i < vecSize; i++)
		m_collision_InteractionObjectPrev.push_back(m_collision_InteractionObjectCurrnet[i]);
	/*{
	bool * getStopPlayer = m_collisionCGameObjectCurrnet[i]->Get_StopPlayer();
	for (int i = 0; i < KEY_END; i++)
	{
	if (getStopPlayer[i])
	isKeyStop[i] = true;
	}
	m_collisionCGameObjectPrev.push_back(m_collisionCGameObjectCurrnet[i]);
	}*/

	if (m_collision_InteractionObjectCompare.size())
		return true;
	else
		return false;

	//auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");

	//bool isCollision = false;
	//int distNum = 4;

	//m_collisionCGameObjectCurrnet.clear();
	//m_collisionCGameObjectCompare.clear();

	//for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
	//{
	//	if (!iter->second->Get_Draw())
	//		continue;

	//	CComponent* getComponent = iter->second->Get_Component(L"Com_Collider", ID_STATIC);
	//	const _vec3 * pDestMin = dynamic_cast<CCollider*>(getComponent)->Get_Min();
	//	const _vec3 * pDestMax = dynamic_cast<CCollider*>(getComponent)->Get_Max();
	//	const _matrix * pDestWorld = dynamic_cast<CCollider*>(getComponent)->Get_CollWorldMatrix();
	//	_vec3		vDestMin, vDestMax;
	//	_float		fMin, fMax;
	//	float dist = 0.f;

	//	D3DXVec3TransformCoord(&vDestMin, pDestMin, pDestWorld);
	//	D3DXVec3TransformCoord(&vDestMax, pDestMax, pDestWorld);


	//	// x축에서 바라봤을 때

	//	const _matrix *playerMatrix = playerCollider->Get_CollWorldMatrix();
	//	_matrix		matWorld;
	//	D3DXMatrixInverse(&matWorld, NULL, playerMatrix);
	//	float ridius = playerCollider->Get_Radius();
	//	_vec3 objectVec3 = { pDestWorld->_41, pDestWorld->_42 , pDestWorld->_43 };
	//	_vec3 playerVec3 = { playerMatrix->_41, 0.f ,playerMatrix->_43 };

	//	float playerObjectDist = D3DXVec3Length(&(objectVec3 - playerVec3));


	//	float x = max(vDestMin.x, min(playerVec3.x, vDestMax.x));
	//	float y = max(vDestMin.y, min(playerVec3.y, vDestMax.y));
	//	float z = max(vDestMin.z, min(playerVec3.z, vDestMax.z));

	//	// this is the same as isPointInsideSphere
	//	float distance = sqrt((x - playerVec3.x) * (x - playerVec3.x) +
	//		(y - playerVec3.y) * (y - playerVec3.y) +
	//		(z - playerVec3.z) * (z - playerVec3.z));

	//	float radius = playerCollider->Get_Radius();
	//	//radius = sqrt(radius);

	//	int sensor = 2;

	//	if (distance < sensor)
	//	{
	//		iter->second->Set_IsColl(true);
	//		isCollision = true;

	//		//iter->second->Set_StopPlayer(pushKey);
	//		m_collisionCGameObjectCurrnet.push_back(iter->second);
	//	}
	//	else
	//		iter->second->Set_IsColl(false);
	//}

	//bool isVecPush = false;
	//bool isDifferent = false;

	//// 지금 현재 충돌체크 갯수
	//int vecSize = m_collisionCGameObjectCurrnet.size();

	//// 이전 충돌체크 충돌체크 갯수
	//int vecSizeAfter = m_collisionCGameObjectPrev.size();

	//if (vecSize == 1 && vecSizeAfter == 2)
	//{
	//	int i;
	//	i = 10;
	//}

	//// 현재 <= 이전
	//if (vecSize <= vecSizeAfter)
	//{
	//	for (int i = 0; i < vecSizeAfter; i++)
	//	{
	//		isVecPush = false;
	//		for (int j = 0; j < vecSize; j++)
	//		{
	//			if (m_collisionCGameObjectCurrnet[j] == m_collisionCGameObjectPrev[i])
	//				isVecPush = true;
	//		}
	//		if (!isVecPush)
	//			m_collisionCGameObjectCompare.push_back(m_collisionCGameObjectPrev[i]);
	//	}

	//	int compareLength = m_collisionCGameObjectCompare.size();
	//	for (int i = 0; i < compareLength; i++)
	//	{
	//		bool * getStopPlayer = m_collisionCGameObjectCompare[i]->Get_StopPlayer();
	//		for (int j = 0; j < KEY_END; j++)
	//		{
	//			if (getStopPlayer[j])
	//				isKeyStop[j] = false;
	//		}
	//		m_collisionCGameObjectCompare[i]->Reset_StopPlayer();
	//	}

	//}
	//// 현재 > 이전
	//else
	//{
	//	for (int i = 0; i < vecSize; i++)
	//	{
	//		isVecPush = false;
	//		for (int j = 0; j < vecSizeAfter; j++)
	//		{
	//			if (m_collisionCGameObjectCurrnet[i] == m_collisionCGameObjectPrev[j])
	//				isVecPush = true;
	//		}
	//		if (!isVecPush)
	//			m_collisionCGameObjectCompare.push_back(m_collisionCGameObjectCurrnet[i]);
	//	}

	//	int compareLength = m_collisionCGameObjectCompare.size();
	//	for (int i = 0; i < compareLength; i++)
	//	{
	//		m_collisionCGameObjectCompare[i]->Set_StopPlayer(pushKey);
	//		for (int j = 0; j < KEY_END; j++)
	//		{
	//			if (pushKey[j])
	//				isKeyStop[j] = true;
	//		}
	//	}
	//}

	//for (int i = 0; i < vecSize; i++)
	//{
	//	auto stopPlayer = m_collisionCGameObjectCurrnet[i]->Get_StopPlayer();
	//	for (int j = 0; j < KEY_END; j++)
	//	{
	//		if (stopPlayer[j])
	//			isKeyStop[j] = true;
	//	}
	//}

	//m_collisionCGameObjectPrev.clear();
	//for (int i = 0; i < vecSize; i++)
	//	m_collisionCGameObjectPrev.push_back(m_collisionCGameObjectCurrnet[i]);


	return true;
}

_bool CCalculator::Collision_Object_StaticObject(CCollider * ObjectCollider)
{
	auto getStaticObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"StaticObject_Layer");

	bool isCollisionX = false;
	bool isCollisionZ = false;
	int distNum = 4;
	for (auto iter = getStaticObject->begin(); iter != getStaticObject->end(); iter++)
	{
		isCollisionX = false;
		isCollisionZ = false;
		if (!_tcscmp(dynamic_cast<CStatic_Objects*>(iter->second)->Get_Static_Objects_Data().m_objectTextureName, L"Proto_Mesh_Table2.x"))
		{
			int a;
			a = 10;
		}
		CCollider* getColl = dynamic_cast<CStatic_Objects*>(iter->second)->Get_Collider_Component();
		if (getColl == nullptr)
			continue;
		if (!iter->second->Get_Draw())
			continue;
		const _vec3 * pDestMin = dynamic_cast<CCollider*>(getColl)->Get_Min();
		const _vec3 * pDestMax = dynamic_cast<CCollider*>(getColl)->Get_Max();

		const _vec3 * pSourMin = ObjectCollider->Get_Min();
		const _vec3 * pSourMax = ObjectCollider->Get_Max();

		const _matrix * pDestWorld = dynamic_cast<CCollider*>(getColl)->Get_CollWorldMatrix();
		const _matrix * pSourWorld = ObjectCollider->Get_CollWorldMatrix();
		_vec3		vDestMin, vDestMax, vSourMin, vSourMax;
		_float		fMin, fMax;
		//float dist = 0.f;

		D3DXVec3TransformCoord(&vDestMin, pDestMin, pDestWorld);
		D3DXVec3TransformCoord(&vDestMax, pDestMax, pDestWorld);

		D3DXVec3TransformCoord(&vSourMin, pSourMin, pSourWorld);
		D3DXVec3TransformCoord(&vSourMax, pSourMax, pSourWorld);


		// x축에서 바라봤을 때
		_vec3 temp = vDestMin;
		if (vDestMax.x < vDestMin.x)
		{
			vDestMin.x = vDestMax.x;
			vDestMax.x = temp.x;
		}

		if (vDestMax.z < vDestMin.z)
		{
			vDestMin.z = vDestMax.z;
			vDestMax.z = temp.z;
		}

		_vec3 temp2 = vSourMin;
		if (vSourMax.x < vSourMin.x)
		{
			vSourMin.x = vSourMax.x;
			vSourMax.x = temp2.x;
		}

		if (vSourMax.z < vSourMin.z)
		{
			vSourMin.z = vSourMax.z;
			vSourMax.z = temp2.z;
		}

		fMin = max(vDestMin.x, vSourMin.x);
		fMax = min(vDestMax.x, vSourMax.x);

		if (fMax >= fMin+0.5)
			isCollisionX = true;

		// y축에서 바라봤을 때

		//fMin = max(vDestMin.y, vSourMin.y);
		//fMax = min(vDestMax.y, vSourMax.y);

		//if (fMax < fMin)
		//	return false;

		// z축에서 바라봤을 때

		fMin = max(vDestMin.z, vSourMin.z);
		fMax = min(vDestMax.z, vSourMax.z);

		if (fMax >= fMin)
			isCollisionZ = true;
		if (isCollisionX && isCollisionZ)
			break;
	}
	if (isCollisionX && isCollisionZ)
		return true;
	else 
		return false;
	//	// test
	//	_vec3 temp = vDestMin;
	//	if (vDestMax.x < vDestMin.x)
	//	{
	//		vDestMin.x = vDestMax.x;
	//		vDestMax.x = temp.x;
	//	}

	//	if (vDestMax.y < vDestMin.y)
	//	{
	//		vDestMin.y = vDestMax.y;
	//		vDestMax.y = temp.y;
	//	}

	//	if (vDestMax.z < vDestMin.z)
	//	{
	//		vDestMin.z = vDestMax.z;
	//		vDestMax.z = temp.z;
	//	}



	//	// x축에서 바라봤을 때

	//	const _matrix *playerMatrix = playerCollider->Get_CollWorldMatrix();
	//	_matrix		matWorld;
	//	D3DXMatrixInverse(&matWorld, NULL, playerMatrix);
	//	float ridius = playerCollider->Get_Radius();
	//	_vec3 objectVec3 = { pDestWorld->_41, pDestWorld->_42 , pDestWorld->_43 };
	//	_vec3 playerVec3 = { playerMatrix->_41, 0.f ,playerMatrix->_43 };

	//	float playerObjectDist = D3DXVec3Length(&(objectVec3 - playerVec3));


	//	float x = max(vDestMin.x, min(playerVec3.x, vDestMax.x));
	//	float y = max(vDestMin.y, min(playerVec3.y, vDestMax.y));
	//	float z = max(vDestMin.z, min(playerVec3.z, vDestMax.z));

	//	// this is the same as isPointInsideSphere
	//	float distance = sqrt((x - playerVec3.x) * (x - playerVec3.x) +
	//		(y - playerVec3.y) * (y - playerVec3.y) +
	//		(z - playerVec3.z) * (z - playerVec3.z));

	//	float radius = playerCollider->Get_Radius();
	//	//radius = sqrt(radius);

	//	int sensor = 2;

	//	if (distance < sensor)
	//	{
	//		iter->second->Set_IsColl(true);
	//		isCollision = true;

	//		//iter->second->Set_StopPlayer(pushKey);
	//		m_collision_InteractionObjectCurrnet.push_back(iter->second);
	//	}
	//	else
	//		iter->second->Set_IsColl(false);
	//}


	//_vec3		vDestMin, vDestMax, vSourMin, vSourMax;
	//_float		fMin, fMax;

	//D3DXVec3TransformCoord(&vDestMin, pDestMin, pDestWorld);
	//D3DXVec3TransformCoord(&vDestMax, pDestMax, pDestWorld);

	//D3DXVec3TransformCoord(&vSourMin, pSourMin, pSourWorld);
	//D3DXVec3TransformCoord(&vSourMax, pSourMax, pSourWorld);

	//// x축에서 바라봤을 때
	//_vec3 temp = vDestMin;
	//if (vDestMax.x < vDestMin.x)
	//{
	//	vDestMin.x = vDestMax.x;
	//	vDestMax.x = temp.x;
	//}

	//if (vDestMax.z < vDestMin.z)
	//{
	//	vDestMin.z = vDestMax.z;
	//	vDestMax.z = temp.z;
	//}

	//fMin = max(vDestMin.x, vSourMin.x);
	//fMax = min(vDestMax.x, vSourMax.x);

	//if (fMax < fMin)
	//	return false;

	//// y축에서 바라봤을 때

	//fMin = max(vDestMin.y, vSourMin.y);
	//fMax = min(vDestMax.y, vSourMax.y);

	//if (fMax < fMin)
	//	return false;

	//// z축에서 바라봤을 때

	//fMin = max(vDestMin.z, vSourMin.z);
	//fMax = min(vDestMax.z, vSourMax.z);

	//if (fMax < fMin)
	//	return false;

	//return true;
}

_bool CCalculator::Collision_Warp_InteractionObject(CSphereCollider * playerCollider, _bool *playerHideAble, CGameObject*& hideObject)
{
	auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"InteractionObject_Layer");

	bool isCollision = false;
	int distNum = 4;

	for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
	{
		CCollider* getSensorColl = dynamic_cast<CInteractionObject*>(iter->second)->Get_Collider_Component();
		if (getSensorColl == nullptr)
			continue;
		if (!iter->second->Get_Draw())
			continue;
		const _vec3 * pDestMin = dynamic_cast<CCollider*>(getSensorColl)->Get_Min();
		const _vec3 * pDestMax = dynamic_cast<CCollider*>(getSensorColl)->Get_Max();
		const _matrix * pDestWorld = dynamic_cast<CCollider*>(getSensorColl)->Get_CollWorldMatrix();
		_vec3		vDestMin, vDestMax;
		_float		fMin, fMax;
		float dist = 0.f;

		D3DXVec3TransformCoord(&vDestMin, pDestMin, pDestWorld);
		D3DXVec3TransformCoord(&vDestMax, pDestMax, pDestWorld);


		// test
		_vec3 temp = vDestMin;
		if (vDestMax.x < vDestMin.x)
		{
			vDestMin.x = vDestMax.x;
			vDestMax.x = temp.x;
		}

		if (vDestMax.y < vDestMin.y)
		{
			vDestMin.y = vDestMax.y;
			vDestMax.y = temp.y;
		}

		if (vDestMax.z < vDestMin.z)
		{
			vDestMin.z = vDestMax.z;
			vDestMax.z = temp.z;
		}



		// x축에서 바라봤을 때

		const _matrix *playerMatrix = playerCollider->Get_CollWorldMatrix();
		_matrix		matWorld;
		D3DXMatrixInverse(&matWorld, NULL, playerMatrix);
		float ridius = playerCollider->Get_Radius();
		_vec3 objectVec3 = { pDestWorld->_41, pDestWorld->_42 , pDestWorld->_43 };
		_vec3 playerVec3 = { playerMatrix->_41, 0.f ,playerMatrix->_43 };

		float playerObjectDist = D3DXVec3Length(&(objectVec3 - playerVec3));


		float x = max(vDestMin.x, min(playerVec3.x, vDestMax.x));
		float y = max(vDestMin.y, min(playerVec3.y, vDestMax.y));
		float z = max(vDestMin.z, min(playerVec3.z, vDestMax.z));

		// this is the same as isPointInsideSphere
		float distance = sqrt((x - playerVec3.x) * (x - playerVec3.x) +
			(y - playerVec3.y) * (y - playerVec3.y) +
			(z - playerVec3.z) * (z - playerVec3.z));

		float radius = playerCollider->Get_Radius();
		//radius = sqrt(radius);

		int sensor = 2;

		if (distance < sensor)
		{
			isCollision = true;

			*playerHideAble = dynamic_cast<CInteractionObject*>(iter->second)->Get_IsObject_PlayerHide();
			if (*playerHideAble)
				hideObject = iter->second;
			break;
		}

	}
	if (!isCollision)
	{
		*playerHideAble = false;
		hideObject = nullptr;
	}
	return isCollision;
}

_bool CCalculator::Collision_Warp_StaticObject(CSphereCollider * playerCollider)
{
	auto getStaticObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"StaticObject_Layer");

	bool isCollision = false;
	int distNum = 4;

	m_collision_StaticObjectCurrnet.clear();
	m_collision_StaticObjectCompare.clear();

	for (auto iter = getStaticObject->begin(); iter != getStaticObject->end(); iter++)
	{
		if (!_tcscmp(dynamic_cast<CStatic_Objects*>(iter->second)->Get_Static_Objects_Data().m_objectTextureName, L"Proto_Mesh_DoorClearFin.x"))
			continue;
		CComponent* getComponent = iter->second->Get_Component(L"Com_Collider", ID_STATIC);
		const _vec3 * pDestMin = dynamic_cast<CCollider*>(getComponent)->Get_Min();
		const _vec3 * pDestMax = dynamic_cast<CCollider*>(getComponent)->Get_Max();
		const _matrix * pDestWorld = dynamic_cast<CCollider*>(getComponent)->Get_CollWorldMatrix();
		_vec3		vDestMin, vDestMax;
		_float		fMin, fMax;
		float dist = 0.f;

		D3DXVec3TransformCoord(&vDestMin, pDestMin, pDestWorld);
		D3DXVec3TransformCoord(&vDestMax, pDestMax, pDestWorld);

		// test
		_vec3 temp = vDestMin;
		if (vDestMax.x < vDestMin.x)
		{
			vDestMin.x = vDestMax.x;
			vDestMax.x = temp.x;
		}

		if (vDestMax.y < vDestMin.y)
		{
			vDestMin.y = vDestMax.y;
			vDestMax.y = temp.y;
		}

		if (vDestMax.z < vDestMin.z)
		{
			vDestMin.z = vDestMax.z;
			vDestMax.z = temp.z;
		}


		// x축에서 바라봤을 때

		const _matrix *playerMatrix = playerCollider->Get_CollWorldMatrix();
		_matrix		matWorld;
		D3DXMatrixInverse(&matWorld, NULL, playerMatrix);
		float ridius = playerCollider->Get_Radius();
		_vec3 objectVec3 = { pDestWorld->_41, pDestWorld->_42 , pDestWorld->_43 };
		_vec3 playerVec3 = { playerMatrix->_41, 0.f ,playerMatrix->_43 };

		float playerObjectDist = D3DXVec3Length(&(objectVec3 - playerVec3));


		float x = max(vDestMin.x, min(playerVec3.x, vDestMax.x));
		float y = max(vDestMin.y, min(playerVec3.y, vDestMax.y));
		float z = max(vDestMin.z, min(playerVec3.z, vDestMax.z));

		// this is the same as isPointInsideSphere
		float distance = sqrt((x - playerVec3.x) * (x - playerVec3.x) +
			(y - playerVec3.y) * (y - playerVec3.y) +
			(z - playerVec3.z) * (z - playerVec3.z));

		float radius = playerCollider->Get_Radius();
		//radius = sqrt(radius);

		int sensor = 2;
		if (!_tcscmp(dynamic_cast<CStatic_Objects*>(iter->second)->Get_Static_Objects_Data().m_objectTextureName, L"Proto_Mesh_Maze_Wall1.x"))
			sensor = 2;

		if (distance < sensor)
		{
			isCollision = true;
			break;
		}
	}
	return isCollision;
}

_bool CCalculator::Collision_OrderTile(CSphereCollider * playerCollider)
{
	auto getInteractionObject = CManagement::GetInstance()->Get_Scene()->Get_Layer_GameObjects(L"OrderTile_Layer");

	bool isCollision = false;
	int distNum = 4;

	for (auto iter = getInteractionObject->begin(); iter != getInteractionObject->end(); iter++)
	{
		CSphereCollider* getSensorColl = dynamic_cast<CInteractionObject*>(iter->second)->Get_SphereCollider_Component();
		if (getSensorColl == nullptr)
			continue;
		if (!iter->second->Get_Draw())
			continue;

		_vec3		vDestMin, vDestMax;
		_float		fMin, fMax;
		float dist = 0.f;

		// x축에서 바라봤을 때

		const _matrix *playerMatrix = playerCollider->Get_CollWorldMatrix();
		const _matrix *objectMatrix = getSensorColl->Get_CollWorldMatrix();
		_matrix		matWorld;
		D3DXMatrixInverse(&matWorld, NULL, playerMatrix);
		float ridius = playerCollider->Get_Radius();
		float ridius2 = getSensorColl->Get_Radius();

		_vec3 objectVec3 = { objectMatrix->_41, objectMatrix->_42 , objectMatrix->_43 };
		_vec3 playerVec3 = { playerMatrix->_41, 0.f ,playerMatrix->_43 };

		float playerObjectDist = D3DXVec3Length(&(objectVec3 - playerVec3));

		if (playerObjectDist < 2)
		{
			iter->second->Set_IsColl(true);
		}
		else
			iter->second->Set_IsColl(false);

		float radius = playerCollider->Get_Radius();
		//radius = sqrt(radius);

		int sensor = 2;

		/*if (distance < sensor)
		{
			isCollision = true;
			iter->second->Set_IsColl(true);
			break;
		}*/

	}
	if (!isCollision)
	{

	}
	return isCollision;
}

void CCalculator::Set_Point(OBB * pObb, const _vec3 * pMin, const _vec3 * pMax)
{
	pObb->vPoint[0] = _vec3(pMin->x, pMax->y, pMin->z);
	pObb->vPoint[1] = _vec3(pMax->x, pMax->y, pMin->z);
	pObb->vPoint[2] = _vec3(pMax->x, pMin->y, pMin->z);
	pObb->vPoint[3] = _vec3(pMin->x, pMin->y, pMin->z);
		  	
	pObb->vPoint[4] = _vec3(pMin->x, pMax->y, pMax->z);
	pObb->vPoint[5] = _vec3(pMax->x, pMax->y, pMax->z);
	pObb->vPoint[6] = _vec3(pMax->x, pMin->y, pMax->z);
	pObb->vPoint[7] = _vec3(pMin->x, pMin->y, pMax->z);

	pObb->vCenter = (*pMin + *pMax) * 0.5f;
}

void CCalculator::Set_Axis(OBB* pObb)
{
	pObb->vProjAxis[0] = (pObb->vPoint[2] + pObb->vPoint[5]) * 0.5f - pObb->vCenter;
	pObb->vProjAxis[1] = (pObb->vPoint[0] + pObb->vPoint[5]) * 0.5f - pObb->vCenter;
	pObb->vProjAxis[2] = (pObb->vPoint[7] + pObb->vPoint[5]) * 0.5f - pObb->vCenter;

	pObb->vAxis[0] = pObb->vPoint[2] - pObb->vPoint[3];
	pObb->vAxis[1] = pObb->vPoint[0] - pObb->vPoint[3];
	pObb->vAxis[2] = pObb->vPoint[7] - pObb->vPoint[3];

	for (_uint i = 0; i < 3; ++i)
		D3DXVec3Normalize(&pObb->vAxis[i], &pObb->vAxis[i]);

}

