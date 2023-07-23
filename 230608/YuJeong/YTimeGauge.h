#pragma once
#include "Obj.h"
class CYTimeGauge :
    public CObj
{
public:
	CYTimeGauge();
	virtual ~CYTimeGauge();

public:
	virtual void		Initialize()	override;
	virtual int			Update()		override;
	virtual void		Late_Update()	override;
	virtual void		Render(HDC hDC)	override;
	virtual void		Release()		override;
	virtual void		Collide(CObj* _pDst)		override;

public:
	void		Draw_Rectangle(HDC hDC);	// �簢�� �׸���

private:
	D3DXMATRIX		matScale;
	D3DXMATRIX		matRotZ;
	D3DXMATRIX		matTrans;

	D3DXVECTOR3		m_vCenter;		// ����, Ÿ�� ������ ������ġ?
	D3DXVECTOR3		m_vPointScale;	// ������ ����

	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];

private:
	DWORD		m_dwTime = GetTickCount();		//GetTickCount() Ÿ�̸ӿ�
	int			m_iCount;						// ������ Ÿ�̸ӿ�

	float			m_fmaxTime;
	float			m_fCurTime;
};

