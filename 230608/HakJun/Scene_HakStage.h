#pragma once
#include "Scene.h"
class CScene_HakStage : public CScene
{
public:
	CScene_HakStage() {}
	virtual ~CScene_HakStage() {}

public:
	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

