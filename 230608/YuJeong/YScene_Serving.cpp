#include "stdafx.h"
#include "YScene_Serving.h"

#// MGR �Ŵ���
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"

// ������ ����
#include "AbstractFactory.h"

// Obj
#include "YPlayer.h"
#include "YDish.h"
#include "YCustomer.h"
#include "YTeacher.h"

// Obj - UI
#include "YTimeGauge.h"


CYScene_Serving::CYScene_Serving()
	: m_bIsEnd(false)
	, m_imaxCustomer(3)
	, m_iCurCustomer(0)
	, m_imaxDish(3)
	, m_iCurDish(0)
{
}

CYScene_Serving::~CYScene_Serving()
{
	Release();
}

void CYScene_Serving::Initialize()
{
	// ��� �̹���
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../230608/YuJeong/Image_Yu/00_������������_BG.bmp", L"Serving_BG");

	// �ð� ������ UI
	CObjMgr::Get_Instance()->Add_Object(UI, CAbstractFactory<CYTimeGauge>::Create());


	// ============
	// �÷��̾� ����
	// ============
	CObjMgr::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CYPlayer>::Create());


	m_vCustomerPos[0] = { 566.1, 248, 0.f };
	m_vCustomerPos[1] = { 354.1, 248, 0.f };
	m_vCustomerPos[2] = { 136.1, 248, 0.f };
	m_vCustomerPos[3] = { 566.1, 428, 0.f };
	m_vCustomerPos[4] = { 354.1, 428, 0.f };
	m_vCustomerPos[5] = { 136.1, 428, 0.f };

	for (int i = 0; i < 6; ++i)
	{
		m_Customer[i] = Create_Customer(m_vCustomerPos[i]);
	}

	// =========
	// ���� ����
	// =========
	//CObjMgr::Get_Instance()->Add_Object(UNIT, CAbstractFactory<CYTeacher>::Create());

	m_dwTime = GetTickCount();
}

void CYScene_Serving::Update()
{
	CObjMgr::Get_Instance()->Update();

	if (m_dwTime + 1000 < GetTickCount())
	{
		if (m_iCurCustomer < m_imaxCustomer)
		{
			m_iRand = rand() % 6;		// 0���� 6����
			
			if (true == dynamic_cast<CYCustomer*>(m_Customer[m_iRand])->Get_Active())
			{
				// �̹� Ȱ��ȭ �� �մ��̸� �ٽ� �̱�
				m_iRand = rand() % 6;
			}
			else
			{
				++m_iCurCustomer;
				++m_iCurDish;
				dynamic_cast<CYCustomer*>(m_Customer[m_iRand])->Set_Active(true);
				dynamic_cast<CYCustomer*>(m_Customer[m_iRand])->Create_Dish();			
			}
			m_dwTime = GetTickCount();
		}
	}
}

void CYScene_Serving::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CYScene_Serving::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Serving_BG");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
	//CObjMgr::Get_Instance()->Get_Player()->Render(hDC);


	TCHAR szCustomerCount[128];
	_stprintf_s(szCustomerCount, L"���� �մ� �� : %d", m_iCurCustomer);
	TextOutW(hDC, 0, 520, szCustomerCount, lstrlen(szCustomerCount));
}

void CYScene_Serving::Release()
{
}


CObj* CYScene_Serving::Create_Customer(D3DXVECTOR3 _vCenterPos)
{
	// �մ� ���� �׽�Ʈ
	//CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CYCustomer>::Create());

	//++m_iCurCustomer;

	CObj* pCustomer = new CYCustomer;
	dynamic_cast<CYCustomer*>(pCustomer)->Set_Center(_vCenterPos);
	dynamic_cast<CYCustomer*>(pCustomer)->Set_Scene(this);
	pCustomer->Initialize();

	CObjMgr::Get_Instance()->Add_Object(MONSTER, pCustomer);

	return pCustomer;

}
