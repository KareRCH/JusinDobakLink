#pragma once
#include "Obj.h"

class CYPlayer :
    public CObj
{
public:
    CYPlayer();
	virtual ~CYPlayer();

public:
	virtual void		Initialize()	override;
	virtual int			Update()		override;
	virtual void		Late_Update()	override;
	virtual void		Render(HDC hDC)	override;
	virtual void		Release()		override;
	virtual void		Collide(CObj* _pDst)		override;

public:
	void	Draw_Rectangle(HDC hDC);	// 사각형 그리기

private:
	void		Key_Input();

private:
	D3DXMATRIX		matScale;
	D3DXMATRIX		matRotZ;
	D3DXMATRIX		matTrans;

	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];

	D3DXVECTOR3 vTest;

	float				fDot;
	float				fDot2;

public:
	D3DXVECTOR3		Get_vPoint(int _iIndex) { return m_vPoint[_iIndex]; }
};