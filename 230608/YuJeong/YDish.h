#pragma once
#include "Obj.h"
class CYDish :
    public CObj
{
public:
	CYDish();
	virtual ~CYDish();

public:
	virtual void		Initialize()	override;
	virtual int			Update()		override;
	virtual void		Late_Update()	override;
	virtual void		Render(HDC hDC)	override;
	virtual void		Release()		override;
	virtual void		Collide()		override;

public:
	void			Draw_Rectangle(HDC hDC);	// 사각형 그리기

private:
	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];

private:
	CObj*			m_pOwner;

private:
	D3DXMATRIX		matScale;
	D3DXMATRIX		matRotZ;
	D3DXMATRIX		matTrans;

public:
	void			Set_Owner(CObj* _pOwner) { m_pOwner = _pOwner; }
	CObj*			Get_Owner() { return m_pOwner; }


private:
	void		Key_Input();
};