#include "stdafx.h"
#include "YScene_Serving.h"

#// MGR 매니저
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"

// 디자인 패턴
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
	// 배경 이미지
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../230608/YuJeong/Image_Yu/00_서빙스테이지_BG.bmp", L"Serving_BG");

	// 시간 게이지 UI
	CObjMgr::Get_Instance()->Add_Object(UI, CAbstractFactory<CYTimeGauge>::Create());


	// ============
	// 플레이어 생성
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
	// 유쌤 생성
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
			m_iRand = rand() % 6;		// 0부터 6까지
			
			if (true == dynamic_cast<CYCustomer*>(m_Customer[m_iRand])->Get_Active())
			{
				// 이미 활성화 된 손님이면 다시 뽑기
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
	_stprintf_s(szCustomerCount, L"현재 손님 수 : %d", m_iCurCustomer);
	TextOutW(hDC, 0, 520, szCustomerCount, lstrlen(szCustomerCount));
}

void CYScene_Serving::Release()
{
}


CObj* CYScene_Serving::Create_Customer(D3DXVECTOR3 _vCenterPos)
{
	// 손님 생성 테스트
	//CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CYCustomer>::Create());

	//++m_iCurCustomer;

	CObj* pCustomer = new CYCustomer;
	dynamic_cast<CYCustomer*>(pCustomer)->Set_Center(_vCenterPos);
	dynamic_cast<CYCustomer*>(pCustomer)->Set_Scene(this);
	pCustomer->Initialize();

	CObjMgr::Get_Instance()->Add_Object(MONSTER, pCustomer);

	return pCustomer;

}
