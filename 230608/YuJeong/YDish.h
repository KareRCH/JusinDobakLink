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

public:
	void			Draw_Rectangle(HDC hDC);	// 사각형 그리기

private:
	float			m_fAngle;

	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];
};