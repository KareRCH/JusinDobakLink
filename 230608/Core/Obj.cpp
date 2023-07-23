#include "stdafx.h"
#include "Obj.h"

CObj::CObj() : m_fSpeed(0.f), m_eRender() , m_eID()
{
	/*ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);*/
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left = LONG(m_tInfo.vPos.x - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.vPos.y - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.vPos.x + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.vPos.y + (m_tInfo.fCY * 0.5f));
}