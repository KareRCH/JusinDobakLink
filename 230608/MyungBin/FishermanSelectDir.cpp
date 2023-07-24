#include "stdafx.h"
#include "FishermanSelectDir.h"

CFishermanSelectDir::CFishermanSelectDir()
{
}

CFishermanSelectDir::~CFishermanSelectDir()
{
}

void CFishermanSelectDir::Initialize(CFisherman& _Actor)
{
	m_preDeley = GetTickCount64();
	m_PostDelay = GetTickCount64();

	D3DXVECTOR3 startPos = { WINCX / 2.f, 450.f, 0.f };
	D3DXVECTOR3 startTargetOriginPos = { 0.f, -100.f, 0.f };
	D3DXVECTOR3 vLook = { 0.f, -1.f, 0.f };

	_Actor.Set_AngleDegree(0.f);
	_Actor.Set_Pos(startPos);
	_Actor.Set_vLook(vLook);
	_Actor.Set_Speed(3.f);
	_Actor.UpdateMatrixDefault();
	
	_Actor.Set_TargetOriginPos(startTargetOriginPos);

	_Actor.Update_TargetPos();

}

FishermanState CFishermanSelectDir::Update(CFisherman& _Actor)
{
	int direction = 0;
	int rangeDegree = 30;
	float speed = 1.2f;

	//if (GetAsyncKeyState(VK_LEFT))
	//	_Actor.Add_Angle(-speed);

	//if (GetAsyncKeyState(VK_RIGHT))
	//	_Actor.Add_Angle(speed);

	//_Actor.UpdateMatrixDefault();
	//_Actor.Update_TargetPos();

	if (_Actor.Get_Flag()) 
	{
		_Actor.Add_Angle(speed);

		if (_Actor.Get_AngleDegree() > direction + rangeDegree)
		{
			_Actor.Set_Flag(false);
		}
	}
	else 
	{
		_Actor.Add_Angle(-speed);
		if (_Actor.Get_AngleDegree() < direction - rangeDegree)
		{
			_Actor.Set_Flag(true);
		}
	}

	_Actor.UpdateMatrixDefault();
	_Actor.Update_TargetPos();


	if (CKeyMgr::Get_Instance()->Key_Down('Z'))
	{
		return FishermanState::SELECT_POWER;
	}
	return FishermanState::SELECT_DIR;
}

void CFishermanSelectDir::Late_Update(CFisherman& _Actor)
{
}

void CFishermanSelectDir::Render(HDC hDC, CFisherman& _Actor)
{

	_Actor.Render_SelectDir(hDC);
	//MoveToEx(hDC, _Actor.Get_Info().vPos.x, _Actor.Get_Info().vPos.y, nullptr);
	//LineTo(hDC, _Actor.Get_TargetPos().x, _Actor.Get_TargetPos().y);


	//MoveToEx(hDC, WINCX - 300, WINCY - 100, nullptr);
	//LineTo(hDC, WINCX - 100, (WINCY - 100) / 2);

	//MoveToEx(hDC, 300, WINCY - 100, nullptr);
	//LineTo(hDC, 100, (WINCY - 100) / 2);

}

void CFishermanSelectDir::Release(CFisherman& _Actor)
{
}
