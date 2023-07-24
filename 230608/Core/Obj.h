#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void			Set_Info(INFO& value) { m_tInfo = value; }
	const INFO&		Get_Info() const { return m_tInfo; }
	INFO&			Get_Info() { return m_tInfo; }
	RENDERID		Get_RenderID() { return m_eRender; }
	void			Set_Dead() { m_bIsDead = true; }
	bool			Get_Dead() { return m_bIsDead; }

public:
	public:
	virtual void		Initialize()	PURE;
	virtual int			Update()		PURE;
	virtual void		Late_Update()	PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release()					PURE;
	virtual void		Collide(CObj* _pDst)		PURE;

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	bool		m_bIsDead = false;

	float		m_fSpeed;
	RENDERID	m_eRender;
	OBJID		m_eID;

public: 
	void			Update_Rect();
	RECT			Get_Rect() { return m_tRect; }

};

