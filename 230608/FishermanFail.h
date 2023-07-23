#pragma once
#include "Fisherman.h"
#include "IState.h"
class CFishermanFail : public IState<CFisherman, FishermanState>
{
public:
	CFishermanFail();
	~CFishermanFail();

public:
	virtual void Initialize(CFisherman& _Actor) override;
	virtual FishermanState Update(CFisherman& _Actor) override;
	virtual void Late_Update(CFisherman& _Actor) override;
	virtual void Render(HDC hDC, CFisherman& _Actor) override;
	virtual void Release(CFisherman& _Actor) override;

};