#include "pch.h"
#include "CMeltKnightTraceState.h"

CMeltKnightTraceState::CMeltKnightTraceState()
	: CState(STATE_TYPE::MELTKNIGHTTRACESTATE)
{
}

CMeltKnightTraceState::~CMeltKnightTraceState()
{
}

void CMeltKnightTraceState::Enter()
{
	// Melt Knight Animation Number (0 : IDLE, 1 : Move, 2 : Attack, 3 : Dead)
	GetFSM()->GetOwner()->Animator2D()->Play(1, 7.f, true);
}

void CMeltKnightTraceState::FinalTick()
{
	CGameObject* pTarget = (CGameObject*)GetFSM()->GetBlackboardData(L"Target");

	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 vTargetPos = pTarget->Transform()->GetRelativePos();

	bool* bMoveable = GetOwner()->GetMoveable();

	Vec3 vDist = vTargetPos - vPos;

	vDist.Normalize();
	
	// ����/������, ����/�Ʒ����� ��� ���� ��� �켱 ó��
	if (!bMoveable[(UINT)PLATFORM_TYPE::LEFT] && !bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		vDist.x = 0.f;
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		vDist.x = 0.f;
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		vDist.x = 0.f;
	}

	if (!bMoveable[(UINT)PLATFORM_TYPE::UP] && !bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		vDist.z = 0.f;
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::UP])
	{
		vDist.z = 0.f;
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		vDist.z = 0.f;
	}

	// ���ʰ� �������� ���ÿ� ���� ��� ó��
	if (!bMoveable[(UINT)PLATFORM_TYPE::UP] && !bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		vDist.x = -1.f;  // �������� ����
		vDist.z = 1.f;   // ������ ������ �Ʒ��� �̵�
	}

	// ���ʰ� ������ ���ÿ� ���� ��� ó��
	else if (!bMoveable[(UINT)PLATFORM_TYPE::UP] && !bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		vDist.x = 1.f;   // ������ ����
		vDist.z = 1.f;   // ������ ������ �Ʒ��� �̵�
	}

	// �Ʒ��ʰ� �������� ���ÿ� ���� ��� ó��
	else if (!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM] && !bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		vDist.x = -1.f;  // �������� ����
		vDist.z = -1.f;  // �Ʒ����� ������ ���� �̵�
	}

	// �Ʒ��ʰ� ������ ���ÿ� ���� ��� ó��
	else if (!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM] && !bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		vDist.x = 1.f;   // ������ ����
		vDist.z = -1.f;  // �Ʒ����� ������ ���� �̵�
	}

	// ��� ������ ���� ���
	if (!bMoveable[(UINT)PLATFORM_TYPE::LEFT] &&
		!bMoveable[(UINT)PLATFORM_TYPE::RIGHT] &&
		!bMoveable[(UINT)PLATFORM_TYPE::UP] &&
		!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		vDist.x = 0.f;
		vDist.z = 0.f;  // ��� ������ �̵� �Ұ�
	}

	Vec3 vColScale = GetOwner()->Collider2D()->GetScale();
	Vec3 vScale = GetOwner()->Transform()->GetWorldScale();

	Vec3 vFinalScale = vScale * vColScale;

	vPos.x += vDist.x * 50.f * DT;
	vPos.y += vDist.z * 50.f * DT;
	vPos.z = vPos.y - vFinalScale.y * 0.5f;


	float fDist = vTargetPos.x - vPos.x;
	float fYDist = fabs(vTargetPos.y - vPos.y);
	if (0.f < fDist)
		GetOwner()->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	else
		GetOwner()->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));


	if (100.f > fabs(fDist) 
		&& 50.f > fabs(fYDist))
	{
		GetFSM()->ChangeState(L"Attack");
	}

	GetOwner()->Transform()->SetRelativePos(vPos);
}

void CMeltKnightTraceState::Exit()
{
}