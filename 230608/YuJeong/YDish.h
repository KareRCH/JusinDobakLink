#pragma once
#include "Obj.h"

class CScene;	// 전방선언

class CYDish :
	public CObj
{
public:
	CYDish();
	virtual ~CYDish();

public:
	virtual void		Initialize()				override;
	virtual int			Update()					override;
	virtual void		Late_Update()				override;
	virtual void		Render(HDC hDC)				override;
	virtual void		Release()					override;
	virtual void		Collide(CObj* _pDst)		override;

public:
	void			Draw_Rectangle(HDC hDC);	// 사각형 그리기

private:
	D3DXVECTOR3		m_vCenter;		// 원점, 플레이어 생성위치?
	D3DXVECTOR3		m_vPointScale;	// 점들의 간격
	D3DXVECTOR3		m_vOffset;	// 플레이어로부터 얼마나 떨어져 있을지

	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];

public:
	void			Set_Center(D3DXVECTOR3 _vCenter) { m_vCenter = _vCenter; }
	D3DXVECTOR3		Get_Center() { return m_vCenter; }

private:
	D3DXMATRIX		matScale;
	D3DXMATRIX		matRotZ;
	D3DXMATRIX		matTrans;


	// 객체 활성화 여부 판단
private:
	bool	m_bActive;

public:
	void	Set_Active(bool _Active) { m_bActive = _Active; }
	bool	Get_Active() { return m_bActive; }


private:
	CObj* m_pPlayer3;
	CObj* m_pCustomer;


public:
	void			Set_Player3(CObj* _pPlayer) { m_pPlayer3 = _pPlayer; }
	CObj*			Get_Player3() { return m_pPlayer3; }

	void			Set_Customer(CObj* _pCustomer) { m_pCustomer = _pCustomer; }
	CObj*			Get_Customer() { return m_pCustomer; }


public:
	OBJID   Get_Id() { return m_eID; };

	// 무엇과 충돌했는지 판단
private:
	bool		m_bIsPlayerColl;
	bool		m_bIsCustomerColl;


	// 씬...ㅠ
private:
	CScene* m_ServingScene;

public:
	void		Set_Scene(CScene* _ServingScene) { m_ServingScene = _ServingScene; }
	CScene* Get_Scene() { return m_ServingScene; }

private:
	int			m_iRand;			// 난수 생성
	TCHAR* m_pKey[5];

public:
	void		Set_Rand(int _iRand) { m_iRand = _iRand; }
	int			Get_Rand() { return m_iRand; }

private:
	DWORD		m_dwTime = GetTickCount();		//GetTickCount() 타이머용
	int			m_iCount;						// 딜레이 타이머용

};