#include "stdafx.h"
#include "VecCollisionMgr.h"
#include "Obj.h"

//list<CObj*> CVecCollisionMgr::Collision_Box(list<CObj*>* Dst, CObj* Src)
//{
//	CCharacter_NetBattle* pSrc = dynamic_cast<CCharacter_NetBattle*>(Src);
//	if (!pSrc) { return list<CObj*>(); }
//
//	list<CObj*> resultList = list<CObj*>();
//
//	for (auto pObj : *Dst)
//	{
//		CCharacter_NetBattle* pDst = dynamic_cast<CCharacter_NetBattle*>(pObj);
//
//		if (!pDst) { continue; }
//
//		if (Src == pDst) { continue; }
//
//		if (CVecCollisionMgr_Check<float>::Check_Box(pDst->Get_BoxArea(), pSrc->Get_BoxArea()))
//		{
//			resultList.push_back(pDst);
//		}
//	}
//
//	for (auto& pDst : resultList)
//	{
//		pSrc->Collide(pDst);
//	}
//
//	return resultList;
//}
//
//list<CObj*> CVecCollisionMgr::Collision_Box_Quater(list<CObj*>* Dst, CObj* Src)
//{
//	CCharacter_QuaterView* pSrc = dynamic_cast<CCharacter_QuaterView*>(Src);
//	if (!pSrc) { return list<CObj*>(); }
//
//	list<CObj*> resultList = list<CObj*>();
//
//	for (auto pObj : *Dst)
//	{
//		CCharacter_QuaterView* pDst = dynamic_cast<CCharacter_QuaterView*>(pObj);
//
//		if (!pDst) { continue; }
//
//		if (Src == pDst) { continue; }
//
//		if (CVecCollisionMgr_Check<float>::Check_Box(pDst->Get_BoxArea(), pSrc->Get_BoxArea()))
//		{
//			resultList.push_back(pDst);
//		}
//	}
//
//	for (auto& pDst : resultList)
//	{
//		pSrc->Collide(pDst);
//	}
//
//	return resultList;
//}
//
//list<CObj*> CVecCollisionMgr::Collision_PointToRhombus_Quater(list<CObj*>* Dst, CObj* Src)
//{
//	CCharacter_QuaterView* pSrc = dynamic_cast<CCharacter_QuaterView*>(Src);
//	if (!pSrc) { return list<CObj*>(); }
//
//	list<CObj*> resultList = list<CObj*>();
//
//	for (auto pObj : *Dst)
//	{
//		CCharacter_QuaterView* pDst = dynamic_cast<CCharacter_QuaterView*>(pObj);
//
//		if (!pDst) { continue; }
//
//		if (Src == pDst) { continue; }
//
//		if (CVecCollisionMgr_Check<float>::Check_PointToRhombus(pDst->Get_BoxArea(), pSrc->Get_VecPos()))
//		{
//			resultList.push_back(pDst);
//		}
//	}
//
//	for (auto& pDst : resultList)
//	{
//		pSrc->Collide(pDst);
//	}
//
//	return resultList;
//}
//
//list<CObj*> CVecCollisionMgr::Collision_Box_Tile(vector<CObj*>* Dst, CObj* Src)
//{
//	CCharacter_QuaterView* pSrc = dynamic_cast<CCharacter_QuaterView*>(Src);
//	if (!pSrc) { return list<CObj*>(); }
//
//	list<CObj*> resultList = list<CObj*>();
//
//	for (auto pObj : *Dst)
//	{
//		CTile* pDst = dynamic_cast<CTile*>(pObj);
//
//		if (!pDst) { continue; }
//
//		if (CVecCollisionMgr_Check<float>::Check_PointToRhombus(pDst->Get_BoxArea(), pSrc->Get_VecPos()))
//		{
//			resultList.push_back(pDst);
//		}
//	}
//
//	for (auto& pDst : resultList)
//	{
//		pSrc->Collide(pDst);
//	}
//
//	return resultList;
//}
//

