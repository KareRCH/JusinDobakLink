#include "stdafx.h"
#include "BitMap.h"

void CBitMap::Load_Bmp(const TCHAR* pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : �̹����� �Ź� �׸� ������ �ҷ����⸦ �ϸ� ������ Ŀ���� ������ �̸� ȿ�������� �����ϱ� ���� ȭ�� dc�� ȣȯ�Ǵ� dc�� �Ҵ��Ѵ�.

	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	m_hBitMap = (HBITMAP)LoadImage(NULL,	// ���α׷��� �ν��Ͻ� �ڵ�, �̹����� ���α׷����� ������ �ʰ� ���� ������� ���� ���� ���̾ NULL
		pFilePath,   // ������ ���
		IMAGE_BITMAP, // � Ÿ������ �о�� ���ΰ�
		0,		// �̹����� ���� ����
		0,		// �̹����� ���� ����
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : ���Ϸκ��� �̹����� �о���� / LR_CREATEDIBSECTION : �о�� ������ DIB���·� ��ȯ

	// SelectObject �Լ��� ������ DC(����̽� ���ؽ�Ʈ)�� ��ü�� �����մϴ�.�� ��ü�� ������ ������ ���� ��ü�� ��ü�մϴ�.
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
}

void CBitMap::Load_PNG(const TCHAR* pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : �̹����� �Ź� �׸� ������ �ҷ����⸦ �ϸ� ������ Ŀ���� ������ �̸� ȿ�������� �����ϱ� ���� ȭ�� dc�� ȣȯ�Ǵ� dc�� �Ҵ��Ѵ�.
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	// SelectObject �Լ��� ������ DC(����̽� ���ؽ�Ʈ)�� ��ü�� �����մϴ�. �� ��ü�� ������ ������ ���� ��ü�� ��ü�մϴ�.
	m_pBitMap = Gdp::Bitmap::FromFile(pFilePath);
	m_pOld_BMP = static_cast<Gdp::Bitmap*>(SelectObject(m_hMemDC, m_hBitMap));
}

void CBitMap::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}
