#pragma once
#include "MiniGame.h"
#include "MB_Player.h"

class CLobby : public CMiniGame
{
public:
	CLobby() 
	{
		m_cPlayer.Initialize();
	};
	
public:
	virtual void				Initialize() override;
	virtual MyungBinStageState	Update() override;
	virtual void				Late_Update() override;
	virtual void				Render(HDC hDC) override;
	virtual void				Release() override;

public:
	CMB_Player m_cPlayer;
};