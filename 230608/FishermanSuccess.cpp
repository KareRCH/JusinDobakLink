#include "stdafx.h"
#include "FishermanSuccess.h"

CFishermanSuccess::CFishermanSuccess()
{
}

CFishermanSuccess::~CFishermanSuccess()
{
}

void CFishermanSuccess::Initialize(CFisherman& _Actor)
{
	m_preDeley = GetTickCount64();
	m_PostDelay = GetTickCount64();


}

FishermanState CFishermanSuccess::Update(CFisherman& _Actor)
{

	if (m_preDeley + 3000 < GetTickCount64())
	{
		return FishermanState::SELECT_DIR;
	}
	return FishermanState::SUCCESS;
}

void CFishermanSuccess::Late_Update(CFisherman& _Actor)
{
}

void CFishermanSuccess::Render(HDC hDC, CFisherman& _Actor)
{
	int srcWidth	= 164;
	int srcHeight	= 31;

	INFO	success;
	success.vPos.x = WINCX * 1 / 2 - (srcWidth / 1.5f);
	success.vPos.y = WINCY * 1 / 2 - srcHeight;

	success.vSize.x = 2.f;
	success.vSize.y = 2.f;
	success.tFrameTSet.sFrameKey = L"success";

	CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/catch-removebg.png", L"success");
	CBmpMgr::Get_Instance()->Draw_PNG(hDC, success, false);

}

void CFishermanSuccess::Release(CFisherman& _Actor)
{
}
