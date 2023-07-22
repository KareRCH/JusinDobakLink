#include "stdafx.h"
#include "YScene_Serving.h"

#// MGR �Ŵ���
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"

// ������ ����
#include "AbstractFactory.h"

// Obj
#include "YPlayer.h"
#include "YDish.h"
#include "YCustomer.h"

// Obj - UI
#include "YTimeGauge.h"


CYScene_Serving::CYScene_Serving()
{
}

CYScene_Serving::~CYScene_Serving()
{
	Release();
}

void CYScene_Serving::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../230608/YuJeong/Image_Yu/00_������������_BG.bmp", L"Serving_BG");

	// ============
	// �÷��̾� ����
	// ============
	CObjMgr::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CYPlayer>::Create((float)WINCX / 2, (float)WINCY / 2));


	// ���� ���� �׽�Ʈ
	CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<CYDish>::Create((float)WINCX / 2, (float)WINCY / 2));


	// �մ� ���� �׽�Ʈ
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CYCustomer>::Create((float)WINCX / 2, (float)WINCY / 2));
}

void CYScene_Serving::Update()
{
	CObjMgr::Get_Instance()->Update();

}

void CYScene_Serving::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CYScene_Serving::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Serving_BG");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
	//CObjMgr::Get_Instance()->Get_Player()->Render(hDC);
}

void CYScene_Serving::Release()
{
}