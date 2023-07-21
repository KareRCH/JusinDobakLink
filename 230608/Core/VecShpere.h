#pragma once


#include "Vector3.h"

/*
* 위치 좌표와 반지름으로 구성된 구체
* 원점이 존재하고 반지름으로 영역을 알아냅니다.
*/

template<typename T = float>
class CVecSphere final
{
    static_assert(std::is_arithmetic<T>::value, "T는 원시 타입이어야만 합니다.");
public:
    CVector3<T> pos;
    T radius;

public:
    CVecSphere() : pos(CVector3<T>()), radius(T()) {}
    ~CVecSphere() {}
};

