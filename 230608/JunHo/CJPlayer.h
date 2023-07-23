#pragma once
#include "Obj.h"
class CJPlayer : public CObj
{
public:
	CJPlayer();
	virtual ~CJPlayer();
public:
	// CObj을(를) 통해 상속됨
	virtual void		Initialize()	override;
	virtual int			Update()		override;
	virtual void		Late_Update()	override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release()					override;
	virtual void		Collide(CObj* _pDst)		override;

public:
	bool Get_fuckingswitch() { return fuckingswitch; }
	void Set_fucking(bool _fucking) { fuckingswitch = _fucking; }
	void Key_Input();
	void Jump();

private:
	D3DXVECTOR3 m_vP[4];
	D3DXVECTOR3 m_vQ[4];
	D3DXVECTOR3 vTest;
	D3DXMATRIX matScale, matRotZ, matTrans, matZero;
	POINT				m_tPosin;
	float				m_fDistance;
	float				fAngle;
	float				fDot;
	float				fDot2;
	float				m_fAngle;
	bool				fuckingswitch=false;

	bool				m_bJump;
	float				m_fPower;
	float				m_fTime;
	bool				m_bIsDrop = false;
};

