#include "stdafx.h"
#include "StageMyungBin.h"
#include "Lobby.h"
#include "FishingStart.h"
#include "SceneMgr.h"

CStageMyungBin::CStageMyungBin()
	:m_eState(MyungBinStageState::MyungBinStageState_End)
{
	ZeroMemory(m_eMiniGames, sizeof(m_eMiniGames));
}

CStageMyungBin::~CStageMyungBin()
{
	Release();
}

void CStageMyungBin::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	m_eState = MyungBinStageState::LOBBY;
	m_eMiniGames[(int)MyungBinStageState::LOBBY] = new CLobby;
	m_eMiniGames[(int)MyungBinStageState::FISHING_START] = new CFishingStart;

	//m_eScenes[STAGE1] = new CStage1();
	//m_eScenes[STAGE2] = new CStage2();
	//m_eScenes[STAGE3] = new CStage3();
	//m_eScenes[STAGE4] = new CStage4();

	m_eMiniGames[(int)MyungBinStageState::LOBBY]->Initialize();
}

void CStageMyungBin::Update()
{
	MyungBinStageState nowState = m_eMiniGames[(int)m_eState]->Update();
	if (m_eState != nowState) 
	{
		m_eMiniGames[(int)m_eState]->Release();
		m_eState = nowState;
		m_eMiniGames[(int)m_eState]->Initialize();
	}

	if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		//Release();
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE2);
		return;
	}

}

void CStageMyungBin::Late_Update()
{
	m_eMiniGames[(int)m_eState]->Late_Update();
}

void CStageMyungBin::Render(HDC hDC)
{
	if (m_eMiniGames[(int)MyungBinStageState::LOBBY] != nullptr) 
	{
		m_eMiniGames[(int)MyungBinStageState::LOBBY]->Render(hDC);
	}
	m_eMiniGames[(int)m_eState]->Render(hDC);
}

void CStageMyungBin::Release()
{
	m_eMiniGames[(int)m_eState]->Release();
	for (auto scene : m_eMiniGames)
	{
		if (scene != nullptr)
			Safe_Delete(scene);
	}
}
