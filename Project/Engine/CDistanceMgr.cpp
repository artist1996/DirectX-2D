#include "pch.h"
#include "CDistanceMgr.h"

#include "CLevelMgr.h"
#include "CGameObject.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CTransform.h"

CDistanceMgr::CDistanceMgr()
	: m_Player(nullptr)
	, m_Range(false)
{}

CDistanceMgr::~CDistanceMgr()
{}

void CDistanceMgr::Init()
{
	m_Player = CLevelMgr::GetInst()->FindObjectByName(L"PlayerMove");
}

void CDistanceMgr::Tick()
{
	if (!m_Player)
		return;

	m_Range = CalculateDistance();
}

bool CDistanceMgr::CalculateDistance()
{
	CLayer* pLayer = CLevelMgr::GetInst()->GetCurrentLevel()->GetLayer(6);
	const vector<CGameObject*>& vecMonsters = pLayer->GetParentObjects();

	Vec3 vPlayerPos = m_Player->Transform()->GetWorldPos();
	
	for (size_t i = 0; i < vecMonsters.size(); ++i)
	{
		if (nullptr == vecMonsters[i])
			continue;

		Vec3 vMonsterPos = vecMonsters[i]->Transform()->GetWorldPos();

		if (300.f > fabs(vPlayerPos.x - vMonsterPos.x)
			&& 50.f < (vPlayerPos.y - vMonsterPos.y))
		{
			return true;
		}
	}

	return false;
}