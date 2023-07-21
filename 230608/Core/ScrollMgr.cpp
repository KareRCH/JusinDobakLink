#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock()
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;


	if (WINCX - MAP_SIZE > m_fScrollX)
		m_fScrollX = WINCX - MAP_SIZE;

	if (WINCY - (MAP_SIZE + 100) > m_fScrollY)
		m_fScrollY = WINCY - (MAP_SIZE + 100);

}
