#pragma once
#include "singleton.h"

class CObjectPoolMgr :
		public CSingleton<CObjectPoolMgr>
{
	SINGLE(CObjectPoolMgr);
private:
	vector<CGameObject*> m_vecObjects[(UINT)OBJ_ID::END];

	CGameObject* m_PlayerEntity;
	CGameObject* m_PlayerMove;
	CGameObject* m_PlayerJump;

public:
	void Init();

public:
	CGameObject* GetObj(OBJ_ID _ID);
	CGameObject* GetPlayerEntity() { return m_PlayerEntity; }
	CGameObject* GetPlayerMove()   { return m_PlayerMove; }
	CGameObject* GetPlayerJump()   { return m_PlayerJump; }
	void RetrieveObject(OBJ_ID _ID, CGameObject* _Object);
};

