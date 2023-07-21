#pragma once


#include "Define.h"

class FAnimData final
{
public:
	FAnimData() {}
	~FAnimData() {}

public:
	// 모션 종류, 최대 애니메이션 수
	int iMotionX = 0;
	int iMotionY = 0;
	int	iMotionSize = 0;

	// 시트의 프레임별 사이즈
	int	iWidth = 0;
	int iHeight = 0;

	// 원점
	int iOffsetX = 0;
	int iOffsetY = 0;

	// 초당 속도
	float fSpeed = 0.f;

public:
	ULONGLONG Get_Speed_ForFrame()
	{
		return static_cast<ULONGLONG>(round((1.f - fSpeed) * 16.f * 1000.f / 65.f));
	}

	void Parse_Frame(FRAME& tFrame)
	{
		tFrame.bLoop = true;
		tFrame.bStop = false;
		tFrame.iMotion = iMotionY;
		tFrame.iFrameEnd = iMotionSize - 1;
		tFrame.iFrameStart = iMotionX;
		tFrame.iFrameCur = 0;
		tFrame.ulSpeed = Get_Speed_ForFrame();
		tFrame.ulTime = GetTickCount64();
		
		tFrame.iOffsetX = iOffsetX;
		tFrame.iOffsetY = iOffsetY;

		tFrame.iWidth = iWidth;
		tFrame.iHeight = iHeight;
	}

	void Parse_Frame_Maintain(FRAME& tFrame)
	{
		tFrame.bLoop = true;
		tFrame.bStop = false;
		tFrame.iMotion = iMotionY;
		tFrame.iFrameEnd = iMotionSize - 1;
		tFrame.iFrameStart = iMotionX;

		if (tFrame.iFrameCur > tFrame.iFrameEnd)
			tFrame.iFrameCur = 0;

		tFrame.ulSpeed = Get_Speed_ForFrame();

		tFrame.iOffsetX = iOffsetX;
		tFrame.iOffsetY = iOffsetY;

		tFrame.iWidth = iWidth;
		tFrame.iHeight = iHeight;
	}
};

class CAnimationTable final
{
private:
	CAnimationTable() {}
	~CAnimationTable() {}
	CAnimationTable(const CAnimationTable& _rhs) = delete;

private:
	void Initialize();
	void Release();

private:
	static CAnimationTable* g_pInstance;

public:
	static CAnimationTable* Get_Instance()
	{
		if (!g_pInstance)
		{
			g_pInstance = new CAnimationTable;
			g_pInstance->Initialize();
		}

		return g_pInstance;
	}
	static void		Destroy_Instance()
	{
		if (g_pInstance)
		{
			g_pInstance->Release();
			delete g_pInstance;
			g_pInstance = nullptr;
		}
	}

private:
	// 2차원 맵, 시트를 찾고, 애니메이션의 이름으로 프레임의 정보를 찾는다.
	map<const TCHAR*, map<const TCHAR*, FAnimData>> m_mapTable;

	void Create_Animation(const TCHAR* sName, const TCHAR* sAnimName,	
		int iMotionX, int iMotionY, int iMotionSize, float fSpeed,
		int iOffsetX, int iOffsetY, int iFrameWidth, int iFrameHeight)
	{
		FAnimData pNewData = FAnimData();

		pNewData.iMotionX = iMotionX;
		pNewData.iMotionY = iMotionY;
		pNewData.iMotionSize = iMotionSize;

		pNewData.iWidth = iFrameWidth;
		pNewData.iHeight = iFrameHeight;

		pNewData.iOffsetX = iOffsetX;
		pNewData.iOffsetY = iOffsetY;
		pNewData.fSpeed = fSpeed;

		if (m_mapTable.find(sName) == m_mapTable.end())
			m_mapTable.emplace(sName, map<const TCHAR*, FAnimData>());

		auto& mapAnim = m_mapTable[sName];
		mapAnim.emplace(sAnimName, pNewData);
	}

public:
	FAnimData Get_AnimData(const TCHAR* sName, const TCHAR* sAnimName)
	{
		if (m_mapTable.empty())
			return FAnimData();

		// 애니메이션 카테고리가 있을 때
		auto iter = find_if(m_mapTable.begin(), m_mapTable.end(),
			[&sName](auto& Pair) {
				return (!lstrcmp(sName, Pair.first));
			});

		if (iter != m_mapTable.end())
		{
			auto& mapAnim = (*iter).second;
			auto iterAnim = find_if(mapAnim.begin(), mapAnim.end(),
				[&sAnimName](auto& Pair) {
					return (!lstrcmp(sAnimName, Pair.first));
				});

			// 애니메이션이 있을 때
			if (iterAnim != mapAnim.end())
			{
				auto& AnimData = (*iterAnim).second;
				return AnimData;
			}
		}

		return FAnimData();
	}

	FAnimData Load_AnimData(const TCHAR* sAnimName, pair<const TCHAR*, FRAME>& pairFrame, bool bMaintain = false)
	{
		if (m_mapTable.empty())
			return FAnimData();

		auto iter = find_if(m_mapTable.begin(), m_mapTable.end(), 
			[&pairFrame](auto& Pair) {
			return (!lstrcmp(pairFrame.first, Pair.first));
			});

		// 애니메이션 카테고리가 있을 때
		if (iter != m_mapTable.end())
		{
			auto& mapAnim = (*iter).second;
			auto iterAnim = find_if(mapAnim.begin(), mapAnim.end(),
				[&sAnimName](auto& Pair) {
					return (!lstrcmp(sAnimName, Pair.first));
				});

			// 카테고리에 대한 애니메이션이 있을 때
			if (iterAnim != mapAnim.end())
			{
				auto& AnimData = (*iterAnim).second;
				auto& tFrameData = pairFrame.second;

				// Frame 구조체에 대한 변환작업
				if (!bMaintain)
					AnimData.Parse_Frame(tFrameData);
				else
					AnimData.Parse_Frame_Maintain(tFrameData);
				
				return AnimData;
			}
		}

		return FAnimData();
	}
};

