#include "stdafx.h"
#include "YDish.h"

CYDish::CYDish()
	: m_fAngle(0.f)
{
}

CYDish::~CYDish()
{
	Release();
}

void CYDish::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;

	m_tInfo.vPos = { 566.1f, 250.f, 0.f };
	//m_tInfo.vPos = { 0.f, 0.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_fSpeed = 2.f;

	m_vPoint[0] = { m_tInfo.vPos.x - 40.f ,m_tInfo.vPos.y - 40.f, 0.f };	// �� ���
	m_vPoint[1] = { m_tInfo.vPos.x + 40.f ,m_tInfo.vPos.y - 40.f, 0.f };	// �� ���	
	m_vPoint[2] = { m_tInfo.vPos.x + 40.f ,m_tInfo.vPos.y + 40.f, 0.f };	// �� �ϴ�
	m_vPoint[3] = { m_tInfo.vPos.x - 40.f ,m_tInfo.vPos.y + 40.f, 0.f };	// �� �ϴ�

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];


	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

int CYDish::Update()
{
	// D3DXVec3Normalize(��� ���� ������ ���� �ּ�, ���� ���ͷ� ���� ���� �ּ�) : ���� ���͸� ������ִ� �Լ�
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
	D3DXMatrixIdentity(&m_tInfo.matWorld);	// �׵���ķ� �����

	// ȸ������� �����, �̸� ���Ϳ� ���ؼ� ȸ���� ���͸� ���� �Ѵ�.
	D3DXMATRIX matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);			// ũ��
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));	// ȸ��
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);	// �̵�

	// ũ��x����x�̵�
	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	// �簢�� ������ ȸ����ķ� ��ȯ
	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= {566.1f, 250.f, 0.f};

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}
	return 0;
}

void CYDish::Late_Update()
{
}

void CYDish::Render(HDC hDC)
{
	HBRUSH hNewBrush = NULL;
	HBRUSH hOldBrush = NULL;

	HPEN hNewPen = NULL;
	HPEN hOldPen = NULL;

	// �귯�� ����
	//hNewBrush = CreateSolidBrush(RGB(240, 128, 128));
	hNewBrush = CreateSolidBrush(RGB(100, 0, 50));
	hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

	// �� ���� + ����
	hNewPen = CreatePen(PS_SOLID, 3, RGB(100, 0, 50));
	hOldPen = (HPEN)SelectObject(hDC, hNewPen);

	Draw_Rectangle(hDC);

	Draw_Rectangle(hDC);

	// �� ����
	SelectObject(hDC, hOldPen);
	DeleteObject(hNewPen);

	// �귯�� ����
	SelectObject(hDC, hOldBrush);
	DeleteObject(hNewBrush);
}

void CYDish::Release()
{
}

void CYDish::Draw_Rectangle(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
}
