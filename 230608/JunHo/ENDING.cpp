#include "stdafx.h"
#include "ENDING.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
CENDING::CENDING()
{
}

CENDING::~CENDING()
{
}

void CENDING::Initialize()
{
	float g_fSound = 3.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ending3.bmp", L"Ending");
	CSoundMgr::Get_Instance()->PlayBGM(L"Ending.wav", g_fSound);
}

void CENDING::Update()
{
	CCamera::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
}

void CENDING::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CENDING::Render(HDC hDC)
{
	INFO tLookAtPos = CCamera::Get_Instance()->Get_LookAtPos();
	HDC		hGoundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ending");

	//int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScollX();
	//int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScollY();


	BitBlt(hDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
		0, 0, 900, 600,
		hGoundDC,			// 비트맵 이미지를 담고 있는 DC
		0,					// 비트맵을 출력할 시작 X,Y좌표
		0,
		SRCCOPY);
	
	CObjMgr::Get_Instance()->Render(hDC);
}

void CENDING::Release()
{
}
