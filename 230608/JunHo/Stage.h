#pragma once
#include "Scene.h"
class CStage :
    public CScene
{
public:
	CStage();
	virtual ~CStage();
	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

