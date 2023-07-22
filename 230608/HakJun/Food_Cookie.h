#pragma once
#include "Food.h"
class CFood_Cookie : public CFood
{
public:
	CFood_Cookie() {}
	virtual ~CFood_Cookie() {}

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Collide(CObj* _pDst) override;
};

