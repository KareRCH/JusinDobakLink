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

public:
	void	Draw_Rectangle(HDC hDC);	// 사각형 그리기

private:
	void		Key_Input();

private:
	float			m_fAngle;

	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];

public:
	void			Set_Pos() {};
};