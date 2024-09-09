#include "pch.h"
#include "CJurisAttackState.h"

#include <Engine/CRandomMgr.h>

CJurisAttackState::CJurisAttackState()
	: CState(STATE_TYPE::JURISATTACKSTATE)
	, m_AttackPref(nullptr)
{
}

CJurisAttackState::~CJurisAttackState()
{
}

void CJurisAttackState::Enter()
{
	if (nullptr == m_AttackPref)
		m_AttackPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\jurisattack.pref");

	// Juris Animation Num (0 : Idle, 1 : Move, 2 : Hide, 3 : Attack, 4 : Hit, 5 : Dead)
	GetOwner()->Animator2D()->Play(3, 10.f, true);
}

void CJurisAttackState::FinalTick()
{
	if (GetOwner()->Animator2D()->IsFinish())
		GetFSM()->ChangeState(L"Idle");
}

void CJurisAttackState::Exit()
{
}