#pragma once
#include "singleton.h"

class CObjectPoolMgr :
		public CSingleton<CObjectPoolMgr>
{
	SINGLE(CObjectPoolMgr);
private:
	vector<CGameObject*> m_vecObjects[(UINT)OBJ_ID::END];

	CGameObject* m_Player;

public:
	void Init();

public:
	CGameObject* GetObj(OBJ_ID _ID);
	CGameObject* GetPlayerEntity() { return m_Player; }
	void RetrieveObject(OBJ_ID _ID, CGameObject* _Object);
};

