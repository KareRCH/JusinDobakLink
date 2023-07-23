#pragma once
#include "Obj.h"

class CBitMap; // 전방선언(포인터 타입만!)

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
	
	// 충돌관련
public:
	
private:
	CBitMap* m_pTex;


	// CObj을(를) 통해 상속됨
	

};