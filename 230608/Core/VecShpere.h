#pragma once


#include "Vector3.h"

/*
* ��ġ ��ǥ�� ���������� ������ ��ü
* ������ �����ϰ� ���������� ������ �˾Ƴ��ϴ�.
*/

template<typename T = float>
class CVecSphere final
{
    static_assert(std::is_arithmetic<T>::value, "T�� ���� Ÿ���̾�߸� �մϴ�.");
public:
    CVector3<T> pos;
    T radius;

public:
    CVecSphere() : pos(CVector3<T>()), radius(T()) {}
    ~CVecSphere() {}
};

