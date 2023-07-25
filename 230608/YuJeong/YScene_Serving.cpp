#include "stdafx.h"
#include "YScene_Serving.h"

#// MGR 매니저
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "TileMgr.h"

// 디자인 패턴
#include "AbstractFactory.h"

// Obj
#include "YPlayer.h"
#include "YDish.h"
#include "YCustomer.h"
#include "YTeacher.h"
#include "YWall.h"

// Obj - UI
#include "YTimeGauge.h"


CYScene_Serving::CYScene_Serving()
	: m_bIsEnd(false)
	, m_imaxCustomer(3)
	, m_iCurCustomer(0)
	, m_imaxDish(3)
	, m_iCurDish(0)
	, m_iCustomerRand(6)
	, m_pTimeGauge(nullptr)
{
}

CYScene_Serving::~CYScene_Serving()
{
	Release();
}

void CYScene_Serving::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"와르루루 꺄르루루.mp3", 0.3f);

	// 배경 이미지
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../230608/YuJeong/Image_Yu/00_서빙스테이지_BG.bmp", L"Serving_BG");

	// 시간 게이지 UI
	CObj* m_pTimeGauge = new CYTimeGauge;
	dynamic_cast<CYTimeGauge*>(m_pTimeGauge)->Set_Scene(this);
	m_pTimeGauge->Initialize();
	CObjMgr::Get_Instance()->Add_Object(UI, m_pTimeGauge);


	// 벽(야매 타일) 생성
	m_vWallPos[0] = { 565.f, 315.f, 0.f };
	m_vWallPos[1] = { 353.f, 315.f, 0.f };
	m_vWallPos[2] = { 135.f, 315.f, 0.f };
	m_vWallPos[3] = { 565.f, 495.f, 0.f };
	m_vWallPos[4] = { 353.f, 495.f, 0.f };
	m_vWallPos[5] = { 135.f, 495.f, 0.f };
	m_vWallPos[6] = { WINCX/2, 68.5f, 0.f };
	m_vWallPos[7] = { (float)WINCX - 22.5f, WINCY / 2, 0.f };


	// 벽 생성
	for (int i = 0; i < 8; ++i)
	{
		if ( 6 > i)
		{
			m_pWall[i] = Create_Wall(m_vWallPos[i], 0);
		}
		else if( 6 == i )
		{
			m_pWall[i] = Create_Wall(m_vWallPos[i], 1);
		}
		else if ( 7 == i)
		{
			m_pWall[i] = Create_Wall(m_vWallPos[i], 2);
		}

	}

	// ============
	// 플레이어 생성
	// ============
	CObjMgr::Get_Instance()->Add_Object(PLAYER3, CAbstractFactory<CYPlayer>::Create());


	// 손님 위치
	m_vCustomerPos[0] = { 565.f, 290.f, 0.f };
	m_vCustomerPos[1] = { 353.f, 290.f, 0.f };
	m_vCustomerPos[2] = { 135.f, 290.f, 0.f };
	m_vCustomerPos[3] = { 565.f, 470.f, 0.f };
	m_vCustomerPos[4] = { 353.f, 470.f, 0.f };
	m_vCustomerPos[5] = { 135.f, 470.f, 0.f };


	// 손님 생성
	for (int i = 0; i < 6; ++i)
	{
		m_pCustomer[i] = Create_Customer(m_vCustomerPos[i]);
	}

	m_dwTime = GetTickCount();
}

void CYScene_Serving::Update()
{
	if (!m_bIsEnd)
	{
		if (m_dwTime + 2000 < GetTickCount())
		{
			if (m_iCurCustomer < m_imaxCustomer)
			{
				m_iRand = rand() % 6;		// 0부터 6까지

				if (dynamic_cast<CYCustomer*>(m_pCustomer[m_iRand])->Get_Active())
				{
					// 이미 활성화 된 손님이면 다시 뽑기
					m_iRand = rand() % 6;
				}
				else
				{
					if (m_dwTime + 4000 < GetTickCount())
					{
						++m_iCurCustomer;
						++m_iCurDish;
						m_iCustomerRand = rand() % 5;		// 0부터 5까지
						dynamic_cast<CYCustomer*>(m_pCustomer[m_iRand])->Set_Rand(m_iCustomerRand);
						dynamic_cast<CYCustomer*>(m_pCustomer[m_iRand])->Set_Active(true);
						dynamic_cast<CYCustomer*>(m_pCustomer[m_iRand])->Create_Dish();

						m_dwTime = GetTickCount();
					}
				}
			}
		}
		CObjMgr::Get_Instance()->Update();
	}
}

void CYScene_Serving::Late_Update()
{	
	CObjMgr::Get_Instance()->Late_Update();

	if (m_bIsEnd)
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);
			return;
		}
	}
}

void CYScene_Serving::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Serving_BG");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
	//CObjMgr::Get_Instance()->Get_Player()->Render(hDC);


	//TCHAR szCustomerCount[128];
	//_stprintf_s(szCustomerCount, L"현재 손님 수 : %d", m_iCurCustomer);
	//TextOutW(hDC, 0, 560, szCustomerCount, lstrlen(szCustomerCount));

	//TCHAR szEnd[128];
	//_stprintf_s(szEnd, L"게임종료? : %d", m_bIsEnd);
	//TextOutW(hDC, 0, 580, szEnd, lstrlen(szEnd));

	if (m_bIsEnd)
	{
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, 0xffffff);
		TCHAR szEndMoney[128];
		_stprintf_s(szEndMoney, L"%d 원", dynamic_cast<CYPlayer*>(CObjMgr::Get_Instance()->Get_Player3())->Get_Money());
		TextOutW(hDC, 350, 245, szEndMoney, lstrlen(szEndMoney));
	}
}

void CYScene_Serving::Release()
{
	CSoundMgr::Get_Instance()->StopAll();

	CObjMgr::Get_Instance()->Delete_ID_Dead(BULLET);
	CObjMgr::Get_Instance()->Delete_ID_Dead(MONSTER);	
	CObjMgr::Get_Instance()->Delete_ID_Dead(UI);
	CObjMgr::Get_Instance()->Delete_ID_Dead(PLAYER3);

	//Safe_Delete(m_pTimeGauge);
}


CObj* CYScene_Serving::Create_Customer(D3DXVECTOR3 _vCenterPos)
{
	CObj* pCustomer = new CYCustomer;
	dynamic_cast<CYCustomer*>(pCustomer)->Set_Center(_vCenterPos);
	dynamic_cast<CYCustomer*>(pCustomer)->Set_Scene(this);
	pCustomer->Initialize();

	CObjMgr::Get_Instance()->Add_Object(MONSTER, pCustomer);

	return pCustomer;
}

CObj* CYScene_Serving::Create_Wall(D3DXVECTOR3 _vCenterPos, int _iType)
{
	CObj* pWall = new CYWall;
	dynamic_cast<CYWall*>(pWall)->Set_Center(_vCenterPos);
	if( 0 ==_iType)
	{
		// 식탁
		dynamic_cast<CYWall*>(pWall)->Set_PointScale(D3DXVECTOR3(52.5f, 65.f, 0.f));
		dynamic_cast<CYWall*>(pWall)->Set_fcxy(105.f, 130.f);
	}

	if(1 == _iType)
	{
		// 상단 벽
		dynamic_cast<CYWall*>(pWall)->Set_PointScale(D3DXVECTOR3(WINCX / 2, 61.5f, 0.f));
		dynamic_cast<CYWall*>(pWall)->Set_fcxy(WINCX, 137.f);
	}

	if (2 == _iType)
	{
		// 우측 벽
		dynamic_cast<CYWall*>(pWall)->Set_PointScale(D3DXVECTOR3(22.5f, WINCY, 0.f));
		dynamic_cast<CYWall*>(pWall)->Set_fcxy(45.f, WINCY);
	}

	pWall->Initialize();
	CObjMgr::Get_Instance()->Add_Object(TILE, pWall);

	return pWall;
}
