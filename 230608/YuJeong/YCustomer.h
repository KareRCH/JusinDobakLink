#pragma once
#include "Obj.h"
class CYCustomer :
    public CObj
{
public:
	CYCustomer();
	virtual ~CYCustomer();

public:
	virtual void		Initialize()	override;
	virtual int			Update()		override;
	virtual void		Late_Update()	override;
	virtual void		Render(HDC hDC)	override;
	virtual void		Release()		override;
	virtual void		Collide()		override;

public:
	void		Draw_Rectangle(HDC hDC);	// �簢�� �׸���

private:
	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];
};