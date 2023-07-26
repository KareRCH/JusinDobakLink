#include "stdafx.h"
#include "CJPlayer.h"
#include "Camera.h"
#include "BmpMgr.h"
#include "LineMgr.h"
#include "SceneMgr.h"
CJPlayer::CJPlayer()
{
}

CJPlayer::~CJPlayer()
{
	Release();
}

void CJPlayer::Initialize()
{
	//m_tInfo.vPos = { 100.f,100.f,0.f };
	D3DXVECTOR3 NOCHANGE = { 50.f ,50.f, 0.f };
	m_fSpeed = 1.f;
	m_tInfo.vPos = { 400.f, 300.f, 0.f }; //위치
	m_tInfo.vLook = { 1.f, 0.f, 0.f }; //방향
	m_tInfo.vSize = {1.f ,1.f, 0.f };
	m_fDistance = 100.f;
	m_fSpeed = 3.f;
	m_fAngle = 0.f;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_tInfo.fAngle = 0.f;
	m_bJump = false;
	m_fPower = 0.f;
	m_fTime = 0.f;
	
	m_eRender = RENDER_GAMEOBJECT;
	m_eID = PLAYER;
	// 좌상단 
	m_vQ[0] = { m_tInfo.vPos.x - NOCHANGE.x , m_tInfo.vPos.y - NOCHANGE.y, 0.f };

	// 우 상단
	m_vQ[1] = { m_tInfo.vPos.x + NOCHANGE.x, m_tInfo.vPos.y - NOCHANGE.y, 0.f };

	// 우하단 
	m_vQ[2] = { m_tInfo.vPos.x + NOCHANGE.x, m_tInfo.vPos.y + NOCHANGE.y, 0.f };

	// 좌하단
	m_vQ[3] = { m_tInfo.vPos.x - NOCHANGE.x, m_tInfo.vPos.y + NOCHANGE.y, 0.f };


	for (int i = 0; i < 4; ++i)
	{
		m_vP[i] = m_vQ[i];
	}
	//(sText + L"LINKSKI2.png").c_str()
	wstring sText = L"../Image/Player/";
	CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/Player/LINKSKI.png", L"Link_Ski");
}

int CJPlayer::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down('D'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_BOSS);
		return OBJ_NOEVENT;
	}
	Key_Input();
	Jump();

	vTest = { (m_vQ[1].x - m_vQ[0].x) * 0.5f, (m_vQ[1].y - m_vQ[0].y) * 0.5f, 0.f };
	vTest += m_tInfo.vPos;

	m_tInfo.vDir = ::Get_Mouse() - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
	fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	fAngle = acosf(fDot);
	if (m_tInfo.vPos.y < Get_Mouse().y)
		fAngle = 2 * D3DX_PI - fAngle;

	if (m_tInfo.vPos.y < m_tInfo.vLook.y)
		m_tInfo.fAngle = 2 * D3DX_PI - m_tInfo.fAngle;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_tInfo.fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vQ[i] = m_vP[i];
		m_vQ[i] -= D3DXVECTOR3{ 400.f, 300.f, 0.f };

		D3DXVec3TransformCoord(&m_vQ[i], &m_vQ[i], &m_tInfo.matWorld);
	}

    return OBJ_NOEVENT;
}

void CJPlayer::Late_Update()
{
	m_tPosin.x = LONG(m_tInfo.vPos.x + m_fDistance * cos(fAngle));
	m_tPosin.y = LONG(m_tInfo.vPos.y - m_fDistance * sin(fAngle));
}

void CJPlayer::Render(HDC hDC)
{
	FRAME tFrame = {};
	tFrame.iOffsetX = 25; tFrame.iOffsetY = 25;
	CBmpMgr::Get_Instance()->Draw_PNG(hDC, L"Link_Ski", m_tInfo, tFrame, 0, 0, 50,50);
	//CBmpMgr::Get_Instance()->Draw_Text_Circle_Vec3(hDC, m_tInfo.vPos, 3);

	//MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);
	//LineTo(hDC, m_tPosin.x, m_tPosin.y);

	//MoveToEx(hDC, m_vQ[0].x, m_vQ[0].y, nullptr);

	//for (int i = 1; i < 4;++i)
	//	LineTo(hDC, m_vQ[i].x, m_vQ[i].y);

	//LineTo(hDC, m_vQ[0].x, m_vQ[0].y);
	//Rectangle(hDC, vTest.x - 3.f, vTest.y - 3.f, vTest.x + 3.f, vTest.y + 3.f);
}

void CJPlayer::Release()
{

}
void CJPlayer::Collide(CObj* _pDst)
{
	
}
void CJPlayer::Key_Input(void)
{

	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fAngle -=10.f;

	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fAngle +=10.f;

	//if (GetAsyncKeyState(VK_UP))
	//{
		D3DXVECTOR3 vLook = m_tInfo.vPos - vTest;
		D3DXVec3Normalize(&vLook, &vLook);
		m_tInfo.vPos -= m_fSpeed * vLook;
		fuckingswitch = true;
	//}

	if (GetAsyncKeyState(VK_UP))
		m_fSpeed += 0.05f;
	if (GetAsyncKeyState(VK_SPACE))
		m_bJump = true;

	if (GetAsyncKeyState(VK_DOWN))
	{
		D3DXVECTOR3 vLook = m_tInfo.vPos - vTest;
		D3DXVec3Normalize(&vLook, &vLook);
		m_tInfo.vPos += m_fSpeed * vLook;
		fuckingswitch = true;
	}
	//if (GetAsyncKeyState('D'))
	//{
	//	m_bDead = true;
	//}
}

void CJPlayer::Jump()
{
	float	fY = 0.f;
	float	fGradient = 0.f;
	CLine* pLine = nullptr;

	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo, &pLine , &fY, &fGradient);

	if (m_bJump)
	{
		m_fPower = 3.f;
		m_tInfo.vPos.y -= (m_fPower * m_fTime) - 9.8 * m_fTime * m_fTime * 0.5f;
		m_fTime += 0.1f;
		if (bLineCol && (fY - 15 < m_tInfo.vPos.y))
		{
			m_bJump = false;
			m_fTime = 0.f;
			
			m_tInfo.vPos.y = fY-15;
			if (fGradient != 0.f)
			{
				m_tInfo.fAngle = (fGradient)*180/D3DX_PI;
				//fAngle 값 조정
			}
		}
	}
	else if (bLineCol)
	{
		m_tInfo.vPos.y = fY-15;
		m_fTime = 0.f;
		if (fGradient != 0.f)
		{
			m_tInfo.fAngle = (fGradient) * 180 / D3DX_PI;
			//fAngle 값 조정
		}
	}
	else
	{
		m_tInfo.vPos.y += 9.8f * m_fTime * m_fTime * 0.5f;
		m_fTime += 0.2f;
	}

	if (pLine)
	{
		if (pLine->GetLine_Option() == 0 || m_tInfo.fAngle >= 0)
		{
			m_fSpeed += 0.1f;
			if (m_bIsDrop == false)
			{
				m_bIsDrop = true;
				m_bJump = true;
 			}
		}
		else
		{
			m_fSpeed -= 0.13f;
			if (m_bIsDrop)
 				m_bIsDrop = false;
		}
	}
}
