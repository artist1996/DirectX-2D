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
#include <States/CHyungteoDeadState.h>
#include <States/CHyungteoRecoilState.h>
#include <States/CHyungteoAirHitState.h>
#include <States/CHyungteoStiffnessState.h>
#include <States/CHyungteoDownHitState.h>
#include <States/CHyungteoHitBBQState.h>

CHyungteoScript::CHyungteoScript()
	: CScript(SCRIPT_TYPE::HYUNGTEOSCRIPT)
	, m_Dead(false)
{
}

CHyungteoScript::~CHyungteoScript()
{
}

void CHyungteoScript::InitInfo()
{
	INFO Info = {};
	Info.MaxHP = 2500;
	Info.HP = Info.MaxHP;
	Info.Defense = 0;
	Info.MinAttack = 30;
	Info.MaxAttack = 50;

	GetOwner()->SetInfo(Info);
}

void CHyungteoScript::Begin()
{
	InitInfo();

	FSM()->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, CLevelMgr::GetInst()->FindObjectByName(L"PlayerMove"));

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
	FSM()->AddState(L"Dead", new CHyungteoDeadState);
	FSM()->AddState(L"Recoil", new CHyungteoRecoilState);
	FSM()->AddState(L"AirHit", new CHyungteoAirHitState);
	FSM()->AddState(L"Stiffness", new CHyungteoStiffnessState);
	FSM()->AddState(L"DownHit", new CHyungteoDownHitState);
	FSM()->AddState(L"HitBBQ", new CHyungteoHitBBQState);

	FSM()->ChangeState(L"Eat");
}

void CHyungteoScript::Tick()
{
	INFO& info = GetOwner()->GetInfo();

	if (0 >= info.HP && !m_Dead)
	{
		FSM()->ChangeState(L"Dead");
		m_Dead = true;
		info.bDead = true;
		CGameObject* pObject = CLevelMgr::GetInst()->FindObjectByName(L"NamedMonsterHUD");
		pObject->SetActive(false);
	}

	CheckZAxis();
}

void CHyungteoScript::CheckZAxis()
{
	GetOwner()->Transform()->SetZAxis(GetOwner()->GetParent()->Collider2D()->GetWorldPos().y);
}

void CHyungteoScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (7 == _OtherObj->GetLayerIdx())
	{
		CGameObject* pObject = CLevelMgr::GetInst()->FindObjectByName(L"NamedMonsterHUD");
		pObject->SetActive(true);
		pObject->SetTarget(GetOwner());
	}
}

void CHyungteoScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CHyungteoScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}