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
	void Key_Input();
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
};

