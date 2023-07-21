#include "stdafx.h"
#include "ITeamAgent.h"

ULONGLONG ITeamAgent::ID_COUNT = 0;
map<BYTE, map<BYTE, ITeamAgent::ERELATION>>	ITeamAgent::m_mapTeamRelation = map<BYTE, map<BYTE, ERELATION>>();