#include "stdafx.h"
#include "YDish.h"

#// MGR �Ŵ���
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AnimationTable.h"

// Obj
#include "YPlayer.h"
#include "YCustomer.h"
#include "YDish.h"

// ��..��
#include "YScene_Serving.h"

CYDish::CYDish()
	: m_bActive(false)
	, m_pPlayer(nullptr)
	, m_pCustomer(nullptr)
	, m_vOffset{}
	, m_vPointScale{}
	, m_vCenter{}
	, m_bIsPlayerColl(false)
	, m_bIsCustomerColl(false)
{
}

CYDish::~CYDish()
{
	Release();
}

void CYDish::Initialize()
{
	m_eRender = RENDER_EFFECT;
	m_eID = BULLET;

	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	// ================
	// D3DXVECTOR3 Init
	// ================
	// �÷��̾��� ��ġ���� ���� ������ �¾��.
	//m_vCenter = { CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos.x, CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos.y, 0.f };
	//m_vCenter = {m_pCustomer->Get_Info().vPos.x, m_pCustomer->Get_Info().vPos.y, 0.f };
	//m_vCenter = { 0.f, 0.f, 0.f };

	m_vOffset = { 40.f, 12.f, 0.f };								// �÷��̾�κ��� �󸶳� ������ ������
	m_tInfo.vPos = { m_vCenter.x - m_vOffset.x, m_vCenter.y - m_vOffset.y, m_vCenter.z };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };							//����
	m_tInfo.vLook = { 0.f, -1.f, 0.f };							// �ٶ󺸴� ����
	m_tInfo.vSize = { 1.f, 1.f, 0.f };							// ũ��(����)
	m_vPointScale = { 20.f, 20.f, 0.f };						// ������ ����

	m_fSpeed = 2.f;		// �̵� �ӵ�

	m_vPoint[0] = { m_tInfo.vPos.x - m_vPointScale.x ,m_tInfo.vPos.y - m_vPointScale.y, m_vPointScale.z };	// �� ���
	m_vPoint[1] = { m_tInfo.vPos.x + m_vPointScale.x ,m_tInfo.vPos.y - m_vPointScale.y, m_vPointScale.z };	// �� ���	
	m_vPoint[2] = { m_tInfo.vPos.x + m_vPointScale.x ,m_tInfo.vPos.y + m_vPointScale.y, m_vPointScale.z };	// �� �ϴ�
	m_vPoint[3] = { m_tInfo.vPos.x - m_vPointScale.x ,m_tInfo.vPos.y + m_vPointScale.y, m_vPointScale.z };	// �� �ϴ�

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	// ================
	// �̹��� ���� Init
	// ================
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/03_������������_����_����.png", L"YDish_lobster");
	CAnimationTable::Get_Instance()->Create_Animation(
		L"YDish_lobster", L"1",
		0, 0, 1, 0.f,
		0, 35, 50, 50
	);

	// �ִϸ��̼�, �̹��� ���� �ʱ�ȭ
	m_tInfo.tFrameTSet.Set_Keys(L"YDish_lobster", L"1");
	CAnimationTable::Get_Instance()->Load_AnimData(m_tInfo.tFrameTSet);

}

int CYDish::Update()
{
	if (m_bActive)
	{
		if (m_bIsPlayerColl)
		{
			// �÷��̾ �ٶ󺸴� ���� ���ϱ� (�����ʿ�)
			m_tInfo.vDir = CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos - m_tInfo.vPos;

			// �÷��̾��� ������ ���ϸ� �÷��̾��� ������ ���� ���ϰ�
			m_tInfo.fAngle = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fAngle;

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
				m_vPoint[i] -= { m_vCenter.x - m_vOffset.x, m_vCenter.y - m_vOffset.y, m_vCenter.z};

				D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
			}

			m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;	// �̵�
		}

		// �մ԰� �浹�ϸ� ����
		if (m_bIsCustomerColl)
		{
			//m_tInfo.vPos = { m_vCenter.x, m_vCenter.y, m_vCenter.z };
			dynamic_cast<CYPlayer*>(m_pPlayer)->Set_DishCount(-1);
			dynamic_cast<CYScene_Serving*>(m_ServingScene)->Set_CurDish(-1);
			m_bIsCustomerColl = false;
			return OBJ_DEAD;			
		}

		//Key_Input();

		__super::Update_Rect();

	}

	return OBJ_NOEVENT;
}

void CYDish::Late_Update()
{
}

void CYDish::Render(HDC hDC)
{
	if (m_bActive)
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

		//Rectangle(hDC,
		//	m_tRect.left,
		//	m_tRect.top,
		//	m_tRect.right,
		//	m_tRect.bottom);

		Draw_Rectangle(hDC);

		// �� ����
		SelectObject(hDC, hOldPen);
		DeleteObject(hNewPen);

		// �귯�� ����
		SelectObject(hDC, hOldBrush);
		DeleteObject(hNewBrush);

		CBmpMgr::Get_Instance()->Draw_PNG(hDC, m_tInfo, false);
	}
}

void CYDish::Release()
{
}

void CYDish::Collide(CObj* _pDst)
{
	//if (PLAYER == dynamic_cast<CYPlayer*>(_pDst)->Get_Id());
	//{
	//	m_bIsPlayerColl = true;
	//}

	if (m_bActive)
	{
		if (dynamic_cast<CYPlayer*>(_pDst) != nullptr)
		{
			if (1 > dynamic_cast<CYPlayer*>(m_pPlayer)->Get_DishCount())
			{
				// �÷��̾�� �ѹ��� �Ѱ����� ������ �� �ִ�.
				dynamic_cast<CYPlayer*>(m_pPlayer)->Set_DishCount(1);
				m_bIsPlayerColl = true;
			}
			
		}
		else if (dynamic_cast<CYCustomer*>(_pDst) != nullptr)
		{
			m_bIsCustomerColl = true;
			m_bIsPlayerColl = false;
			dynamic_cast<CYPlayer*>(m_pPlayer)->Set_Money(100);
		}
	}
}

void CYDish::Draw_Rectangle(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
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