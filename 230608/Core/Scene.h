#pragma once

#include "Define.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void		Initialize() = 0;
	virtual void		Update() = 0;
	virtual void		Late_Update() = 0;
	virtual void		Render(HDC hDC) = 0;
	virtual void		Release() = 0;
};

