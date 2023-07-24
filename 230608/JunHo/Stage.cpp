#include "stdafx.h"
#include "Stage.h"
#include "CJPlayer.h"
#include "LineMgr.h"
#include "Camera.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "MoveBg.h"
#include "KeyMgr.h"
#include "ENDING.h"
#include "SceneMgr.h"
CStage::CStage() : fuckingx(1200),fuckingy(0), m_bMapEdit(false)
{

}
CStage::~CStage()
{
	Release();
}
void CStage::Initialize()
{
	CLineMgr::Get_Instance()->Load_Line();
	CObjMgr::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CJPlayer>::Create());
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackGround2.bmp", L"BackGround");
	CCamera::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());

}

void CStage::Update()
{
	CCamera::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	if (GetAsyncKeyState('D'))
	{
		if (CSceneMgr::Get_Instance()->Get_PreScene() == SC_STAGE)
		{
			CSceneMgr::Get_Instance()->Set_CurScene(SC_STAGE_BOSS);

		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(0x72))
	{
		m_bMapEdit = true;
		MessageBox(g_hWnd, L"에디터모드 ON", _T("모드 전환"), MB_OK);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(0x73))
	{
		m_bMapEdit = false;
		MessageBox(g_hWnd, L"에디터모드 OFF", _T("모드 전환"), MB_OK);
	}

	if (m_bMapEdit)
		CLineMgr::Get_Instance()->Update();
	
	
	if (dynamic_cast<CJPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_fuckingswitch())
	{
		if (fuckingx >= 3600.f)
		{
			//CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos.x = 1200.f;
			fuckingx = 1200.f;
			dynamic_cast<CJPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_fucking(true);
		}
		else
		{

			fuckingx += 3.f;
		}
	}
	
	dynamic_cast<CJPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_fucking(false);
}

void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC hDC)
{
	////CBmpMgr::Get_Instance()->
	INFO tLookAtPos = CCamera::Get_Instance()->Get_LookAtPos();
	HDC		hGoundDC = CBmpMgr::Get_Instance()->Find_Img(L"BackGround");

	//int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScollX();
	//int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScollY();
	

	BitBlt(hDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
		0, 0, 4800, 900,
		hGoundDC,			// 비트맵 이미지를 담고 있는 DC
		fuckingx ,					// 비트맵을 출력할 시작 X,Y좌표
		tLookAtPos.vPos.y - (WINCY / 2),
		SRCCOPY);
	CLineMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	
}

void CStage::Release()
{
	CLineMgr::Get_Instance()->Destroy_Instance();
}
