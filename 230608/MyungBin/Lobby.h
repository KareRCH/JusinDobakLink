#pragma once
#include "MiniGame.h"

class Lobby : public MiniGame
{
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};