#include "stdafx.h"
#include "YTimeGauge.h"

#include "BmpMgr.h"
#include "AnimationTable.h"
#include "SCeneMgr.h"

// ��..��
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
	m_vCenter = { 304.f, 11.f, 0.f };	// ����, �÷��̾� ������ġ?
	m_tInfo.vPos = { m_vCenter.x, m_vCenter.y, m_vCenter.z };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };							//����
	m_tInfo.vLook = { 0.f, 1.f, 0.f };							// �ٶ󺸴� ����
	m_tInfo.vSize = { 1.f, 1.f, 0.f };							// ũ��(����)
	m_vPointScale = { 191.f, 10.f, 0.f };						// ������ ����

	m_fSpeed = 2.f;												// �ӵ�

	m_vPoint[0] = { m_tInfo.vPos.x - m_vPointScale.x ,m_tInfo.vPos.y - m_vPointScale.y, m_vPointScale.z };	// �� ���
	m_vPoint[1] = { m_tInfo.vPos.x + m_vPointScale.x ,m_tInfo.vPos.y - m_vPointScale.y, m_vPointScale.z };	// �� ���	
	m_vPoint[2] = { m_tInfo.vPos.x + m_vPointScale.x ,m_tInfo.vPos.y + m_vPointScale.y, m_vPointScale.z };	// �� �ϴ�
	m_vPoint[3] = { m_tInfo.vPos.x - m_vPointScale.x ,m_tInfo.vPos.y + m_vPointScale.y, m_vPointScale.z };	// �� �ϴ�

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];


	// ================
	// �̹��� ���� Init
	// ================
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/01_������������_�ð�������.png", L"YTimeGauge");
	CAnimationTable::Get_Instance()->Create_Animation(
		L"YTimeGauge", L"1",
		0, 0, 1, 0.f,
		0, 0, 191, 11
	);

	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/���â.png", L"YEnd");

	// �ִϸ��̼�, �̹��� ���� �ʱ�ȭ
	m_tInfo.tFrameTSet.Set_Keys(L"YTimeGauge", L"1");
	CAnimationTable::Get_Instance()->Load_AnimData(m_tInfo.tFrameTSet);

	m_dwTime = GetTickCount();
}

int CYTimeGauge::Update()
{
	// ���� ���� �������� ���� ������Ʈ �Ѵ�.
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


	// �ּ� Ǯ����� ������
	//���� ��(������)�϶��� ������ �ϱ�
	if (CSceneMgr::Get_Instance()->Get_CurScene() == SC_STAGE3)
	{
		if (dynamic_cast<CYScene_Serving*>(m_ServingScene)->Get_IsEnd())
		{
			// ������ ����Ǹ� ���â�� ������ �Ѵ�.
			m_tInfo.vSize.x = 1.f;
			FRAME tFrame = {};
			tFrame.iOffsetX = 180; tFrame.iOffsetY = -80;
			CBmpMgr::Get_Instance()->Draw_PNG(hDC, L"YEnd", m_tInfo, tFrame, 0, 0, 400, 300, false);
		}
		else
		{
			// �ƴϸ� Ÿ�� ������ ������
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
