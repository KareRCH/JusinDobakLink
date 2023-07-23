#include "stdafx.h"
#include "CollisionMgr.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				Dst->Collide(Src);
				Src->Collide(Dst);
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float fX = 0.f, fY = 0.f;


	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dst->Get_Info().vPos.x < Src->Get_Info().vPos.y)
					{
						//Dst->Set_PosY(-fY);
					}
					// 하 충돌
					else
					{
						//Dst->Set_PosY(fY);
					}
				}
				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dst->Get_Info().vPos.x < Src->Get_Info().vPos.y)
					{
						//Dst->Set_PosX(-fX);
					}
					// 우 충돌
					else
					{
						//Dst->Set_PosX(fX);
					}
				}
			}
		}
	}
}

bool CCollisionMgr::Check_Rect(CObj * _Dst, CObj * _Src, float* _pX, float* _pY)
{
	float		fWidth = fabs(_Dst->Get_Info().vPos.x - _Src->Get_Info().vPos.x);
	float		fHeight = fabs(_Dst->Get_Info().vPos.y - _Src->Get_Info().vPos.y);

	float		fRadiusX = (_Dst->Get_Info().fCX + _Src->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (_Dst->Get_Info().fCY + _Src->Get_Info().fCY) * 0.5f;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		*_pX = fRadiusX - fWidth;
		*_pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->Collide(Src);
				Src->Collide(Dst);
			}
		}
	}

}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, CObj* _Src)
{
	for (auto& Dst : _Dst)
	{
		if (Check_Sphere(Dst, _Src))
		{
			Dst->Collide(_Src);
			_Src->Collide(Dst);
		}
	}

}

bool CCollisionMgr::Check_Sphere(CObj * _Dst, CObj * _Src)
{
	float	fWidth  = abs(_Dst->Get_Info().vPos.x - _Src->Get_Info().vPos.x);
	float	fHeight = _Dst->Get_Info().vPos.y - _Src->Get_Info().vPos.y;

	float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (_Dst->Get_Info().fCX + _Src->Get_Info().fCX) * 0.5f;
	
	return fDiagonal <= fRadius;
}
