#include "pch.h"
#include "CJurisScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CObjectPoolMgr.h>

#include <States/CJurisIdleState.h>
#include <States/CJurisTraceState.h>
#include <States/CJurisHideState.h>
#include <States/CJurisAttackState.h>
#include <States/CJurisBackAttackState.h>
#include <States/CJurisHitState.h>
#include <States/CJurisDeadState.h>
#include <States/CJurisStiffnessState.h>

CJurisScript::CJurisScript()
	: CScript(SCRIPT_TYPE::JURISSCRIPT)
	, m_Dead(false)
{
}

CJurisScript::~CJurisScript()
{
}

void CJurisScript::InitInfo()
{
	INFO info = {};

	info.MaxHP = 2700.f;
	info.HP = 2700.f;

	GetOwner()->SetInfo(info);
}

void CJurisScript::Begin()
{
	MeshRender()->GetDynamicMaterial();

	InitInfo();
	FSM()->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, CObjectPoolMgr::GetInst()->GetPlayerEntity());

	FSM()->AddState(L"Idle", new CJurisIdleState);
	FSM()->AddState(L"Trace", new CJurisTraceState);
	FSM()->AddState(L"Hide", new CJurisHideState);
	FSM()->AddState(L"Attack", new CJurisAttackState);
	FSM()->AddState(L"BackAttack", new CJurisBackAttackState);
	FSM()->AddState(L"Hit", new CJurisHitState);
	FSM()->AddState(L"Dead", new CJurisDeadState);
	FSM()->AddState(L"Stiffness", new CJurisStiffnessState);

	FSM()->ChangeState(L"Idle");
}

void CJurisScript::Tick()
{
	INFO& info = GetOwner()->GetInfo();

	if (0 >= info.HP && !m_Dead)
	{
		FSM()->ChangeState(L"Dead");
		m_Dead = true;
	}
}

void CJurisScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (7 == _OtherObj->GetLayerIdx())
	{
		//INFO& info = GetOwner()->GetInfo();
		//info.HP -= 10.f;

		CGameObject* pObject = CLevelMgr::GetInst()->FindObjectByName(L"NamedMonsterHUD");
		pObject->SetActive(true);
		pObject->SetTarget(GetOwner());
	}
}

void CJurisScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CJurisScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}