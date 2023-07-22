#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	const INFO&		Get_Info() const { return m_tInfo; }
	RENDERID		Get_RenderID() { return m_eRender; }
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

	float		m_fSpeed;
	RENDERID	m_eRender;
	OBJID		m_eID;

public: 
	void			Update_Rect();
	RECT			Get_Rect() { return m_tRect; }

};

