#pragma once
#include "Scene.h"

class CObj;	// 전방선언

class CYScene_Serving :
    public CScene
{
public:
	CYScene_Serving();
	virtual ~CYScene_Serving();

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;


private:
	bool	m_bIsEnd;

public:
	void	Set_IsEnd(bool _bEnd) { m_bIsEnd = _bEnd; }
	bool	Get_IsEnd() { return m_bIsEnd; }


private:
	DWORD		m_dwTime = GetTickCount();		//GetTickCount() 타이머용
	int			m_iCount;						// 딜레이 타이머용

	int			m_imaxCustomer;		// 동시에 존재할 수 있는 최대 손님 3명
	int			m_iCurCustomer;		// 현재 손님 수

private:
	int			m_imaxDish;		// 동시에 존재할 수 있는 최대 접시 3개
	int			m_iCurDish;		// 현재 접시 수

public:
	void		Set_CurCustomer(int _iCurCustomer) { m_iCurCustomer += _iCurCustomer; }
	int			Get_CurCustomer() { return m_iCurCustomer; }

	void		Set_CurDish(int _iCurDish) { m_iCurDish += _iCurDish; }
	int			Get_CurDish() { return m_iCurDish; }

private:
	CObj*		m_pCustomer[6];		// 손님 6명
	D3DXVECTOR3 m_vCustomerPos[6];	// 손님 생성 위치

	int			m_iRand;			// 난수 생성
	int			m_iCustomerRand;

public:
	CObj* Create_Customer(D3DXVECTOR3 _vCenterPos);


// 벽이 생성될 위치
private:
	CObj*			m_pWall[8];		// 벽 개수
	D3DXVECTOR3		m_vWallPos[8];

public:
	CObj* Create_Wall(D3DXVECTOR3 _vCenterPos, int _iType);

private:
	CObj*	m_pTimeGauge;



};