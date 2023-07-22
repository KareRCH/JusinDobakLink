#include "stdafx.h"
#include "Scene_HakStage.h"

#include "ObjMgr.h"
#include "ObjFactory.h"
#include "Food_Cookie.h"

void CScene_HakStage::Initialize()
{
	INFO tInfo;
	tInfo.vPos = { 400.f, 300.f, 0.f };
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
	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_HakStage::Release()
{
	CObjMgr::Get_Instance()->Release();
}
