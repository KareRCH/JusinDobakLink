#include "stdafx.h"
#include "Lobby.h"

#include "BmpMgr.h"
#include "KeyMgr.h"
#include "Camera.h"

void CLobby::Initialize()
{
	
}

MyungBinStageState CLobby::Update()
{
	m_cPlayer.Update();

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
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");
	//HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Logo");
	//BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/StartArea.bmp", L"StartArea");
	//HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"StartArea");
	//BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	//int iSize = 100;
	//Rectangle(hDC, iSize, iSize, WINCX - iSize, WINCY - iSize);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/StartArea.bmp", L"StartArea");
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"StartArea");

	FRAME f;
	f.iWidth = WINCX;
	f.iHeight = WINCY;
	f.iFrameStart = 0;
	f.iFrameCur = 0;

	INFO background;
	background.vPos.x = 0;// +CCamera::Get_Instance()->Get_RenderPos;
	background.vPos.y = 0;

	CBmpMgr::Get_Instance()->Draw_BMP(hDC, L"StartArea", background, f, 
		m_cPlayer.Get_Info().vPos.x,// + CCamera::Get_Instance()->Get_WindowPos().x, 
		m_cPlayer.Get_Info().vPos.y,// + CCamera::Get_Instance()->Get_WindowPos().y,
		WINCX, WINCY, false);


	m_cPlayer.Render(hDC);
}

void CLobby::Release()
{
}
