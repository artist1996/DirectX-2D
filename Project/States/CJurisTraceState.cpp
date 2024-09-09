#include "pch.h"
#include "CJurisTraceState.h"

#include <Engine/CRandomMgr.h>

CJurisTraceState::CJurisTraceState()
	: CState(STATE_TYPE::JURISTRACESTATE)
{
}

CJurisTraceState::~CJurisTraceState()
{
}

void CJurisTraceState::Enter()
{
	// Juris Animation Num (0 : Idle, 1 : Move, 2 : Hide, 3 : Attack, 4 : Hit, 5 : Dead)
	GetOwner()->Animator2D()->Play(1, 5.f, true);
}

void CJurisTraceState::FinalTick()
{
	CGameObject* pTarget = static_cast<CGameObject*>(GetFSM()->GetBlackboardData(L"Target"));

	Vec3 vPos = GetOwner()->GetParent()->Transform()->GetRelativePos();
	Vec3 vTargetPos = pTarget->Transform()->GetRelativePos();
	Vec3 vTargetColScale = pTarget->Collider2D()->GetScale();

	//Vec3 vTargetPos = vTargetPos - vTargetColScale * 0.5f;

	bool* bMoveable = GetOwner()->GetParent()->GetMoveable();

	Vec3 vDist = Vec3(vTargetPos.x, vTargetPos.y - 50.f, vTargetPos.z) - vPos;

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
		vDist.y = 1.f;  // ���ʸ� �̵� �Ұ�
	}
	else if (!bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		vDist.y = -1.f;  // �Ʒ��ʸ� �̵� �Ұ�
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

	//Vec3 vColScale = GetOwner()->Collider2D()->GetScale();
	//Vec3 vScale = GetOwner()->Transform()->GetWorldScale();
	//
	//Vec3 vFinalScale = vScale * vColScale;


	vPos.x += vDist.x * 100.f * DT;
	vPos.y += vDist.y * 100.f * DT;
	vPos.z = vPos.y;

	float fDist = vTargetPos.x - vPos.x;
	float fYDist = fabs((vTargetPos.y - 50.f) - vPos.y);
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

	int Random = CRandomMgr::GetInst()->GetRandom(1);

	if (150.f > fabs(fDist)
		&& 30.f > fabs(fYDist))
	{
		if(0 == Random)
			GetFSM()->ChangeState(L"Attack");
		else if(1 == Random)
			GetFSM()->ChangeState(L"Hide");
	}

	GetOwner()->GetParent()->Transform()->SetRelativePos(vPos);
}

void CJurisTraceState::Exit()
{
}