#pragma once

#include "Define.h"

/*
* ���͸� Ȱ���� �浹ó���� ���� �ٷ�� Ŭ�����Դϴ�.
* �浹������ ���� ���� ��ü���� �޾� ������ݴϴ�.
*/

class CVecCollisionMgr
{
private:
	CVecCollisionMgr() = delete;
	CVecCollisionMgr(const CVecCollisionMgr& rhs) = delete;
	~CVecCollisionMgr() = delete;

public: // ��ü ����Ʈ�� ���� �浹 ������ �ϴ� �Լ�
	// Src�� ���� ������ ���ϴ� ��� ���� CObj ����Ʈ�� ���� �浹 ������ �Ѵ�.
	//static list<CObj*> Collision_Box(list<CObj*>* Dst, CObj* Src);
	//static list<CObj*> Collision_Box_Quater(list<CObj*>* Dst, CObj* Src);
	//static list<CObj*> Collision_PointToRhombus_Quater(list<CObj*>* Dst, CObj* Src);
	//static list<CObj*> Collision_Box_Tile(vector<CObj*>* Dst, CObj* Src);	// Ÿ�� ����
};

template <typename T>
class CVecCollisionMgr_Check
{
private:
	CVecCollisionMgr_Check() = delete;
	CVecCollisionMgr_Check(const CVecCollisionMgr_Check& rhs) = delete;
	~CVecCollisionMgr_Check() = delete;

public: // �� ����� �־� �浹������ �ϴ� �Լ�
	static bool Check_LineToBox(CVecBox<T> Dst, CVecLine3<T> Src);			// ���� �ڽ� �浹�Դϴ�.
	static bool Check_PointToRhombus(CVecBox<T> Dst, CVector3<T> Src);		// ���� ������ ������ �浹�Դϴ�.
	static bool Check_Box(CVecBox<T> Dst, CVecBox<T> Src);					// AABB ����Դϴ�.
	static bool Check_OrientedBox(CVecBox<T> Dst, CVecBox<T> Src);			// OBB ����Դϴ�.
	static bool Check_Sphere(CVecSphere<T> DstPos, CVecSphere<T> SrcPos);	// �� �浹�Դϴ�.
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

	// ���� ����� ���� ��ȯ �۾�
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

	//// 1���
	//if (Src.x >= origin.x && Src.x < right.x && Src.y >= origin.y && Src.y < up.y)
	//{
	//	// ������ ���͵��� ���� ��, �밢 ������ x <= ���� ���� x
	//	if ((abs(origin.x - Src.x) / origin.x + abs(origin.y - Src.y) / origin.y) < 1.f)
	//	{
	//		return true;
	//	}
	//}
	//// 2���
	//else if (Src.x > left.x && Src.x <= origin.x && Src.y >= origin.y && Src.y < up.y)
	//{
	//	// ������ ���͵��� ���� ��, �밢 ������ x <= ���� ���� x
	//	if ((abs(origin.x - Src.x) / origin.x + abs(origin.y - Src.y) / origin.y) < 1.f)
	//	{
	//		return true;
	//	}
	//}
	//// 3���
	//else if (Src.x > left.x && Src.x <= origin.x && Src.y > down.y && Src.y <= origin.y)
	//{
	//	// ������ ���͵��� ���� ��, �밢 ������ x <= ���� ���� x
	//	if ((abs(origin.x - Src.x) / origin.x + abs(origin.y - Src.y) / origin.y) < 1.f)
	//	{
	//		return true;
	//	}
	//}
	//// 4���
	//else if (Src.x >= origin.x && Src.x < right.x && Src.y > down.y && Src.y <= origin.y)
	//{
	//	// ������ ���͵��� ���� ��, �밢 ������ x <= ���� ���� x
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
	// Scr�� Dst
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