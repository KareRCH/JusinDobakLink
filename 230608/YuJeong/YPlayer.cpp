#include "stdafx.h"
#include "YPlayer.h"

#// MGR �Ŵ���
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "AnimationTable.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"
#include "TileMgr.h"
#include "Tile.h"

// Obj
#include "YDish.h"
#include "YCustomer.h"
#include "YWall.h"

CYPlayer::CYPlayer()
	: m_vPointScale{}
	, m_vCenter{}
	, m_bIsDishColl(false)
	, m_bIsWallColl(false)
	, m_iPreMoney(0)
	, m_iMoney(0)
	, m_iDishCount(0)
	, m_fPreAngle(0)
{

}

CYPlayer::~CYPlayer()
{
	Release();
}

void CYPlayer::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;
	m_eID = PLAYER3;

	m_tInfo.fCX = 35.f;
	m_tInfo.fCY = 45.f;

	// ================
	// D3DXVECTOR3 Init
	// ================
	m_vCenter = { (WINCX / 2 + 60), (WINCY / 2 - 70), 0.f };	// ����, �÷��̾� ������ġ?
	m_tInfo.vPos = { m_vCenter.x, m_vCenter.y, m_vCenter.z };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };							//����
	m_tInfo.vLook = { 0.f, 1.f, 0.f };							// �ٶ󺸴� ����
	m_tInfo.vSize = { 1.f, 1.f, 0.f };							// ũ��(����)
	m_vPointScale = { 17.5f, 22.5f, 0.f };						// ������ ����

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
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/Link_Down1.png", L"YPlayer_Down");
	CAnimationTable::Get_Instance()->Create_Animation(
		L"YPlayer_Down", L"1",
		0, 0, 1, 0.f,
		32, 43, 50, 50
	);

	// �ִϸ��̼�, �̹��� ���� �ʱ�ȭ
	m_tInfo.tFrameTSet.Set_Keys(L"YPlayer_Down", L"1");
	CAnimationTable::Get_Instance()->Load_AnimData(m_tInfo.tFrameTSet);

}


int CYPlayer::Update()
{
	Key_Input();

	// D3DXVec3Normalize(��� ���� ������ ���� �ּ�, ���� ���ͷ� ���� ���� �ּ�) : ���� ���͸� ������ִ� �Լ�
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
	D3DXMatrixIdentity(&m_tInfo.matWorld);	// �׵���ķ� �����

	// ȸ������� �����, �̸� ���Ϳ� ���ؼ� ȸ���� ���͸� ���� �Ѵ�.
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);					// ũ��
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_tInfo.fAngle));	// ȸ��
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);	// �̵�

	// ũ��x����x�̵�
	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	// �簢�� ������ ȸ����ķ� ��ȯ
	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= { m_vCenter.x, m_vCenter.y, m_vCenter.z };

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	if (m_bIsWallColl)
	{

	}


	//m_fPreAngle = m_tInfo.fAngle;

	//if (m_iPreMoney != m_iMoney)
	//{
	//	CSoundMgr::Get_Instance()->PlaySound(L"PickUpItem.mp3", SOUND_EFFECT, 1.f);

	//	m_iPreMoney = m_iMoney;
	//}



	__super::Update_Rect();

	return OBJ_NOEVENT;
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
	hNewBrush = CreateSolidBrush(RGB(0, 255, 0));
	hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

	// �� ���� + ����
	hNewPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	hOldPen = (HPEN)SelectObject(hDC, hNewPen);

	//Ellipse(hDC,
	//	m_vPoint[2].x - 5.f,
	//	m_vPoint[2].y - 5.f,
	//	m_vPoint[2].x + 5.f,
	//	m_vPoint[2].y + 5.f);

	//Ellipse(hDC,
	//	m_vPoint[3].x - 5.f,
	//	m_vPoint[3].y - 5.f,
	//	m_vPoint[3].x + 5.f,
	//	m_vPoint[3].y + 5.f);


	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);


	//Draw_Rectangle(hDC);


	// �� ����
	SelectObject(hDC, hOldPen);
	DeleteObject(hNewPen);

	// �귯�� ����
	SelectObject(hDC, hOldBrush);
	DeleteObject(hNewBrush);

	CBmpMgr::Get_Instance()->Draw_PNG(hDC, m_tInfo, false);

	// ===================
	// �� ��� �ؽ�Ʈ ǥ��
	// ===================
	TCHAR szMoney[128];
	_stprintf_s(szMoney, L"%d", m_iMoney);
	TextOutW(hDC, 670, 11, szMoney, lstrlen(szMoney));

	//TCHAR szDishCount[128];
	//_stprintf_s(szDishCount, L"DishCount : %d", m_iDishCount);
	//TextOutW(hDC, 0, 540, szDishCount, lstrlen(szDishCount));


	//if (m_bIsDishColl)
	//{
	//	TCHAR szBuffer[128];
	//	_stprintf_s(szBuffer, L"�浹!!!");
	//	TextOutW(hDC, 0, 560, szBuffer, lstrlen(szBuffer));
	//}

	//TCHAR szsWallColl[128];
	//_stprintf_s(szsWallColl, L" �� �浹!!! : %d", m_bIsWallColl);
	//TextOutW(hDC, 0, 540, szsWallColl, lstrlen(szsWallColl));

	// ===================
	// ��ǥ Ȯ�� �ؽ�Ʈ ǥ��
	// ===================
	TCHAR szBuffer[128];
	_stprintf_s(szBuffer, L"Player.x : %f \t Player.y : %f", m_tInfo.vPos.x, m_tInfo.vPos.y);
	TextOutW(hDC, 0, 580, szBuffer, lstrlen(szBuffer));
}

void CYPlayer::Release()
{
}

void CYPlayer::Collide(CObj* _pDst)
{
	if (dynamic_cast<CYDish*>(_pDst) != nullptr)
	{
		m_bIsDishColl = true;
	}

	if (dynamic_cast<CYWall*>(_pDst) != nullptr)
	{
		//m_bIsWallColl = true;

		// ���� �ٶ󺸴� ������ �ݴ� ���ⱸ�ϱ�
		m_tInfo.vDir = (_pDst->Get_Info().vPos - m_tInfo.vPos) * -1.f;

		// D3DXVec3Normalize(��� ���� ������ ���� �ּ�, ���� ���ͷ� ���� ���� �ּ�) : ���� ���͸� ������ִ� �Լ�
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
		D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
		D3DXMatrixIdentity(&m_tInfo.matWorld);	// �׵���ķ� �����

		// ȸ������� �����, �̸� ���Ϳ� ���ؼ� ȸ���� ���͸� ���� �Ѵ�.
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);					// ũ��
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_tInfo.fAngle));	// ȸ��
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);	// �̵�

		// ũ��x����x�̵�
		m_tInfo.matWorld = matScale * matRotZ * matTrans;

		// �簢�� ������ ȸ����ķ� ��ȯ
		for (int i = 0; i < 4; ++i)
		{
			m_vPoint[i] = m_vOriginPoint[i];
			//m_vPoint[i] -= { m_vCenter.x - m_vOffset.x, m_vCenter.y - m_vOffset.y, m_vCenter.z};
			m_vPoint[i] -= { m_vCenter.x, m_vCenter.y, m_vCenter.z };

			D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
		}

		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;	// �̵�
	}
}

void CYPlayer::CollisionTile(CObj* pTarget)
{
	if (pTarget == nullptr)
		return;

	CTile* tile = dynamic_cast<CTile*>(pTarget);
	RECT Temp = tile->Get_Rect();
	switch (tile->Get_Option())
	{
	case TILEOPTION::NORMAL:

		break;
	case TILEOPTION::WALL:
		//if (m_eDir == RIGHT)
		//{
		//	m_tInfo.fX -= m_fSpeed;
		//}
		//else if (m_eDir == LEFT)
		//{
		//	m_tInfo.fX += m_fSpeed;
		//}
		//else if (m_eDir == UP)
		//{
		//	m_tInfo.fY += m_fSpeed;
		//}
		//else if (m_eDir == DOWN)
		//{
		//	m_tInfo.fY -= m_fSpeed;
		//}

		//isCollision = true;
		break;

	}
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
	if (GetAsyncKeyState(VK_LEFT))
	{
		//m_fAngle += D3DX_PI / 180.0f;
		m_tInfo.fAngle -= 2.f;
	}


	if (GetAsyncKeyState(VK_RIGHT))
	{
		//m_fAngle -= D3DX_PI / 180.0f;
		m_tInfo.fAngle += 2.f;
	}


	if (GetAsyncKeyState(VK_UP))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;

		//D3DXVec3TransformCoord(&)
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}
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