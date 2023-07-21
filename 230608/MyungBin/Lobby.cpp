#include "stdafx.h"
#include "Lobby.h"

#include "BmpMgr.h"
#include "KeyMgr.h"

void Lobby::Initialize()
{
}

MyungBinStageState Lobby::Update()
{
	return MyungBinStageState::LOBBY;
}

void Lobby::Late_Update()
{
}

void Lobby::Render(HDC hDC)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Logo");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void Lobby::Release()
{
}
