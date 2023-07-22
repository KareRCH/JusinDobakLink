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

	_Actor.Reset_Bobber_Pos();
	_Actor.Set_Bobber_Dir(true);
	_Actor.Get_Bobber()->Set_Speed(_Actor.Get_Gauge()/100);

}

FishermanState CFishermanThrowing::Update(CFisherman& _Actor)
{
	//float speed = _Actor.Calc_Distance() / 100;

	_Actor.Get_Bobber()->Update();


	//if (m_preDeley + 1000 >= GetTickCount64()) 
	//{
	//	_Actor.Get_Bobber()->Scale_Up();
	//}
	//else //if (m_preDeley + 2000 >= GetTickCount64())
	//{
	//	_Actor.Get_Bobber()->Scale_Down();
	//}


	if (m_preDeley + 1000 < GetTickCount64())
	{
		_Actor.Set_BobberPos(_Actor.Get_Bobber()->Get_Info().vPos);

		return FishermanState::HOOKING;
	}

	return FishermanState::THROWING;
}

void CFishermanThrowing::Late_Update(CFisherman& _Actor)
{
}

void CFishermanThrowing::Render(HDC hDC, CFisherman& _Actor)
{
	_Actor.Render_SelectPower(hDC);

	_Actor.Get_Bobber()->Render(hDC);

	//MoveToEx(hDC, _Actor.Get_Info().vPos.x, _Actor.Get_Info().vPos.y, nullptr);
	//LineTo(hDC, _Actor.Get_TargetPos().x, _Actor.Get_TargetPos().y);

	//Rectangle(hDC, WINCX - 225, 125, WINCX - 125, WINCY - 125);

	//MoveToEx(hDC, WINCX - 225, WINCY - _Actor.Get_Gauge(), nullptr);
	//LineTo(hDC, WINCX - 125, WINCY - _Actor.Get_Gauge());
}

void CFishermanThrowing::Release(CFisherman& _Actor)
{
}
