#include "stdafx.h"
#include "FishermanHooking.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"

CFishermanHooking::CFishermanHooking()
{
}

CFishermanHooking::~CFishermanHooking()
{
}

void CFishermanHooking::Initialize(CFisherman& _Actor)
{
	m_preDeley = GetTickCount64();
	m_PostDelay = GetTickCount64();


	D3DXVECTOR3 startPos = { WINCX / 2.f, 100.f, 0.f };
	D3DXVECTOR3 startTargetOriginPos = { 0.f, 100.f, 0.f };
	D3DXVECTOR3 vLook = { 0.f, 1.f, 0.f };

	_Actor.Set_Pos(startPos);
	_Actor.Get_Bobber()->Set_Pos(startPos + startTargetOriginPos);
	_Actor.Get_Bobber()->Set_Dir(vLook);


	D3DXVECTOR3 startFishPos = { 150.f, WINCY / 2, 0.f };
	_Actor.Get_Fish()->Set_Pos(startFishPos);
	_Actor.Get_Fish()->Set_AngleDegree(90.f);

	iRand = 20;

	_Actor.Get_Fish()->Set_FishImg(FishImgState::LEFT);
	_Actor.Get_Fish()->Set_Flag(false);

}

FishermanState CFishermanHooking::Update(CFisherman& _Actor)
{
	if (m_preDeley + iRand * 100 < GetTickCount64())
	{
		_Actor.Get_Fish()->Update();
		if (_Actor.Get_Fish()->Get_Flag() && _Actor.Get_Fish()->Get_TargetPos().x <= 100)
		{
			D3DXVECTOR3 startFishPos = { 150.f, WINCY / 2 + float(rand() % (WINCY / 2) - (WINCY / 4)) , 0.f };
			_Actor.Get_Fish()->Set_Pos(startFishPos);
			_Actor.Get_Fish()->Set_AngleDegree(90.f);
			_Actor.Get_Fish()->Set_Flag(false);
			_Actor.Get_Fish()->Set_FishImg(FishImgState::LEFT);

			m_preDeley = GetTickCount64();
			iRand = rand() % 30 + 10;
		}
		else if (!_Actor.Get_Fish()->Get_Flag() && _Actor.Get_Fish()->Get_TargetPos().x >= WINCX - 100)
		{
			D3DXVECTOR3 startFishPos = { WINCX - 150.f, WINCY / 2 + float(rand() % (WINCY / 2) - (WINCY / 4)), 0.f };
			_Actor.Get_Fish()->Set_Pos(startFishPos);
			_Actor.Get_Fish()->Set_AngleDegree(270.f);
			_Actor.Get_Fish()->Set_Flag(true);
			_Actor.Get_Fish()->Set_FishImg(FishImgState::RIGHT);

			m_preDeley = GetTickCount64();
			iRand = rand() % 30 + 10;
		}

		float fX;
		float fY;

		if (CCollisionMgr::Check_Rect(_Actor.Get_Bobber(), _Actor.Get_Fish(), &fX, &fY)) 
		{
			return FishermanState::CATCHING;
		}

	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN)) 
	{
		if (_Actor.Get_Bobber()->Get_Info().vPos.y < WINCY - 150) 
		{
			_Actor.Get_Bobber()->Move(0.4f);
		}
		
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		if (_Actor.Get_Bobber()->Get_Info().vPos.y > 150)
		{
			_Actor.Get_Bobber()->Move_Back(0.4f);
		}
		
	}

	//if (CKeyMgr::Get_Instance()->Key_Pressing('C')) 
	//{
	//	return FishermanState::CATCHING;
	//}

	return FishermanState::HOOKING;
}

void CFishermanHooking::Late_Update(CFisherman& _Actor)
{

}

void CFishermanHooking::Render(HDC hDC, CFisherman& _Actor)
{
	int iSize = 100;
	Rectangle(hDC, iSize, iSize, WINCX - iSize, WINCY - iSize);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/inSea.bmp", L"inSea");
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"inSea");

	FRAME f;
	f.iWidth = WINCX - iSize * 2;
	f.iHeight = WINCY - iSize * 2;
	f.iFrameStart = 0;
	f.iFrameCur = 0;

	INFO background;
	background.vPos.x = iSize;
	background.vPos.y = iSize;

	CBmpMgr::Get_Instance()->Draw_BMP(hDC, L"inSea", background, f, 0, 0, 612, 339, false);



	MoveToEx(hDC, _Actor.Get_Info().vPos.x, _Actor.Get_Info().vPos.y, nullptr);
	LineTo(hDC, _Actor.Get_Bobber()->Get_Info().vPos.x, _Actor.Get_Bobber()->Get_Info().vPos.y);

	_Actor.Get_Bobber()->Render(hDC);
	
	if (m_preDeley + iRand * 100.f < GetTickCount64())
	{
		_Actor.Get_Fish()->Render(hDC);
	}


}

void CFishermanHooking::Release(CFisherman& _Actor)
{
}
