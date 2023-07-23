#pragma once

#include "Define.h"
//#include "ScrollMgr.h"
#include "Camera.h" // 카메라

class CLine
{
public:
	CLine();
	CLine(LINE& tLine);	// 유정 0622 추가
	CLine(LINEPOINT& _tLpoint, LINEPOINT& _tRpoint);
	~CLine();

public:
	LINE		Get_Info() { return m_tInfo; }
	void 		Line_Option(int _Lineoption) { m_Lineoption = _Lineoption; }
	int 		GetLine_Option() { return m_Lineoption; }

public:

	void		Render(HDC hDC);

private:
	LINE		m_tInfo;
	int			m_Lineoption;
};