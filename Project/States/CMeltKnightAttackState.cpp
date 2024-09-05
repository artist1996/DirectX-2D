#include "pch.h"
#include "CMeltKnightAttackState.h"

CMeltKnightAttackState::CMeltKnightAttackState()
	: CState(STATE_TYPE::MELTKNIGHTATTACKSTATE)
{
}

CMeltKnightAttackState::~CMeltKnightAttackState()
{
}

void CMeltKnightAttackState::Enter()
{
	// Melt Knight Animation Number (0 : IDLE, 1 : Move, 2 : Attack, 3 : Dead)
	GetFSM()->GetOwner()->Animator2D()->Play(2, 7.f, true);
}

void CMeltKnightAttackState::FinalTick()
{
	if (GetOwner()->Animator2D()->IsFinish())
		GetFSM()->ChangeState(L"StandBy");
}

void CMeltKnightAttackState::Exit()
{
}