#pragma once
#include "Scene.h"
#include "Food.h"
class CScene_HakStage : public CScene
{
public:
	CScene_HakStage() {}
	virtual ~CScene_HakStage() { Release(); }

public:
	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	INFO m_tInfo;

private:
	enum class ESTATE { READY, START, PLAYING, END };
	STATE_SET<ESTATE, void(CScene_HakStage*)> m_tState;

	void Ready();
	void Start();
	void Playing();
	void End();

private:
	GAUGE<float> m_fGameTime = GAUGE<float>(84.f);
	DELAY<float> m_fRhythm_Delay = DELAY<float>(3.f);
	list<CFood*> m_listFood;
};

