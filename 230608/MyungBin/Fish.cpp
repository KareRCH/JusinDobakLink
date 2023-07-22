#include "stdafx.h"
#include "Fish.h"


CFish::CFish()
    : m_fAngle(0.f)
    , m_fSpeed(0.f)
{
}

CFish::~CFish()
{
}

void CFish::Initialize()
{
    m_tInfo.fCX = 40;
    m_tInfo.fCY = 40;

    m_tInfo.vPos = { 400.f, 300.f, 0.f };

    m_vTargetPos = { m_tInfo.vPos.x, m_tInfo.vPos.y - m_tInfo.fCY, 0.f };
    m_vOriginTargetPos = m_vTargetPos - m_tInfo.vPos;
    m_tInfo.vLook = { 0.f, -1.f, 0.f };
    m_fSpeed = 3.f;
}

int CFish::Update()
{
    UpdateDir();
    UpdateMatrixDefault();
    D3DXVec3TransformCoord(&m_vTargetPos, &m_vOriginTargetPos, &m_tInfo.matWorld);

    Move();

    return OBJ_NOEVENT;
}

void CFish::Late_Update()
{
}

void CFish::Render(HDC hDC)
{
    Ellipse(hDC
        , m_tInfo.vPos.x - m_tInfo.fCX / 2
        , m_tInfo.vPos.y - m_tInfo.fCY / 2
        , m_tInfo.vPos.x + m_tInfo.fCX / 2
        , m_tInfo.vPos.y + m_tInfo.fCY / 2
    );

    MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
    LineTo(hDC, (int)m_vTargetPos.x, (int)m_vTargetPos.y);
}

void CFish::Release()
{
}

void CFish::Collide()
{
}
