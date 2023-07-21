#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CTile::CTile()
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	/*m_tInfo.vPos.x = TILECX;
	m_tInfo.vPos.y = TILECY;*/

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile.bmp", L"Tile");
}

int CTile::Update(void)
{

	//__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CTile::Late_Update(void)
{
}

void CTile::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Tile");

	//BitBlt(hDC,
	//	m_tRect.left + iScrollX,
	//	m_tRect.top + iScrollY,
	//	TILECX,
	//	TILECY,
	//	hMemDC,
	//	TILECX * m_iDrawID,
	//	0,
	//	SRCCOPY);

	//GdiTransparentBlt(hDC,
	//	(int)m_tRect.left + iScrollX, // 복사 받을 위치 X,Y 좌표
	//	(int)m_tRect.top + iScrollY,
	//	TILECX,	// 복사 받을 가로, 세로 길이
	//	TILECY,
	//	hMemDC,			// 비트맵 이미지를 담고 있는 DC
	//	TILECX * m_iDrawID,
	//	0,
	//	TILECX,		// 출력할 비트맵의 가로, 세로 사이즈
	//	TILECY,
	//	RGB(255, 255, 255)); // 제거하고자 하는 색상



}

void CTile::Release(void)
{
}
