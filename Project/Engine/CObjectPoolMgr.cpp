#include "pch.h"
#include "CObjectPoolMgr.h"

#include "CAssetMgr.h"
#include "CGameObject.h"

#include "CTransform.h"

CObjectPoolMgr::CObjectPoolMgr()
	: m_PlayerEntity(nullptr)
	, m_PlayerMove(nullptr)
	, m_PlayerJump(nullptr)
{
}

CObjectPoolMgr::~CObjectPoolMgr()
{
	for (UINT i = 3; i < (UINT)OBJ_ID::END; ++i)
	{
		Delete_Vec(m_vecObjects[i]);
	}
}

void CObjectPoolMgr::Init()
{
	Ptr<CPrefab> RandomShootPref = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\skill_randomshoot.pref", L"prefab\\skill_randomshoot.pref");
	Ptr<CPrefab> PlayerMovePref = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\PlayerMove.pref", L"prefab\\PlayerMove.pref");
	Ptr<CPrefab> PlayerEntityPref = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\Player.pref", L"prefab\\Player.pref");
	Ptr<CPrefab> PlayerJumpPref = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\PlayerJump.pref", L"prefab\\PlayerJump.pref");
	Ptr<CPrefab> HeadShotPref = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\skill_headshot.pref", L"prefab\\skill_headshot.pref");

	m_PlayerEntity = PlayerEntityPref->Instantiate();
	m_PlayerMove = PlayerMovePref->Instantiate();
	m_PlayerJump = PlayerJumpPref->Instantiate();

	m_PlayerEntity->m_LayerIdx = -1;
	m_PlayerMove->m_LayerIdx = -1;
	m_PlayerJump->m_LayerIdx = -1;

	m_PlayerMove->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));

	m_vecObjects[(UINT)OBJ_ID::PLAYERMOVE].push_back(m_PlayerMove);
	m_vecObjects[(UINT)OBJ_ID::PLAYER].push_back(m_PlayerEntity);
	m_vecObjects[(UINT)OBJ_ID::PLAYERJUMP].push_back(m_PlayerJump);

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
