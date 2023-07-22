#pragma once
#include "Define.h"
#include "Obj.h"
#include "Tile.h"

class CObj;

class CCamera
{
    //SINGLE(CCamera);
private:
    CCamera();
    ~CCamera();

private:
    //Vec2   m_vLookAt;         // 카메라가 보는 위치
    INFO   m_tLookAt;         // 카메라가 보는 위치
    CObj* m_pTargetObj;      // 카메라 타겟 오브젝트
    INFO   m_tDiff;         // 해상도 중심위치와, 카메라 LookAt간의 차이 값

    LINE    m_tLineDiff;
    POINT   m_PointDiff;

public:
    void      Set_LookAt(int _iX, int _iY) { m_tLookAt.vPos.x = (float)_iX, m_tLookAt.vPos.y = (float)_iY; }
    void      Set_Target(CObj* _pTarget) { m_pTargetObj = _pTarget; }

    INFO      Get_RenderPos(INFO _tObjPos);

    LINE      Get_Line_RenderPos(LINE _tLinePos);

    POINT      Get_Point_RenderPos(POINT _tPointPos);

    INFO      Get_LookAtPos()
	{ 
		INFO vTmp;
		vTmp.vPos= { m_tLookAt.vPos.x + (m_IsCameraShake ? -10.f : 0.f),
					        m_tLookAt.vPos.y + (m_IsCameraShake ? -10.f : 0.f), 0.f};
		return vTmp;
	}

    D3DXVECTOR3        Get_WindowPos()
    {
        D3DXVECTOR3 vTmp = { m_tLookAt.vPos.x - (WINCX / 2) + (m_IsCameraShake ? -10.f : 0.f),
					            m_tLookAt.vPos.y - (WINCY / 2) + (m_IsCameraShake ? -10.f : 0.f), 0.f};
        return vTmp;
    }


public:
    void	Update();
	void	CameraShake() 
	{ 
		m_IsCameraShakeSet = true;
		RandomTime = 100;
	}

private:
    void      CalDiff();
    void      Key_Input(void);

public:
    void      Initialize();
    void      Render(HDC hDC);
    void      Release();

public:
    static CCamera* Get_Instance()
    {
        if (!m_pInstance)
        {
            m_pInstance = new CCamera;
        }

        return m_pInstance;
    }
    static void      Destroy_Instance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    static CCamera* m_pInstance;

    SCENEID					m_eCurScene;
    SCENEID					m_ePreScene;
	bool					m_IsCameraShake = false;
	bool					m_IsCameraShakeSet = false;
	int			RandomTime = 100;
};