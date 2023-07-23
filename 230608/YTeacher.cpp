#include "stdafx.h"
#include "YTeacher.h"

#include "BmpMgr.h"
#include "AnimationTable.h"

CYTeacher::CYTeacher()
{
}

CYTeacher::~CYTeacher()
{
	Release();
}

void CYTeacher::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;
	m_eID = PLAYER;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;


	// ================
	// D3DXVECTOR3 Init
	// ================
	m_vCenter = { (WINCX / 2 + 160), (WINCY / 2 - 70), 0.f };	// 원점, 플레이어 생성위치?
	m_tInfo.vPos = { m_vCenter.x, m_vCenter.y, m_vCenter.z };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };							//방향
	m_tInfo.vLook = { 0.f, 1.f, 0.f };							// 바라보는 방향
	m_tInfo.vSize = { 1.f, 1.f, 0.f };							// 크기(배율)
	m_vPointScale = { 50.f, 50.f, 0.f };						// 점들의 간격

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
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/유쌤_1.png", L"YTeacher");
	CAnimationTable::Get_Instance()->Create_Animation(
		L"YTeacher", L"1",
		0, 0, 1, 0.f,
		32, 50, 50, 50
	);

	// 애니메이션, 이미지 설정 초기화
	m_tInfo.tFrameTSet.Set_Keys(L"YTeacher", L"1");
	CAnimationTable::Get_Instance()->Load_AnimData(m_tInfo.tFrameTSet);

}

int CYTeacher::Update()
{
	return 0;
}

void CYTeacher::Late_Update()
{
}

void CYTeacher::Render(HDC hDC)
{
	Draw_Rectangle(hDC);

	CBmpMgr::Get_Instance()->Draw_PNG(hDC, m_tInfo, false);

}

void CYTeacher::Release()
{
}

void CYTeacher::Collide(CObj* _pDst)
{
}

void CYTeacher::Draw_Rectangle(HDC hDC)
{
}
