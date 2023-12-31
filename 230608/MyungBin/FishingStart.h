#pragma once
#include "MiniGame.h"

class CFishingStart : public CMiniGame
{
public:
	CFishingStart();
	~CFishingStart();
public:
	virtual void				Initialize() override;
	virtual MyungBinStageState	Update() override;
	virtual void				Late_Update() override;
	virtual void				Render(HDC hDC) override;
	virtual void				Release() override;


};