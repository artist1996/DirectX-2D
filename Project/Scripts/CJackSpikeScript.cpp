#include "pch.h"
#include "CJackSpikeScript.h"

CJackSpikeScript::CJackSpikeScript()
	: CScript(SCRIPT_TYPE::JACKSPIKESCRIPT)
	, m_Time(0.f)
{
}

CJackSpikeScript::~CJackSpikeScript()
{
}

void CJackSpikeScript::Begin()
{
}

void CJackSpikeScript::Tick()
{
	m_Time += DT;

	if (0.15f < m_Time)
	{
		DeleteObject(GetOwner()->GetParent());
	}
}

void CJackSpikeScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"hyungteo" == _OtherObj->GetName())
	{
		Vec3 vPos = Transform()->GetWorldPos();
		Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();

		Vec3 vDist = vPos - vOtherPos;

		if (GetOwner()->GetParent()->GetGroundCollision())
		{
			CRigidbody* pRB = _OtherObj->Rigidbody();

			if (pRB->IsGround())
			{
				pRB->Rigidbody()->SetMaxGravitySpeed(800.f);
				pRB->Rigidbody()->SetJumpSpeed(700.f);
			}

			else
			{
				pRB->SetGround(true);
				pRB->Rigidbody()->SetGravityVelocity(Vec3(0.f, 0.f, 0.f));
				pRB->Rigidbody()->SetMaxGravitySpeed(600.f);
				pRB->Rigidbody()->SetJumpSpeed(600.f);
				pRB->Jump();
			}

			_OtherObj->FSM()->ChangeState(L"Fly");
		}
	}
}