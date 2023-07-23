#pragma once

#include "Obj.h"

class CFood : public CObj
{
public:
	CFood() {}
	virtual ~CFood() {}

private:
	float m_fDelay = 0.f;
public:
	void Set_Delay(float value) { m_fDelay = value; }
	const float& Get_Delay() const { return m_fDelay; }
};

