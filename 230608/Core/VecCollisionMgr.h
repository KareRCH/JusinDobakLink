#pragma once

#include "Define.h"

/*
* 벡터를 활용한 충돌처리에 대해 다루는 클래스입니다.
* 충돌범위를 비교할 물리 객체만을 받아 계산해줍니다.
*/

class CVecCollisionMgr
{
private:
	CVecCollisionMgr() = delete;
	CVecCollisionMgr(const CVecCollisionMgr& rhs) = delete;
	~CVecCollisionMgr() = delete;

public: // 전체 리스트를 통해 충돌 판정을 하는 함수
	// Src로 부터 판정을 원하는 대상에 대한 CObj 리스트에 대해 충돌 판정을 한다.
	//static list<CObj*> Collision_Box(list<CObj*>* Dst, CObj* Src);
	//static list<CObj*> Collision_Box_Quater(list<CObj*>* Dst, CObj* Src);
	//static list<CObj*> Collision_PointToRhombus_Quater(list<CObj*>* Dst, CObj* Src);
	//static list<CObj*> Collision_Box_Tile(vector<CObj*>* Dst, CObj* Src);	// 타일 전용
};

template <typename T>
class CVecCollisionMgr_Check
{
private:
	CVecCollisionMgr_Check() = delete;
	CVecCollisionMgr_Check(const CVecCollisionMgr_Check& rhs) = delete;
	~CVecCollisionMgr_Check() = delete;

public: // 비교 대상을 넣어 충돌검출을 하는 함수
	static bool Check_LineToBox(CVecBox<T> Dst, CVecLine3<T> Src);			// 선과 박스 충돌입니다.
	static bool Check_PointToRhombus(CVecBox<T> Dst, CVector3<T> Src);		// 점과 마름모 사이의 충돌입니다.
	static bool Check_Box(CVecBox<T> Dst, CVecBox<T> Src);					// AABB 방식입니다.
	static bool Check_OrientedBox(CVecBox<T> Dst, CVecBox<T> Src);			// OBB 방식입니다.
	static bool Check_Sphere(CVecSphere<T> DstPos, CVecSphere<T> SrcPos);	// 구 충돌입니다.
};

template<typename T>
inline bool CVecCollisionMgr_Check<T>::Check_LineToBox(CVecBox<T> Dst, CVecLine3<T> Src)
{

	return false;
}

template<typename T>
inline bool CVecCollisionMgr_Check<T>::Check_PointToRhombus(CVecBox<T> Dst, CVector3<T> Src)
{
	CVector2<T> left, right, down, up, origin;
	T width = abs(Dst.right - Dst.left);
	T height = abs(Dst.down - Dst.up);

	// 벡터 계산을 위한 변환 작업
	origin.x = Dst.left + width / 2;
	origin.y = Dst.down + height / 2;

	left.x = Dst.left;
	left.y = origin.y;

	right.x = Dst.right;
	right.y = origin.y;

	down.x = origin.x;
	down.y = Dst.down;

	up.x = origin.x;
	up.y = Dst.up;

	//// 1사분
	//if (Src.x >= origin.x && Src.x < right.x && Src.y >= origin.y && Src.y < up.y)
	//{
	//	// 내적한 벡터들의 값을 비교, 대각 벡터의 x <= 절편 벡터 x
	//	if ((abs(origin.x - Src.x) / origin.x + abs(origin.y - Src.y) / origin.y) < 1.f)
	//	{
	//		return true;
	//	}
	//}
	//// 2사분
	//else if (Src.x > left.x && Src.x <= origin.x && Src.y >= origin.y && Src.y < up.y)
	//{
	//	// 내적한 벡터들의 값을 비교, 대각 벡터의 x <= 절편 벡터 x
	//	if ((abs(origin.x - Src.x) / origin.x + abs(origin.y - Src.y) / origin.y) < 1.f)
	//	{
	//		return true;
	//	}
	//}
	//// 3사분
	//else if (Src.x > left.x && Src.x <= origin.x && Src.y > down.y && Src.y <= origin.y)
	//{
	//	// 내적한 벡터들의 값을 비교, 대각 벡터의 x <= 절편 벡터 x
	//	if ((abs(origin.x - Src.x) / origin.x + abs(origin.y - Src.y) / origin.y) < 1.f)
	//	{
	//		return true;
	//	}
	//}
	//// 4사분
	//else if (Src.x >= origin.x && Src.x < right.x && Src.y > down.y && Src.y <= origin.y)
	//{
	//	// 내적한 벡터들의 값을 비교, 대각 벡터의 x <= 절편 벡터 x
	//	if ((abs(origin.x - Src.x) / origin.x + abs(origin.y - Src.y) / origin.y) < 1.f)
	//	{
	//		return true;
	//	}
	//}

	if ((abs(origin.x - Src.x) / (width / 2) + abs(origin.y - Src.y) / (height / 2)) <= 1.f)
	{
		return true;
	}

	return false;
}

template<typename T>
inline bool CVecCollisionMgr_Check<T>::Check_Box(CVecBox<T> Dst, CVecBox<T> Src)
{
	bool bX(false), bY(false), bZ(false);
	// Scr대 Dst
	if (Dst.left <= Src.right && Dst.right >= Src.left)
	{
		bX = true;
	}
	if (Dst.down <= Src.up && Dst.up >= Src.down)
	{
		bY = true;
	}
	if (Dst.bottom <= Src.top && Dst.top >= Src.bottom)
	{
		bZ = true;
	}

	return (bX && bY && bZ);
}

template<typename T>
bool CVecCollisionMgr_Check<T>::Check_OrientedBox(CVecBox<T> Dst, CVecBox<T> Src)
{

	return false;
}

template<typename T>
inline bool CVecCollisionMgr_Check<T>::Check_Sphere(CVecSphere<T> DstPos, CVecSphere<T> SrcPos)
{

	return false;
}