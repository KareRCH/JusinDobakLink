#pragma once
#include "Actor.h"
#include "FishingBobber.h"
#include "Fish.h"

enum class FishermanState 
{
	SELECT_DIR,
	SELECT_POWER,
	THROWING,
	//HOOKING,
	CATCHING,
	//FINISHING,
	FishermanState_End,
};

class CFisherman : public Actor<CFisherman, FishermanState>
{
public:
	CFisherman();
	~CFisherman();

public:
	void Set_State(FishermanState _state)
	{
		if (m_eState != _state)
		{
			m_States[(int)m_eState]->Release(*this);

			m_eState = _state;
			m_States[(int)m_eState]->Initialize(*this);
		}
	};

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void	Set_Pos(D3DXVECTOR3 _Pos) { m_tInfo.vPos = _Pos; };
	void	Set_TargetOriginPos(D3DXVECTOR3 _Pos) { m_vOriginTargetPos = _Pos; };
	void	Update_TargetPos() { D3DXVec3TransformCoord(&m_vTargetPos, &m_vOriginTargetPos, &m_tInfo.matWorld); };
	void	Set_vLook(D3DXVECTOR3 _Look) { m_tInfo.vLook = _Look; };

	D3DXVECTOR3		Get_TargetPos() { return m_vTargetPos; };


	float	Get_Angle() { return m_fAngle; };
	float	Get_AngleDegree() { return D3DXToDegree(m_fAngle); };
	void	Set_Angle(float _fAngle) { m_fAngle = _fAngle; };
	void	Set_AngleDegree(float _fDegree) { m_fAngle = D3DXToRadian(_fDegree); };
	void	Add_Angle(float _fAngle) { m_fAngle += D3DXToRadian(_fAngle); };

	void	Set_Speed(float fSpeed) { m_fSpeed = fSpeed; };

	bool	Get_Flag() { return m_bFlag; };
	void	Set_Flag(bool _bFlag) { m_bFlag = _bFlag; };


	void	UpdateDir() { D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld); };

	void	UpdateMatrixDefault()
	{
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixRotationZ(&matRotZ, m_fAngle);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
		m_tInfo.matWorld = matScale * matRotZ * matTrans;
	};

	int		Get_Gauge() { return m_iGauge; };
	void	Set_Gauge(int _gauge) { m_iGauge = _gauge; };
	void	Add_Gauge(int _value) { m_iGauge += _value; };

	float	Calc_Distance() 
	{
		return sqrt
		(
			(m_tInfo.vPos.x - m_vTargetPos.x) * (m_tInfo.vPos.x - m_vTargetPos.x) + 
			(m_tInfo.vPos.y - m_vTargetPos.y) * (m_tInfo.vPos.y - m_vTargetPos.y)
		);
	};


	void Reset_Bobber_Pos() 
	{
		m_pFishingBobber->Set_Pos(m_tInfo.vPos);
	}


	void	Render_SelectDir(HDC hDC)
	{
		MoveToEx(hDC, Get_Info().vPos.x, Get_Info().vPos.y, nullptr);
		LineTo(hDC, Get_TargetPos().x, Get_TargetPos().y);
	};

	void	Render_SelectPower(HDC hDC) 
	{
		Render_SelectDir(hDC);

		Rectangle(hDC, WINCX - 225, 125, WINCX - 125, WINCY - 125);

		MoveToEx(hDC, WINCX - 225, WINCY - Get_Gauge(), nullptr);
		LineTo(hDC, WINCX - 125, WINCY - Get_Gauge());
	};

	CFishingBobber*	Get_Bobber() { return m_pFishingBobber; };


	void	Set_Bobber_Dir(bool _bool) 
	{
		D3DXVECTOR3 vDir = _bool ? m_tInfo.vDir : -m_tInfo.vDir;
		m_pFishingBobber->Set_Dir(vDir);
	}


	CFish* Get_Fish() { return m_pFish; };



private:
	//D3DXVECTOR3		m_vPoint[4];
	//D3DXVECTOR3		m_vOriginPoint[4];

	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXVECTOR3		m_vTargetPos;
	D3DXVECTOR3		m_vOriginTargetPos;

	float			m_fAngle;
	float			m_fSpeed;

	bool			m_bFlag;

	int				m_iGauge;

	CFishingBobber*	m_pFishingBobber;
	CFish*			m_pFish;

};