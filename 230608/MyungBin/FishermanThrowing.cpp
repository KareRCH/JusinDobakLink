#include "stdafx.h"
#include "FishermanThrowing.h"

CFishermanThrowing::CFishermanThrowing()
{
}

CFishermanThrowing::~CFishermanThrowing()
{
}

void CFishermanThrowing::Initialize(CFisherman& _Actor)
{
	m_preDeley = GetTickCount64();
	m_PostDelay = GetTickCount64();


}

FishermanState CFishermanThrowing::Update(CFisherman& _Actor)
{
	

	if (m_preDeley + 3000 < GetTickCount64())
	{
		return FishermanState::SELECT_DIR;
	}

	return FishermanState::THROWING;
}

void CFishermanThrowing::Late_Update(CFisherman& _Actor)
{
}

void CFishermanThrowing::Render(HDC hDC, CFisherman& _Actor)
{
	_Actor.Render_SelectPower(hDC);

	//MoveToEx(hDC, _Actor.Get_Info().vPos.x, _Actor.Get_Info().vPos.y, nullptr);
	//LineTo(hDC, _Actor.Get_TargetPos().x, _Actor.Get_TargetPos().y);

	//Rectangle(hDC, WINCX - 225, 125, WINCX - 125, WINCY - 125);

	//MoveToEx(hDC, WINCX - 225, WINCY - _Actor.Get_Gauge(), nullptr);
	//LineTo(hDC, WINCX - 125, WINCY - _Actor.Get_Gauge());
}

void CFishermanThrowing::Release(CFisherman& _Actor)
{
}