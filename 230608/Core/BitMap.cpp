#include "stdafx.h"
#include "BitMap.h"

void CBitMap::Load_Bmp(const TCHAR* pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : 이미지를 매번 그릴 때마다 불러오기를 하면 연산이 커지기 때문에 이를 효율적으로 진행하기 위해 화면 dc와 호환되는 dc를 할당한다.

	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	m_hBitMap = (HBITMAP)LoadImage(NULL,	// 프로그램의 인스턴스 핸들, 이미지는 프로그램에서 얻어오지 않고 파일 입출력을 통해 얻어올 것이어서 NULL
		pFilePath,   // 파일의 경로
		IMAGE_BITMAP, // 어떤 타입으로 읽어올 것인가
		0,		// 이미지의 가로 길이
		0,		// 이미지의 세로 길이
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : 파일로부터 이미지를 읽어들임 / LR_CREATEDIBSECTION : 읽어온 파일을 DIB형태로 변환

	// SelectObject 함수는 지정된 DC(디바이스 컨텍스트)로 개체를 선택합니다.새 개체는 동일한 형식의 이전 개체를 대체합니다.
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
}

void CBitMap::Load_PNG(const TCHAR* pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : 이미지를 매번 그릴 때마다 불러오기를 하면 연산이 커지기 때문에 이를 효율적으로 진행하기 위해 화면 dc와 호환되는 dc를 할당한다.
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	// SelectObject 함수는 지정된 DC(디바이스 컨텍스트)로 개체를 선택합니다. 새 개체는 동일한 형식의 이전 개체를 대체합니다.
	m_pBitMap = Gdp::Bitmap::FromFile(pFilePath);
	m_pOld_BMP = static_cast<Gdp::Bitmap*>(SelectObject(m_hMemDC, m_hBitMap));
}

void CBitMap::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}
