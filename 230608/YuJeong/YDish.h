#pragma once
#include "Obj.h"

class CScene;	// ���漱��

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
	void			Draw_Rectangle(HDC hDC);	// �簢�� �׸���

private:
	D3DXVECTOR3		m_vCenter;		// ����, �÷��̾� ������ġ?
	D3DXVECTOR3		m_vPointScale;	// ������ ����
	D3DXVECTOR3		m_vOffset;	// �÷��̾�κ��� �󸶳� ������ ������

	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];

public:
	void			Set_Center(D3DXVECTOR3 _vCenter) { m_vCenter = _vCenter; }
	D3DXVECTOR3		Get_Center() { return m_vCenter; }

private:
	D3DXMATRIX		matScale;
	D3DXMATRIX		matRotZ;
	D3DXMATRIX		matTrans;


	// ��ü Ȱ��ȭ ���� �Ǵ�
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

	// ������ �浹�ߴ��� �Ǵ�
private:
	bool		m_bIsPlayerColl;
	bool		m_bIsCustomerColl;


	// ��...��
private:
	CScene* m_ServingScene;

public:
	void		Set_Scene(CScene* _ServingScene) { m_ServingScene = _ServingScene; }
	CScene* Get_Scene() { return m_ServingScene; }

private:
	int			m_iRand;			// ���� ����
	TCHAR* m_pKey[5];

public:
	void		Set_Rand(int _iRand) { m_iRand = _iRand; }
	int			Get_Rand() { return m_iRand; }

private:
	DWORD		m_dwTime = GetTickCount();		//GetTickCount() Ÿ�̸ӿ�
	int			m_iCount;						// ������ Ÿ�̸ӿ�

};