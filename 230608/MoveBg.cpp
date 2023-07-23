#include "stdafx.h"
#include "MoveBg.h"
#include "BmpMgr.h"

#include "Camera.h"



CMoveBg::CMoveBg()
	
{
}

CMoveBg::~CMoveBg()
{
}

void CMoveBg::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackGround.bmp", L"Background");

	m_eRender = RENDER_BACKGROUND;
}

int CMoveBg::Update(void)
{
	if (m_tInfo.vPos.x >= 2400.f)
	{
		m_tInfo.vPos.x = 0;
	}
	else
	{
		m_tInfo.vPos.x += 2000.f ;
	}
	return OBJ_NOEVENT;
}

void CMoveBg::Render(HDC _hDC)
{

	// 카메라 관련 추가
	INFO vRenderPos = CCamera::Get_Instance()->Get_RenderPos(m_tInfo);
	HDC      hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BackGround");
	// ==================
	// 배경 이미지 출력
	// ==================
	

	BitBlt(_hDC                  // 목적지 DC
		, 0, 0                  // 목적지에서 복사받을 부위 시작 지점
		, 2400               // 목적지에서 복사받을 부위 끝 지점
		,900               // 목적지에서 복사받을 부위 끝 지점
		, hMemDC      // 전달할 그림이 그려져있는DC
		, m_tInfo.vPos.x               // 전달할 그림이 그려져있는DC의 어디서부터인지
		, vRenderPos.vPos.y + 250
		, SRCCOPY);                  // 복사하겠다.

	 //BLENDFUNCTION _bf;
	 //_bf.AlphaFormat = AC_SRC_ALPHA; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
	 //_bf.BlendFlags = 0;            // 무조건 0이어야 한다
	 //_bf.BlendOp = AC_SRC_OVER;      // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
	 //_bf.SourceConstantAlpha = 255;   // 투명도(투명 0 - 불투명 255)


	 //GdiAlphaBlend(_hDC
	 //   , vRenderPos.fX             // 출력할 이미지의 시작 위치 x // 여기부터~
	 //   , vRenderPos.fY             // 출력할 이미지의 시작 위치 y
	 //   , iWidth                  // 출력할 이미지의 가로 
	 //   , iHeight                  // 출력할 이미지의 세로   // 여기까지 크기로~ (도화지 크기)
	 //   , m_pTex->Get_MemDC()         // 비트맵 이미지를 담고 있는 DC
	 //   , 0                        // 받아온 이미지의 이 xy좌표 부분을 출력하겠다! (그림)
	 //   , 0
	 //   , iWidth                  // 출력할 비트맵의 가로, 세로 사이즈
	 //   , iHeight
	 //   , _bf);

	 //Rectangle(_hDC,
	 //   (int)m_vPos.fX - m_vScale.fX * 0.5f,
	 //   (int)m_vPos.fY - m_vScale.fY * 0.5f,
	 //   (int)m_vPos.fX + m_vScale.fX * 0.5f,
	 //   (int)m_vPos.fY + m_vScale.fY * 0.5f);
}

void CMoveBg::Release(void)
{
}

void CMoveBg::Late_Update()
{
}

void CMoveBg::Collide(CObj* _pDst)
{
}
