#pragma once

#include "BitMap.h"

class CBmpMgr
{
private:
	CBmpMgr();
	~CBmpMgr();

public:
	void		Release();
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	void		Insert_PNG(const TCHAR* pFilePath, const TCHAR* pImgKey);

	HDC			Find_Img(const TCHAR* pImgKey);			// 비트맵용
	CBitMap*	Find_CBitMap(const TCHAR* pImgKey);		// PNG용


	// BMP 계열 드로우
	void		Draw_BMP(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, bool bAllowScroll = true);
	void		Draw_BMP(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, int srcx, int srcy, bool bAllowScroll = true);
	void		Draw_BMP(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, int srcx, int srcy, int src_width, int src_height, bool bAllowScroll = true);
	void		Draw_BMP_Strip(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, bool bAllowScroll);

	// PNG 계열 드로우
	void		Draw_PNG(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, bool bAllowScroll = true);
	void		Draw_PNG(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, int srcx, int srcy, bool bAllowScroll = true);
	void		Draw_PNG(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, int srcx, int srcy, int src_width, int src_height, bool bAllowScroll = true);
	void		Draw_PNG_Alpha(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, int srcx, int srcy, float fOpacity, bool bAllowScroll = true);

	void		Draw_PNG_Strip(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, bool bAllowScroll = true);
	void		Draw_PNG_StripAlpha(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, float fOpacity, bool bAllowScroll = true);

	// 디버그 계열
	void		Draw_Test_Circle(HDC hDC, INFO tInfo, int iSize = 3);
	void		Draw_Text_Circle_Vec3(HDC hDC, D3DXVECTOR3 vecPos, int iSize = 3, bool bAllowScroll = true);

public:
	static CBmpMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CBmpMgr;
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
	static CBmpMgr* m_pInstance;
	map<const TCHAR*, CBitMap*>			m_mapBit;

};

