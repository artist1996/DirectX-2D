#include "pch.h"
#include "CMeltKnightScript.h"

#include <Engine/CObjectPoolMgr.h>

#include <States/CMeltKnightIdleState.h>
#include <States/CMeltKnightTraceState.h>
#include <States/CMeltKnightAttackState.h>
#include <States/CMeltKnightStandByState.h>
#include <States/CMeltKnightDeadState.h>

CMeltKnightScript::CMeltKnightScript()
	: CScript(SCRIPT_TYPE::MELTKNIGHTSCRIPT)
	, m_Info{}
{
	InitInfo();
}

CMeltKnightScript::~CMeltKnightScript()
{
}

void CMeltKnightScript::InitInfo()
{
	m_Info.MaxHP = 100;
	m_Info.HP = m_Info.MaxHP;
	m_Info.Defense = 0;
	m_Info.MinAttack = 10;
	m_Info.MaxAttack = 20;
}

void CMeltKnightScript::Begin()
{
	//GetOwner()->AddComponent(new CFSM);


	FSM()->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, CObjectPoolMgr::GetInst()->GetPlayerEntity());
	FSM()->AddState(L"Idle", new CMeltKnightIdleState);
	FSM()->AddState(L"Trace", new CMeltKnightTraceState);
	FSM()->AddState(L"Attack", new CMeltKnightAttackState);
	FSM()->AddState(L"StandBy", new CMeltKnightStandByState);
	FSM()->AddState(L"Dead", new CMeltKnightDeadState);

	FSM()->ChangeState(L"Idle");

	Collider2D()->SetActive(true);
}

void CMeltKnightScript::Tick()
{
	if (0 >= m_Info.HP)
		FSM()->ChangeState(L"Dead");
}

void CMeltKnightScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (7 == _OtherObj->GetLayerIdx())
	{
		m_Info.HP -= 10;
	}

	if (3 == _OtherObj->GetLayerIdx())
	{
		Vec3 vPos = _OwnCollider->GetWorldPos();
		Vec3 vScale = Transform()->GetWorldScale();
		Vec3 vOtherPos = _OtherCollider->GetWorldPos();
		Vec3 vOtherScale = _OtherObj->Transform()->GetWorldScale();

		bool* bMoveable = GetOwner()->GetMoveable();

		if (vOtherPos.x + vOtherScale.x * 0.5f < vPos.x - vScale.x * 0.5f + 10.f
			&& vOtherPos.y + vOtherScale.y * 0.5f > vPos.y - vScale.y * 0.5f
			&& vOtherPos.y - vOtherScale.y * 0.5f < vPos.y + vScale.y * 0.5f)
		{
			GetOwner()->SetMoveable(PLATFORM_TYPE::RIGHT, false);
		}

		else if (vOtherPos.x - vOtherScale.x * 0.5f > vPos.x + vScale.x * 0.5f - 10.f
			&& vOtherPos.y + vOtherScale.y * 0.5f > vPos.y - vScale.y * 0.5f
			&& vOtherPos.y - vOtherScale.y * 0.5f < vPos.y + vScale.y * 0.5f)
		{
			GetOwner()->SetMoveable(PLATFORM_TYPE::LEFT, false);
		}

		else if (vOtherPos.y - vOtherScale.y * 0.5f < vPos.y + vScale.y * 0.5f - 10.f
			&& vOtherPos.x - vOtherScale.x * 0.5f > vPos.x - vScale.x * 0.5 - 100.f
			&& vOtherPos.x + vOtherScale.x * 0.5f < vPos.x + vScale.x * 0.5f + 100.f)
		{
			GetOwner()->SetMoveable(PLATFORM_TYPE::UP, false);
		}

		else if (vOtherPos.y + vOtherScale.y * 0.5f > vPos.y - vScale.y * 0.5f + 10.f
			&& vOtherPos.x - vOtherScale.x * 0.5f > vPos.x - vScale.x * 0.5f - 100.f
			&& vOtherPos.x + vOtherScale.x * 0.5f < vPos.x + vScale.x * 0.5f + 100.f)
		{
			GetOwner()->SetMoveable(PLATFORM_TYPE::BOTTOM, false);
		}
	}
}

void CMeltKnightScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (3 == _OtherObj->GetLayerIdx())
	{
		Vec3 vPos = _OwnCollider->GetWorldPos();
		Vec3 vScale = Transform()->GetWorldScale();
		Vec3 vOtherPos = _OtherCollider->GetWorldPos();
		Vec3 vOtherScale = _OtherObj->Transform()->GetWorldScale();

		bool* bMoveable = GetOwner()->GetMoveable();

		if (vOtherPos.x - vOtherScale.x * 0.5f < vPos.x + vScale.x * 0.5f + 10.f)
			//&& vOtherPos.y + vOtherScale.y * 0.5f > vPos.y - vScale.y * 0.5f
			//&& vOtherPos.y - vOtherScale.y * 0.5f < vPos.y + vScale.y * 0.5f)
		{
			GetOwner()->SetMoveable(PLATFORM_TYPE::RIGHT, false);
		}

		else if (vOtherPos.x + vOtherScale.x * 0.5f + 10.f > vPos.x - vScale.x * 0.5f - 10.f)
			//&& vOtherPos.y + vOtherScale.y * 0.5f > vPos.y - vScale.y * 0.5f
			//&& vOtherPos.y - vOtherScale.y * 0.5f < vPos.y + vScale.y * 0.5f)
		{
			GetOwner()->SetMoveable(PLATFORM_TYPE::LEFT, false);
		}

		else if (vOtherPos.y - vOtherScale.y * 0.5f < vPos.y + vScale.y * 0.5f - 10.f)
			//&& vOtherPos.x - vOtherScale.x * 0.5f > vPos.x - vScale.x * 0.5 - 100.f
			//&& vOtherPos.x + vOtherScale.x * 0.5f < vPos.x + vScale.x * 0.5f + 100.f)
		{
			GetOwner()->SetMoveable(PLATFORM_TYPE::UP, false);
		}

		else if (vOtherPos.y + vOtherScale.y * 0.5f > vPos.y - vScale.y * 0.5f + 10.f)
			//&& vOtherPos.x - vOtherScale.x * 0.5f > vPos.x - vScale.x * 0.5f - 100.f
			//&& vOtherPos.x + vOtherScale.x * 0.5f < vPos.x + vScale.x * 0.5f + 100.f)
		{
			GetOwner()->SetMoveable(PLATFORM_TYPE::BOTTOM, false);
		}
	}
}

void CMeltKnightScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (3 == _OtherObj->GetLayerIdx())
	{
		GetOwner()->SetMoveable(PLATFORM_TYPE::LEFT, true);
		GetOwner()->SetMoveable(PLATFORM_TYPE::RIGHT, true);
		GetOwner()->SetMoveable(PLATFORM_TYPE::BOTTOM, true);
		GetOwner()->SetMoveable(PLATFORM_TYPE::UP, true);
	}
}
