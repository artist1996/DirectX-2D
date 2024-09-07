#include "pch.h"
#include "CHyungteoScript.h"

#include <Engine/CLevelMgr.h>

#include <States/CHyungteoEatState.h>
#include <States/CHyungteoLookState.h>
#include <States/CHyungteoIdleState.h>
#include <States/CHyungteoTraceState.h>
#include <States/CHyungteoPunchState.h>
#include <States/CHyungteoStingState.h>
#include <States/CHyungteoHitState.h>
#include <States/CHyungteoFlyState.h>
#include <States/CHyungteoWakeUpState.h>
#include <States/CHyungteoFallState.h>

CHyungteoScript::CHyungteoScript()
	: CScript(SCRIPT_TYPE::HYUNGTEOSCRIPT)
{
}

CHyungteoScript::~CHyungteoScript()
{
}

void CHyungteoScript::InitInfo()
{
	INFO Info = {};
	Info.MaxHP = 600;
	Info.HP = Info.MaxHP;
	Info.Defense = 0;
	Info.MinAttack = 30;
	Info.MaxAttack = 50;

	GetOwner()->SetInfo(Info);
}

void CHyungteoScript::Begin()
{
	InitInfo();

	FSM()->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, CLevelMgr::GetInst()->FindObjectByName(L"Player"));

	FSM()->AddState(L"Eat", new CHyungteoEatState);
	FSM()->AddState(L"Look", new CHyungteoLookState);
	FSM()->AddState(L"Idle", new CHyungteoIdleState);
	FSM()->AddState(L"Trace", new CHyungteoTraceState);
	FSM()->AddState(L"Punch", new CHyungteoPunchState);
	FSM()->AddState(L"Sting", new CHyungteoStingState);
	FSM()->AddState(L"Hit", new CHyungteoHitState);
	FSM()->AddState(L"Fly", new CHyungteoFlyState);
	FSM()->AddState(L"WakeUp", new CHyungteoWakeUpState);
	FSM()->AddState(L"Fall", new CHyungteoFallState);

	FSM()->ChangeState(L"Eat");
}

void CHyungteoScript::Tick()
{
}

void CHyungteoScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CHyungteoScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CHyungteoScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}