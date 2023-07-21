#pragma once
#include "DefindMyungBin.h"

class MiniGame 
{
public:
	MiniGame() {};
	virtual ~MiniGame() {};

public:
	virtual void					Initialize()	PURE;
	virtual MyungBinStageState		Update()		PURE;
	virtual void					Late_Update()	PURE;
	virtual void					Render(HDC hDC) PURE;
	virtual void					Release()		PURE;

};