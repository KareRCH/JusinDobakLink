#include "stdafx.h"
#include "FishingStart.h"
#include "KeyMgr.h"
#include "BmpMgr.h"

CFishingStart::CFishingStart()
{
}

CFishingStart::~CFishingStart()
{
}

void CFishingStart::Initialize()
{
	m_cFisherman.Initialize();
	m_cFisherman.Set_State(FishermanState::SELECT_DIR);
}

MyungBinStageState CFishingStart::Update()
{
	m_cFisherman.Update();
	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		return MyungBinStageState::LOBBY;
	}
	return MyungBinStageState::FISHING_START;
}

void CFishingStart::Late_Update()
{
	m_cFisherman.Late_Update();
}

void CFishingStart::Render(HDC hDC)
{
	int iSize = 100;
	Rectangle(hDC, iSize, iSize, WINCX - iSize, WINCY - iSize);
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/bg-generic-water.bmp", L"fish-background");
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"fish-background");

	FRAME f;
	f.iWidth = WINCX - iSize * 2;
	f.iHeight = WINCY - iSize * 2;
	f.iFrameStart = 0;
	f.iFrameCur = 0;

	INFO background;
	background.vPos.x = iSize;
	background.vPos.y = iSize;

	CBmpMgr::Get_Instance()->Draw_BMP(hDC, L"fish-background", background, f, 0, 0, 360, 228, false);
	
	//BitBlt(hDC, iSize, iSize, WINCX - iSize, WINCY - iSize, hMemDC, 0, 0, SRCCOPY);



	m_cFisherman.Render(hDC);
}

void CFishingStart::Release()
{
	m_cFisherman.Release();
}
