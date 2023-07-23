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

	// ī�޶� ���� �߰�
	INFO vRenderPos = CCamera::Get_Instance()->Get_RenderPos(m_tInfo);
	HDC      hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BackGround");
	// ==================
	// ��� �̹��� ���
	// ==================
	

	BitBlt(_hDC                  // ������ DC
		, 0, 0                  // ���������� ������� ���� ���� ����
		, 2400               // ���������� ������� ���� �� ����
		,900               // ���������� ������� ���� �� ����
		, hMemDC      // ������ �׸��� �׷����ִ�DC
		, m_tInfo.vPos.x               // ������ �׸��� �׷����ִ�DC�� ��𼭺�������
		, vRenderPos.vPos.y + 250
		, SRCCOPY);                  // �����ϰڴ�.

	 //BLENDFUNCTION _bf;
	 //_bf.AlphaFormat = AC_SRC_ALPHA; // ��Ʈ�� ������ �Ϲ� ��Ʈ���� ��� 0, 32��Ʈ ��Ʈ���� ��� AC_SRC_ALPHA
	 //_bf.BlendFlags = 0;            // ������ 0�̾�� �Ѵ�
	 //_bf.BlendOp = AC_SRC_OVER;      // ������ AC_SRC_OVER�̾�� �ϰ� ������ ��� �̹����� ��ģ�ٴ� �ǹ�
	 //_bf.SourceConstantAlpha = 255;   // ����(���� 0 - ������ 255)


	 //GdiAlphaBlend(_hDC
	 //   , vRenderPos.fX             // ����� �̹����� ���� ��ġ x // �������~
	 //   , vRenderPos.fY             // ����� �̹����� ���� ��ġ y
	 //   , iWidth                  // ����� �̹����� ���� 
	 //   , iHeight                  // ����� �̹����� ����   // ������� ũ���~ (��ȭ�� ũ��)
	 //   , m_pTex->Get_MemDC()         // ��Ʈ�� �̹����� ��� �ִ� DC
	 //   , 0                        // �޾ƿ� �̹����� �� xy��ǥ �κ��� ����ϰڴ�! (�׸�)
	 //   , 0
	 //   , iWidth                  // ����� ��Ʈ���� ����, ���� ������
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
