#include "pch.h"
#include "CObjectPoolMgr.h"

#include "CAssetMgr.h"
#include "CGameObject.h"

#include "CTransform.h"

CObjectPoolMgr::CObjectPoolMgr()
	: m_Player(nullptr)
{
}

CObjectPoolMgr::~CObjectPoolMgr()
{
	for (UINT i = 1; i < (UINT)OBJ_ID::END; ++i)
	{
		Delete_Vec(m_vecObjects[i]);
	}

	//SAFE_DELETE(m_Player);
}

void CObjectPoolMgr::Init()
{
	Ptr<CPrefab> PlayerEntityPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\PlayerMove.pref");
	m_Player = PlayerEntityPref->Instantiate();

	m_Player->m_LayerIdx = -1;

	m_vecObjects[(UINT)OBJ_ID::PLAYER].push_back(m_Player);

}

CGameObject* CObjectPoolMgr::GetObj(OBJ_ID _ID)
{
	CGameObject* pObject = m_vecObjects[(UINT)_ID].back();

	m_vecObjects[(UINT)_ID].pop_back();

	return pObject;
}

void CObjectPoolMgr::RetrieveObject(OBJ_ID _ID, CGameObject* _Object)
{
	m_vecObjects[(UINT)_ID].push_back(_Object);
}
