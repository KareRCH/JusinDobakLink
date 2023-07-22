#pragma once
#include "Scene.h"
class CYScene_Serving :
    public CScene
{
public:
	CYScene_Serving();
	virtual ~CYScene_Serving();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};