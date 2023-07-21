#pragma once

#include "Define.h"

class CBitMap
{
public:
	CBitMap() : m_hMemDC(), m_hBitMap(), m_hOldBmp() {}
	~CBitMap() { Release(); }

public:
	HDC			Get_MemDC() { return m_hMemDC; }

	void		Load_Bmp(const TCHAR* pFilePath);
	void		Load_PNG(const TCHAR* pFilePath);
	void		Release();

private:
	HDC			m_hMemDC;
	HBITMAP		m_hBitMap;
	HBITMAP		m_hOldBmp;

	Gdp::Bitmap* m_pBitMap = nullptr;
	Gdp::Bitmap* m_pOld_BMP = nullptr;

public:
	Gdp::Bitmap* Get_Image() { return m_pBitMap; }
};

// DDB(Device Dependent Bitmap) : ��ġ�� �������� ��Ʈ�� ���� ����, �̹����� ũ��, ���� �� �⺻���� ������ �̹��� �����ͷ� �����Ǿ� �־� �پ��� �ػ��� ��ġ�� �������ϰ� ������ ���Ѵ�. 
// DIB(Device Independet Bitmap) : ��ġ�� �������� ��Ʈ�� ���� ����, DDB�� ���� ���� ���̺�, �ػ� ���� ���� �߰� ������ �����Ƿ� ��ġ�� ���ӵ��� �ʾ� Ȱ�뵵�� �� �������ϰ� ȣȯ���� �پ.

