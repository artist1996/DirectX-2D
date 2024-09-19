#include "pch.h"
#include "CDirezieDeadState.h"

CDirezieDeadState::CDirezieDeadState()
	: CState(STATE_TYPE::DIREZIEDEADSTATE)
{
}

CDirezieDeadState::~CDirezieDeadState()
{
}

void CDirezieDeadState::Enter()
{
	GetOwner()->Animator2D()->Play(9, 4.f, false);
	
}

void CDirezieDeadState::FinalTick()
{
	if (GetOwner()->Animator2D()->IsFinish())
		DeleteObject(GetOwner()->GetParent());
}

void CDirezieDeadState::Exit()
{
}