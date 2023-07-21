#pragma once

#include "Define.h"

#include "Vector2.h"
#include "Vector3.h"
#include "VecLine3.h"
#include "VecBox.h"
#include "VecShpere.h"


template<typename T>
typename std::enable_if<is_floating_point<T>::value, bool>::type
inline Equals(T a, T b, T epsilon)
{
	return abs(a - b) <= epsilon;
}

// 정수 타입도 범위를 지정하여 가능한 함수
template<typename T>
typename std::enable_if<is_arithmetic<T>::value, bool>::type
inline Equals_Ranged(T a, T b, T epsilon)
{
	return abs(a - b) <= epsilon;
}