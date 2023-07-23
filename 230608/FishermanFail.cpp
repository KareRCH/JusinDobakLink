#include "stdafx.h"
#include "FishermanFail.h"

CFishermanFail::CFishermanFail()
{
}

CFishermanFail::~CFishermanFail()
{
}

void CFishermanFail::Initialize(CFisherman& _Actor)
{
	m_preDeley = GetTickCount64();
	m_PostDelay = GetTickCount64();


}

FishermanState CFishermanFail::Update(CFisherman& _Actor)
{
	if (m_preDeley + 3000 < GetTickCount64())
	{
		return FishermanState::SELECT_DIR;
	}
	return FishermanState::FAIL;
}

void CFishermanFail::Late_Update(CFisherman& _Actor)
{
}

void CFishermanFail::Render(HDC hDC, CFisherman& _Actor)
{
	int srcWidth = 127;
	int srcHeight = 33;

	INFO	fail;
	fail.vPos.x = WINCX * 1 / 2 - (srcWidth / 1.5f);
	fail.vPos.y = WINCY * 1 / 2 - srcHeight;
	fail.vSize.x = 2.f;
	fail.vSize.y = 2.f;
	fail.tFrameTSet.sFrameKey = L"fail";

	CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/miss-removebg.png", L"fail");
	CBmpMgr::Get_Instance()->Draw_PNG(hDC, fail, false);

}

void CFishermanFail::Release(CFisherman& _Actor)
{
}
