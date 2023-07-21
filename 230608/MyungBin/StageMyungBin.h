#pragma once
#include "DefindMyungBin.h"
#include "MiniGame.h"



class StageMyungBin 
{
public:
	StageMyungBin();
	~StageMyungBin();

public:
	virtual void		Initialize()	;
	virtual void		Update()		;
	virtual void		Late_Update()	;
	virtual void		Render(HDC hDC) ;
	virtual void		Release()		;

private:
	HDC					m_hDC;
	MyungBinStageState	m_eState;
	MiniGame*			m_eMiniGames[(int)MyungBinStageState::MyungBinStageState_End];

};