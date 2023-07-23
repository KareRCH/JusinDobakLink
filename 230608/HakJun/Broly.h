#pragma once
#include "Obj.h"
class CBroly :
    public CObj
{
public:
	CBroly() {}
	virtual ~CBroly() {}

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Collide(CObj* _pDst) override;
};

