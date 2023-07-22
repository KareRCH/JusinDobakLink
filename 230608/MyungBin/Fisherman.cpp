#include "stdafx.h"
#include "Fisherman.h"
#include "FishermanSelectDir.h"
#include "FishermanSelectPower.h"
#include "FishermanThrowing.h"
#include "FishermanHooking.h"
#include "FishermanCatching.h"

CFisherman::CFisherman()
    :  m_vTargetPos(0.f, 0.f, 0.f)
    , m_vOriginTargetPos(0.f, 0.f, 0.f)
    , m_fAngle(0.f)
    , m_fSpeed(0.f)
    , m_bFlag(false)
    , m_iGauge(0)
    , m_pFishingBobber(nullptr)
    , m_pFish(nullptr)
    , m_bFishingEnd(false)

{
    //ZeroMemory(m_vPoint, sizeof(m_vPoint));
    //ZeroMemory(m_vOriginPoint, sizeof(m_vOriginPoint));
}

CFisherman::~CFisherman()
{
    Release();
}

void CFisherman::Initialize(void)
{

    m_States[(int)FishermanState::SELECT_DIR]   = new CFishermanSelectDir();
    m_States[(int)FishermanState::SELECT_POWER] = new CFishermanSelectPower();
    m_States[(int)FishermanState::THROWING]     = new CFishermanThrowing();
    m_States[(int)FishermanState::HOOKING]      = new CFishermanHooking();
    m_States[(int)FishermanState::CATCHING]     = new CFishermanCatching();


    m_eState = FishermanState::SELECT_DIR;
    m_States[(int)m_eState]->Initialize(*this);


    m_pFishingBobber = new CFishingBobber;
    m_pFishingBobber->Initialize();
    Reset_Bobber_Pos();
    Set_Bobber_Dir(true);


    m_pFish = new CFish;
    m_pFish->Initialize();

}

int CFisherman::Update(void)
{
    if (m_eState == FishermanState::FishermanState_End) 
        return OBJ_DEAD;


    D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
    D3DXMATRIX	matScale, matRotZ, matTrans;

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, m_fAngle);
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

    FishermanState nowState = m_States[(int)m_eState]->Update(*this);
    //Set_State(nowState);
    if (m_eState != nowState)
    {
        m_States[(int)m_eState]->Release(*this);

        m_eState = nowState;
        m_States[(int)m_eState]->Initialize(*this);
    }

    return OBJ_NOEVENT;
}

void CFisherman::Late_Update(void)
{
    if (m_eState == FishermanState::FishermanState_End)
        return;

    m_States[(int)m_eState]->Late_Update(*this);
}

void CFisherman::Render(HDC hDC)
{
    if (m_eState == FishermanState::FishermanState_End)
        return;

    m_States[(int)m_eState]->Render(hDC , *this);
}

void CFisherman::Release(void)
{
    for (int i = 0; i < (int)FishermanState::FishermanState_End; ++i) {
        if (nullptr != m_States[i]) 
        {
            Safe_Delete(m_States[i]);
            //m_States[i] = nullptr;
        }  

    }

    Safe_Delete(m_pFishingBobber);
    Safe_Delete(m_pFish);


}

void CFisherman::Collide(CObj* _pDst)
{
}
