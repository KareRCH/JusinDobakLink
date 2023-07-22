#include "stdafx.h"
#include "Food_Cookie.h"

#include "KeyMgr.h"
#include "BmpMgr.h"
#include "AnimationTable.h"

void CFood_Cookie::Initialize()
{
#pragma region 이미지 & 애니메이션
	CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/Hak/cookie.png", L"Cookie");
	CAnimationTable::Get_Instance()->Create_Animation(
		L"Cookie", L"1",
		0, 0, 1, 0.f,
		16, 7, 32, 15
	);
#pragma endregion

	// 애니메이션, 이미지 설정 초기화
	m_tInfo.tFrameTSet.Set_Keys(L"Cookie", L"1");
	CAnimationTable::Get_Instance()->Load_AnimData(m_tInfo.tFrameTSet);
}

int CFood_Cookie::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.vPos.x += 5.f;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.vPos.x -= 5.f;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.vPos.y -= 5.f;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.vPos.y += 5.f;
	}

	return 0;
}

void CFood_Cookie::Late_Update()
{
	m_tInfo.tFrameTSet->Update();
}

void CFood_Cookie::Render(HDC hDC)
{
	CBmpMgr::Get_Instance()->Draw_PNG(hDC, m_tInfo, false);
}

void CFood_Cookie::Release()
{

}

void CFood_Cookie::Collide()
{

}
