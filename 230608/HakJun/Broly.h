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

private:
	enum class ESTATE { MOVE, IDLE, HIT };
	STATE_SET< ESTATE, void(CBroly*)> m_tState;

	void Move();
	void Idle();
	void Hit();
public:
	STATE_SET< ESTATE, void(CBroly*)>* Get_State() { return &m_tState; }
};

