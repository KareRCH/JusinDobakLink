#pragma once
#include "Fisherman.h"
#include "IState.h"
class CFishermanHooking : public IState<CFisherman, FishermanState>
{
public:
	CFishermanHooking();
	~CFishermanHooking();

public:
	virtual void Initialize(CFisherman& _Actor) override;
	virtual FishermanState Update(CFisherman& _Actor) override;
	virtual void Late_Update(CFisherman& _Actor) override;
	virtual void Render(HDC hDC, CFisherman& _Actor) override;
	virtual void Release(CFisherman& _Actor) override;
private:
	D3DXVECTOR3 targetVec3;
	D3DXVECTOR3 tempVec3;
};