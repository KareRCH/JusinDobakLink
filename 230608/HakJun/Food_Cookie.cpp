#include "stdafx.h"
#include "Food_Cookie.h"

#include "KeyMgr.h"
#include "BmpMgr.h"
#include "AnimationTable.h"
#include <HakJun/HitCircle.h>
#include <HakJun/Bowl.h>
#include <Core/CollisionMgr.h>

void CFood_Cookie::Initialize()
{
	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 80.f;

	m_tInfo.vSize = { 3.f, 3.f, 1.f };

#pragma region 이미지 & 애니메이션
	CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/Hak/cookie.png", L"Cookie");
	CAnimationTable::Get_Instance()->Create_Animation(
		L"Cookie", L"1",
		0, 0, 1, 0.f,
		16, 7, 32, 15
	);
	CBmpMgr::Get_Instance()->Insert_PNG(L"../Image/Hak/boong.png", L"Boong");
	CAnimationTable::Get_Instance()->Create_Animation(
		L"Boong", L"1",
		0, 0, 1, 0.f,
		19, 12, 39, 25
	);
#pragma endregion

	// 애니메이션, 이미지 설정 초기화
	m_tInfo.tFrameTSet.Set_Keys(L"Boong", L"1");
	CAnimationTable::Get_Instance()->Load_AnimData(m_tInfo.tFrameTSet);

	m_tState.Set_State(ESTATE::MOVE);
	m_tState.Add_Func(ESTATE::IDLE, &CFood_Cookie::Idle);
	m_tState.Add_Func(ESTATE::MOVE, &CFood_Cookie::Move);
	m_tState.Add_Func(ESTATE::HIT, &CFood_Cookie::Hit);
	m_tState.Add_Func(ESTATE::BUCKET, &CFood_Cookie::Bucket);
}

int CFood_Cookie::Update()
{
	/*if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.vPos.x += 5.f;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.vPos.x -= 5.f;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.vPos.y -= 5.f;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.vPos.y += 5.f;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
	{
		m_tInfo.fAngle -= 5.f;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('E'))
	{
		m_tInfo.fAngle += 5.f;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
	{
		m_tInfo.vSize *= 1.1f;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
	{
		m_tInfo.vSize *= 0.9f;
	}*/

	m_tState.Get_StateFunc()(this);

	return 0;
}

void CFood_Cookie::Late_Update()
{
	m_tInfo.tFrameTSet->Update();
}

void CFood_Cookie::Render(HDC hDC)
{
	CBmpMgr::Get_Instance()->Draw_PNG(hDC, m_tInfo, false);

	/*D3DXMATRIX matTrans, matRot, matScale;
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matScale);

	m_points[0] = { - m_tInfo.fCX, -m_tInfo.fCY, 0.f };
	m_points[1] = { m_tInfo.fCX, -m_tInfo.fCY, 0.f };
	m_points[2] = { m_tInfo.fCX, m_tInfo.fCY, 0.f };
	m_points[3] = { -m_tInfo.fCX, m_tInfo.fCY, 0.f };

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, m_tInfo.vSize.z);
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(m_tInfo.fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	for (int i = 3; i >= 0; i--)
	{
		D3DXVec3TransformCoord(&m_points[i], &m_points[i], &(matScale * matRot * matTrans));
	}

	MoveToEx(hDC, m_points[0].x, m_points[0].y, NULL);
	for (int i = 3; i >= 0; i--)
	{
		LineTo(hDC, (int)m_points[i].x, (int)m_points[i].y);
	}
	
	CBmpMgr::Get_Instance()->Draw_Text_Circle_Vec3(hDC, m_tInfo.vPos, 3, false);*/
}

void CFood_Cookie::Release()
{
	
}

void CFood_Cookie::Collide(CObj* _pDst)
{
	CHitCircle* pCircle = dynamic_cast<CHitCircle*>(_pDst);
	if (pCircle)
	{
		m_tState.Set_State(ESTATE::HIT);
	}

	CBowl* pObj = dynamic_cast<CBowl*>(_pDst);
	if (pObj)
	{
		Set_Dead();
	}
}

void CFood_Cookie::Idle()
{
	if (m_tState.IsState_Entered())
	{

	}

	if (m_tState.Can_Update())
	{
		
	}

	if (m_tState.IsState_Exit())
	{

	}
}

void CFood_Cookie::Move()
{
	if (m_tState.IsState_Entered())
	{

	}

	if (m_tState.Can_Update())
	{
		m_tInfo.vPos += m_tInfo.vSpeed;
	}

	if (m_tState.IsState_Exit())
	{

	}
}

void CFood_Cookie::Hit()
{
	if (m_tState.IsState_Entered())
	{
		m_tInfo.vSpeed = { 0.f, 0.f, 0.f };
		m_tInfo.vAccel = { 0.f, -G, 0.f };
		/*m_tInfo.vDir = { m_vTargetPos.x - m_tInfo.vPos.x, 0.f, 0.f };
		m_tInfo.vDir.x = (m_tInfo.vDir.x < 0.f) ? (-1.f) : (1.f);*/

		float dtY = m_vTargetPos.y - m_tInfo.vPos.y;
		float fDistanceX = m_vTargetPos.x - m_tInfo.vPos.x;

		float fRequired = 1.f;

		m_tInfo.vSpeed.x = fDistanceX / fRequired;

		m_tInfo.vSpeed.y = (m_fMaxHeight - dtY) + (m_fMaxHeight) * ((m_fMaxHeight) / (m_fMaxHeight + fabs(dtY))) * fRequired;
	}

	if (m_tState.Can_Update())
	{
		m_fTime += g_fDeltaTime;
		m_tInfo.vSpeed.y += m_tInfo.vAccel.y;

		m_tInfo.vPos.x += m_tInfo.vSpeed.x * g_fDeltaTime;
		m_tInfo.vPos.y -= m_tInfo.vSpeed.y * g_fDeltaTime;

		m_tInfo.fAngle -= 10.f * ((m_tInfo.vSpeed.x >= 0) ? 1.f : -1.f);

		if (m_tInfo.vPos.x < m_vTargetPos.x)
			m_fTime = m_fTime;


		CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_Objects(UNIT), this);
	}

	if (m_tState.IsState_Exit())
	{

	}
}

void CFood_Cookie::Bucket()
{
	if (m_tState.IsState_Entered())
	{

	}

	if (m_tState.Can_Update())
	{

	}

	if (m_tState.IsState_Exit())
	{

	}
}
