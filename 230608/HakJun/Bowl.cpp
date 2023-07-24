#include "stdafx.h"
#include "Bowl.h"

#include "KeyMgr.h"
#include "BmpMgr.h"
#include "AnimationTable.h"
#include <HakJun/HitCircle.h>
#include <HakJun/Bowl.h>

void CBowl::Initialize()
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_tInfo.vSize = { 0.5f, 0.5f, 1.f };

#pragma region 이미지 & 애니메이션
	CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/Hak/bowl.png", L"Bowl");
	CAnimationTable::Get_Instance()->Create_Animation(
		L"Bowl", L"1",
		0, 0, 1, 0.f,
		157, 100, 315, 149
	);
#pragma endregion
	// 애니메이션, 이미지 설정 초기화
	m_tInfo.tFrameTSet.Set_Keys(L"Bowl", L"1");
	CAnimationTable::Get_Instance()->Load_AnimData(m_tInfo.tFrameTSet);
}

int CBowl::Update()
{
    return 0;
}

void CBowl::Late_Update()
{
}

void CBowl::Render(HDC hDC)
{
	CBmpMgr::Get_Instance()->Draw_PNG(hDC, m_tInfo, false);

}

void CBowl::Release()
{
}

void CBowl::Collide(CObj* _pDst)
{
}
