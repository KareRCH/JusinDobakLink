#include "stdafx.h"
#include "BmpMgr.h"

#include "Camera.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}

void CBmpMgr::Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImgKey));

	if (iter == m_mapBit.end())
	{
		CBitMap* pBmp = new CBitMap;
		pBmp->Load_Bmp(pFilePath);

		TCHAR* sText = new TCHAR[100];
		lstrcpy(sText, pImgKey);
		m_mapBit.insert({ sText, pBmp });
	}
}

void CBmpMgr::Insert_PNG(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImgKey));

	if (iter == m_mapBit.end())
	{
		CBitMap* pBmp = new CBitMap;
		pBmp->Load_PNG(pFilePath);

		TCHAR* sText = new TCHAR[100];
		lstrcpy(sText, pImgKey);
		m_mapBit.insert({ sText, pBmp });
	}
}

HDC CBmpMgr::Find_Img(const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

CBitMap* CBmpMgr::Find_CBitMap(const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second;
}


void CBmpMgr::Draw_BMP(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, bool bAllowScroll)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(pImgKey);

	int		iScrollX = (int)CCamera::Get_Instance()->Get_WindowPos().x;
	int		iScrollY = (int)CCamera::Get_Instance()->Get_WindowPos().y;

	GdiTransparentBlt(hDC,
		(int)tInfo.vPos.x - (int)tFrame.iOffsetX - iScrollX * (int)bAllowScroll,
		(int)tInfo.vPos.y - (int)tFrame.iOffsetY - iScrollY * (int)bAllowScroll,
		tFrame.iWidth, tFrame.iHeight,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		(tFrame.iFrameStart + tFrame.iFrameCur) * tFrame.iWidth, 0,
		tFrame.iWidth, tFrame.iHeight,
		RGB(255, 255, 255)); // 제거하고자 하는 색상
}

void CBmpMgr::Draw_BMP(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, int srcx, int srcy, bool bAllowScroll)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(pImgKey);

	int		iScrollX = (int)CCamera::Get_Instance()->Get_WindowPos().x;
	int		iScrollY = (int)CCamera::Get_Instance()->Get_WindowPos().y;

	GdiTransparentBlt(hDC,
		(int)tInfo.vPos.x - (int)tFrame.iOffsetX - iScrollX * (int)bAllowScroll,
		(int)tInfo.vPos.y - (int)tFrame.iOffsetY - iScrollY * (int)bAllowScroll,
		tFrame.iWidth, tFrame.iHeight,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		srcx, srcy,
		tFrame.iWidth, tFrame.iHeight,
		RGB(255, 255, 255)); // 제거하고자 하는 색상
}

void CBmpMgr::Draw_BMP(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, int srcx, int srcy, int src_width, int src_height, bool bAllowScroll)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(pImgKey);

	int		iScrollX = (int)CCamera::Get_Instance()->Get_WindowPos().x;
	int		iScrollY = (int)CCamera::Get_Instance()->Get_WindowPos().y;

	GdiTransparentBlt(hDC,
		(int)tInfo.vPos.x - (int)tFrame.iOffsetX - iScrollX * (int)bAllowScroll,
		(int)tInfo.vPos.y - (int)tFrame.iOffsetY - iScrollY * (int)bAllowScroll,
		tFrame.iWidth, tFrame.iHeight,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		srcx, srcy,
		src_width, src_height,
		RGB(255, 255, 255)); // 제거하고자 하는 색상
}

void CBmpMgr::Draw_BMP_Strip(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, bool bAllowScroll)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(pImgKey);

	int		iScrollX = (int)CCamera::Get_Instance()->Get_WindowPos().x;
	int		iScrollY = (int)CCamera::Get_Instance()->Get_WindowPos().y;

	GdiTransparentBlt(hDC,
		(int)tInfo.vPos.x - (int)tFrame.iOffsetX - iScrollX * (int)bAllowScroll,
		(int)tInfo.vPos.y - (int)tFrame.iOffsetY - iScrollY * (int)bAllowScroll,
		tFrame.iWidth, tFrame.iHeight,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		(tFrame.iFrameStart + tFrame.iFrameCur) * tFrame.iWidth, 0,
		tFrame.iWidth, tFrame.iHeight,
		RGB(255, 255, 255)); // 제거하고자 하는 색상
}

void CBmpMgr::Draw_BMP(HDC hDC, INFO tInfo, bool bAllowScroll)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(tInfo.tFrameTSet.Get_StrFrameKey());

	int		iScrollX = (int)CCamera::Get_Instance()->Get_WindowPos().x;
	int		iScrollY = (int)CCamera::Get_Instance()->Get_WindowPos().y;

	FRAME& tFrame = (*tInfo.tFrameTSet);

	GdiTransparentBlt(hDC,
		(int)tInfo.vPos.x - (int)tFrame.iOffsetX - iScrollX * (int)bAllowScroll,
		(int)tInfo.vPos.y - (int)tFrame.iOffsetY - iScrollY * (int)bAllowScroll,
		tFrame.iWidth, tFrame.iHeight,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		(tFrame.iFrameStart + tFrame.iFrameCur) * tFrame.iWidth, 0,
		tFrame.iWidth, tFrame.iHeight,
		RGB(255, 255, 255)); // 제거하고자 하는 색상
}

void CBmpMgr::Draw_BMP(HDC hDC, INFO tInfo, int srcx, int srcy, bool bAllowScroll)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(tInfo.tFrameTSet.Get_StrFrameKey());

	int		iScrollX = (int)CCamera::Get_Instance()->Get_WindowPos().x;
	int		iScrollY = (int)CCamera::Get_Instance()->Get_WindowPos().y;

	FRAME& tFrame = (*tInfo.tFrameTSet);

	GdiTransparentBlt(hDC,
		(int)tInfo.vPos.x - (int)tFrame.iOffsetX - iScrollX * (int)bAllowScroll,
		(int)tInfo.vPos.y - (int)tFrame.iOffsetY - iScrollY * (int)bAllowScroll,
		tFrame.iWidth, tFrame.iHeight,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		srcx, srcy,
		tFrame.iWidth, tFrame.iHeight,
		RGB(255, 255, 255)); // 제거하고자 하는 색상
}

void CBmpMgr::Draw_BMP(HDC hDC, INFO tInfo, int srcx, int srcy, int src_width, int src_height, bool bAllowScroll)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(tInfo.tFrameTSet.Get_StrFrameKey());

	int		iScrollX = (int)CCamera::Get_Instance()->Get_WindowPos().x;
	int		iScrollY = (int)CCamera::Get_Instance()->Get_WindowPos().y;

	FRAME& tFrame = (*tInfo.tFrameTSet);

	GdiTransparentBlt(hDC,
		(int)tInfo.vPos.x - (int)tFrame.iOffsetX - iScrollX * (int)bAllowScroll,
		(int)tInfo.vPos.y - (int)tFrame.iOffsetY - iScrollY * (int)bAllowScroll,
		tFrame.iWidth, tFrame.iHeight,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		srcx, srcy,
		src_width, src_height,
		RGB(255, 255, 255)); // 제거하고자 하는 색상
}

void CBmpMgr::Draw_PNG_Strip(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, bool bAllowScroll)
{
	// Strip 형태의 PNG를 표시하는데 쓰인다.
	// 단일용 PNG는 따로 관리한다.

	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(pImgKey);
	if (!pBitMap) return;
	Gdp::Bitmap* pImage = pBitMap->Get_Image();
	Gdp::Graphics g(hDC);

	float fScrollX = CCamera::Get_Instance()->Get_WindowPos().x;
	float fScrollY = CCamera::Get_Instance()->Get_WindowPos().y;

	g.TranslateTransform(tInfo.vPos.x - fScrollX * (float)bAllowScroll, tInfo.vPos.y - fScrollY * (float)bAllowScroll);
	g.RotateTransform(tInfo.fAngle);
	g.ScaleTransform(tInfo.vSize.x, tInfo.vSize.y);

	// 쉽샵 버그 땜에 복잡한 식으로 잡은 모습이다.
	g.DrawImage(
		pImage, (-(tFrame.iOffsetX)), (-(tFrame.iOffsetY)),
		((tFrame.iFrameStart + tFrame.iFrameCur) * tFrame.iWidth - 1),
		((tFrame.iMotion * tFrame.iHeight)),
		tFrame.iWidth, tFrame.iHeight,
		Gdp::UnitPixel
	);
}

void CBmpMgr::Draw_PNG_StripAlpha(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, float fOpacity, bool bAllowScroll)
{
	// Strip 형태의 PNG를 표시하는데 쓰인다.
	// 단일용 PNG는 따로 관리한다.

	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(pImgKey);
	if (!pBitMap) return;
	Gdp::Bitmap* pImage = pBitMap->Get_Image();
	Gdp::Graphics g(hDC);

	float fScrollX = CCamera::Get_Instance()->Get_WindowPos().x;
	float fScrollY = CCamera::Get_Instance()->Get_WindowPos().y;

	g.TranslateTransform(tInfo.vPos.x - fScrollX * (float)bAllowScroll, tInfo.vPos.y - fScrollY * (float)bAllowScroll);
	g.RotateTransform(tInfo.fAngle);
	g.ScaleTransform(tInfo.vSize.x, tInfo.vSize.y);

	if (fOpacity < 1.f)
	{
		Gdp::ColorMatrix colorMatrix = {
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, fOpacity, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		Gdp::ImageAttributes attr;
		attr.SetColorMatrix(&colorMatrix, Gdp::ColorMatrixFlagsDefault, Gdp::ColorAdjustTypeBitmap);

		Gdp::Rect rc = {
			-(tFrame.iOffsetX), -(tFrame.iOffsetY),
			tFrame.iWidth, tFrame.iHeight
		};

		// 쉽샵 버그 땜에 복잡한 식으로 잡은 모습이다.
		g.DrawImage(
			pImage, rc,
			(tFrame.iFrameStart + tFrame.iFrameCur) * tFrame.iWidth - 1,
			(tFrame.iMotion * tFrame.iHeight),
			tFrame.iWidth,
			tFrame.iHeight,
			Gdp::UnitPixel,
			&attr
		);
	}
	else
	{
		// 쉽샵 버그 땜에 복잡한 식으로 잡은 모습이다.
		g.DrawImage(
			pImage, -(tFrame.iOffsetX), -(tFrame.iOffsetY),
			(tFrame.iFrameStart + tFrame.iFrameCur) * tFrame.iWidth - 1,
			tFrame.iMotion * tFrame.iHeight,
			tFrame.iWidth, tFrame.iHeight,
			Gdp::UnitPixel
		);
	}
}

void CBmpMgr::Draw_PNG(HDC hDC, INFO& tInfo, bool bAllowScroll)
{
	// Strip 형태의 PNG를 표시하는데 쓰인다.
	// 단일용 PNG는 따로 관리한다.

	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(tInfo.tFrameTSet.Get_StrFrameKey());
	if (!pBitMap) return;
	Gdp::Bitmap* pImage = pBitMap->Get_Image();
	Gdp::Graphics g(hDC);
	auto& tFrame = (*tInfo.tFrameTSet);

	float fScrollX = CCamera::Get_Instance()->Get_WindowPos().x;
	float fScrollY = CCamera::Get_Instance()->Get_WindowPos().y;

	g.TranslateTransform(tInfo.vPos.x - fScrollX * (float)bAllowScroll, tInfo.vPos.y - fScrollY * (float)bAllowScroll);
	g.RotateTransform(tInfo.fAngle);
	g.ScaleTransform(tInfo.vSize.x, tInfo.vSize.y);

	g.DrawImage(
		pImage, -(tFrame.iOffsetX), -(tFrame.iOffsetY),
		0, 0, pImage->GetWidth(), pImage->GetHeight(),
		Gdp::UnitPixel
	);
}

void CBmpMgr::Draw_PNG(HDC hDC, INFO& tInfo, int srcx, int srcy, bool bAllowScroll)
{
	// Strip 형태의 PNG를 표시하는데 쓰인다.
	// 단일용 PNG는 따로 관리한다.

	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(tInfo.tFrameTSet.Get_StrFrameKey());
	if (!pBitMap) return;
	Gdp::Bitmap* pImage = pBitMap->Get_Image();
	Gdp::Graphics g(hDC);
	auto& tFrame = (*tInfo.tFrameTSet);

	float fScrollX = CCamera::Get_Instance()->Get_WindowPos().x;
	float fScrollY = CCamera::Get_Instance()->Get_WindowPos().y;

	g.TranslateTransform(tInfo.vPos.x - fScrollX * (float)bAllowScroll, tInfo.vPos.y - fScrollY * (float)bAllowScroll);
	g.RotateTransform(tInfo.fAngle);
	g.ScaleTransform(tInfo.vSize.x, tInfo.vSize.y);

	g.DrawImage(
		pImage, -(tFrame.iOffsetX), -(tFrame.iOffsetY),
		srcx, srcy, pImage->GetWidth(), pImage->GetHeight(),
		Gdp::UnitPixel
	);
}

void CBmpMgr::Draw_PNG(HDC hDC, INFO& tInfo, int srcx, int srcy, int src_width, int src_height, bool bAllowScroll)
{
	// Strip 형태의 PNG를 표시하는데 쓰인다.
	// 단일용 PNG는 따로 관리한다.

	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(tInfo.tFrameTSet.Get_StrFrameKey());
	if (!pBitMap) return;
	Gdp::Bitmap* pImage = pBitMap->Get_Image();
	Gdp::Graphics g(hDC);
	auto& tFrame = (*tInfo.tFrameTSet);

	float fScrollX = CCamera::Get_Instance()->Get_WindowPos().x;
	float fScrollY = CCamera::Get_Instance()->Get_WindowPos().y;

	g.TranslateTransform(tInfo.vPos.x - fScrollX * (float)bAllowScroll, tInfo.vPos.y - fScrollY * (float)bAllowScroll);
	g.RotateTransform(tInfo.fAngle);
	g.ScaleTransform(tInfo.vSize.x, tInfo.vSize.y);

	g.DrawImage(
		pImage, -(tFrame.iOffsetX), -(tFrame.iOffsetY),
		srcx, srcy, src_width, src_height,
		Gdp::UnitPixel
	);
}

void CBmpMgr::Draw_PNG(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, bool bAllowScroll)
{
	// Strip 형태의 PNG를 표시하는데 쓰인다.
	// 단일용 PNG는 따로 관리한다.

	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(pImgKey);
	if (!pBitMap) return;
	Gdp::Bitmap* pImage = pBitMap->Get_Image();
	Gdp::Graphics g(hDC);

	float fScrollX = CCamera::Get_Instance()->Get_WindowPos().x;
	float fScrollY = CCamera::Get_Instance()->Get_WindowPos().y;

	g.TranslateTransform(tInfo.vPos.x - fScrollX * (float)bAllowScroll, tInfo.vPos.y - fScrollY * (float)bAllowScroll);
	g.RotateTransform(tInfo.fAngle);
	g.ScaleTransform(tInfo.vSize.x, tInfo.vSize.y);

	g.DrawImage(
		pImage, -(tFrame.iOffsetX), -(tFrame.iOffsetY),
		0, 0, pImage->GetWidth(), pImage->GetHeight(),
		Gdp::UnitPixel
	);
}

void CBmpMgr::Draw_PNG(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, int srcx, int srcy, bool bAllowScroll)
{
	// 단일용 PNG는 따로 관리한다.

	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(pImgKey);
	if (!pBitMap) return;
	Gdp::Bitmap* pImage = pBitMap->Get_Image();
	Gdp::Graphics g(hDC);

	float fScrollX = CCamera::Get_Instance()->Get_WindowPos().x;
	float fScrollY = CCamera::Get_Instance()->Get_WindowPos().y;

	g.TranslateTransform(tInfo.vPos.x - fScrollX * (float)bAllowScroll, tInfo.vPos.y - fScrollY * (float)bAllowScroll);
	g.RotateTransform(tInfo.fAngle);
	g.ScaleTransform(tInfo.vSize.x, tInfo.vSize.y);

	g.DrawImage(
		pImage, -(tFrame.iOffsetX), -(tFrame.iOffsetY),
		srcx, srcy, tFrame.iWidth, tFrame.iHeight,
		Gdp::UnitPixel
	);
}

void CBmpMgr::Draw_PNG(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, int srcx, int srcy, int src_width, int src_height, bool bAllowScroll)
{
	// 단일용 PNG는 따로 관리한다.

	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(pImgKey);
	if (!pBitMap) return;
	Gdp::Bitmap* pImage = pBitMap->Get_Image();
	Gdp::Graphics g(hDC);

	float fScrollX = CCamera::Get_Instance()->Get_WindowPos().x;
	float fScrollY = CCamera::Get_Instance()->Get_WindowPos().y;

	g.TranslateTransform(tInfo.vPos.x - fScrollX * (float)bAllowScroll, tInfo.vPos.y - fScrollY * (float)bAllowScroll);
	g.RotateTransform(tInfo.fAngle);
	g.ScaleTransform(tInfo.vSize.x, tInfo.vSize.y);

	g.DrawImage(
		pImage, -(tFrame.iOffsetX), -(tFrame.iOffsetY),
		srcx, srcy, src_width, src_height,
		Gdp::UnitPixel
	);
}

void CBmpMgr::Draw_PNG_Alpha(HDC hDC, const TCHAR* pImgKey, INFO tInfo, FRAME tFrame, int srcx, int srcy, float fOpacity, bool bAllowScroll)
{
	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(pImgKey);
	if (!pBitMap) return;
	Gdp::Bitmap* pImage = pBitMap->Get_Image();
	Gdp::Graphics g(hDC);

	float fScrollX = CCamera::Get_Instance()->Get_WindowPos().x;
	float fScrollY = CCamera::Get_Instance()->Get_WindowPos().y;

	g.TranslateTransform(float(int(tInfo.vPos.x - fScrollX * (float)bAllowScroll)),
		float(int(tInfo.vPos.y - fScrollY * (float)bAllowScroll)));

	if (fOpacity < 1.f)
	{
		Gdp::ColorMatrix colorMatrix = {
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, fOpacity, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		Gdp::ImageAttributes attr;
		attr.SetColorMatrix(&colorMatrix, Gdp::ColorMatrixFlagsDefault, Gdp::ColorAdjustTypeBitmap);

		Gdp::Rect rc = {
			-(tFrame.iOffsetX), -(tFrame.iOffsetY),
			tFrame.iWidth, tFrame.iHeight
		};

		// 쉽샵 버그 땜에 복잡한 식으로 잡은 모습이다.
		g.DrawImage(
			pImage, rc,
			srcx, srcy,
			tFrame.iWidth, tFrame.iHeight,
			Gdp::UnitPixel,
			&attr
		);
	}
	else
	{
		// 쉽샵 버그 땜에 복잡한 식으로 잡은 모습이다.
		g.DrawImage(
			pImage, -(tFrame.iOffsetX), -(tFrame.iOffsetY),
			srcx, srcy, tFrame.iWidth, tFrame.iHeight,
			Gdp::UnitPixel
		);
	}
}

void CBmpMgr::Draw_Test_Circle(HDC hDC, INFO tInfo, int iSize)
{
	MoveToEx(hDC, (int)tInfo.vPos.x, (int)tInfo.vPos.y, NULL);
	Ellipse(hDC, (int)tInfo.vPos.x - iSize, (int)tInfo.vPos.y - iSize, (int)tInfo.vPos.x + iSize, (int)tInfo.vPos.y + iSize);
}

void CBmpMgr::Draw_Text_Circle_Vec3(HDC hDC, D3DXVECTOR3 vecPos, int iSize, bool bAllowScroll)
{
	float fScrollX = CCamera::Get_Instance()->Get_WindowPos().x;
	float fScrollY = CCamera::Get_Instance()->Get_WindowPos().y;

	MoveToEx(hDC, (int)vecPos.x - (int)fScrollX * (int)bAllowScroll,
		(int)vecPos.y + (int)vecPos.z - (int)fScrollY * (int)bAllowScroll,
		NULL);
	Ellipse(hDC,
		(int)vecPos.x - iSize - (int)fScrollX * (int)bAllowScroll,
		(int)vecPos.y - (int)vecPos.z - iSize - (int)fScrollY * (int)bAllowScroll,
		(int)vecPos.x + iSize - (int)fScrollX * (int)bAllowScroll,
		(int)vecPos.y - (int)vecPos.z + iSize - (int)fScrollY * (int)bAllowScroll);
}
