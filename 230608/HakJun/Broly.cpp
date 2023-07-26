#include "stdafx.h"
#include "Broly.h"

#include "KeyMgr.h"
#include "BmpMgr.h"
#include "AnimationTable.h"
#include <HakJun/HitCircle.h>
#include <HakJun/Bowl.h>
#include <Core/CollisionMgr.h>

void CBroly::Initialize()
{
	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 80.f;

	m_tInfo.vSize = { 1.f, 1.f, 1.f };

#pragma region 이미지 & 애니메이션
	CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/Hak/cookie.png", L"Cookie");
	CAnimationTable::Get_Instance()->Create_Animation(
		L"Cookie", L"1",
		0, 0, 1, 0.f,
		16, 7, 32, 15
	);
	CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/Hak/boong.png", L"Boong");
	CAnimationTable::Get_Instance()->Create_Animation(
		L"Boong", L"1",
		0, 0, 1, 0.f,
		19, 12, 39, 25
	);
#pragma endregion

	// 애니메이션, 이미지 설정 초기화
	m_tInfo.tFrameTSet.Set_Keys(L"Boong", L"1");
	CAnimationTable::Get_Instance()->Load_AnimData(m_tInfo.tFrameTSet);

	m_tState.Set_State(ESTATE::MOVE);
	m_tState.Add_Func(ESTATE::IDLE, &CBroly::Idle);
	m_tState.Add_Func(ESTATE::MOVE, &CBroly::Move);
	m_tState.Add_Func(ESTATE::HIT, &CBroly::Hit);
}

int CBroly::Update()
{
	m_tState.Get_StateFunc()(this);

    return 0;
}

void CBroly::Late_Update()
{
}

void CBroly::Render(HDC hDC)
{
	CBmpMgr::Get_Instance()->Draw_PNG(hDC, m_tInfo, false);
}

void CBroly::Release()
{
}

void CBroly::Collide(CObj* _pDst)
{
}

void CBroly::Move()
{
}

void CBroly::Idle()
{
}

void CBroly::Hit()
{
}
