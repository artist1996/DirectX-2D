#include "pch.h"
#include "CDistanceMgr.h"

#include "CLevelMgr.h"
#include "CGameObject.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CTransform.h"
#include "CCollider2D.h"

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
	if (PAUSE == CLevelMgr::GetInst()->GetCurrentLevel()->GetState()
		|| STOP == CLevelMgr::GetInst()->GetCurrentLevel()->GetState())
		return false;

	CLayer* pLayer = CLevelMgr::GetInst()->GetCurrentLevel()->GetLayer(6);
	const vector<CGameObject*>& vecMonsters = pLayer->GetParentObjects();

	Vec3 vPlayerPos = m_Player->Collider2D()->GetWorldPos();
	Vec3 vScale		= m_Player->Collider2D()->GetScale();
	
	float fPlayerY = vPlayerPos.y - vScale.y * 0.5f;

	OBJ_DIR Dir = m_Player->GetDir();

	for (size_t i = 0; i < vecMonsters.size(); ++i)
	{
		if (nullptr == vecMonsters[i])
			continue;

		Vec3 vMonsterColPos = vecMonsters[i]->Collider2D()->GetWorldPos();
		Vec3 vMonsterScale = vecMonsters[i]->Collider2D()->GetScale();

		float vMonsterPosY = vMonsterColPos.y - vMonsterScale.y * 0.5f;

		if (500.f > fabs(vPlayerPos.x - vMonsterColPos.x)
			&& 40.f > fabs(fPlayerY - vMonsterPosY))
		{		
			return true;
		}
	}

	return false;
}