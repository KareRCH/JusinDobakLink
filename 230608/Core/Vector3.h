#pragma once

#include "Define.h"

template<typename T = float>
class CVector3
{
    static_assert(std::is_arithmetic<T>::value, "T는 원시 타입이어야만 합니다.");
public:
    T x, y, z;

public:
    CVector3() : x(T()), y(T()), z(T()) {}
    CVector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
    CVector3(const CVector3<T>& _rhs) : x(_rhs.x), y(_rhs.y), z(_rhs.z) {}
    ~CVector3() {}

    // Assignment operator
    CVector3<T>& operator=(const CVector3<T>& other)
    {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    CVector3<T> operator+(const CVector3<T>& other) const
    {
        return CVector3<T>(x + other.x, y + other.y, z + other.z);
    }

    CVector3<T> operator-(const CVector3<T>& other) const
    {
        return CVector3<T>(x - other.x, y - other.y, z - other.z);
    }

    CVector3<T> operator*(T scalar) const
    {
        return CVector3<T>(x * scalar, y * scalar, z * scalar);
    }

    CVector3<T> operator/(T scalar) const
    {
        return CVector3<T>(x / scalar, y / scalar, z / scalar);
    }

    CVector3<T>& operator+=(const CVector3<T>& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    CVector3<T>& operator-=(const CVector3<T>& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    CVector3<T>& operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    CVector3<T>& operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    bool operator==(const CVector3<T>& other) const
    {
        return (x == other.x) && (y == other.y) && (z == other.z);
    }

    bool operator!=(const CVector3<T>& other) const
    {
        return !(*this == other);
    }

    //내적
    T Dot(const CVector3<T>& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    // 외적
    CVector3<T> Cross(const CVector3<T>& other) const
    {
        return CVector3<T>(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    T Length() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    CVector3<T> Normalized() const
    {
        float len = Length();
        float normalizedX = static_cast<float>(x) / len;
        float normalizedY = static_cast<float>(y) / len;
        float normalizedZ = static_cast<float>(z) / len;
        return CVector3<T>(normalizedX, normalizedY, normalizedZ);
    }
};