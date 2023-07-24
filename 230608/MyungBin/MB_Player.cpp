#include "stdafx.h"
#include "MB_Player.h"
#include "KeyMgr.h"
#include "BmpMgr.h"

void CMB_Player::Initialize()
{
    m_tInfo.vPos.x = WINCX / 2;
    m_tInfo.vPos.y = WINCY / 2;

    m_fSpeed = 3.f;

    CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/Link-removebg-preview.png",          L"Link-removebg");
    CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/Link_Up-removebg-preview.png",       L"Link_Up-removebg");
    CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/Link_Left-removebg-preview.png",     L"Link_Left-removebg");
    CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/Link_Right-removebg-preview.png",    L"Link_Right-removebg");

    link.tFrameTSet.sFrameKey = L"Link-removebg";
}

int CMB_Player::Update()
{
    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) 
    {

        link.tFrameTSet.sFrameKey = L"Link_Left-removebg";
        m_tInfo.vPos.x -= m_fSpeed;
    }

    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
    {
        link.tFrameTSet.sFrameKey = L"Link_Right-removebg";
        m_tInfo.vPos.x += m_fSpeed;
    }

    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
    {
        link.tFrameTSet.sFrameKey = L"Link_Up-removebg";
        m_tInfo.vPos.y -= m_fSpeed;
    }

    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
    {
        link.tFrameTSet.sFrameKey = L"Link-removebg";
        m_tInfo.vPos.y += m_fSpeed;
    }

    return 0;
}

void CMB_Player::Late_Update()
{
}

void CMB_Player::Render(HDC hDC)
{

    //int iSize = 50;
    //Rectangle(hDC
    //    , m_tInfo.vPos.x - iSize
    //    , m_tInfo.vPos.y - iSize
    //    , m_tInfo.vPos.x + iSize
    //    , m_tInfo.vPos.y + iSize
    //);


    
    link.vPos.x = m_tInfo.vPos.x / 2 + 100;
    link.vPos.y = m_tInfo.vPos.y / 2 + 100;
    link.vSize.x = 1.f;
    link.vSize.y = 1.f;
    CBmpMgr::Get_Instance()->Draw_PNG(hDC, link, false);



}

void CMB_Player::Release()
{
}

void CMB_Player::Collide(CObj* _pDst)
{
}
