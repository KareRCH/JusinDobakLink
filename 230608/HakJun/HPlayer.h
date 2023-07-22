#pragma once

#include "Define.h"

/*
* 임시용 플레이어
*/

class CHPlayer
{
private:
	CHPlayer() {}
	~CHPlayer() {}

public:
	void		Release();


private:
	static CHPlayer* m_pInstance;
public:
	static CHPlayer* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CHPlayer;
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

private: // 플레이어 속성 정의부
	int m_iScore = 0;
	GAUGE<int> m_iComboGauge = GAUGE<int>(100);
};

