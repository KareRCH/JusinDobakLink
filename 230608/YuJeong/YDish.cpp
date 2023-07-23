#include "stdafx.h"
#include "YDish.h"

#// MGR 매니저
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AnimationTable.h"

// Obj
#include "YPlayer.h"
#include "YCustomer.h"
#include "YDish.h"

// 씬..ㅠ
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
	// 플레이어의 위치벡터 값을 가지고 태어난다.
	//m_vCenter = { CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos.x, CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos.y, 0.f };
	//m_vCenter = {m_pCustomer->Get_Info().vPos.x, m_pCustomer->Get_Info().vPos.y, 0.f };
	//m_vCenter = { 0.f, 0.f, 0.f };

	m_vOffset = { 40.f, 12.f, 0.f };								// 플레이어로부터 얼마나 떨어져 있을지
	m_tInfo.vPos = { m_vCenter.x - m_vOffset.x, m_vCenter.y - m_vOffset.y, m_vCenter.z };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };							//방향
	m_tInfo.vLook = { 0.f, -1.f, 0.f };							// 바라보는 방향
	m_tInfo.vSize = { 1.f, 1.f, 0.f };							// 크기(배율)
	m_vPointScale = { 20.f, 20.f, 0.f };						// 점들의 간격

	m_fSpeed = 2.f;		// 이동 속도

	m_vPoint[0] = { m_tInfo.vPos.x - m_vPointScale.x ,m_tInfo.vPos.y - m_vPointScale.y, m_vPointScale.z };	// 좌 상단
	m_vPoint[1] = { m_tInfo.vPos.x + m_vPointScale.x ,m_tInfo.vPos.y - m_vPointScale.y, m_vPointScale.z };	// 우 상단	
	m_vPoint[2] = { m_tInfo.vPos.x + m_vPointScale.x ,m_tInfo.vPos.y + m_vPointScale.y, m_vPointScale.z };	// 우 하단
	m_vPoint[3] = { m_tInfo.vPos.x - m_vPointScale.x ,m_tInfo.vPos.y + m_vPointScale.y, m_vPointScale.z };	// 좌 하단

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	// ================
	// 이미지 관련 Init
	// ================
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/03_서빙스테이지_음식_가재.png", L"YDish_lobster");
	CAnimationTable::Get_Instance()->Create_Animation(
		L"YDish_lobster", L"1",
		0, 0, 1, 0.f,
		0, 35, 50, 50
	);

	// 애니메이션, 이미지 설정 초기화
	m_tInfo.tFrameTSet.Set_Keys(L"YDish_lobster", L"1");
	CAnimationTable::Get_Instance()->Load_AnimData(m_tInfo.tFrameTSet);

}

int CYDish::Update()
{
	if (m_bActive)
	{
		if (m_bIsPlayerColl)
		{
			// 플레이어를 바라보는 방향 구하기 (수정필요)
			m_tInfo.vDir = CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos - m_tInfo.vPos;

			// 플레이어의 각도가 변하면 플레이어의 각도로 같이 변하게
			m_tInfo.fAngle = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fAngle;

			// D3DXVec3Normalize(결과 값을 저장할 벡터 주소, 단위 벡터로 만들 벡터 주소) : 단위 벡터를 만들어주는 함수
			D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
			D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
			D3DXMatrixIdentity(&m_tInfo.matWorld);	// 항등행렬로 만들기

			// 회전행렬을 만들고, 이를 벡터에 곱해서 회전된 벡터를 얻어야 한다.
			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);					// 크기
			D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_tInfo.fAngle));	// 회전
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);	// 이동

			// 크기x자전x이동
			m_tInfo.matWorld = matScale * matRotZ * matTrans;

			// 사각형 점들을 회전행렬로 변환
			for (int i = 0; i < 4; ++i)
			{
				m_vPoint[i] = m_vOriginPoint[i];
				m_vPoint[i] -= { m_vCenter.x - m_vOffset.x, m_vCenter.y - m_vOffset.y, m_vCenter.z};

				D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
			}

			m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;	// 이동
		}

		// 손님과 충돌하면 삭제
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
				// 플레이어는 한번에 한개씩만 서빙할 수 있다.
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



// 항등 행렬을 만들어주는 함수
// D3DXMatrixIdentity(항등행렬을 만들고자 하는 행렬의 주소)

// 크기 행렬을 만들어주는 함수
// D3DXMatrixScaling(크기 행렬의 주소, x 배율, y배율, z배율)

// x축 회전 행렬을 만들어주는 함수
// D3DXMatrixRotationX(x축 회전 행렬의 주소, 회전각도(라디안))

// y축 회전 행렬을 만들어주는 함수
// D3DXMatrixRotationY(y축 회전 행렬의 주소, 회전각도(라디안))

// z축 회전 행렬을 만들어주는 함수
// D3DXMatrixRotationZ(z축 회전 행렬의 주소, 회전각도(라디안))

// 이동 행렬을 만들어주는 함수
// D3DXMatrixTranslation(이동 행렬의 주소, x좌표, y좌표, z좌표)

// 역 행렬을 만들어주는 함수
// D3DXMatrixInverse(결과 값을 저장할 행렬의 주소, NULL, 원본 행렬의 주소)

// 벡터와 행렬의 곱셈을 수행하는 함수
// 결과 값으로 위치 벡터가 발생 D3DXVec3TransformCoord(결과 값을 저장할 벡터 주소, 행렬과 곱하기를 할 위치 벡터 주소, 행렬 주소);
// 결과 값으로 방향 벡터가 발생 D3DXVec3TransformNormal(결과 값을 저장할 벡터 주소, 행렬과 곱하기를 할 방향 벡터 주소, 행렬 주소);