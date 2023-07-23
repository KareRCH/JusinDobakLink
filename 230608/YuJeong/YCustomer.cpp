#include "stdafx.h"
#include "YCustomer.h"

#// MGR 매니저
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "AnimationTable.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

// 디자인 패턴
#include "AbstractFactory.h"

// Obj
#include "YDish.h"

// 씬..ㅠ
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
	//m_vCenter = { 566.1, 248, 0.f };	// 원점, 손님 생성위치?
	m_tInfo.vPos = { m_vCenter.x, m_vCenter.y, m_vCenter.z };	
	m_tInfo.vDir = { 1.f, 0.f, 0.f };							//방향
	m_tInfo.vLook = { 0.f, 1.f, 0.f };							// 바라보는 방향
	m_tInfo.vSize = { 1.f, 1.f, 0.f };							// 이미지 크기(배율)
	m_vPointScale = { 45.f, 40.f, 0.f };						// 점들의 간격

	m_fSpeed = 2.f;												// 속도

	m_vPoint[0] = { m_tInfo.vPos.x - m_vPointScale.x ,m_tInfo.vPos.y - m_vPointScale.y, m_vPointScale.z };	// 좌 상단
	m_vPoint[1] = { m_tInfo.vPos.x + m_vPointScale.x ,m_tInfo.vPos.y - m_vPointScale.y, m_vPointScale.z };	// 우 상단	
	m_vPoint[2] = { m_tInfo.vPos.x + m_vPointScale.x ,m_tInfo.vPos.y + m_vPointScale.y, m_vPointScale.z };	// 우 하단
	m_vPoint[3] = { m_tInfo.vPos.x - m_vPointScale.x ,m_tInfo.vPos.y + m_vPointScale.y, m_vPointScale.z };	// 좌 하단

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];


	// ================
	// 이미지 관련 Init
	// ================
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/02_서빙스테이지_손님.png", L"YCustomer");
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/유쌤_origin.png", L"YTeacher_origin");
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/유쌤_red.png", L"YTeacher_red");
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/유쌤_blue.png", L"YTeacher_blue");
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/유쌤_green.png", L"YTeacher_green");
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/유쌤_reverse.png", L"YTeacher_reverse");

	m_pKey[0] = L"YCustomer";
	m_pKey[1] = L"YTeacher_origin";
	m_pKey[2] = L"YTeacher_red";
	m_pKey[3] = L"YTeacher_blue";
	m_pKey[4] = L"YTeacher_green";
	m_pKey[5] = L"YTeacher_reverse";

	//CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/02_서빙스테이지_손님.png", L"YCustomer");
	//CAnimationTable::Get_Instance()->Create_Animation(
	//	L"YCustomer", L"1",
	//	0, 0, 1, 0.f,
	//	33, 25, 50, 50
	//);

	//CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/02_서빙스테이지_손님유쌤.png", L"YTeacher");
	//CAnimationTable::Get_Instance()->Create_Animation(
	//	L"YTeacher", L"1",
	//	0, 0, 1, 0.f,
	//	32, 50, 50, 50
	//);

	//// 애니메이션, 이미지 설정 초기화
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
			// D3DXVec3Normalize(결과 값을 저장할 벡터 주소, 단위 벡터로 만들 벡터 주소) : 단위 벡터를 만들어주는 함수
			D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
			D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
			D3DXMatrixIdentity(&m_tInfo.matWorld);	// 항등행렬로 만들기

			// 회전행렬을 만들고, 이를 벡터에 곱해서 회전된 벡터를 얻어야 한다.
			D3DXMATRIX matScale, matRotZ, matTrans;
			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);			// 크기
			D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_tInfo.fAngle));	// 회전
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);	// 이동

			// 크기x자전x이동
			m_tInfo.matWorld = matScale * matRotZ * matTrans;

			// 사각형 점들을 회전행렬로 변환
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

		// 브러쉬 설정
		//hNewBrush = CreateSolidBrush(RGB(240, 128, 128));
		hNewBrush = CreateSolidBrush(RGB(0, 255, 0));
		hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

		// 펜 설정 + 해제
		hNewPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		hOldPen = (HPEN)SelectObject(hDC, hNewPen);

		//Rectangle(hDC,
		//	m_tRect.left,
		//	m_tRect.top,
		//	m_tRect.right,
		//	m_tRect.bottom);

		Draw_Rectangle(hDC);

		// 펜 해제
		SelectObject(hDC, hOldPen);
		DeleteObject(hNewPen);

		// 브러쉬 해제
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
	m_iDishRand = rand() % 2;		// 0부터 2까지

	if (m_bActive)
	{
		// 음식 생성 테스트
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
