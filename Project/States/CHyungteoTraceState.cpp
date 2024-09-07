#include "pch.h"
#include "CHyungteoTraceState.h"

CHyungteoTraceState::CHyungteoTraceState()
	: CState(STATE_TYPE::HYUNGTEOTRACESTATE)
{
}

CHyungteoTraceState::~CHyungteoTraceState()
{
}

void CHyungteoTraceState::Enter()
{
	// Hyungteo Animation Num (0 : Eat, 1 : Look, 2 : Idle, 3 : Trace, 4 : Punch, 5 : Sting, 5 : Down)
	GetOwner()->Collider2D()->SetOffset(Vec3(0.f, -0.15f, 0.f));
	GetOwner()->Collider2D()->SetScale(Vec3(0.4f, 0.2f, 0.f));
	GetOwner()->Animator2D()->Play(3, 7.f, true);
}

void CHyungteoTraceState::FinalTick()
{
	CGameObject* pTarget = (CGameObject*)GetFSM()->GetBlackboardData(L"Target");

	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 vTargetPos = pTarget->Transform()->GetRelativePos();

	bool* bMoveable = GetOwner()->GetMoveable();

	Vec3 vDist = vTargetPos - vPos;

	vDist.Normalize();

	// 왼쪽/오른쪽, 위쪽/아래쪽이 모두 막힌 경우 우선 처리
	if (!bMoveable[(UINT)PLATFORM_TYPE::LEFT] && !bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		vDist.x = 0.f;  // 양쪽 모두 이동 불가
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		vDist.x = 1.f;  // 왼쪽만 이동 불가
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		vDist.x = -1.f;  // 오른쪽만 이동 불가
	}

	if (!bMoveable[(UINT)PLATFORM_TYPE::UP] && !bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		vDist.z = 0.f;  // 위쪽과 아래쪽 모두 이동 불가
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::UP])
	{
		vDist.z = 1.f;  // 위쪽만 이동 불가
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		vDist.z = -1.f;  // 아래쪽만 이동 불가
	}

	// 위쪽과 오른쪽이 동시에 막힌 경우 처리
	if (!bMoveable[(UINT)PLATFORM_TYPE::UP] && !bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		vDist.x = 0.f;  // 오른쪽을 막고
		vDist.z = 1.f;   // 위쪽을 막으면 아래로 이동
	}

	// 위쪽과 왼쪽이 동시에 막힌 경우 처리
	else if (!bMoveable[(UINT)PLATFORM_TYPE::UP] && !bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		vDist.x = 0.f;   // 왼쪽을 막고
		vDist.z = 1.f;   // 위쪽을 막으면 아래로 이동
	}

	// 아래쪽과 오른쪽이 동시에 막힌 경우 처리
	else if (!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM] && !bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		vDist.x = 0.f;  // 오른쪽을 막고
		vDist.z = -1.f;  // 아래쪽을 막으면 위로 이동
	}

	// 아래쪽과 왼쪽이 동시에 막힌 경우 처리
	else if (!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM] && !bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		vDist.x = 0.f;   // 왼쪽을 막고
		vDist.z = -1.f;  // 아래쪽을 막으면 위로 이동
	}

	// 모든 방향이 막힌 경우
	if (!bMoveable[(UINT)PLATFORM_TYPE::LEFT] &&
		!bMoveable[(UINT)PLATFORM_TYPE::RIGHT] &&
		!bMoveable[(UINT)PLATFORM_TYPE::UP] &&
		!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		vDist.x = 0.f;
		vDist.z = 0.f;  // 모든 방향이 이동 불가
	}
	
	Vec3 vColScale = GetOwner()->Collider2D()->GetScale();
	Vec3 vScale = GetOwner()->Transform()->GetWorldScale();

	Vec3 vFinalScale = vScale * vColScale;


	vPos.x += vDist.x * 100.f * DT;
	vPos.y += vDist.z * 100.f * DT;
	vPos.z = vPos.y - vFinalScale.y * 0.5f;

	float fDist = vTargetPos.x - vPos.x;
	float fYDist = fabs(vTargetPos.y - vPos.y);
	if (0.f < fDist)
	{
		GetOwner()->SetDir(OBJ_DIR::DIR_RIGHT);
		GetOwner()->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	}
	else
	{
		GetOwner()->SetDir(OBJ_DIR::DIR_LEFT);
		GetOwner()->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
	}


	if (100.f > fabs(fDist)
		&& 100.f > fabs(fYDist))
	{
		GetFSM()->ChangeState(L"Sting");
	}

	GetOwner()->Transform()->SetRelativePos(vPos);
}

void CHyungteoTraceState::Exit()
{
}