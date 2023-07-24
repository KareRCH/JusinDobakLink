#pragma once
#include "Obj.h"

class CYPlayer :
	public CObj
{
public:
	CYPlayer();
	virtual ~CYPlayer();

public:
	virtual void		Initialize()				override;
	virtual int			Update()					override;
	virtual void		Late_Update()				override;
	virtual void		Render(HDC hDC)				override;
	virtual void		Release()					override;
	virtual void		Collide(CObj* _pDst)		override;

	void				CollisionTile(CObj* pTarget);

public:
	void	Draw_Rectangle(HDC hDC);	// 사각형 그리기

private:
	void		Key_Input();

private:
	D3DXMATRIX		matScale;
	D3DXMATRIX		matRotZ;
	D3DXMATRIX		matTrans;

	D3DXVECTOR3		m_vCenter;		// 원점, 플레이어 생성위치?
	D3DXVECTOR3		m_vPointScale;	// 점들의 간격


	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];


public:
	D3DXVECTOR3		Get_vPoint(int _iIndex) { return m_vPoint[_iIndex]; }


public:
	OBJID   Get_Id() { return m_eID; };

private:
	bool		m_bIsDishColl;
	bool		m_bIsWallColl;

	float		m_fPreAngle;

private:
	int			m_iMoney;
	int			m_iPreMoney;
	int			m_iDishCount;

public:
	void	Set_Money(int _iMoney) { m_iMoney += _iMoney; }
	int		Get_Money() { return m_iMoney; }

	void	Set_DishCount(int _iDishCount) { m_iDishCount += _iDishCount; }
	int		Get_DishCount() { return m_iDishCount; }
};