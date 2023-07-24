#include "stdafx.h"
#include "Scene_HakStage.h"

#include "ObjMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "ObjFactory.h"
#include "Food_Cookie.h"
#include "HitCircle.h"
#include <Core/KeyMgr.h>

#include "SceneMgr.h"

void CScene_HakStage::Initialize()
{
#pragma region 이미지 추가
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Hak/Kitchen.bmp", L"BG_Kitchen");
#pragma endregion

	m_tInfo.tFrameTSet.Set_Keys(L"BG_Kitchen", L"");
	(*m_tInfo.tFrameTSet).iWidth = 800;
	(*m_tInfo.tFrameTSet).iHeight = 600;

	float fStartHeight = 350.f;

	INFO tInfo;
	tInfo.vPos = { 800.f, fStartHeight, 0.f };
	tInfo.vSpeed = { 5.f, 0.f, 0.f };
	CObjFactory<CFood_Cookie>::Create(UNIT, tInfo);

	tInfo = INFO();
	tInfo.vPos = { 200.f, fStartHeight, 0.f };
	CObjFactory<CHitCircle>::Create(UI, tInfo);

	m_tState.Set_State(ESTATE::READY);
	m_tState.Add_Func(ESTATE::READY, &CScene_HakStage::Ready);
	m_tState.Add_Func(ESTATE::START, &CScene_HakStage::Start);
	m_tState.Add_Func(ESTATE::PLAYING, &CScene_HakStage::Playing);
	m_tState.Add_Func(ESTATE::END, &CScene_HakStage::End);
}

void CScene_HakStage::Update()
{
	m_tState.Get_StateFunc()(this);

	CObjMgr::Get_Instance()->Update();
}

void CScene_HakStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();

	if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE3);
		return;
	}
}

void CScene_HakStage::Render(HDC hDC)
{
	CBmpMgr::Get_Instance()->Draw_BMP(hDC, m_tInfo, 0, 0, 800, 600, false);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_HakStage::Release()
{
	CObjMgr::Get_Instance()->Release();

	for (auto iter = m_listFood.begin(); iter != m_listFood.end();)
	{
		Safe_Delete<CFood*>(m_listFood.front());
		m_listFood.pop_front();
		iter = m_listFood.begin();
	}

	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}

void CScene_HakStage::Ready()
{
	if (m_tState.IsState_Entered())
	{

	}

	if (m_tState.Can_Update())
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
			m_tState.Set_State(ESTATE::START);
	}

	if (m_tState.IsState_Exit())
	{

	}
}

void CScene_HakStage::Start()
{
	if (m_tState.IsState_Entered())
	{
		CSoundMgr::Get_Instance()->PlayBGM(L"rhythm_rally.mp3", 1.f);
		m_fGameTime.Reset();

		float fStartX = 800.f;
		float fStartY = 350.f;
		for (size_t i = 0; i < 1000; i++)
		{
			m_listFood.push_back(CFood_Cookie::Create(UNIT, { fStartX, fStartY, 0.f }, { -10.f, 0.f, 0.f }, float(rand() % 100) * 0.01f, false));
		}
		
	}

	if (m_tState.Can_Update())
	{
		// 준비 작업
		if (m_fGameTime.Update(g_fDeltaTime, 1.f))
		{
			m_tState.Set_State(ESTATE::PLAYING);
		}
	}

	if (m_tState.IsState_Exit())
	{

	}
}

void CScene_HakStage::Playing()
{
	if (m_tState.IsState_Entered())
	{
		m_fGameTime.Reset();
		m_fRhythm_Delay.Reset();
	}

	if (m_tState.Can_Update())
	{
		if (!m_listFood.empty())
		{
			if (m_fRhythm_Delay.Update(g_fDeltaTime))
			{
				CObjMgr::Get_Instance()->Add_Object(UNIT, m_listFood.front());
				m_fRhythm_Delay.ReAdjust(m_listFood.front()->Get_Delay());
				m_listFood.pop_front();
			}
		}
		else
			m_tState.Set_State(ESTATE::END);
	}

	if (m_tState.IsState_Exit())
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	}
}

void CScene_HakStage::End()
{
	if (m_tState.IsState_Entered())
	{

	}

	if (m_tState.Can_Update())
	{

	}

	if (m_tState.IsState_Exit())
	{

	}
}
