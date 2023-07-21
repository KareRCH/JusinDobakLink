#include "stdafx.h"
#include "StageMyungBin.h"
#include "Lobby.h"

StageMyungBin::StageMyungBin()
	:m_eState(MyungBinStageState::MyungBinStageState_End)
{
	ZeroMemory(m_eMiniGames, sizeof(m_eMiniGames));
}

StageMyungBin::~StageMyungBin()
{
	Release();
}

void StageMyungBin::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	m_eState = MyungBinStageState::LOBBY;
	m_eMiniGames[(int)MyungBinStageState::LOBBY] = new Lobby;

	//m_eScenes[STAGE1] = new CStage1();
	//m_eScenes[STAGE2] = new CStage2();
	//m_eScenes[STAGE3] = new CStage3();
	//m_eScenes[STAGE4] = new CStage4();

	m_eMiniGames[(int)MyungBinStageState::LOBBY]->Initialize();
}

void StageMyungBin::Update()
{
	m_eMiniGames[(int)m_eState]->Update();
}

void StageMyungBin::Late_Update()
{
	m_eMiniGames[(int)m_eState]->Late_Update();
}

void StageMyungBin::Render(HDC hDC)
{
	m_eMiniGames[(int)m_eState]->Render(hDC);
}

void StageMyungBin::Release()
{
	m_eMiniGames[(int)m_eState]->Release();
	for (auto scene : m_eMiniGames)
	{
		Safe_Delete(scene);
	}
}
