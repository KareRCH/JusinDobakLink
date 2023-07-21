#include "stdafx.h"
#include "ObjMgr.h"
//#include "CollisionMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pInstance)
{
	if (m_ObjList[(int)eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;
	float	fDistance = 0.f;

	for (auto& iter : m_ObjList[(int)eID])
	{
		//if (iter->Get_Dead())
			//continue;

		float	fWidth = iter->Get_Info().vPos.x - pInstance->Get_Info().vPos.x;
		float	fHeight = iter->Get_Info().vPos.y - pInstance->Get_Info().vPos.y;

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		// 최초의 경우
		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

void CObjMgr::Add_Object(OBJID eID, CObj* pInstance)
{
	if (OBJID::OBJID_END <= eID || nullptr == pInstance)
		return;

	m_ObjList[(int)eID].push_back(pInstance);
	//pInstance->Set_OBJID(eID);
}

int CObjMgr::Update()
{
	for (size_t i = 0; i < (int)OBJID::OBJID_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < (int)OBJID::OBJID_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			//RENDERID eRender = iter->Get_RenderID();
			//m_RenderList[(int)eRender].push_back(iter);
		}

	}
}

void CObjMgr::Render(HDC hDC)
{

	for (size_t i = 0; i < (int)RENDERID::RENDER_END; ++i)
	{
		m_RenderList[i].sort([](CObj* pDst, CObj* pSrc) { return pDst->Get_Info().vPos.y < pSrc->Get_Info().vPos.y; });

		for (auto& iter : m_RenderList[i])
			iter->Render(hDC);

		m_RenderList[i].clear();
	}

}

void CObjMgr::Release()
{
	for (size_t i = 0; i < (int)OBJID::OBJID_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	for (size_t i = 0; i < (int)RENDERID::RENDER_END; ++i)
		m_RenderList[i].clear();
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[(int)eID])
		Safe_Delete(iter);

	m_ObjList[(int)eID].clear();
}
