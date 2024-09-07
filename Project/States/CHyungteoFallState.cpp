#include "pch.h"
#include "CHyungteoFallState.h"

CHyungteoFallState::CHyungteoFallState()
	: CState(STATE_TYPE::HYUNGTEOFALLSTATE)
{
}

CHyungteoFallState::~CHyungteoFallState()
{
}

void CHyungteoFallState::Enter()
{

}

void CHyungteoFallState::FinalTick()
{
	Vec3 vPos = GetOwner()->Transform()->GetWorldPos();

	//if (_Pos.y <= m_GroundPosY)
	//{
	//	Rigidbody()->SetGround(true);
	//	_Pos.y = m_GroundPosY;
	//
	//	return true;
	//}

}

void CHyungteoFallState::Exit()
{
}