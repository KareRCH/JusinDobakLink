#include "stdafx.h"
#include "HitCircle.h"

#include "KeyMgr.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "AnimationTable.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

void CHitCircle::Initialize()
{
    m_tInfo.fCX = 80.f;
    m_tInfo.fCY = 80.f;
}

int CHitCircle::Update()
{
    if (CKeyMgr::Get_Instance()->Key_Down('A') && CKeyMgr::Get_Instance()->Key_Down('S'))
    {
        CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_Objects(UNIT), this);
        m_iHitCate = 1;
    }
    else if (CKeyMgr::Get_Instance()->Key_Down('A'))
    {
        CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_Objects(UNIT), this);
        m_iHitCate = 0;
    }
    else if (CKeyMgr::Get_Instance()->Key_Down('S'))
    {
        CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_Objects(UNIT), this);
        m_iHitCate = 0;
    }
        

    return 0;
}

void CHitCircle::Late_Update()
{
}

void CHitCircle::Render(HDC hDC)
{
    CBmpMgr::Get_Instance()->Draw_Text_Circle_Vec3(hDC, m_tInfo.vPos, 40, false);
}

void CHitCircle::Release()
{
}

void CHitCircle::Collide(CObj* _pDst)
{
    CHitCircle* pCircle = dynamic_cast<CHitCircle*>(_pDst);
    if (_pDst)
    {
        if (m_iHitCate == 0)
            CSoundMgr::Get_Instance()->PlaySound(L"punch.mp3", SOUND_PLAYER, 1.f);
        else if (m_iHitCate == 1)
            CSoundMgr::Get_Instance()->PlaySound(L"punch_critical.mp3", SOUND_PLAYER, 1.f);
    }
}
