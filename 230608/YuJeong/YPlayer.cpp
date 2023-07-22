#include "stdafx.h"
#include "YPlayer.h"

CYPlayer::CYPlayer()
	: m_fAngle(0.f)
{
}

CYPlayer::~CYPlayer()
{
	Release();
}

void CYPlayer::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;

	m_tInfo.vPos = { (WINCX / 2 + 60), (WINCY / 2 - 70), 0.f };
	//m_tInfo.vPos = { 0.f, 0.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_fSpeed = 2.f;

	m_vPoint[0] = { m_tInfo.vPos.x - 10.f ,m_tInfo.vPos.y - 30.f, 0.f };	// �� ���
	m_vPoint[1] = { m_tInfo.vPos.x + 10.f ,m_tInfo.vPos.y - 30.f, 0.f };	// �� ���	
	m_vPoint[2] = { m_tInfo.vPos.x + 10.f ,m_tInfo.vPos.y + 30.f, 0.f };	// �� �ϴ�
	m_vPoint[3] = { m_tInfo.vPos.x - 10.f ,m_tInfo.vPos.y + 30.f, 0.f };	// �� �ϴ�

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];


	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

int CYPlayer::Update()
{
	Key_Input();

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
		m_vPoint[i] -= {(WINCX / 2 + 60), (WINCY / 2 - 70), 0.f};

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	return 0;
}

void CYPlayer::Late_Update()
{
}

void CYPlayer::Render(HDC hDC)
{
	HBRUSH hNewBrush = NULL;
	HBRUSH hOldBrush = NULL;

	HPEN hNewPen = NULL;
	HPEN hOldPen = NULL;

	// �귯�� ����
	//hNewBrush = CreateSolidBrush(RGB(240, 128, 128));
	hNewBrush = CreateSolidBrush(RGB(0, 100, 100));
	hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

	// �� ���� + ����
	hNewPen = CreatePen(PS_SOLID, 3, RGB(0, 100, 100));
	hOldPen = (HPEN)SelectObject(hDC, hNewPen);

	Ellipse(hDC,
		m_vPoint[0].x - 5.f,
		m_vPoint[0].y - 5.f,
		m_vPoint[0].x + 5.f,
		m_vPoint[0].y + 5.f);

	Ellipse(hDC,
		m_vPoint[1].x - 5.f,
		m_vPoint[1].y - 5.f,
		m_vPoint[1].x + 5.f,
		m_vPoint[1].y + 5.f);


	Draw_Rectangle(hDC);

	// �� ����
	SelectObject(hDC, hOldPen);
	DeleteObject(hNewPen);

	// �귯�� ����
	SelectObject(hDC, hOldBrush);
	DeleteObject(hNewBrush);
}

void CYPlayer::Release()
{
}

void CYPlayer::Draw_Rectangle(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
}



void CYPlayer::Key_Input()
{
	if (GetAsyncKeyState('A'))
	{
		//m_fAngle += D3DX_PI / 180.0f;
		m_fAngle -= 2.f;
	}


	if (GetAsyncKeyState('D'))
	{
		//m_fAngle -= D3DX_PI / 180.0f;
		m_fAngle += 2.f;
	}


	if (GetAsyncKeyState('W'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

		//D3DXVec3TransformCoord(&)
	}

	//if (GetAsyncKeyState('S'))
	//{
	//	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	//	m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	//}
}
