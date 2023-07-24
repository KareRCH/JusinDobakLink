#pragma once
#include "DefindMyungBin.h"
#include "MiniGame.h"
#include "Scene.h"


class CStageMyungBin : public CScene
{
public:
	CStageMyungBin();
	~CStageMyungBin();

public:
	virtual void		Initialize();
	virtual void		Update();
	virtual void		Late_Update();
	virtual void		Render(HDC hDC);
	virtual void		Release();

private:
	HDC					m_hDC;
	MyungBinStageState	m_eState;
	CMiniGame*			m_eMiniGames[(int)MyungBinStageState::MyungBinStageState_End];

};