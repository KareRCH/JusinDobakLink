#include "stdafx.h"
#include "YTimeGauge.h"

#include "BmpMgr.h"
#include "AnimationTable.h"
#include "SCeneMgr.h"

// 씬..ㅠ
#include "YScene_Serving.h"

CYTimeGauge::CYTimeGauge()
	: m_iCount(0)
	, m_fmaxTime(60.f)
	, m_fCurTime(0.f)
{
}

CYTimeGauge::~CYTimeGauge()
{
	Release();
}

void CYTimeGauge::Initialize()
{
	m_eRender = RENDER_UI;
	m_eID = UI;

	// ================
	// D3DXVECTOR3 Init
	// ================
	m_vCenter = { 304.f, 11.f, 0.f };	// 원점, 플레이어 생성위치?
	m_tInfo.vPos = { m_vCenter.x, m_vCenter.y, m_vCenter.z };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };							//방향
	m_tInfo.vLook = { 0.f, 1.f, 0.f };							// 바라보는 방향
	m_tInfo.vSize = { 1.f, 1.f, 0.f };							// 크기(배율)
	m_vPointScale = { 191.f, 10.f, 0.f };						// 점들의 간격

	m_fSpeed = 2.f;												// 속도

	m_vPoint[0] = { m_tInfo.vPos.x - m_vPointScale.x ,m_tInfo.vPos.y - m_vPointScale.y, m_vPointScale.z };	// 좌 상단
	m_vPoint[1] = { m_tInfo.vPos.x + m_vPointScale.x ,m_tInfo.vPos.y - m_vPointScale.y, m_vPointScale.z };	// 우 상단	
	m_vPoint[2] = { m_tInfo.vPos.x + m_vPointScale.x ,m_tInfo.vPos.y + m_vPointScale.y, m_vPointScale.z };	// 우 하단
	m_vPoint[3] = { m_tInfo.vPos.x - m_vPointScale.x ,m_tInfo.vPos.y + m_vPointScale.y, m_vPointScale.z };	// 좌 하단

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];


	// ================
	// 이미지 관련 Init
	// ================
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/01_서빙스테이지_시간게이지.png", L"YTimeGauge");
	CAnimationTable::Get_Instance()->Create_Animation(
		L"YTimeGauge", L"1",
		0, 0, 1, 0.f,
		0, 0, 191, 11
	);

	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/결과창.png", L"YEnd");

	// 애니메이션, 이미지 설정 초기화
	m_tInfo.tFrameTSet.Set_Keys(L"YTimeGauge", L"1");
	CAnimationTable::Get_Instance()->Load_AnimData(m_tInfo.tFrameTSet);

	m_dwTime = GetTickCount();
}

int CYTimeGauge::Update()
{
	// 현재 씬이 서빙씬일 때만 업데이트 한다.
	if (CSceneMgr::Get_Instance()->Get_CurScene() == SC_STAGE3)
	{
		if (m_dwTime + 2000 < GetTickCount())
		{
			if (0 <= m_tInfo.vSize.x)
			{
				m_tInfo.vSize.x -= 0.1f;

				m_dwTime = GetTickCount();
			}
			if (0 >= m_tInfo.vSize.x)
			{
				dynamic_cast<CYScene_Serving*>(m_ServingScene)->Set_IsEnd(true);			
			}
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CYTimeGauge::Late_Update()
{
}

void CYTimeGauge::Render(HDC hDC)
{
	//Draw_Rectangle(hDC);


	// 주석 풀어야지 렌더됨
	//현재 씬(서빙씬)일때만 렌더링 하기
	if (CSceneMgr::Get_Instance()->Get_CurScene() == SC_STAGE3)
	{
		if (dynamic_cast<CYScene_Serving*>(m_ServingScene)->Get_IsEnd())
		{
			// 게임이 종료되면 결과창을 렌더링 한다.
			m_tInfo.vSize.x = 1.f;
			FRAME tFrame = {};
			tFrame.iOffsetX = 180; tFrame.iOffsetY = -80;
			CBmpMgr::Get_Instance()->Draw_PNG(hDC, L"YEnd", m_tInfo, tFrame, 0, 0, 400, 300, false);
		}
		else
		{
			// 아니면 타임 게이지 렌더링
			CBmpMgr::Get_Instance()->Draw_PNG(hDC, m_tInfo, false);
		}
	}

}

void CYTimeGauge::Release()
{
}

void CYTimeGauge::Collide(CObj* _pDst)
{
}

void CYTimeGauge::Draw_Rectangle(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
}
