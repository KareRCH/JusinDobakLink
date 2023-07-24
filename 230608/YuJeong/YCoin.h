#pragma once
#include "Obj.h"
class CYCoin :
    public CObj
{
public:
	CYCoin();
	virtual ~CYCoin();

public:
	virtual void		Initialize()				override;
	virtual int			Update()					override;
	virtual void		Late_Update()				override;
	virtual void		Render(HDC hDC)				override;
	virtual void		Release()					override;
	virtual void		Collide(CObj* _pDst)		override;

public:
	void		Draw_Rectangle(HDC hDC);	// 사각형 그리기

private:
	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];

	D3DXVECTOR3		m_vCenter;		// 원점, 손님 생성위치
	D3DXVECTOR3		m_vPointScale;	// 점들의 간격

public:
	void			Set_Center(D3DXVECTOR3 _vCenter) { m_vCenter = _vCenter; }
	D3DXVECTOR3		Get_Center() { return m_vCenter; }

	// 객체 활성화 여부 판단
private:
	bool	m_bActive;

public:
	void	Set_Active(bool _Active) { m_bActive = _Active; }
	bool	Get_Active() { return m_bActive; }
};

