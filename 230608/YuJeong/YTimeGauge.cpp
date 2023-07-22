#include "stdafx.h"
#include "YTimeGauge.h"

CYTimeGauge::CYTimeGauge()
	: m_fAngle(0.f)
{
}

CYTimeGauge::~CYTimeGauge()
{
	Release();
}

void CYTimeGauge::Initialize()
{
}

int CYTimeGauge::Update()
{


	return OBJ_NOEVENT;
}

void CYTimeGauge::Late_Update()
{
}

void CYTimeGauge::Render(HDC hDC)
{
}

void CYTimeGauge::Release()
{
}

void CYTimeGauge::Collide(CObj* _pDst)
{
}

void CYTimeGauge::Draw_Rectangle(HDC hDC)
{
}
