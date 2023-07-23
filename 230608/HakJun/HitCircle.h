#pragma once

#include "Obj.h"

class CHitCircle : public CObj
{
public:
	CHitCircle() {}
	virtual ~CHitCircle() {}

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Collide(CObj* _pDst) override;

public:
	int m_iHitCate = 0;
};

