#include "pch.h"
#include "CJurisScript.h"

#include <Engine/CLevelMgr.h>

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
{
}

CJurisScript::~CJurisScript()
{
}

void CJurisScript::InitInfo()
{
}

void CJurisScript::Begin()
{
	MeshRender()->GetDynamicMaterial();

	FSM()->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, CLevelMgr::GetInst()->FindObjectByName(L"PlayerMove"));

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

}

void CJurisScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CJurisScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CJurisScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}