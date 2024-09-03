#include "pch.h"
#include "CMeltKnightScript.h"

#include <States/CMeltKnightIdleState.h>

CMeltKnightScript::CMeltKnightScript()
	: CScript(SCRIPT_TYPE::MELTKNIGHTSCRIPT)
{

}

CMeltKnightScript::~CMeltKnightScript()
{
}

void CMeltKnightScript::Begin()
{
	GetOwner()->AddComponent(new CFSM);

	FSM()->AddState(L"IDLE", new CMeltKnightIdleState);

	FSM()->ChangeState(L"IDLE");

	Collider2D()->SetActive(true);
}

void CMeltKnightScript::Tick()
{
}

void CMeltKnightScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}