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
	Ptr<CPrefab> RandomShootPref = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\skill_randomshoot.pref", L"prefab\\skill_randomshoot.pref");

	Ptr<CPrefab> PlayerEntityPref = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\Player.pref", L"prefab\\PlayerMove.pref");
	Ptr<CPrefab> HeadShotPref = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\headshotground.pref", L"prefab\\headshotground.pref");

	m_Player = PlayerEntityPref->Instantiate();

	m_Player->m_LayerIdx = -1;

	m_vecObjects[(UINT)OBJ_ID::PLAYER].push_back(m_Player);

	for (UINT i = 0; i < 50; ++i)
	{
		CGameObject* pObject = RandomShootPref->Instantiate();
		pObject->m_LayerIdx = -1;
		m_vecObjects[(UINT)OBJ_ID::RANDOMSHOOT].push_back(pObject);
	}

	for (UINT i = 0; i < 10; ++i)
	{
		CGameObject* pObject = HeadShotPref->Instantiate();
		pObject->m_LayerIdx = -1;
		pObject->SetID(OBJ_ID::HEADSHOT);
		m_vecObjects[(UINT)OBJ_ID::HEADSHOT].push_back(pObject);
	}
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
