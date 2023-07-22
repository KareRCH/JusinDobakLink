#pragma once

#include "Obj.h"
#include "ObjMgr.h"

template<typename T>
class CObjFactory
{
public:
	CObjFactory(){}
	~CObjFactory(){}

public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(OBJID eID, INFO& tInfo)
	{
		CObj*		pObj = new T;
		pObj->Set_Info(tInfo);
		pObj->Initialize();
		

		CObjMgr::Get_Instance()->Add_Object(eID, pObj);

		return pObj;
	}


};

