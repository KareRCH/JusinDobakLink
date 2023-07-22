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
#include "Camera.h"
#include "AnimationTable.h"

#include "TileMgr.h"
#include "LineMgr.h"
#include "Camera.h"

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

	Gdp::GdiplusStartupInput gdiplusStartupInput;
	gdiplusStartupInput.GdiplusVersion = 1;
	gdiplusStartupInput.SuppressBackgroundThread = FALSE;
	Gdp::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	
	CSceneMgr::Get_Instance()->Scene_Change(SCENEID::SC_STAGE3);

	//CSoundMgr::Get_Instance()->Initialize();
	CAnimationTable::Get_Instance();
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

	// ��Ⱦ ����
	StretchBlt(
		m_hDC,				// ���� ���� DC(���������� �׸��� �׸� DC����)
		iDstX, iDstY, iDstCX, iDstCY,
		hMemDC,				// ��Ʈ�� �̹����� ��� �ִ� DC
		0, 0, iTargetCX, iTargetCY,
		SRCCOPY
	);
	//94번줄~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//BitBlt(m_hDC,	// ���� ���� DC(���������� �׸��� �׸� DC����)
	//	0, 0, WINCX, WINCY,
	//	hMemDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
	//	0,					// ��Ʈ���� ����� ���� X,Y��ǥ
	//	0,
	//	SRCCOPY);

}

void CMainGame::Release()
{
	CBmpMgr::Destroy_Instance();
	CAnimationTable::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CCamera::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CCamera::Destroy_Instance();

	Gdp::GdiplusShutdown(m_gdiplusToken);
	ReleaseDC(g_hWnd, m_hDC);
}
