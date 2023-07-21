#include "stdafx.h"
#include "Lobby.h"

#include "BmpMgr.h"
#include "KeyMgr.h"

void CLobby::Initialize()
{
}

MyungBinStageState CLobby::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)) 
	{
		return MyungBinStageState::FISHING_START;
	}
	return MyungBinStageState::LOBBY;
}

void CLobby::Late_Update()
{
}

void CLobby::Render(HDC hDC)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Logo");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CLobby::Release()
{
}
