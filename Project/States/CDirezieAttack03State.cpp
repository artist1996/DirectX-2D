#include "pch.h"
#include "CDirezieAttack03State.h"

CDirezieAttack03State::CDirezieAttack03State()
	: CState(STATE_TYPE::DIREZIEATTACK03STATE)
{
}

CDirezieAttack03State::~CDirezieAttack03State()
{
}

void CDirezieAttack03State::Enter()
{
	INFO& info = GetOwner()->GetInfo();
	info.bSuperArmor = true;
	// Direzie Animation Num(0. idle, 1. move, 2. attack1, 3. attack2, 4. attack3, 5. attack4, 6. hide, 7. attack5)
	GetOwner()->Animator2D()->Play(4, 7.f, false);

	CGameObject* pTarget = static_cast<CGameObject*>(GetFSM()->GetBlackboardData(L"Target"));

	Vec3 vPos = GetOwner()->GetParent()->Transform()->GetRelativePos();

	Vec3 vTargetColPos = pTarget->Collider2D()->GetWorldPos();
	Vec3 vTargetColScale = pTarget->Collider2D()->GetScale();

	Vec3 vTargetPos = vTargetColPos - vTargetColScale * 0.5f;
	bool* bMoveable = GetOwner()->GetParent()->GetMoveable();

	m_ArrivalPoint = vTargetPos;
	m_Dist = vTargetPos - vPos;

	m_Dist.Normalize();
}

void CDirezieAttack03State::FinalTick()
{
	Vec3 vPos = GetOwner()->GetParent()->Transform()->GetRelativePos();
	bool* bMoveable = GetOwner()->GetParent()->GetMoveable();

	// ����/������, ����/�Ʒ����� ��� ���� ��� �켱 ó��
	if (!bMoveable[(UINT)PLATFORM_TYPE::LEFT] && !bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		m_Dist.x = 0.f;  // ���� ��� �̵� �Ұ�
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		m_Dist.x = 0.f;  // ���ʸ� �̵� �Ұ�
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		m_Dist.x = 0.f;  // �����ʸ� �̵� �Ұ�
	}

	if (!bMoveable[(UINT)PLATFORM_TYPE::UP] && !bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		m_Dist.y = 0.f;  // ���ʰ� �Ʒ��� ��� �̵� �Ұ�
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::UP])
	{
		m_Dist.y = 0.f;  // ���ʸ� �̵� �Ұ�
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		m_Dist.y = 0.f;  // �Ʒ��ʸ� �̵� �Ұ�
	}

	// ���ʰ� �������� ���ÿ� ���� ��� ó��
	if (!bMoveable[(UINT)PLATFORM_TYPE::UP] && !bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		m_Dist.x = 0.f;  // �������� ����
		m_Dist.y = 0.f;   // ������ ������ �Ʒ��� �̵�
	}

	// ���ʰ� ������ ���ÿ� ���� ��� ó��
	else if (!bMoveable[(UINT)PLATFORM_TYPE::UP] && !bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		m_Dist.x = 0.f;   // ������ ����
		m_Dist.y = 0.f;   // ������ ������ �Ʒ��� �̵�
	}

	// �Ʒ��ʰ� �������� ���ÿ� ���� ��� ó��
	else if (!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM] && !bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		m_Dist.x = 0.f;  // �������� ����
		m_Dist.y = 0.f;  // �Ʒ����� ������ ���� �̵�
	}

	// �Ʒ��ʰ� ������ ���ÿ� ���� ��� ó��
	else if (!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM] && !bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		m_Dist.x = 0.f;   // ������ ����
		m_Dist.y = 0.f;  // �Ʒ����� ������ ���� �̵�
	}

	// ��� ������ ���� ���
	if (!bMoveable[(UINT)PLATFORM_TYPE::LEFT] &&
		!bMoveable[(UINT)PLATFORM_TYPE::RIGHT] &&
		!bMoveable[(UINT)PLATFORM_TYPE::UP] &&
		!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		m_Dist.x = 0.f;
		m_Dist.y = 0.f;  // ��� ������ �̵� �Ұ�
	}

	if (2 <= GetOwner()->Animator2D()->GetCurFrameIndex()
		&& 6 >= GetOwner()->Animator2D()->GetCurFrameIndex())
	{
		vPos += m_Dist * 700.f * DT;
	}

	if (GetOwner()->Animator2D()->IsFinish())
		GetFSM()->ChangeState(L"Idle");

	vPos.z = vPos.y;

	GetOwner()->GetParent()->Transform()->SetRelativePos(vPos);
}

void CDirezieAttack03State::Exit()
{
	GetOwner()->GetParent()->SetMoveable(PLATFORM_TYPE::LEFT, true);
	GetOwner()->GetParent()->SetMoveable(PLATFORM_TYPE::RIGHT, true);
	GetOwner()->GetParent()->SetMoveable(PLATFORM_TYPE::BOTTOM, true);
	GetOwner()->GetParent()->SetMoveable(PLATFORM_TYPE::UP, true);
}