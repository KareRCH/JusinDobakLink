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
	_Actor.Get_Fish()->Set_Pos(_Actor.Get_BobberPos());
	iRand = rand() % 20 + 3;

	_Actor.Get_Fish()->Set_RenderMode(1);
	_Actor.Get_Fish()->Set_FishImg(FishImgState::UP);
}

FishermanState CFishermanCatching::Update(CFisherman& _Actor)
{
	_Actor.Get_Fish()->Update();
	
	//tempPosVec3 = _Actor.Get_Fish()->Get_Info().vPos;


	D3DXVECTOR3 tempVec3;

	tempVec3 = _Actor.Get_Fish()->Get_Info().vPos - targetVec3;

	if (sqrt(tempVec3.x * tempVec3.x + tempVec3.y * tempVec3.y) < _Actor.Get_Fish()->Get_Speed() * 2)
	{
		return FishermanState::SELECT_DIR;
	}

	if (_Actor.Get_Fish()->Get_TargetPos().y <= 100) 
	{
 		return FishermanState::SELECT_DIR;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		D3DXVec3Normalize(&tempVec3, &tempVec3);
		_Actor.Get_Fish()->Add_Pos((-tempVec3) * _Actor.Get_Fish()->Get_Speed() * 1.0f);

		float	fDot = D3DXVec3Dot(&tempVec3, &_Actor.Get_Fish()->Get_Info().vDir);

		float	fAngle = acosf(fDot);
		if (targetVec3.x > _Actor.Get_Fish()->Get_Info().vPos.x)
		{
			fAngle = 2 * D3DX_PI - fAngle;
		}

		_Actor.Get_Fish()->Set_Angle(fAngle);
	}

	D3DXVec3Normalize(&tempVec3, &tempVec3);
	_Actor.Get_Fish()->Add_Pos((-tempVec3) * _Actor.Get_Fish()->Get_Speed() * 0.8f);

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
		//_Actor.Get_Fish()->Set_Pos(tempPosVec3);
		//_Actor.Get_Fish()->Set_Angle(0);

		_Actor.Get_Fish()->Initialize();
	}

	if (m_preDeley + iRand * 100.f < GetTickCount64())
	{
		_Actor.Get_Fish()->Move_Pop();
		m_preDeley = GetTickCount64();
		iRand = rand() % 20 + 10;
	}

	return FishermanState::CATCHING;
}

void CFishermanCatching::Late_Update(CFisherman& _Actor)
{
	
}

void CFishermanCatching::Render(HDC hDC, CFisherman& _Actor)
{
	int iSize = 40;

	MoveToEx(hDC, targetVec3.x, targetVec3.y, nullptr);
	LineTo(hDC, _Actor.Get_Fish()->Get_Info().vPos.x, _Actor.Get_Fish()->Get_Info().vPos.y);

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
