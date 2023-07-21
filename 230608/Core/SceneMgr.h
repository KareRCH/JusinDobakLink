#pragma once

#include "Scene.h"
#include "StageMyungBin.h"
//#include "MyMenu.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void		Scene_Change(SCENEID eScene);
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr* m_pInstance;
	CScene* m_pScene;

	SCENEID					m_eCurScene;
	SCENEID					m_ePreScene;

public:
	void					Set_CurScene(SCENEID _id) { m_eCurScene = _id; }
	int						Get_CurScene() { return m_eCurScene; }
	int						Get_PreScene() { return m_ePreScene; }
};

