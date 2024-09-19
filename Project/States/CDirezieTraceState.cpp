#include "pch.h"
#include "CDirezieTraceState.h"

#include <Engine/CRandomMgr.h>

CDirezieTraceState::CDirezieTraceState()
	: CState(STATE_TYPE::DIREZIETRACESTATE)
	, m_Time(0.f)
{
}

CDirezieTraceState::~CDirezieTraceState()
{
}

void CDirezieTraceState::Enter()
{
	GetOwner()->Animator2D()->Play(1, 7.f, true);
	INFO& info = GetOwner()->GetInfo();
	info.bSuperArmor = false;
}

void CDirezieTraceState::FinalTick()
{
	CGameObject* pTarget = static_cast<CGameObject*>(GetFSM()->GetBlackboardData(L"Target"));

	Vec3 vPos = GetOwner()->GetParent()->Transform()->GetRelativePos();

	Vec3 vTargetColPos = pTarget->Collider2D()->GetWorldPos();
	Vec3 vTargetColScale = pTarget->Collider2D()->GetScale();

	Vec3 vTargetPos = vTargetColPos - vTargetColScale * 0.5f;
	bool* bMoveable = GetOwner()->GetParent()->GetMoveable();

	Vec3 vDist = vTargetPos - vPos;

	vDist.Normalize();

	// ����/������, ����/�Ʒ����� ��� ���� ��� �켱 ó��
	if (!bMoveable[(UINT)PLATFORM_TYPE::LEFT] && !bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		vDist.x = 0.f;  // ���� ��� �̵� �Ұ�
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		vDist.x = 1.f;  // ���ʸ� �̵� �Ұ�
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		vDist.x = -1.f;  // �����ʸ� �̵� �Ұ�
	}

	if (!bMoveable[(UINT)PLATFORM_TYPE::UP] && !bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		vDist.y = 0.f;  // ���ʰ� �Ʒ��� ��� �̵� �Ұ�
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::UP])
	{
		vDist.y = -1.f;  // ���ʸ� �̵� �Ұ�
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		vDist.y = 1.f;  // �Ʒ��ʸ� �̵� �Ұ�
	}

	// ���ʰ� �������� ���ÿ� ���� ��� ó��
	if (!bMoveable[(UINT)PLATFORM_TYPE::UP] && !bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		vDist.x = 0.f;  // �������� ����
		vDist.y = 1.f;   // ������ ������ �Ʒ��� �̵�
	}

	// ���ʰ� ������ ���ÿ� ���� ��� ó��
	else if (!bMoveable[(UINT)PLATFORM_TYPE::UP] && !bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		vDist.x = 0.f;   // ������ ����
		vDist.y = 1.f;   // ������ ������ �Ʒ��� �̵�
	}

	// �Ʒ��ʰ� �������� ���ÿ� ���� ��� ó��
	else if (!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM] && !bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		vDist.x = 0.f;  // �������� ����
		vDist.y = -1.f;  // �Ʒ����� ������ ���� �̵�
	}

	// �Ʒ��ʰ� ������ ���ÿ� ���� ��� ó��
	else if (!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM] && !bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		vDist.x = 0.f;   // ������ ����
		vDist.y = -1.f;  // �Ʒ����� ������ ���� �̵�
	}

	// ��� ������ ���� ���
	if (!bMoveable[(UINT)PLATFORM_TYPE::LEFT] &&
		!bMoveable[(UINT)PLATFORM_TYPE::RIGHT] &&
		!bMoveable[(UINT)PLATFORM_TYPE::UP] &&
		!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		vDist.x = 0.f;
		vDist.y = 0.f;  // ��� ������ �̵� �Ұ�
	}

	vPos.x += vDist.x * 100.f * DT;
	vPos.y += vDist.y * 100.f * DT;
	vPos.z = vPos.y;

	float fDist = vTargetPos.x - vPos.x;
	float fYDist = fabs(vTargetPos.y - vPos.y);

	if (0.f < fDist)
	{
		GetOwner()->GetParent()->SetDir(OBJ_DIR::DIR_RIGHT);
		GetOwner()->GetParent()->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	}
	else
	{
		GetOwner()->GetParent()->SetDir(OBJ_DIR::DIR_LEFT);
		GetOwner()->GetParent()->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
	}

	m_Time += DT;

	if (3.f < m_Time)
	{
		int Rand = CRandomMgr::GetInst()->GetRandom(2);

		if (0 == Rand)
			GetFSM()->ChangeState(L"Attack03");
		else if (1 == Rand)
			GetFSM()->ChangeState(L"Attack04");
		else if (2 == Rand)
			GetFSM()->ChangeState(L"Hide");
	}

	if (150.f > fabs(fDist)
		&& 30.f > fabs(fYDist))
	{
		int Rand = CRandomMgr::GetInst()->GetRandom(1);

		if (0 == Rand)
			GetFSM()->ChangeState(L"Attack01");
		else if (1 == Rand)
			GetFSM()->ChangeState(L"Attack02");
	}

	GetOwner()->GetParent()->Transform()->SetRelativePos(vPos);
}

void CDirezieTraceState::Exit()
{
	m_Time = 0.f;
}