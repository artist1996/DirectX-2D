#include "pch.h"
#include "CMeltKnightIdleState.h"

CMeltKnightIdleState::CMeltKnightIdleState()
	: CState(STATE_TYPE::MELTKNIGHTIDLESTATE)
{
}

CMeltKnightIdleState::~CMeltKnightIdleState()
{
}

void CMeltKnightIdleState::Enter()
{
	// Melt Knight Animation Number (0 : IDLE, 1 : Move, 2 : Attack, 3 : Dead)
	GetFSM()->GetOwner()->Animator2D()->Play(0, 7.f, true);
}

void CMeltKnightIdleState::FinalTick()
{
	// Logic
}

void CMeltKnightIdleState::Exit()
{
	// Exit Logic
}