#include "stdafx.h"
#include "YWall.h"

CYWall::CYWall()
	: m_bActive(true)
{
}

CYWall::~CYWall()
{
	Release();
}

void CYWall::Initialize()
{
	m_eRender = RENDER_BACKGROUND;
	m_eID = TILE;

	//m_tInfo.fCX = 105.f;
	//m_tInfo.fCY = 130.f;

	// ================
	// D3DXVECTOR3 Init
	// ================
	//m_vCenter = { 566.1, 248, 0.f };	// 원점, 벽 생성위치?
	m_tInfo.vPos = { m_vCenter.x, m_vCenter.y, m_vCenter.z };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };							//방향
	m_tInfo.vLook = { 0.f, 1.f, 0.f };							// 바라보는 방향
	m_tInfo.vSize = { 1.f, 1.f, 0.f };							// 이미지 크기(배율)
	//m_vPointScale = { 52.5f, 65.f, 0.f };						// 점들의 간격

	m_fSpeed = 2.f;												// 속도

	m_vPoint[0] = { m_tInfo.vPos.x - m_vPointScale.x ,m_tInfo.vPos.y - m_vPointScale.y, m_vPointScale.z };	// 좌 상단
	m_vPoint[1] = { m_tInfo.vPos.x + m_vPointScale.x ,m_tInfo.vPos.y - m_vPointScale.y, m_vPointScale.z };	// 우 상단	
	m_vPoint[2] = { m_tInfo.vPos.x + m_vPointScale.x ,m_tInfo.vPos.y + m_vPointScale.y, m_vPointScale.z };	// 우 하단
	m_vPoint[3] = { m_tInfo.vPos.x - m_vPointScale.x ,m_tInfo.vPos.y + m_vPointScale.y, m_vPointScale.z };	// 좌 하단

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];
}

int CYWall::Update()
{
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CYWall::Late_Update()
{
}

void CYWall::Render(HDC hDC)
{
	//HBRUSH hNewBrush = NULL;
	//HBRUSH hOldBrush = NULL;

	//HPEN hNewPen = NULL;
	//HPEN hOldPen = NULL;

	//// 브러쉬 설정
	////hNewBrush = CreateSolidBrush(RGB(240, 128, 128));
	//hNewBrush = CreateSolidBrush(RGB(0, 255, 0));
	//hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

	//// 펜 설정 + 해제
	//hNewPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	//hOldPen = (HPEN)SelectObject(hDC, hNewPen);

	////Ellipse(hDC,
	////	m_vPoint[2].x - 5.f,
	////	m_vPoint[2].y - 5.f,
	////	m_vPoint[2].x + 5.f,
	////	m_vPoint[2].y + 5.f);

	////Ellipse(hDC,
	////	m_vPoint[3].x - 5.f,
	////	m_vPoint[3].y - 5.f,
	////	m_vPoint[3].x + 5.f,
	////	m_vPoint[3].y + 5.f);


	////Rectangle(hDC,
	////	m_tRect.left,
	////	m_tRect.top,
	////	m_tRect.right,
	////	m_tRect.bottom);


	//Draw_Rectangle(hDC);


	//// 펜 해제
	//SelectObject(hDC, hOldPen);
	//DeleteObject(hNewPen);

	//// 브러쉬 해제
	//SelectObject(hDC, hOldBrush);
	//DeleteObject(hNewBrush);
}

void CYWall::Release()
{
}

void CYWall::Collide(CObj* _pDst)
{
}

void CYWall::Draw_Rectangle(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
}
