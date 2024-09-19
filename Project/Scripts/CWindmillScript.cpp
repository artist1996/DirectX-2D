#include "pch.h"
#include "CWindmillScript.h"

CWindmillScript::CWindmillScript()
	: CScript(SCRIPT_TYPE::WINDMILLSCRIPT)
	, m_OverlapCount(0)
{
}

CWindmillScript::~CWindmillScript()
{
}

void CWindmillScript::Begin()
{
	Animator2D()->Play(0, 20.f, false);
	Collider2D()->SetRender(true);
}

void CWindmillScript::Tick()
{
	if (Animator2D()->IsFinish())
	{
		DeleteObject(GetOwner());
	}
}

void CWindmillScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CWindmillScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx())
	{
		INFO& info = _OtherObj->GetInfo();

		if (2 > m_OverlapCount)
		{
			m_OverlapCount++;
			info.HP -= 10.f;
		}

		if (L"direzie" == _OtherObj->GetName())
		{
			CRigidbody* pRB = _OtherObj->Rigidbody();

			if (pRB->IsGround() && !info.bSuperArmor)
			{
				_OtherObj->FSM()->ChangeState(L"GroundHit");
			}
			else
			{
				pRB->SetGround(true);
				pRB->SetJumpSpeed(20.f);
				pRB->SetMaxGravitySpeed(200.f);
				_OtherObj->FSM()->ChangeState(L"Fall");
			}
		}

		if (L"hyungteo" == _OtherObj->GetName())
		{
			CRigidbody* pRB = _OtherObj->Rigidbody();

			if (pRB->IsGround())
			{
				_OtherObj->FSM()->ChangeState(L"Hit");
			}
			else
			{
				pRB->SetGround(true);
				pRB->SetJumpSpeed(20.f);
				pRB->SetMaxGravitySpeed(200.f);
				pRB->Jump();
				_OtherObj->FSM()->ChangeState(L"AirHit");
			}
		}
	}
}