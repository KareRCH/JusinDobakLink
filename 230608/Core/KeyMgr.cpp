#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

CKeyMgr::~CKeyMgr()
{
	Release();
}

void CKeyMgr::Initialzie()
{
	Add_InputKey(new INPUT_KEY_INFO(L"Right"));
	//m_vInputKeys.back()->Add_Keys(VK_RIGHT, 'D');
	Add_InputKey(new INPUT_KEY_INFO(L"Left"));
	//m_vInputKeys.back()->Add_Keys(VK_LEFT, 'A');
	Add_InputKey(new INPUT_KEY_INFO(L"Up"));
	//m_vInputKeys.back()->Add_Key(VK_UP);
	Add_InputKey(new INPUT_KEY_INFO(L"Down"));
	//m_vInputKeys.back()->Add_Key(VK_DOWN);

	Add_InputKey(new INPUT_KEY_INFO(L"UI_Accept"));
	//m_vInputKeys.back()->Add_Key(VK_ACCEPT);
	Add_InputKey(new INPUT_KEY_INFO(L"UI_Cancel"));
	//m_vInputKeys.back()->Add_Key(VK_ESCAPE);
	Add_InputKey(new INPUT_KEY_INFO(L"UI_Menu"));
	//m_vInputKeys.back()->Add_Key(VK_ACCEPT);
}

void CKeyMgr::Late_Update()
{
	if (!g_bWinActivate)
		return;

	for (int i = 0; i < m_vInputKeys.size(); ++i)
	{
		if (nullptr == m_vInputKeys[i])
			continue;

		for (int j = 0; j < m_vInputKeys[i]->vKeys.size(); ++j)
		{
			// �Է��� �޾��� ��
			if (GetAsyncKeyState(get<0>(m_vInputKeys[i]->vKeys[j])) & 0x8000)
			{
				if (EINPUT_KEY_STATE::NUETRAL >= get<1>(m_vInputKeys[i]->vKeys[j]))
					get<1>(m_vInputKeys[i]->vKeys[j]) = EINPUT_KEY_STATE::PRESSED;
				else
					get<1>(m_vInputKeys[i]->vKeys[j]) = EINPUT_KEY_STATE::PRESSING;
			}
			// �Է��� ���� ��
			else
			{
				if (EINPUT_KEY_STATE::PRESSING <= get<1>(m_vInputKeys[i]->vKeys[j]))
					get<1>(m_vInputKeys[i]->vKeys[j]) = EINPUT_KEY_STATE::RELEASED;
				else
					get<1>(m_vInputKeys[i]->vKeys[j]) = EINPUT_KEY_STATE::NUETRAL;
			}
		}
	}

	// m_bKeyState�� ���� Ű ���¸� ������Ʈ �մϴ�.
	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
		else if (!m_bKeyState[i] && (GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}
}

void CKeyMgr::Release()
{
	if (m_vInputKeys.empty())
		return;

	for_each(m_vInputKeys.begin(), m_vInputKeys.end(), [](INPUT_KEY_INFO* _pKeyInfo) {
		if (nullptr != _pKeyInfo)
		{
			Safe_Delete(_pKeyInfo);
		}
		});
}

bool CKeyMgr::Key_Pressing(int _iKey)
{
	if (!g_bWinActivate)
		return false;

	if (GetAsyncKeyState(_iKey) & 0x8000)
		return true;

	return false;
}

bool CKeyMgr::Key_Down(int _iKey)
{
	if (!g_bWinActivate)
		return false;

	// �������� ���� ���� ���� ���� ������ ���
	if (!m_bKeyState[_iKey] && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		return true;
	}

	return false;
}

bool CKeyMgr::Key_Up(int _iKey)
{
	if (!g_bWinActivate)
		return false;

	// �������� ���� ���� �ְ� ���� ������ �ʾ��� ���
	if (m_bKeyState[_iKey] && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		return true;
	}

	return false;
}


void CKeyMgr::Add_InputKey(INPUT_KEY_INFO* pInputKey)
{
}

void CKeyMgr::Remove_InputKey(INPUT_KEY_INFO* pInputKey)
{
}