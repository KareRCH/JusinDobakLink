#include "stdafx.h"
#include "Line.h"
#include "Camera.h"

CLine::CLine()
{
}

CLine::CLine(LINE& tLine)	// 유정 0622 추가
	:m_tInfo(tLine)
{

}

CLine::CLine(LINEPOINT& _tLpoint, LINEPOINT& _tRpoint)
	: m_tInfo(_tLpoint, _tRpoint)
{
}


CLine::~CLine()
{
}



void CLine::Render(HDC hDC)
{
	 //기존 코드
	//MoveToEx(hDC, (int)m_tInfo.tLpoint.fX, (int)m_tInfo.tLpoint.fY, nullptr);
	//LineTo(hDC, (int)m_tInfo.tRpoint.fX, (int)m_tInfo.tRpoint.fY);

	// 유정 0622 추가
	//float	fScrollX = CCamera::Get_Instance()->Get_WindowPos().x;

	//MoveToEx(hDC, int(m_tInfo.tLpoint.fX + fScrollX), (int)m_tInfo.tLpoint.fY, nullptr);
	//LineTo(hDC, int(m_tInfo.tRpoint.fX + fScrollX), (int)m_tInfo.tRpoint.fY);

		// 카메라 관련 추가
	LINE tLRenderPos = CCamera::Get_Instance()->Get_Line_RenderPos(m_tInfo);
	MoveToEx(hDC, (int)tLRenderPos.tLpoint.fX, (int)tLRenderPos.tLpoint.fY, nullptr);
	LineTo(hDC, (int)tLRenderPos.tRpoint.fX, (int)tLRenderPos.tRpoint.fY);
}
