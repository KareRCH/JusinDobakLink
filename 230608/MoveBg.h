#pragma once
#include "Obj.h"

class CBitMap; // ���漱��(������ Ÿ�Ը�!)

class CMoveBg :
	public CObj
{
public:
	CMoveBg();
	~CMoveBg();

public:
	virtual void Initialize(void)   override;
	virtual int	 Update(void)       override;
	virtual void Render(HDC _hDC)   override;
	virtual void Release(void)      override;
	virtual void Late_Update()		override;
	virtual void Collide(CObj* _pDst) override;

public:
	
	// �浹����
public:
	
private:
	CBitMap* m_pTex;


	// CObj��(��) ���� ��ӵ�
	

};