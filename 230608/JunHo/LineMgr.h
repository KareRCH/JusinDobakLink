#pragma once

#include "Line.h"
//#include "ScrollMgr.h"	// ���� 0622 �߰�

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	bool		Collision_Line(INFO& m_tInfo, CLine** pLine, float* pY, float* pfGradient);
	void		Save_Line();
	void		Load_Line();	// ���� 0622 �߰� : �����Ϳ��� �׸� ���� �ҷ�����(Initialize���� ȣ��)
	bool		DashCheck(float fX, int nDrection);
public:
	void		Initialize();
	int			Update();		// ���� 0622 �߰�
	void		Late_Update();	// ���� 0622 �߰�
	void		Render(HDC hDC);
	void		Release();
public:
	static CLineMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CLineMgr;
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
	list<CLine*>			m_LineList;
	LINEPOINT				m_tLintPoint[2];	// ���� 0622 �߰�

	static CLineMgr* m_pInstance;
	int				m_LineChange = 0;
private:
	bool m_bIsDraw; // 0622 ��û �߰�
};