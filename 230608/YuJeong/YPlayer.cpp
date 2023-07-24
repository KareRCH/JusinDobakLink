#include "stdafx.h"
#include "YPlayer.h"

#// MGR 매니저
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
	m_vCenter = { (WINCX / 2 + 60), (WINCY / 2 - 70), 0.f };	// 원점, 플레이어 생성위치?
	m_tInfo.vPos = { m_vCenter.x, m_vCenter.y, m_vCenter.z };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };							//방향
	m_tInfo.vLook = { 0.f, 1.f, 0.f };							// 바라보는 방향
	m_tInfo.vSize = { 1.f, 1.f, 0.f };							// 크기(배율)
	m_vPointScale = { 17.5f, 22.5f, 0.f };						// 점들의 간격

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
	CBmpMgr::Get_Instance()->Insert_PNG(L"../230608/YuJeong/Image_Yu/Link_Down1.png", L"YPlayer_Down");
	CAnimationTable::Get_Instance()->Create_Animation(
		L"YPlayer_Down", L"1",
		0, 0, 1, 0.f,
		32, 43, 50, 50
	);

	// 애니메이션, 이미지 설정 초기화
	m_tInfo.tFrameTSet.Set_Keys(L"YPlayer_Down", L"1");
	CAnimationTable::Get_Instance()->Load_AnimData(m_tInfo.tFrameTSet);

}


int CYPlayer::Update()
{
	Key_Input();

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

	// 브러쉬 설정
	//hNewBrush = CreateSolidBrush(RGB(240, 128, 128));
	hNewBrush = CreateSolidBrush(RGB(0, 255, 0));
	hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

	// 펜 설정 + 해제
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


	// 펜 해제
	SelectObject(hDC, hOldPen);
	DeleteObject(hNewPen);

	// 브러쉬 해제
	SelectObject(hDC, hOldBrush);
	DeleteObject(hNewBrush);

	CBmpMgr::Get_Instance()->Draw_PNG(hDC, m_tInfo, false);

	// ===================
	// 돈 출력 텍스트 표시
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
	//	_stprintf_s(szBuffer, L"충돌!!!");
	//	TextOutW(hDC, 0, 560, szBuffer, lstrlen(szBuffer));
	//}

	//TCHAR szsWallColl[128];
	//_stprintf_s(szsWallColl, L" 벽 충돌!!! : %d", m_bIsWallColl);
	//TextOutW(hDC, 0, 540, szsWallColl, lstrlen(szsWallColl));

	// ===================
	// 좌표 확인 텍스트 표시
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

		// 벽을 바라보는 방향의 반대 방향구하기
		m_tInfo.vDir = (_pDst->Get_Info().vPos - m_tInfo.vPos) * -1.f;

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
			//m_vPoint[i] -= { m_vCenter.x - m_vOffset.x, m_vCenter.y - m_vOffset.y, m_vCenter.z};
			m_vPoint[i] -= { m_vCenter.x, m_vCenter.y, m_vCenter.z };

			D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
		}

		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;	// 이동
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