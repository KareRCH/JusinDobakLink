#include "stdafx.h"
#include "Stage.h"
#include "CJPlayer.h"
#include "LineMgr.h"
#include "Camera.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
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

	CObjMgr::Get_Instance()->Render(hDC);

}

void CStage::Release()
{
}
