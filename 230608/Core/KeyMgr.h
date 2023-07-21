#pragma once

#include "Define.h"

typedef enum class _EINPUT_KEY_STATE : int
{
	RELEASED,       // ��
	NUETRAL,        // �߸�
	PRESSING,       // ����
	PRESSED,        // �ѹ��� ����
}EINPUT_KEY_STATE;

/// <summary>
/// �Է� �����͸� �����ϴ� ����ü
/// 
/// </summary>
typedef struct _INPUT_KEY_INFO
{
	const TCHAR* const						sKeyName;			// ����Ű �̸�, �� �̸��� ���� Ű�� Ž��
	vector<tuple<int, EINPUT_KEY_STATE>>	vKeys;				// ���� Ű �Է� ����, ���� ����

public:

	_INPUT_KEY_INFO(const TCHAR* sKeyName)
		: sKeyName(sKeyName)
	{

	}

	template<typename T>
	void Add_Key(T _iKey)
	{
		// �ߺ� üũ
		if (!vKeys.empty())
		{
			bool bExists = true;
			for_each(vKeys.begin(), vKeys.end(), [key = _iKey, &bExists](const tuple<int, EINPUT_KEY_STATE>& _tKey) {
				if (key == get<0>(_tKey))
					bExists = false;
				});

			// �̹� �ִ� Ű�� �������� �ʴ´�.
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

	// ������ �߰��� �� ����
	template<typename T, typename... Args>
	void Add_Keys(T _iKey, Args... _iKeys)
	{
		Add_Key(_iKey);
		Add_Keys(_iKeys...);
	}


}INPUT_KEY_INFO;

/*
* Ű �Ŵ����� �ܼ� Ű�Է��� Down, Up, Pressing ���¸� üũ�Ͽ� �˷��ֱ⵵ ������.
* ���ӿ� �Է¿� �־� Ư���� �ൿ�� Ű �Է¿� ���� ó���ϰ�
* ���۹� ����� ���� ��ɵ鿡 �����ϵ��� �����ִ� ���ҵ� �մϴ�.
* ��Ű, ����Ű�� ���� ��ɵ鵵 �����ϵ��� ������� �Ŵ����Դϴ�.
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

	// �ܼ�Ű �Է�üũ �Լ�
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
	// �Ϲ����� �Է¿� ���� �����ϱ� ���� �뵵�� ���Դϴ�.
	bool				m_bKeyState[VK_MAX];
	// �Է�Ű�� ���� ������ �����Ѵ�.
	vector<INPUT_KEY_INFO*> m_vInputKeys;

public:
	void Add_InputKey(INPUT_KEY_INFO* pInputKey);
	void Remove_InputKey(INPUT_KEY_INFO* pInputKey);

public:
	// �ش� �̸��� ���� Ű���� �о� ���ۿ� ����ϱ� ���� �Է�Ű ����ü�� �б������ ��ȯ�޴� �ζ��� �Լ�
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

	// Get_InputKey�� �����Ͽ�, �������� �б� ���� Ű ����ü�� ����, �Է�Ű�� ���� ���¸� üũ�մϴ�.
	// Pressed ���� Ȯ�ο�
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
	// �� �Լ��� false �̸� Ű�� ���� ������ �ǹ�
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

	// Release ���� Ȯ�ο�
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