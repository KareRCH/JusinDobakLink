#pragma once

#include "Define.h"
//#include "ScrollMgr.h"
#include "Camera.h" // ī�޶�

class CLine
{
public:
	CLine();
	CLine(LINE& tLine);	// ���� 0622 �߰�
	CLine(LINEPOINT& _tLpoint, LINEPOINT& _tRpoint);
	~CLine();

public:
	LINE		Get_Info() { return m_tInfo; }

public:

	void		Render(HDC hDC);

private:
	LINE		m_tInfo;

};