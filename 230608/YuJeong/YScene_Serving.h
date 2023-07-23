#pragma once
#include "Scene.h"

class CObj;	// ���漱��

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
	DWORD		m_dwTime = GetTickCount();		//GetTickCount() Ÿ�̸ӿ�
	int			m_iCount;						// ������ Ÿ�̸ӿ�

	int			m_imaxCustomer;		// ���ÿ� ������ �� �ִ� �ִ� �մ� 3��
	int			m_iCurCustomer;		// ���� �մ� ��

private:
	int			m_imaxDish;		// ���ÿ� ������ �� �ִ� �ִ� ���� 3��
	int			m_iCurDish;		// ���� ���� ��

public:
	void		Set_CurCustomer(int _iCurCustomer) { m_iCurCustomer += _iCurCustomer; }
	int			Get_CurCustomer() { return m_iCurCustomer; }

	void		Set_CurDish(int _iCurDish) { m_iCurDish += _iCurDish; }
	int			Get_CurDish() { return m_iCurDish; }

private:
	CObj*		m_Customer[6];		// �մ� 6��
	D3DXVECTOR3 m_vCustomerPos[6];	// �մ� ���� ��ġ

	int			m_iRand;			// ���� ����

public:
	CObj* Create_Customer(D3DXVECTOR3 _vCenterPos);

};