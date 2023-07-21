#include "stdafx.h"
#include "Camera.h"
#include "ObjMgr.h"
#include "SceneMgr.h"

CCamera* CCamera::m_pInstance = nullptr;

CCamera::CCamera() : m_pTargetObj(nullptr)
{
}

CCamera::~CCamera()
{
    Release();
}

INFO CCamera::Get_RenderPos(INFO _tObjPos)
{
    _tObjPos.vPos.x -= m_tDiff.vPos.x + (m_IsCameraShake ? 10.f : 0.f);
    _tObjPos.vPos.y -= m_tDiff.vPos.y + (m_IsCameraShake ? 10.f : 0.f);

    return _tObjPos;
}
//카메라 크기를 타일 크기 정도로 잡아 놓으면 될듯! 
LINE CCamera::Get_Line_RenderPos(LINE _tLinePos)
{
    // 카메라가 이동함에 따라 렌더 좌표가 달라진다.
    // 해상도 중심위치와, 카메라 LookAt간의 차이 만큼
    _tLinePos.tLpoint.fX -= m_tLineDiff.tLpoint.fX;
    _tLinePos.tLpoint.fY -= m_tLineDiff.tLpoint.fY;

    _tLinePos.tRpoint.fX -= m_tLineDiff.tRpoint.fX;
    _tLinePos.tRpoint.fY -= m_tLineDiff.tRpoint.fY;

    return _tLinePos;

}

POINT CCamera::Get_Point_RenderPos(POINT _tPointPos)
{
    _tPointPos.x -= m_PointDiff.x;
    _tPointPos.y -= m_PointDiff.y;

    return _tPointPos;
}


void CCamera::Update()
{
    if (m_pTargetObj)
    {
		if (CObjMgr::Get_Instance()->Get_Player())
			m_tLookAt = CObjMgr::Get_Instance()->Get_Player()->Get_Info();
    }

    // 맵의 끝까지 오면 카메라 조정(플레이어가 중심이 아니도록)
    int mapSizeX = 0, mapSizeY = 0;

    switch (CSceneMgr::Get_Instance()->Get_CurScene())
    {
    case SC_STAGE:
        mapSizeX = STAGE_MAPCX;
        mapSizeY = STAGE_MAPCY;
        break;
    case SC_STAGE2:
        mapSizeX = STAGE2_MAPCX;
        mapSizeY = STAGE2_MAPCY;
        break;
    case SC_STAGE3:
        mapSizeX = STAGE3_MAPCX;
        mapSizeY = STAGE3_MAPCY;
        break;
    case SC_STAGE_BOSS:
        mapSizeX = BOSS_MAPCX;
        mapSizeY = BOSS_MAPCY;
        break;
    }

    if (0 >= m_tLookAt.vPos.x - WINCX / 2)
    {
        m_tLookAt.vPos.x = WINCX / 2;
    }
    if (0 >= m_tLookAt.vPos.y - WINCY / 2)
    {
        m_tLookAt.vPos.y = WINCY / 2;
    }

    if (mapSizeX <= m_tLookAt.vPos.x + WINCX / 2)
    {
        m_tLookAt.vPos.x = mapSizeX - WINCX / 2 ;
    }

    if (mapSizeY <= m_tLookAt.vPos.y + WINCY / 2)
    {
        m_tLookAt.vPos.y = mapSizeY - WINCY / 2 ;
    }
  
    // 화면 중앙좌표와 카메라 LookAt 좌표간의 차이값 계산
    CalDiff();

	--RandomTime;
	if (RandomTime <= 0)
	{
		RandomTime = 100;
		m_IsCameraShakeSet = false;
		m_IsCameraShake = false;
	}

	if (m_IsCameraShakeSet)
	{
		if (m_IsCameraShake)
			m_IsCameraShake = false;
		else
			m_IsCameraShake = true;
	}
}

void CCamera::CalDiff()
{
    //해상도 중심위치와, 카메라 LookAt간의 차이 값을 구해야한다.

    float fcx = (float)(WINCX * 0.5f); // 해상도 중심위치 x
	float fcy = (float)(WINCY * 0.5f); // 해상도 중심위치 y

    m_tDiff.vPos.x = m_tLookAt.vPos.x - fcx ;
    m_tDiff.vPos.y = m_tLookAt.vPos.y - fcy ;

    m_tLineDiff.tLpoint.fX = m_tLookAt.vPos.x - fcx;
    m_tLineDiff.tLpoint.fY = m_tLookAt.vPos.y - fcy;

    m_tLineDiff.tRpoint.fX = m_tLookAt.vPos.x - fcx;
	m_tLineDiff.tRpoint.fY = m_tLookAt.vPos.y - fcy;

    m_PointDiff.x = m_tLookAt.vPos.x - fcx;
    m_PointDiff.y = m_tLookAt.vPos.y - fcy;
}

void CCamera::Key_Input(void)
{
  
}

void CCamera::Initialize()
{
}

void CCamera::Render(HDC hDC)
{
    ////펜 설정 + 해제
    //HPEN hNewPen = CreatePen(PS_SOLID, 3, RGB(204, 102, 102));
    //HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);

    //Rectangle(hDC, 0, 0, WINCX, WINCY);

    //SelectObject(hDC, hOldPen);
    //DeleteObject(hNewPen);

    ////브러쉬 설정 + 해제
    //HBRUSH hNewBrush = CreateSolidBrush(RGB(204, 102, 102));
    //HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
}

void CCamera::Release()
{
}