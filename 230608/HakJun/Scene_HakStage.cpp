#include "stdafx.h"
#include "Scene_HakStage.h"

#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ObjFactory.h"
#include "Food_Cookie.h"

void CScene_HakStage::Initialize()
{
#pragma region 이미지 추가
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Hak/Kitchen.bmp", L"BG_Kitchen");
#pragma endregion

	m_tInfo.tFrameTSet.Set_Keys(L"BG_Kitchen", L"");
	(*m_tInfo.tFrameTSet).iWidth = 800;
	(*m_tInfo.tFrameTSet).iHeight = 600;

	INFO tInfo;
	tInfo.vPos = { 1200.f, 200.f, 0.f };
	tInfo.vSpeed = { 5.f, 0.f, 0.f };
	CObjFactory<CFood_Cookie>::Create(UNIT, tInfo);
}

void CScene_HakStage::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CScene_HakStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene_HakStage::Render(HDC hDC)
{
	CBmpMgr::Get_Instance()->Draw_BMP(hDC, m_tInfo, 0, 0, 800, 600, false);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_HakStage::Release()
{
	CObjMgr::Get_Instance()->Release();
}
