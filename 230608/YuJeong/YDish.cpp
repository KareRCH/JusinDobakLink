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

	m_vPoint[0] = { m_tInfo.vPos.x - 20.f ,m_tInfo.vPos.y - 20.f, 0.f };	// 좌 상단
	m_vPoint[1] = { m_tInfo.vPos.x + 20.f ,m_tInfo.vPos.y - 20.f, 0.f };	// 우 상단	
	m_vPoint[2] = { m_tInfo.vPos.x + 20.f ,m_tInfo.vPos.y + 20.f, 0.f };	// 우 하단
	m_vPoint[3] = { m_tInfo.vPos.x - 20.f ,m_tInfo.vPos.y + 20.f, 0.f };	// 좌 하단

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];
}

int CYDish::Update()
{
	//Key_Input();
	
	// D3DXVec3Normalize(결과 값을 저장할 벡터 주소, 단위 벡터로 만들 벡터 주소) : 단위 벡터를 만들어주는 함수
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
	D3DXMatrixIdentity(&m_tInfo.matWorld);	// 항등행렬로 만들기

	// 회전행렬을 만들고, 이를 벡터에 곱해서 회전된 벡터를 얻어야 한다.
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);							// 크기
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_tInfo.fAngle));			// 회전
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);	// 이동

	// 크기x자전x이동x공전x부모
	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	// 사각형 점들을 회전행렬로 변환
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

	// 브러쉬 설정
	//hNewBrush = CreateSolidBrush(RGB(240, 128, 128));
	hNewBrush = CreateSolidBrush(RGB(0, 100, 100));
	hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

	// 펜 설정 + 해제
	hNewPen = CreatePen(PS_SOLID, 3, RGB(0, 100, 100));
	hOldPen = (HPEN)SelectObject(hDC, hNewPen);

	Draw_Rectangle(hDC);

	// 펜 해제
	SelectObject(hDC, hOldPen);
	DeleteObject(hNewPen);

	// 브러쉬 해제
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
		// 플레이어를 바라보는 방향을 구해야 한다. 플레이어 방향 - 접시의 방향
		m_tInfo.vDir = m_pOwner->Get_Info().vDir - m_tInfo.vDir;
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);	// 방향벡터가 구해짐
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;

		//D3DXVec3TransformCoord(&)
	}

	//if (GetAsyncKeyState('S'))
	//{
	//	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	//	m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	//}
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