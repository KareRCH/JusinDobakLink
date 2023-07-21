#pragma once

#include "Vector3.h"

/*
* 3���� ��ǥ���� �ڽ��Դϴ�.
* ������ �������� �ʰ� ���� ��ǥ�θ� ǥ���մϴ�.
*/

template<typename T = float>
class CVecBox final
{
	static_assert(std::is_arithmetic<T>::value, "T�� ���� Ÿ���̾�߸� �մϴ�.");
public:
    T left, right, up, down, top, bottom;

public:
    CVecBox() : left(T()), right(T()), up(T()), down(T()), top(T()), bottom(T()) {}
    ~CVecBox() {}
};

