#pragma once

#include "Vector3.h"

/*
* CVector3를 이용한 라인입니다.
* 시작점과 끝점을 통해 영역을 알아냅니다.
*/

template<typename T = float>
class CVecLine3 final
{
    static_assert(std::is_arithmetic<T>::value, "T는 원시 타입이어야만 합니다.");
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
