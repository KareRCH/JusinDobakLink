#include "stdafx.h"
#include "LineMgr.h"
#include "KeyMgr.h"		// ���� 0622 �߰�

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr() : m_bIsDraw(true) // ���� 0622 �߰�
{
	ZeroMemory(m_tLintPoint, sizeof(m_tLintPoint));	// ���� 0622 �߰�
}


CLineMgr::~CLineMgr()
{
	Release();
}

bool CLineMgr::Collision_Line(INFO& m_tInfo, float* pY)
{
	if (m_LineList.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& line : m_LineList)
	{
		if (line->Get_Info().tLpoint.fX <= m_tInfo.vPos.x &&
			line->Get_Info().tRpoint.fX > m_tInfo.vPos.x)
			//pTarget = iter;
		{
			float   x1 = line->Get_Info().tLpoint.fX;
			float   x2 = line->Get_Info().tRpoint.fX;

			float   y1 = line->Get_Info().tLpoint.fY;
			float   y2 = line->Get_Info().tRpoint.fY;

			float m_Y = ((y2 - y1) / (x2 - x1)) * (m_tInfo.vPos.x - x1) + y1;

			//bool test1 = m_Y + (m_tInfo.fCY - 40) >= m_tInfo.fY;
			//bool test2 = (m_Y - (m_tInfo.fCY - 40) <= m_tInfo.fY);


			if (m_Y + (m_tInfo.fCY +5) >= m_tInfo.vPos.y && m_Y - (m_tInfo.fCY +5) <= m_tInfo.vPos.y)
			{
				pTarget = line;
			}

		}
	}

	if (!pTarget)
		return false;

	float   x1 = pTarget->Get_Info().tLpoint.fX;
	float   x2 = pTarget->Get_Info().tRpoint.fX;

	float   y1 = pTarget->Get_Info().tLpoint.fY;
	float   y2 = pTarget->Get_Info().tRpoint.fY;

	*pY = ((y2 - y1) / (x2 - x1)) * (m_tInfo.vPos.x - x1) + y1;

	return true;
}

void CLineMgr::Save_Line()
{
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",		// ������ ���
		GENERIC_WRITE,	// ���� ������ ���(GENERIC_READ : �б� ���� ���)
		NULL, // �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� �㰡�� ���ΰ�, NULL�̸� �������� �ʰڴ�.
		NULL, // ���ȼӼ�, NULL�� ��� �⺻ ���� ����
		CREATE_ALWAYS,  // ���� ���� ���, CREATE_ALWAYS : ������ ���ٸ� ����, ������ �ִ� ��� ���� ����, OPEN_EXITING : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ� : FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ����� ���ϻ��� 
		NULL); // ������ ������ �Ӽ��� ������ ���ø� ����, ������� �ʱ� ������ NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"���� ����", _T("����"), MB_OK);
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : m_LineList)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(LINE), &dwByte, nullptr);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"���� ����", _T("����"), MB_OK);

}

// ���� 0622 �߰� : �����Ϳ��� �׸� ���� �ҷ�����(Initialize���� ȣ��)
void CLineMgr::Load_Line()
{
	Release();

	HANDLE		hFile = CreateFile(L"../Data/Line.dat",		// ������ ���
		GENERIC_READ,	// ���� ������ ���(GENERIC_READ : �б� ���� ���)
		NULL, // �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� �㰡�� ���ΰ�, NULL�̸� �������� �ʰڴ�.
		NULL, // ���ȼӼ�, NULL�� ��� �⺻ ���� ����
		OPEN_EXISTING,  // ���� ���� ���, CREATE_ALWAYS : ������ ���ٸ� ����, ������ �ִ� ��� ���� ����, OPEN_EXITING : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ� : FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ����� ���ϻ��� 
		NULL); // ������ ������ �Ӽ��� ������ ���ø� ����, ������� �ʱ� ������ NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"���� ����", _T("����"), MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"�ҷ����� ����", _T("����"), MB_OK);
}



void CLineMgr::Initialize()
{
	
}

// ���� 0622 �߰�
int CLineMgr::Update()
{
	POINT	pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x += (int)CCamera::Get_Instance()->Get_WindowPos().x;
	pt.y += (int)CCamera::Get_Instance()->Get_WindowPos().y;
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		if ((!m_tLintPoint[0].fX) && !(m_tLintPoint[0].fY))
		{
			m_tLintPoint[0].fX = float(pt.x);
			m_tLintPoint[0].fY = float(pt.y);
		}
		else
		{
			m_tLintPoint[1].fX = float(pt.x);
			m_tLintPoint[1].fY = float(pt.y);

			LINE	tInfo{ m_tLintPoint[0], m_tLintPoint[1] };
			m_LineList.push_back(new CLine(tInfo));

			m_tLintPoint[0].fX = m_tLintPoint[1].fX;
			m_tLintPoint[0].fY = m_tLintPoint[1].fY;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON))
	{
		m_tLintPoint[0].fX = float(pt.x);
		m_tLintPoint[0].fY = float(pt.y);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('A'))
		Save_Line();

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
		Load_Line();

	return 0;
}

// ���� 0622 �߰�
void CLineMgr::Late_Update()
{
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}
bool CLineMgr::DashCheck(float fX, int nDirection) {

	if (nDirection == 0) {
		return false;
	}
	CLine* pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (iter->Get_Info().tLpoint.fX <= fX &&
			iter->Get_Info().tRpoint.fX > fX)
			pTarget = iter;
	}
	if (!pTarget)
		return true;
	float	x1 = pTarget->Get_Info().tLpoint.fX;
	float	x2 = pTarget->Get_Info().tRpoint.fX;

	float	y1 = pTarget->Get_Info().tLpoint.fY;
	float	y2 = pTarget->Get_Info().tRpoint.fY;

	float slope = (y2 - y1) / (x2 - x1);

	if (slope * nDirection >= 0)
		return true;
	else return false;
}