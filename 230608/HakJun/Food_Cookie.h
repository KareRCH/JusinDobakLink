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

private:
	D3DXVECTOR3 m_points[4] = {};

private:
	enum class ESTATE { IDLE, MOVE, HIT, BUCKET };
	STATE_SET< ESTATE, void(CFood_Cookie*)> m_tState;

	void Idle();
	void Move();
	void Hit();
	void Bucket();
public:
	STATE_SET< ESTATE, void(CFood_Cookie*)>* Get_State() { return &m_tState; }

	D3DXVECTOR3 m_vTargetPos = { 400.f, 300.f, 0.f };	// 목표 지점
	float		m_fMaxHeight = 300.f;					// 최대 높이
	int			m_iTime;

	const float G = 9.8f;
};

