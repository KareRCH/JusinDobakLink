#include "stdafx.h"
#include "YDish.h"

#include "ObjMgr.h"

#include "YPlayer.h"

CYDish::CYDish()
{
}

CYDish::~CYDish()
{
	Release();
}

void CYDish::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;

	m_pOwner = CObjMgr::Get_Instance()->Get_Player();

	m_tInfo.vPos = { m_pOwner->Get_Info().vPos.x - 20.f, m_pOwner->Get_Info().vPos.y, 0.f };
	//m_tInfo.vPos = { 0.f, 0.f, 0.f };
	m_tInfo.vDir = { m_pOwner->Get_Info().vDir.x, m_pOwner->Get_Info().vDir.y, 0.f };
	m_tInfo.vLook = { 0.f, 1.f, 0.f };
	m_fSpeed = 2.f;

	m_vPoint[0] = { m_tInfo.vPos.x - 20.f ,m_tInfo.vPos.y - 20.f, 0.f };	// �� ���
	m_vPoint[1] = { m_tInfo.vPos.x + 20.f ,m_tInfo.vPos.y - 20.f, 0.f };	// �� ���	
	m_vPoint[2] = { m_tInfo.vPos.x + 20.f ,m_tInfo.vPos.y + 20.f, 0.f };	// �� �ϴ�
	m_vPoint[3] = { m_tInfo.vPos.x - 20.f ,m_tInfo.vPos.y + 20.f, 0.f };	// �� �ϴ�

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];
}

int CYDish::Update()
{
	//Key_Input();
	
	// D3DXVec3Normalize(��� ���� ������ ���� �ּ�, ���� ���ͷ� ���� ���� �ּ�) : ���� ���͸� ������ִ� �Լ�
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
	D3DXMatrixIdentity(&m_tInfo.matWorld);	// �׵���ķ� �����

	// ȸ������� �����, �̸� ���Ϳ� ���ؼ� ȸ���� ���͸� ���� �Ѵ�.
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);							// ũ��
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_tInfo.fAngle));			// ȸ��
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);	// �̵�

	// ũ��x����x�̵�x����x�θ�
	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	// �簢�� ������ ȸ����ķ� ��ȯ
	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		//m_vPoint[i] -= {(WINCX / 2 + 60), (WINCY / 2 - 70), 0.f};
		m_vPoint[i] -= {m_pOwner->Get_Info().vPos.x, m_pOwner->Get_Info().vPos.y, 0.f};
		//m_vPoint[i] -= {dynamic_cast<YCPlayer*>}

		//D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	//m_tInfo.vPos = m_tInfo.vDir * m_fSpeed;

	return OBJ_NOEVENT;
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
	hNewBrush = CreateSolidBrush(RGB(0, 100, 100));
	hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

	// �� ���� + ����
	hNewPen = CreatePen(PS_SOLID, 3, RGB(0, 100, 100));
	hOldPen = (HPEN)SelectObject(hDC, hNewPen);

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

void CYDish::Collide()
{
}

void CYDish::Draw_Rectangle(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
}

void CYDish::Key_Input()
{
	if (GetAsyncKeyState('A'))
	{
		//m_fAngle += D3DX_PI / 180.0f;
		m_tInfo.fAngle -= 2.f;
	}


	if (GetAsyncKeyState('D'))
	{
		//m_fAngle -= D3DX_PI / 180.0f;
		m_tInfo.fAngle += 2.f;
	}


	if (GetAsyncKeyState('W'))
	{
		// �÷��̾ �ٶ󺸴� ������ ���ؾ� �Ѵ�. �÷��̾� ���� - ������ ����
		m_tInfo.vDir = m_pOwner->Get_Info().vDir - m_tInfo.vDir;
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);	// ���⺤�Ͱ� ������
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;

		//D3DXVec3TransformCoord(&)
	}

	//if (GetAsyncKeyState('S'))
	//{
	//	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	//	m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	//}
}


// �׵� ����� ������ִ� �Լ�
// D3DXMatrixIdentity(�׵������ ������� �ϴ� ����� �ּ�)

// ũ�� ����� ������ִ� �Լ�
// D3DXMatrixScaling(ũ�� ����� �ּ�, x ����, y����, z����)

// x�� ȸ�� ����� ������ִ� �Լ�
// D3DXMatrixRotationX(x�� ȸ�� ����� �ּ�, ȸ������(����))

// y�� ȸ�� ����� ������ִ� �Լ�
// D3DXMatrixRotationY(y�� ȸ�� ����� �ּ�, ȸ������(����))

// z�� ȸ�� ����� ������ִ� �Լ�
// D3DXMatrixRotationZ(z�� ȸ�� ����� �ּ�, ȸ������(����))

// �̵� ����� ������ִ� �Լ�
// D3DXMatrixTranslation(�̵� ����� �ּ�, x��ǥ, y��ǥ, z��ǥ)

// �� ����� ������ִ� �Լ�
// D3DXMatrixInverse(��� ���� ������ ����� �ּ�, NULL, ���� ����� �ּ�)

// ���Ϳ� ����� ������ �����ϴ� �Լ�
// ��� ������ ��ġ ���Ͱ� �߻� D3DXVec3TransformCoord(��� ���� ������ ���� �ּ�, ��İ� ���ϱ⸦ �� ��ġ ���� �ּ�, ��� �ּ�);
// ��� ������ ���� ���Ͱ� �߻� D3DXVec3TransformNormal(��� ���� ������ ���� �ּ�, ��İ� ���ϱ⸦ �� ���� ���� �ּ�, ��� �ּ�);