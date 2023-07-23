#include "stdafx.h"
#include "LineMgr.h"
#include "KeyMgr.h"		// 유정 0622 추가
#include "Line.h"
CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr() : m_bIsDraw(true) // 유정 0622 추가
{
	ZeroMemory(m_tLintPoint, sizeof(m_tLintPoint));	// 유정 0622 추가
}


CLineMgr::~CLineMgr()
{
	Release();
}

bool CLineMgr::Collision_Line(INFO& m_tInfo, CLine** pLine, float* pY, float* pfGradient)
{
	if (m_LineList.empty())
		return false;

	list<CLine*>::iterator curiter;
	
	for (auto& iter = m_LineList.begin(); iter != m_LineList.end(); ++iter)
	{
		list<CLine*>::iterator curiter = iter;

		if ((*iter)->Get_Info().tLpoint.fX <= m_tInfo.vPos.x &&
			(*iter)->Get_Info().tRpoint.fX > m_tInfo.vPos.x)
			//pTarget = iter;
		{
			//line 현재 충돌한 라인 객체
			LINEPOINT lPoint = (*curiter)->Get_Info().tLpoint;
			++curiter;
			if (curiter != m_LineList.end())
			{
				LINEPOINT rPoint = (*curiter)->Get_Info().tRpoint;
				
				//*pfGradient = (rPoint.fY - lPoint.fY) / (rPoint.fX - lPoint.fX);
				*pfGradient = atan2(rPoint.fY - lPoint.fY, rPoint.fX - lPoint.fX);
			}

			float   x1 = (*iter)->Get_Info().tLpoint.fX;
			float   x2 = (*iter)->Get_Info().tRpoint.fX;

			float   y1 = (*iter)->Get_Info().tLpoint.fY;
			float   y2 = (*iter)->Get_Info().tRpoint.fY;

			float m_Y = ((y2 - y1) / (x2 - x1)) * (m_tInfo.vPos.x - x1) + y1;

			//bool test1 = m_Y + (m_tInfo.fCY - 40) >= m_tInfo.fY;
			//bool test2 = (m_Y - (m_tInfo.fCY - 40) <= m_tInfo.fY);


			if (m_Y + (m_tInfo.fCY + 5) >= m_tInfo.vPos.y && m_Y - (m_tInfo.fCY + 5) <= m_tInfo.vPos.y)
			{
				*pLine = (*iter);
			}

		}
	}

	if (!(*pLine))
		return false;

	float   x1 = (*pLine)->Get_Info().tLpoint.fX;
	float   x2 = (*pLine)->Get_Info().tRpoint.fX;

	float   y1 = (*pLine)->Get_Info().tLpoint.fY;
	float   y2 = (*pLine)->Get_Info().tRpoint.fY;

	*pY = ((y2 - y1) / (x2 - x1)) * (m_tInfo.vPos.x - x1) + y1;

	return true;
}

void CLineMgr::Save_Line()
{
	HANDLE		hFile = CreateFile(L"../Data/Line2.dat",		// 파일의 경로
		GENERIC_WRITE,	// 개방 파일의 모드(GENERIC_READ : 읽기 전용 모드)
		NULL, // 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 열려할 때 허가할 것인가, NULL이면 공유하지 않겠다.
		NULL, // 보안속성, NULL인 경우 기본 보안 상태
		CREATE_ALWAYS,  // 파일 생성 방식, CREATE_ALWAYS : 파일이 없다면 생성, 파일이 있는 경우 덮어 쓰기, OPEN_EXITING : 파일이 있을 경우에만 열기
		FILE_ATTRIBUTE_NORMAL, // 파일 속성 : FILE_ATTRIBUTE_NORMAL 아무런 속성이 없는 일반적인 파일상태 
		NULL); // 생성될 파일의 속성을 제공할 템플릿 파일, 사용하지 않기 때문에 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"개방 실패", _T("실패"), MB_OK);
		return;
	}
	
	DWORD		dwByte = 0;

	for (auto& iter : m_LineList)
	{
		int lineOption = iter->GetLine_Option();
		WriteFile(hFile, &(iter->Get_Info()), sizeof(LINE), &dwByte, nullptr);
		WriteFile(hFile, &lineOption, sizeof(int), &dwByte, nullptr);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"저장 성공", _T("성공"), MB_OK);

}

// 유정 0622 추가 : 에디터에서 그린 라인 불러오기(Initialize에서 호출)
void CLineMgr::Load_Line()
{
	Release();

	HANDLE		hFile = CreateFile(L"../Data/Line2.dat",		// 파일의 경로
		GENERIC_READ,	// 개방 파일의 모드(GENERIC_READ : 읽기 전용 모드)
		NULL, // 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 열려할 때 허가할 것인가, NULL이면 공유하지 않겠다.
		NULL, // 보안속성, NULL인 경우 기본 보안 상태
		OPEN_EXISTING,  // 파일 생성 방식, CREATE_ALWAYS : 파일이 없다면 생성, 파일이 있는 경우 덮어 쓰기, OPEN_EXITING : 파일이 있을 경우에만 열기
		FILE_ATTRIBUTE_NORMAL, // 파일 속성 : FILE_ATTRIBUTE_NORMAL 아무런 속성이 없는 일반적인 파일상태 
		NULL); // 생성될 파일의 속성을 제공할 템플릿 파일, 사용하지 않기 때문에 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"개방 실패", _T("실패"), MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while (true)
	{
		int lineOption = 0;
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		ReadFile(hFile, &lineOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CLine* pLine = new CLine(tInfo);
		pLine->Line_Option(lineOption);
		m_LineList.push_back(pLine);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"불러오기 성공", _T("성공"), MB_OK);
}



void CLineMgr::Initialize()
{
	
}

// 유정 0622 추가
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
			CLine* pLine = new CLine(tInfo);
			pLine->Line_Option(m_LineChange);
			m_LineList.push_back(pLine);
			
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
	if (CKeyMgr::Get_Instance()->Key_Down('1'))
		m_LineChange = 0;
	if (CKeyMgr::Get_Instance()->Key_Down('2'))
		m_LineChange = 1;
	return 0;
}

// 유정 0622 추가
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