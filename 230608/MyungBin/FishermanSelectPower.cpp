#include "stdafx.h"
#include "FishermanSelectPower.h"

CFishermanSelectPower::CFishermanSelectPower()
{
}

CFishermanSelectPower::~CFishermanSelectPower()
{
}

void CFishermanSelectPower::Initialize(CFisherman& _Actor)
{
	m_preDeley = GetTickCount64();
	m_PostDelay = GetTickCount64();

	_Actor.Set_Gauge(150);

}

FishermanState CFishermanSelectPower::Update(CFisherman& _Actor)
{
	int value = 10;


	if (_Actor.Get_Flag())
	{
		_Actor.Add_Gauge(value);

		if (450 <= _Actor.Get_Gauge())
		{
			_Actor.Set_Flag(false);
		}
	}
	else
	{
		_Actor.Add_Gauge(-value);
		if (150 >= _Actor.Get_Gauge())
		{
			_Actor.Set_Flag(true);
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		return FishermanState::THROWING;
	}

	return FishermanState::SELECT_POWER;
}

void CFishermanSelectPower::Late_Update(CFisherman& _Actor)
{
}

void CFishermanSelectPower::Render(HDC hDC, CFisherman& _Actor)
{
	_Actor.Render_SelectPower(hDC);

	//MoveToEx(hDC, _Actor.Get_Info().vPos.x, _Actor.Get_Info().vPos.y, nullptr);
	//LineTo(hDC, _Actor.Get_TargetPos().x, _Actor.Get_TargetPos().y);

	//Rectangle(hDC, WINCX - 225, 125, WINCX - 125, WINCY - 125);

	//MoveToEx(hDC, WINCX - 225, WINCY - _Actor.Get_Gauge(), nullptr);
	//LineTo(hDC, WINCX - 125, WINCY - _Actor.Get_Gauge());
}

void CFishermanSelectPower::Release(CFisherman& _Actor)
{
}
