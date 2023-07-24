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
	//// D3DXVec3Normalize(��� ���� ������ ���� �ּ�, ���� ���ͷ� ���� ���� �ּ�) : ���� ���͸� ������ִ� �Լ�
	//D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	//D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
	//D3DXMatrixIdentity(&m_tInfo.matWorld);	// �׵���ķ� �����

	//// ȸ������� �����, �̸� ���Ϳ� ���ؼ� ȸ���� ���͸� ���� �Ѵ�.
	//D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);					// ũ��
	//D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_tInfo.fAngle));	// ȸ��
	//D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);	// �̵�

	//// ũ��x����x�̵�
	//m_tInfo.matWorld = matScale * matRotZ * matTrans;

	//// �簢�� ������ ȸ����ķ� ��ȯ
	//for (int i = 0; i < 4; ++i)
	//{
	//	m_vPoint[i] = m_vOriginPoint[i];
	//	m_vPoint[i] -= { m_vCenter.x, m_vCenter.y, m_vCenter.z };

	//	D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	//}

	//if (m_dwTime + 1000 < GetTickCount())
	//{
	//	m_fCurTime += 1.f;

	//	m_dwTime = GetTickCount();
	//}


	//if (0 <= m_tInfo.vSize.x)
	//{
	//	//m_iHpGauge = (int)(((float)m_tData.iHp / (float)m_tData.iMaxHp) * 171.f);
	//	m_tInfo.vSize.x *= 0.8f;
	//}

	//if (CSceneMgr::Get_Instance()->Get_CurScene() == SC_STAGE3)
	//{
		if (m_dwTime + 400 < GetTickCount())
		{
			if (0 <= m_tInfo.vSize.x)
			{
				//m_iHpGauge = (int)(((float)m_tData.iHp / (float)m_tData.iMaxHp) * 171.f);
				m_tInfo.vSize.x -= 0.1f;

				m_dwTime = GetTickCount();
			}
			if (0 >= m_tInfo.vSize.x)
			{
				//dynamic_cast<CYScene_Serving*>(m_ServingScene)->Set_IsEnd(true);

			}
		}
	//}




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

	//if (dynamic_cast<CYScene_Serving*>(m_ServingScene)->Get_IsEnd() && CSceneMgr::Get_Instance()->Get_CurScene() == SC_STAGE3)
	//{
	//	m_tInfo.vSize.x = 1.f;
	//	FRAME tFrame = {};
	//	tFrame.iOffsetX = 180; tFrame.iOffsetY = -80;
	//	CBmpMgr::Get_Instance()->Draw_PNG(hDC, L"YEnd", m_tInfo, tFrame, 0, 0, 400, 300, false);
	//}
	//else
	//{
	//	CBmpMgr::Get_Instance()->Draw_PNG(hDC, m_tInfo, false);

	//}

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
