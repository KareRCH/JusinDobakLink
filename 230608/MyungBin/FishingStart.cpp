#include "stdafx.h"
#include "FishingStart.h"
#include "KeyMgr.h"

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

	m_cFisherman.Render(hDC);
}

void CFishingStart::Release()
{
	m_cFisherman.Release();
}
