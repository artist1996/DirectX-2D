#include "pch.h"
#include "CMeltKnightScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CObjectPoolMgr.h>

#include <States/CMeltKnightIdleState.h>
#include <States/CMeltKnightTraceState.h>
#include <States/CMeltKnightAttackState.h>
#include <States/CMeltKnightStandByState.h>
#include <States/CMeltKnightDeadState.h>

CMeltKnightScript::CMeltKnightScript()
	: CScript(SCRIPT_TYPE::MELTKNIGHTSCRIPT)
	, m_Info{}
	, m_Dead(false)
{
}

CMeltKnightScript::~CMeltKnightScript()
{
}

void CMeltKnightScript::InitInfo()
{
	m_Info.MaxHP = 600;
	m_Info.HP = m_Info.MaxHP;
	m_Info.Defense = 0;
	m_Info.MinAttack = 10;
	m_Info.MaxAttack = 20;

	GetOwner()->SetInfo(m_Info);
}

void CMeltKnightScript::Begin()
{
	InitInfo();

	FSM()->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, CObjectPoolMgr::GetInst()->GetPlayerEntity());
	FSM()->AddState(L"Idle", new CMeltKnightIdleState);
	FSM()->AddState(L"Trace", new CMeltKnightTraceState);
	FSM()->AddState(L"Attack", new CMeltKnightAttackState);
	FSM()->AddState(L"StandBy", new CMeltKnightStandByState);
	FSM()->AddState(L"Dead", new CMeltKnightDeadState);

	FSM()->ChangeState(L"Idle");
}

void CMeltKnightScript::Tick()
{
	m_Info = GetOwner()->GetInfo();

	if (0 >= m_Info.HP && !m_Dead)
	{
		FSM()->ChangeState(L"Dead");
		m_Dead = true;
		m_Info.bDead = true;
		CGameObject* pObject = CLevelMgr::GetInst()->FindObjectByName(L"MonsterHUD");
		pObject->SetActive(false);
	}
}

void CMeltKnightScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (7 == _OtherObj->GetLayerIdx())
	{
		CGameObject* pObject = CLevelMgr::GetInst()->FindObjectByName(L"MonsterHUD");
		pObject->SetActive(true);
		pObject->SetTarget(GetOwner());
	}
}

void CMeltKnightScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CMeltKnightScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}
