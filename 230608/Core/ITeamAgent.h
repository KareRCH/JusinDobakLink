#pragma once

#include "Define.h"

/*
* 팀을 식별할 수 있게 지원하는 인터페이스
* 인터페이스이지만 왠만한 것들은 구현을 해놓고 쓴다.
*/

class ITeamAgent abstract
{
public:
	static const BYTE TEAM_END = (BYTE)255U;		// 마지막 팀 ID

	enum class ERELATION
	{
		NONE,
		HOSTILE,
		NUETRAL,
		FRIEND
	};

public:
	ITeamAgent() : m_ulPrivID(InitID()) {}
	ITeamAgent(const ITeamAgent& _rhs) = delete;
	virtual ~ITeamAgent() {}

private:
	static ULONGLONG ID_COUNT;								// 고유 ID 제공용
	static map<BYTE, map<BYTE, ERELATION>>	m_mapTeamRelation;			// 팀별 관계, 관계도가 없을 때. 중립으로 처리함.
	
private:
	BYTE						m_bTeamID = (BYTE)0U;		// 자신의 팀ID

	ULONGLONG					m_ulPrivID;					// 자신의 ID
	map<ULONGLONG, ERELATION>	m_mapPrivRelation;			// 개별 관계, 우선도 높음

public:
	const BYTE Get_TeamID() { return m_bTeamID; }
	void Set_TeamID(int value) { m_bTeamID = (BYTE)value; }

private:
	// 객체를 초기화 할 때마다 ID를 증가시킴, 복사해서 만들어야 하는 경우, 상관 없음 ULONGLONG은 크니까 ㅋ
	ULONGLONG InitID() { return ID_COUNT++; }

public:
	static void Add_TeamRelation(int iSrcTeam, int iDstTeam, ERELATION eRelation)
	{
		auto iter = m_mapTeamRelation.find((BYTE)iSrcTeam);
		if (iter != m_mapTeamRelation.end())
		{
			m_mapTeamRelation[(BYTE)iSrcTeam].emplace((BYTE)iDstTeam, eRelation);
		}
		else
		{
			map<BYTE, ERELATION> mapTeamRelation = map<BYTE, ERELATION>();
			mapTeamRelation.emplace((BYTE)iDstTeam, eRelation);
			m_mapTeamRelation.emplace((BYTE)iSrcTeam, mapTeamRelation);
		}
	}

	// Dst에 대한 팀의 우호도를 체크한다.
	static ERELATION Check_TeamRelation(ITeamAgent* pDst, ITeamAgent* pSrc)
	{
		ERELATION tRelation = m_mapTeamRelation[pSrc->m_bTeamID][pDst->m_bTeamID];
		if (tRelation == ERELATION::NONE)
			return ERELATION::NUETRAL;
		return tRelation;
	}

	// Src의 관계도를 통해 Dst에 대한 우호도를 체크한다.
	static ERELATION Check_PrivRelation(ITeamAgent* pDst, ITeamAgent* pSrc)
	{
		ERELATION tRelation = pSrc->m_mapPrivRelation[pDst->m_ulPrivID];

		if (tRelation == ERELATION::NONE)
			return ERELATION::NUETRAL;

		return tRelation;
	}

	// 개인, 팀 순으로 우호도를 조사한다.
	static ERELATION Check_Relation(ITeamAgent* pDst, ITeamAgent* pSrc)
	{
		ERELATION tRelation = pSrc->m_mapPrivRelation[pDst->m_ulPrivID];

		if (tRelation == ERELATION::NONE)
			return Check_TeamRelation(pDst, pSrc);

		return tRelation;
	}
};

using ERELATION_STATE = ITeamAgent::ERELATION;