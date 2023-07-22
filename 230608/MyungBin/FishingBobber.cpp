#include "stdafx.h"
#include "FishingBobber.h"

CFishingBobber::CFishingBobber()
    : m_fAngle(0.f)
    , m_fSpeed(0.f)
    //, m_iScaleCount(0)

{
}

CFishingBobber::~CFishingBobber()
{
    Release();
}

void CFishingBobber::Initialize()
{
    m_tInfo.fCX = 10;
    m_tInfo.fCY = 10;


}

int CFishingBobber::Update()
{
    Move();
    return OBJ_NOEVENT;
}

void CFishingBobber::Late_Update()
{
}

void CFishingBobber::Render(HDC hDC)
{
    Ellipse(hDC
        , m_tInfo.vPos.x - m_tInfo.fCX / 2
        , m_tInfo.vPos.y - m_tInfo.fCY / 2
        , m_tInfo.vPos.x + m_tInfo.fCX / 2
        , m_tInfo.vPos.y + m_tInfo.fCY / 2
    );

}

void CFishingBobber::Release()
{
}
