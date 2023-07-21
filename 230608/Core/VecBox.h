#pragma once

#include "Vector3.h"

/*
* 3차원 좌표계의 박스입니다.
* 원점이 존재하지 않고 절대 좌표로만 표현합니다.
*/

template<typename T = float>
class CVecBox final
{
	static_assert(std::is_arithmetic<T>::value, "T는 원시 타입이어야만 합니다.");
public:
    T left, right, up, down, top, bottom;

public:
    CVecBox() : left(T()), right(T()), up(T()), down(T()), top(T()), bottom(T()) {}
    ~CVecBox() {}
};

