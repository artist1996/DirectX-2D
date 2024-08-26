#include "pch.h"
#include "CObjectPoolMgr.h"

#include "CAssetMgr.h"
#include "CGameObject.h"

CObjectPoolMgr::CObjectPoolMgr()
{
}

CObjectPoolMgr::~CObjectPoolMgr()
{
	Delete_Vec(m_vecRandomShootPool);
}

void CObjectPoolMgr::Init()
{
	Ptr<CPrefab> RandomShootPref = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\skill_randomshoot.pref", L"prefab\\skill_randomshoot.pref");

	for (UINT i = 0; i < 100; ++i)
	{
		CGameObject* pObject = RandomShootPref->Instantiate();
		pObject->m_LayerIdx = -1;
		m_vecRandomShootPool.push_back(pObject);
	}
}

CGameObject* CObjectPoolMgr::GetRandomShoot()
{
	CGameObject* pObject = m_vecRandomShootPool.back();
	
	m_vecRandomShootPool.pop_back();

	return pObject;
}
