#pragma once
#include "Obj.h"

class CMB_Player : public CObj
{
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Collide(CObj* _pDst) override;

private:
	INFO	link;
};