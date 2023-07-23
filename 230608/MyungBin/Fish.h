#pragma once
#include "DefindMyungBin.h"
#include "Obj.h"

class CFish : public CObj 
{


public:
	CFish();
	~CFish();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Collide(CObj* _pDst) override;

public:
	void	Set_Pos(D3DXVECTOR3 _Pos) { m_tInfo.vPos = _Pos; };
	void	Add_Pos(D3DXVECTOR3 _Pos) { m_tInfo.vPos += _Pos; }
	void	Set_vLook(D3DXVECTOR3 _Look) { m_tInfo.vLook = _Look; };

	float	Get_Angle() { return m_fAngle; };
	float	Get_AngleDegree() { return D3DXToDegree(m_fAngle); };
	void	Set_Angle(float _fAngle) { m_fAngle = _fAngle; };
	void	Set_AngleDegree(float _fDegree) { m_fAngle = D3DXToRadian(_fDegree); };
	void	Add_Angle(float _fAngle) { m_fAngle += D3DXToRadian(_fAngle); };

	void	Set_Dir(D3DXVECTOR3 _Dir) { m_tInfo.vDir = _Dir; };

	float	Get_Speed() { return m_fSpeed; };
	void	Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; };

	void	UpdateDir() { D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld); };
	void	UpdateMatrixDefault()
	{
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixRotationZ(&matRotZ, m_fAngle);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
		m_tInfo.matWorld = matScale * matRotZ * matTrans;
	};

	void	Move() {
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	};

	void	Move_Pop() 
	{
		int iAngleRange = 120;
		Add_Angle(float(rand() % iAngleRange) - float(iAngleRange / 2.f));
		UpdateDir();
		UpdateMatrixDefault();

		int iboost = 20;

		m_fSpeed *= iboost;
		Move();
		m_fSpeed /= iboost;

	}

	bool	Get_Flag() { return m_bFlag; };
	void	Set_Flag(bool _bool) { m_bFlag = _bool; };

	D3DXVECTOR3	Get_TargetPos() { return m_vTargetPos; };

	int Get_RendMode() { return m_iRendMode; };
	void Set_RenderMode(int iMode) { m_iRendMode = iMode; };

	void	Set_FishImg(FishImgState eState) 
	{



		fishImg.vSize.x = 0.2f;
		fishImg.vSize.y = 0.2f;

		switch (eState)
		{
		case FishImgState::LEFT:
			fishImg.tFrameTSet.sFrameKey = L"TegoFish1";
			fishImg.fAngle = 0;

			break;
		case FishImgState::RIGHT:
			fishImg.tFrameTSet.sFrameKey = L"TegoFish1_1";
			fishImg.fAngle = 0;

			break;
		case FishImgState::UP:
			//fishImg.vSize.x = 0.3f;
			//fishImg.vSize.y = 0.3f;
			fishImg.tFrameTSet.sFrameKey = L"TegoFish2";
			break;
		default:
			break;
		}
	
	};

private:
	D3DXMATRIX		matScale, matRotZ, matTrans;
	D3DXVECTOR3		m_vTargetPos;
	D3DXVECTOR3		m_vOriginTargetPos;

	float	m_fAngle;
	float	m_fSpeed;
	bool	m_bFlag;

	int		m_iRendMode;

	INFO	fishImg;
	

};