#pragma once

#include "Define.h"

typedef enum class _EINPUT_KEY_STATE : int
{
	RELEASED,       // 뗌
	NUETRAL,        // 중립
	PRESSING,       // 누름
	PRESSED,        // 한번만 눌림
}EINPUT_KEY_STATE;

/// <summary>
/// 입력 데이터를 저장하는 구조체
/// 
/// </summary>
typedef struct _INPUT_KEY_INFO
{
	const TCHAR* const						sKeyName;			// 전용키 이름, 이 이름을 통해 키를 탐색
	vector<tuple<int, EINPUT_KEY_STATE>>	vKeys;				// 다중 키 입력 지원, 상태 저장

public:

	_INPUT_KEY_INFO(const TCHAR* sKeyName)
		: sKeyName(sKeyName)
	{

	}

	template<typename T>
	void Add_Key(T _iKey)
	{
		// 중복 체크
		if (!vKeys.empty())
		{
			bool bExists = true;
			for_each(vKeys.begin(), vKeys.end(), [key = _iKey, &bExists](const tuple<int, EINPUT_KEY_STATE>& _tKey) {
				if (key == get<0>(_tKey))
					bExists = false;
				});

			// 이미 있는 키로 저장하지 않는다.
			if (!bExists)
				return;
		}
		else
			vKeys.push_back(make_tuple(_iKey, EINPUT_KEY_STATE::NUETRAL));
	}

	template<typename T>
	void Add_Keys(T _iKey)
	{
		Add_Key(_iKey);
	}

	// 여러개 추가할 수 있음
	template<typename T, typename... Args>
	void Add_Keys(T _iKey, Args... _iKeys)
	{
		Add_Key(_iKey);
		Add_Keys(_iKeys...);
	}


}INPUT_KEY_INFO;

/*
* 키 매니저는 단순 키입력을 Down, Up, Pressing 상태를 체크하여 알려주기도 하지만.
* 게임용 입력에 있어 특수한 행동과 키 입력에 대해 처리하고
* 조작법 변경과 같은 기능들에 대응하도록 도와주는 역할도 합니다.
* 주키, 보조키와 같은 기능들도 대응하도록 만들어진 매니저입니다.
*/

class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public:
	void Initialzie();
	void Late_Update();
	void Release();

	// 단순키 입력체크 함수
	bool		Key_Pressing(int _iKey);
	bool		Key_Down(int _iKey);
	bool		Key_Up(int _iKey);


private:
	static CKeyMgr* m_pInstance;


public:
	static CKeyMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CKeyMgr;
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
	// 일반적인 입력에 대해 반응하기 위한 용도로 쓰입니다.
	bool				m_bKeyState[VK_MAX];
	// 입력키에 대한 정보를 저장한다.
	vector<INPUT_KEY_INFO*> m_vInputKeys;

public:
	void Add_InputKey(INPUT_KEY_INFO* pInputKey);
	void Remove_InputKey(INPUT_KEY_INFO* pInputKey);

public:
	// 해당 이름을 가진 키값을 읽어 동작에 사용하기 쉽게 입력키 구조체를 읽기용으로 반환받는 인라인 함수
	const INPUT_KEY_INFO* Get_InputKey(const TCHAR* sKeyName) const
	{
		if (m_vInputKeys.empty())
			return nullptr;

		for (int i = 0; i < m_vInputKeys.size(); ++i)
		{
			if (0 == lstrcmp(m_vInputKeys[i]->sKeyName, sKeyName))
			{
				return m_vInputKeys[i];
			}
		}

		return nullptr;
	}
	const INPUT_KEY_INFO* operator [](const TCHAR* sKeyName) const
	{
		return Get_InputKey(sKeyName);
	}

	// Get_InputKey와 조합하여, 돌려받은 읽기 전용 키 구조체를 통해, 입력키에 대한 상태를 체크합니다.
	// Pressed 상태 확인용
	const bool IsKeyPressed(const INPUT_KEY_INFO* pKey) const
	{
		if (nullptr == pKey)
			return false;

		for (auto iter = pKey->vKeys.begin(); iter != pKey->vKeys.end(); ++iter)
		{
			if (EINPUT_KEY_STATE::PRESSED == get<1>(*iter))
				return true;
		}

		return false;
	}
	// 이 함수가 false 이면 키를 떼고 있음을 의미
	const bool IsKeyPressing(const INPUT_KEY_INFO* pKey) const
	{
		if (nullptr == pKey)
			return false;

		for (auto iter = pKey->vKeys.begin(); iter != pKey->vKeys.end(); ++iter)
		{
			if (EINPUT_KEY_STATE::PRESSING <= get<1>(*iter))
				return true;
		}

		return false;
	}

	// Release 상태 확인용
	const bool IsKeyReleased(const INPUT_KEY_INFO* pKey) const
	{
		if (nullptr == pKey)
			return false;

		for (auto iter = pKey->vKeys.begin(); iter != pKey->vKeys.end(); ++iter)
		{
			if (EINPUT_KEY_STATE::RELEASED == get<1>(*iter))
				return true;
		}

		return false;
	}
};