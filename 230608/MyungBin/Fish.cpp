#include "stdafx.h"
#include "Fish.h"
#include "BmpMgr.h"


CFish::CFish()
    : m_fAngle(0.f)
    , m_fSpeed(0.f)
    , m_bFlag(false)
    , m_iRendMode(0)
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
    m_fAngle = 0;

    CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/TegoFish1-removebg.png", L"TegoFish1");
    CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/TegoFish1_1-removebg.png", L"TegoFish1_1");
    CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/TegoFish2-removebg.png", L"TegoFish2");
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
    fishImg.vPos.x = m_tInfo.vPos.x - m_tInfo.fCX * 3 / 4;
    fishImg.vPos.y = m_tInfo.vPos.y - m_tInfo.fCY * 3 / 4;

    if (m_iRendMode == 0) 
    {
        CBmpMgr::Get_Instance()->Draw_PNG(hDC, fishImg, false);
    }
    else if (m_iRendMode == 1)
    {
        fishImg.fAngle = m_fAngle;
        CBmpMgr::Get_Instance()->Draw_PNG(hDC, fishImg, false);
    }

    //Ellipse(hDC
    //    , m_tInfo.vPos.x - m_tInfo.fCX / 2
    //    , m_tInfo.vPos.y - m_tInfo.fCY / 2
    //    , m_tInfo.vPos.x + m_tInfo.fCX / 2
    //    , m_tInfo.vPos.y + m_tInfo.fCY / 2
    //);

    //MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
    //LineTo(hDC, (int)m_vTargetPos.x, (int)m_vTargetPos.y);
}

void CFish::Release()
{
}

void CFish::Collide(CObj* _pDst)
{
}
