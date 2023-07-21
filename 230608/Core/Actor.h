#pragma once
#include "Obj.h"
#include "IState.h"

template<typename T, typename T2>
class Actor : public CObj
{
public:
	Actor() {};
	virtual ~Actor() {};

public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void	Late_Update(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

protected:
	T2				m_eState;
	IState<T, T2>*	m_States[99];
};

