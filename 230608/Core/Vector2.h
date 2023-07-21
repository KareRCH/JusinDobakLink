#pragma once

#include "Define.h"

template<typename T = float>
class CVector2
{
	static_assert(std::is_arithmetic<T>::value, "T는 원시 타입이어야만 합니다.");
public:
	CVector2() : x(T()), y(T()) {}
	CVector2(T _X, T _Y) : x(_X), y(_Y)
	{
		x = _X;
		y = _Y;
	}
	CVector2(const CVector2<T>& _rhs)
	{
		x = _rhs.x;
		y = _rhs.y;
	}
	~CVector2() {}

public:
	T	x, y;

public:
	static CVector2<T> Zero() { return CVector2<T>(); }
	/*static CVector2<T> Right()	{ return CVector2<T>(T(1), T(0)); }
	static CVector2<T> Left()	{ return CVector2<T>(T(-1), T(0)); }
	static CVector2<T> Up()		{ return CVector2<T>(T(0), T(1)); }
	static CVector2<T> Down()	{ return CVector2<T>(T(0), T(-)); }*/

public:
#pragma region +, -, +=, -= 연산자
	CVector2<T> operator + (CVector2<T> _Src)
	{
		return CVector2<T>(this->x + _Src.x, this->y + _Src.y);
	}
	CVector2<T> operator += (const CVector2<T>& _Src)
	{
		this->x += _Src.x;
		this->y += _Src.y;

		return *this;
	}

	CVector2<T> operator - (CVector2<T> _Src)
	{
		return CVector2<T>(this->x - _Src.x, this->y - _Src.y);
	}

	CVector2<T>& operator -= (const CVector2<T>& _Src)
	{
		this->x -= _Src.x;
		this->y -= _Src.y;

		return *this;
	}
#pragma endregion

#pragma region *, *= 연산자
	CVector2<T> operator*(T value) const
	{
		return CVector2<T>(value * this->x, value * this->y);
	}

	CVector2<T>& operator*=(T value)
	{
		this->x *= value;
		this->y *= value;

		return *this;
	}
#pragma endregion

#pragma region /, /= 연산자
	CVector2<T> operator/ (T value) const
	{
		return CVector2<T>(value / this->x, value / this->y);
	}
	CVector2<T> operator/= (T value)
	{
		this->x /= value;
		this->y /= value;

		return *this;
	}
#pragma endregion

#pragma region =, == 연산자
	CVector2<T> operator = (CVector2<T> _Src)
	{
		this->x = _Src.x;
		this->y = _Src.y;

		return *this;
	}

	bool operator == (CVector2<T>& _Src)
	{
		return (this->x == _Src.x && this->y == _Src.y);
	}

	bool operator != (CVector2<T>& _Src)
	{
		return !(*this == _Src);
	}
#pragma endregion

#pragma region 내적, 외적, 길이, 정규화

	T Dot(CVector2<T> _Src) const
	{
		return (x * _Src.x + y * _Src.y);
	}

	double Dot_D(CVector2& _Src) const
	{
		return (static_cast<double>(x * _Src.x) + static_cast<double>(y * _Src.y));
	}

	float Dot_F(CVector2& _Src) const
	{
		return (static_cast<float>(x * _Src.x) + static_cast<float>(y * _Src.y));
	}

	T Cross(CVector2& _Src) const
	{
		return (x * _Src.y - y * _Src.x);
	}

	double Cross_D(CVector2& _Src) const
	{
		return (static_cast<double>(x * _Src.y) - static_cast<double>(y * _Src.x));
	}

	float Cross_F(CVector2& _Src) const
	{
		return (static_cast<float>(x * _Src.y) - static_cast<float>(y * _Src.x));
	}

	T Length(CVector2<T>& _Src) const
	{
		return static_cast<T>(sqrt(x * _Src.y - y * _Src.x));
	}

	double Length_D() const
	{
		return sqrt(static_cast<double>(x) * static_cast<double>(x) + static_cast<double>(y) * static_cast<double>(y));
	}

	float Length_F() const
	{
		return sqrt(static_cast<float>(x) * static_cast<float>(x) + static_cast<float>(y) * static_cast<float>(y));
	}

	CVector2<T> Normalized() const
	{
		T length = Length_F();
		if (length == T()) {
			return *this;
		}
		T factor = T(1) / length;
		return CVector2<T>(x * factor, y * factor);
	}

	CVector2<double> Normalized_D() const
	{
		double len = Length_D();
		return CVector2<double>(static_cast<double>(x) / len, static_cast<double>(y) / len);
	}

	CVector2<float> Normalized_F() const
	{
		float len = Length_F();
		return CVector2<float>(static_cast<float>(x) / len, static_cast<float>(y) / len);
	}
#pragma endregion
};

