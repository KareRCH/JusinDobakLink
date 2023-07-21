#include "stdafx.h"
#include "SceneMgr.h"



CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_eCurScene(SCENEID::SC_LOGO), m_ePreScene(SCENEID::SC_END), m_pScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eScene)
{
	return;
	m_eCurScene = eScene;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SCENEID::SC_LOGO:
			m_pScene = new CLogo;
			break;

		//case SC_MENU:
		//	m_pScene = new CMyMenu;
		//	break;

		case SCENEID::SC_EDIT:

			break;

		case SCENEID::SC_STAGE:

			break;
		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}

}

void CSceneMgr::Update()
{
	return;
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	return;
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	return;
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}
