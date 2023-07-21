#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
//#include "CollisionMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CMainGame::CMainGame() : m_dwTime(GetTickCount()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	
	CSceneMgr::Get_Instance()->Scene_Change(SCENEID::SC_LOGO);

	//CSoundMgr::Get_Instance()->Initialize();
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}


void CMainGame::Late_Update()
{
	CScrollMgr::Get_Instance()->Scroll_Lock();

	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");

	CSceneMgr::Get_Instance()->Render(hMemDC);

	RECT rcClient;
	GetClientRect(g_hWnd, &rcClient);

	int iClientCX = (int)rcClient.right;
	int iClientCY = (int)rcClient.bottom;
	float fClientRatioX = ((float)iClientCY / (float)iClientCX);
	float fClientRatioY = ((float)iClientCX / (float)iClientCY);

	float fRatioX = ((float)WINCY / (float)WINCX);
	float fRatioY = ((float)WINCX / (float)WINCY);
	int iTargetCX = WINCX;
	int iTargetCY = WINCY;

	int iDstCX = (fClientRatioX >= fRatioX) ? iClientCX : (int)((float)iClientCY * fRatioY);
	int iDstCY = (fClientRatioY >= fRatioY) ? iClientCY : (int)((float)iClientCX * fRatioX);
	int iDstX = (iClientCY >= fRatioY) ? max(0, (iClientCX - iDstCX) / 2) : (iClientCX - iDstCX) / 2;
	int iDstY = (iClientCX >= fRatioX) ? max(0, (iClientCY - iDstCY) / 2) : (iClientCY - iDstCY) / 2;

	// 종횡 유지
	StretchBlt(
		m_hDC,				// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
		iDstX, iDstY, iDstCX, iDstCY,
		hMemDC,				// 비트맵 이미지를 담고 있는 DC
		0, 0, iTargetCX, iTargetCY,
		SRCCOPY
	);

	//BitBlt(m_hDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
	//	0, 0, WINCX, WINCY,
	//	hMemDC,			// 비트맵 이미지를 담고 있는 DC
	//	0,					// 비트맵을 출력할 시작 X,Y좌표
	//	0,
	//	SRCCOPY);

}

void CMainGame::Release()
{
	
	CBmpMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}
