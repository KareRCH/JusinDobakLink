#include "stdafx.h"
#include "YCustomer.h"

#// MGR �Ŵ���
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "AnimationTable.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

// ������ ����
#include "AbstractFactory.h"

// Obj
#include "YDish.h"

// ��..��
#include "YScene_Serving.h"


CYCustomer::CYCustomer()
	: m_vPointScale{}
	, m_vCenter{}
	, m_bActive(false)
	, m_bIsPlayerColl(false)
	, m_bIsDishColl(false)
	, m_ServingScene(nullptr)
	, m_iRand(6)
	, m_iDishRand(3)

{
}

CYCustomer::~CYCustomer()
{
	Release();
}

void CYCustomer::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;
	m_eID = MONSTER;


	m_tInfo.fCX = 90.f;
	m_tInfo.fCY = 80.f;

	// ================
	// D3DXVECTOR3 Init
	// ================
	//m_vCenter = { 566.1, 248, 0.f };	// ����, �մ� ������ġ?
	m_tInfo.vPos = { m_vCenter.x, m_vCenter.y, m_vCenter.z };	
	m_tInfo.vDir = { 1.f, 0.f, 0.f };							//����
	m_tInfo.vLook = { 0.f, 1.f, 0.f };							// �ٶ󺸴� ����
	m_tInfo.vSize = { 1.f, 1.f, 0.f };							// �̹��� ũ��(����)
	m_vPointScale = { 45.f, 40.f, 0.f };						// ������ ����

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
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/02_������������_�մ�.png", L"YCustomer");
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/����_origin.png", L"YTeacher_origin");
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/����_red.png", L"YTeacher_red");
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/����_blue.png", L"YTeacher_blue");
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/����_green.png", L"YTeacher_green");
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/����_reverse.png", L"YTeacher_reverse");

	m_pKey[0] = L"YCustomer";
	m_pKey[1] = L"YTeacher_origin";
	m_pKey[2] = L"YTeacher_red";
	m_pKey[3] = L"YTeacher_blue";
	m_pKey[4] = L"YTeacher_green";
	m_pKey[5] = L"YTeacher_reverse";

	//CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/02_������������_�մ�.png", L"YCustomer");
	//CAnimationTable::Get_Instance()->Create_Animation(
	//	L"YCustomer", L"1",
	//	0, 0, 1, 0.f,
	//	33, 25, 50, 50
	//);

	//CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/02_������������_�մ�����.png", L"YTeacher");
	//CAnimationTable::Get_Instance()->Create_Animation(
	//	L"YTeacher", L"1",
	//	0, 0, 1, 0.f,
	//	32, 50, 50, 50
	//);

	//// �ִϸ��̼�, �̹��� ���� �ʱ�ȭ
	//m_tInfo.tFrameTSet.Set_Keys(L"YTeacher", L"1");
	//CAnimationTable::Get_Instance()->Load_AnimData(m_tInfo.tFrameTSet);

	//m_tInfo.tFrameTSet.Set_Keys(L"YCustomer", L"1");
	//CAnimationTable::Get_Instance()->Load_AnimData(m_tInfo.tFrameTSet);


	m_vCustomerPos[0] = { 565.f, 290.f, 0.f };
	m_vCustomerPos[1] = { 353.f, 290.f, 0.f };
	m_vCustomerPos[2] = { 135.f, 290.f, 0.f };
	m_vCustomerPos[3] = { 565.f, 470.f, 0.f };
	m_vCustomerPos[4] = { 353.f, 470.f, 0.f };
	m_vCustomerPos[5] = { 135.f, 470.f, 0.f };

	m_dwTime = GetTickCount();
}

int CYCustomer::Update()
{
	if (nullptr != m_ServingScene)
	{
		//if (dynamic_cast<CYScene_Serving*>(m_ServingScene)->Get_IsEnd())
		//{
		//	return OBJ_DEAD;
		//}
		if (m_bActive)
		{
			// D3DXVec3Normalize(��� ���� ������ ���� �ּ�, ���� ���ͷ� ���� ���� �ּ�) : ���� ���͸� ������ִ� �Լ�
			D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
			D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
			D3DXMatrixIdentity(&m_tInfo.matWorld);	// �׵���ķ� �����

			// ȸ������� �����, �̸� ���Ϳ� ���ؼ� ȸ���� ���͸� ���� �Ѵ�.
			D3DXMATRIX matScale, matRotZ, matTrans;
			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);			// ũ��
			D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_tInfo.fAngle));	// ȸ��
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);	// �̵�

			// ũ��x����x�̵�
			m_tInfo.matWorld = matScale * matRotZ * matTrans;

			// �簢�� ������ ȸ����ķ� ��ȯ
			for (int i = 0; i < 4; ++i)
			{
				m_vPoint[i] = m_vOriginPoint[i];
				m_vPoint[i] -= {m_vCenter.x, m_vCenter.y, m_vCenter.z};

				D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
			}

			if (m_bIsDishColl)
			{
				m_bIsDishColl = false;

				if (m_dwTime + 3000 < GetTickCount())
				{
					//CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);


					m_bIsPlayerColl = false;

					dynamic_cast<CYScene_Serving*>(m_ServingScene)->Set_CurCustomer(-1);

					m_bActive = false;
					//return OBJ_DEAD;

					m_dwTime = GetTickCount();
				}

			}

			__super::Update_Rect();

		}
		return OBJ_NOEVENT;
	}
	
}

void CYCustomer::Late_Update()
{
}

void CYCustomer::Render(HDC hDC)
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

		//CBmpMgr::Get_Instance()->Draw_PNG(hDC, m_tInfo, false);

		FRAME tFrame = {};
		tFrame.iOffsetX = 34; tFrame.iOffsetY = 70;

		for (int i = 0; i < 6; ++i)
		{
			if (i == m_iRand)
			{
				CBmpMgr::Get_Instance()->Draw_PNG(hDC, m_pKey[i], m_tInfo, tFrame, 0, 0, 50, 50, false);
			}
		}

	}
	
}

void CYCustomer::Release()
{
}

void CYCustomer::Collide(CObj* _pDst)
{
	if (m_bActive)
	{
		if (dynamic_cast<CYDish*>(_pDst) != nullptr)
		{
			m_bIsDishColl = true;
		}
	}
}

void CYCustomer::Draw_Rectangle(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
}

void CYCustomer::Create_Dish()
{
	m_iDishRand = rand() % 2;		// 0���� 2����

	if (m_bActive)
	{
		// ���� ���� �׽�Ʈ
		//CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<CYDish>::Create());

		CObj* pDish = new CYDish;
		dynamic_cast<CYDish*>(pDish)->Set_Customer(this);


		if (290.f == m_vCenter.y)
		{
			dynamic_cast<CYDish*>(pDish)->Set_Center(D3DXVECTOR3(m_tInfo.vPos.x + 300, m_tInfo.vPos.y - 170, 0.f));
		}
		else
		{
			dynamic_cast<CYDish*>(pDish)->Set_Center(D3DXVECTOR3(m_tInfo.vPos.x + 350, m_tInfo.vPos.y - 350, 0.f));
		}

		pDish->Initialize();
		dynamic_cast<CYDish*>(pDish)->Set_Scene(m_ServingScene);
		dynamic_cast<CYDish*>(pDish)->Set_Rand(m_iDishRand);
		dynamic_cast<CYDish*>(pDish)->Set_Active(true);
		CObjMgr::Get_Instance()->Add_Object(BULLET, pDish);
	}

}
