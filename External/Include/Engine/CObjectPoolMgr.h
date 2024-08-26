#pragma once
#include "singleton.h"

class CObjectPoolMgr :
		public CSingleton<CObjectPoolMgr>
{
	SINGLE(CObjectPoolMgr);
private:
	vector<CGameObject*> m_vecRandomShootPool;

public:
	void Init();

public:
	CGameObject* GetRandomShoot();
	void RetrieveRandomShoot(CGameObject* _Object) { m_vecRandomShootPool.push_back(_Object); }
};

