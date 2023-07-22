#include "stdafx.h"
#include "YPlayer.h"

CYPlayer::CYPlayer()
	: m_fAngle(0.f)
{
}

CYPlayer::~CYPlayer()
{
	Release();
}

void CYPlayer::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;

	m_tInfo.vPos = { (WINCX / 2 + 60), (WINCY / 2 - 70), 0.f };
	//m_tInfo.vPos = { 0.f, 0.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_fSpeed = 2.f;

	m_vPoint[0] = { m_tInfo.vPos.x - 10.f ,m_tInfo.vPos.y - 30.f, 0.f };	// 좌 상단
	m_vPoint[1] = { m_tInfo.vPos.x + 10.f ,m_tInfo.vPos.y - 30.f, 0.f };	// 우 상단	
	m_vPoint[2] = { m_tInfo.vPos.x + 10.f ,m_tInfo.vPos.y + 30.f, 0.f };	// 우 하단
	m_vPoint[3] = { m_tInfo.vPos.x - 10.f ,m_tInfo.vPos.y + 30.f, 0.f };	// 좌 하단

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];


	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

int CYPlayer::Update()
{
	Key_Input();

	// D3DXVec3Normalize(결과 값을 저장할 벡터 주소, 단위 벡터로 만들 벡터 주소) : 단위 벡터를 만들어주는 함수
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
	D3DXMatrixIdentity(&m_tInfo.matWorld);	// 항등행렬로 만들기

	// 회전행렬을 만들고, 이를 벡터에 곱해서 회전된 벡터를 얻어야 한다.
	D3DXMATRIX matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);			// 크기
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));	// 회전
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);	// 이동

	// 크기x자전x이동
	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	// 사각형 점들을 회전행렬로 변환
	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= {(WINCX / 2 + 60), (WINCY / 2 - 70), 0.f};

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	return 0;
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
	hNewBrush = CreateSolidBrush(RGB(0, 100, 100));
	hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

	// 펜 설정 + 해제
	hNewPen = CreatePen(PS_SOLID, 3, RGB(0, 100, 100));
	hOldPen = (HPEN)SelectObject(hDC, hNewPen);

	Ellipse(hDC,
		m_vPoint[0].x - 5.f,
		m_vPoint[0].y - 5.f,
		m_vPoint[0].x + 5.f,
		m_vPoint[0].y + 5.f);

	Ellipse(hDC,
		m_vPoint[1].x - 5.f,
		m_vPoint[1].y - 5.f,
		m_vPoint[1].x + 5.f,
		m_vPoint[1].y + 5.f);


	Draw_Rectangle(hDC);

	// 펜 해제
	SelectObject(hDC, hOldPen);
	DeleteObject(hNewPen);

	// 브러쉬 해제
	SelectObject(hDC, hOldBrush);
	DeleteObject(hNewBrush);
}

void CYPlayer::Release()
{
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
	if (GetAsyncKeyState('A'))
	{
		//m_fAngle += D3DX_PI / 180.0f;
		m_fAngle -= 2.f;
	}


	if (GetAsyncKeyState('D'))
	{
		//m_fAngle -= D3DX_PI / 180.0f;
		m_fAngle += 2.f;
	}


	if (GetAsyncKeyState('W'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

		//D3DXVec3TransformCoord(&)
	}

	//if (GetAsyncKeyState('S'))
	//{
	//	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	//	m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	//}
}
