#pragma once

#include "Vector3.h"

/*
* CVector3�� �̿��� �����Դϴ�.
* �������� ������ ���� ������ �˾Ƴ��ϴ�.
*/

template<typename T = float>
class CVecLine3 final
{
    static_assert(std::is_arithmetic<T>::value, "T�� ���� Ÿ���̾�߸� �մϴ�.");
public:
    CVector3<T> start, end;

public:
    CVecLine3() : start(CVector3<T>()), end(CVector3<T>()){}
    ~CVecLine3() {}

public:
    static CVecLine3<T> Zero() { return CVecLine3<T>(); }

    T Length()
    {
        return sqrt((end.x - start.x) * (end.x - start.x) +
                    (end.y - start.y) * (end.y - start.y) +
                    (end.z - start.z) * (end.z - start.z));
    }
};
