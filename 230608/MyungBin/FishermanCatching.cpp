#include "stdafx.h"
#include "FishermanCatching.h"
#include "KeyMgr.h"

CFishermanCatching::CFishermanCatching()
{
}

CFishermanCatching::~CFishermanCatching()
{
}

void CFishermanCatching::Initialize(CFisherman& _Actor)
{
	m_preDeley = GetTickCount64();
	m_PostDelay = GetTickCount64();

	_Actor.Get_Fish()->Initialize();
	targetVec3 = { 400, 450, 0 };
	_Actor.Get_Fish()->Set_AngleDegree(0.f);
}

FishermanState CFishermanCatching::Update(CFisherman& _Actor)
{
	_Actor.Get_Fish()->Update();

	tempVec3 = _Actor.Get_Fish()->Get_Info().vPos - targetVec3;

	if (sqrt(tempVec3.x * tempVec3.x + tempVec3.y * tempVec3.y) < _Actor.Get_Fish()->Get_Speed() * 2)
	{
		return FishermanState::SELECT_DIR;
	}

	D3DXVec3Normalize(&tempVec3, &tempVec3);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		_Actor.Get_Fish()->Add_Pos((-tempVec3) * _Actor.Get_Fish()->Get_Speed() * 4.f);
	}

	float	fDot = D3DXVec3Dot(&tempVec3, &_Actor.Get_Fish()->Get_Info().vDir);

	float	fAngle = acosf(fDot);
	if (targetVec3.x > _Actor.Get_Fish()->Get_Info().vPos.x)
	{
		fAngle = 2 * D3DX_PI - fAngle;
	}

	_Actor.Get_Fish()->Set_Angle(fAngle);


	if (!((_Actor.Get_Fish()->Get_Info().vPos.x >= 100 && _Actor.Get_Fish()->Get_Info().vPos.x <= WINCX - 100) &&
		(_Actor.Get_Fish()->Get_Info().vPos.y >= 100 && _Actor.Get_Fish()->Get_Info().vPos.y <= WINCY - 100)))
	{
		bool test = true;

	}

	//if (m_preDeley + 2000.f < GetTickCount64()) 
	//{

	//	m_preDeley = GetTickCount64();
	//}



	return FishermanState::CATCHING;
}

void CFishermanCatching::Late_Update(CFisherman& _Actor)
{
	
}

void CFishermanCatching::Render(HDC hDC, CFisherman& _Actor)
{
	int iSize = 40;

	Ellipse(hDC
		, targetVec3.x - iSize
		, targetVec3.y - iSize
		, targetVec3.x + iSize
		, targetVec3.y + iSize
	);

	_Actor.Get_Fish()->Render(hDC);



}

void CFishermanCatching::Release(CFisherman& _Actor)
{
}
