#pragma once
#include "Obj.h"

class CScene;	// ���漱��

class CYCustomer :
	public CObj
{
public:
	CYCustomer();
	virtual ~CYCustomer();

public:
	virtual void		Initialize()				override;
	virtual int			Update()					override;
	virtual void		Late_Update()				override;
	virtual void		Render(HDC hDC)				override;
	virtual void		Release()					override;
	virtual void		Collide(CObj* _pDst)		override;

public:
	void		Draw_Rectangle(HDC hDC);	// �簢�� �׸���

private:
	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];

	D3DXVECTOR3		m_vCenter;		// ����, �մ� ������ġ
	D3DXVECTOR3		m_vPointScale;	// ������ ����

public:
	void			Set_Center(D3DXVECTOR3 _vCenter) { m_vCenter = _vCenter; }
	D3DXVECTOR3		Get_Center() { return m_vCenter; }

	// ��ü Ȱ��ȭ ���� �Ǵ�
private:
	bool	m_bActive;

public:
	void	Set_Active(bool _Active) { m_bActive = _Active; }
	bool	Get_Active() { return m_bActive; }


	// ���� ����(�丮) ����
public:
	void	Create_Dish();

	// ������ ��ġ
private:
	D3DXVECTOR3 m_vCustomerPos[6];

	// ������ �浹�ߴ��� �Ǵ�
private:
	bool		m_bIsPlayerColl;
	bool		m_bIsDishColl;

	// ��...��
private:
	CScene* m_ServingScene;

public:
	void		Set_Scene(CScene* _ServingScene) { m_ServingScene = _ServingScene; }
	CScene*		Get_Scene() { return m_ServingScene; }

private:
	int			m_iRand;			// ���� ����
	int			m_iDishRand;
	TCHAR*		m_pKey[6];

public:
	void		Set_Rand(int _iRand) { m_iRand = _iRand; }
	int			Get_Rand() { return m_iRand; }

private:
	DWORD		m_dwTime = GetTickCount();		//GetTickCount() Ÿ�̸ӿ�
	int			m_iCount;						// ������ Ÿ�̸ӿ�
};