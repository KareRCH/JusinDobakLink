#pragma once
#include "DefindMyungBin.h"
#include "Fisherman.h"

class CMiniGame 
{
public:
	CMiniGame()
		//:m_pFisherman(nullptr)
	{};
	virtual ~CMiniGame() {};

public:
	virtual void					Initialize()	PURE;
	virtual MyungBinStageState		Update()		PURE;
	virtual void					Late_Update()	PURE;
	virtual void					Render(HDC hDC) PURE;
	virtual void					Release()		PURE;

protected:
	CFisherman m_cFisherman;

};