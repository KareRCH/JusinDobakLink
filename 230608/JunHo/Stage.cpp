#include "stdafx.h"
#include "Stage.h"
#include "CJPlayer.h"
#include "LineMgr.h"
#include "Camera.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "Camera.h"
CStage::CStage()
{

}
CStage::~CStage()
{
	Release();
}
void CStage::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CJPlayer>::Create());
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackGround.bmp", L"BackGround");

}

void CStage::Update()
{
	CCamera::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();
}

void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC hDC)
{
	//CBmpMgr::Get_Instance()->
	INFO tLookAtPos = CCamera::Get_Instance()->Get_LookAtPos();
	HDC		hGoundDC = CBmpMgr::Get_Instance()->Find_Img(L"BackGround");

	//int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScollX();
	//int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScollY();

	BitBlt(hDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
		0, 0, 2400, 900,
		hGoundDC,			// 비트맵 이미지를 담고 있는 DC
		tLookAtPos.vPos.x - (WINCX / 2),					// 비트맵을 출력할 시작 X,Y좌표
		tLookAtPos.vPos.y - (WINCY / 2),
		SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);

}

void CStage::Release()
{
}
