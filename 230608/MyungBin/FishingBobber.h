#pragma once
#include "Obj.h"
class CFishingBobber : public CObj 
{
public:
	CFishingBobber();
	~CFishingBobber();

public:
	void	Set_Pos(D3DXVECTOR3 _Pos) { m_tInfo.vPos = _Pos; };
	void	Set_vLook(D3DXVECTOR3 _Look) { m_tInfo.vLook = _Look; };

	float	Get_Angle() { return m_fAngle; };
	float	Get_AngleDegree() { return D3DXToDegree(m_fAngle); };
	void	Set_Angle(float _fAngle) { m_fAngle = _fAngle; };
	void	Set_AngleDegree(float _fDegree) { m_fAngle = D3DXToRadian(_fDegree); };
	void	Add_Angle(float _fAngle) { m_fAngle += D3DXToRadian(_fAngle); };

	void	Set_Dir(D3DXVECTOR3 _Dir) { m_tInfo.vDir = _Dir; };
	void	Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; };
	
	void	UpdateDir() { D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld); };
	void	UpdateMatrixDefault()
	{
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixRotationZ(&matRotZ, m_fAngle);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
		m_tInfo.matWorld = matScale * matRotZ * matTrans;
	};

	void	Set_Scale(float _fScale) { D3DXMatrixScaling(&matScale, _fScale, _fScale, _fScale); };
	void	Scale_Up()
	{
		//D3DXMatrixScaling(&matScale, 1.1f, 1.1f, 1.1f);
		//++m_iScaleCount;

		m_tInfo.fCX *= 1.03f;
		m_tInfo.fCY *= 1.03f;

	};

	void	Scale_Down() 
	{
		//D3DXMatrixScaling(&matScale, (1.0f / 1.1f), (1.0f / 1.1f), (1.0f / 1.1f));
		//--m_iScaleCount;

		m_tInfo.fCX /= 1.01f;
		m_tInfo.fCY /= 1.01f;
	};


	void	Move() { 
		//D3DXVECTOR3 test = { 0.f , -1.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed; 
	};




public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Collide() override;

private:
	D3DXMATRIX		matScale, matRotZ, matTrans;
	float	m_fAngle;
	float	m_fSpeed;

	//int		m_iScaleCount;
};