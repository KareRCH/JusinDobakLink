#pragma once

#include "Food.h"
#include "ObjMgr.h"

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

public:
	static CFood_Cookie* Create(OBJID eObjID, D3DXVECTOR3 vPos, D3DXVECTOR3 vSpeed, float fDelay, bool bAddMgr = true)
	{
		CFood_Cookie* pObj = new CFood_Cookie();
		pObj->Get_Info().vPos = vPos;
		pObj->Get_Info().vSpeed = vSpeed;
		pObj->Set_Delay(fDelay);
		pObj->Initialize();

		if (bAddMgr)
			CObjMgr::Get_Instance()->Add_Object(eObjID, pObj);

		return pObj;
	}

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

	D3DXVECTOR3 m_vTargetPos = { 400.f, 500.f, 0.f };	// 목표 지점
	float		m_fMaxHeight = 300.f;					// 최대 높이
	float			m_fTime = 0.f;

	const float G = 9.8f * 2.f;
};

