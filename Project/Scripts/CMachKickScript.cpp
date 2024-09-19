#include "pch.h"
#include "CMachKickScript.h"

CMachKickScript::CMachKickScript()
	: CScript(SCRIPT_TYPE::MACHKICKSCRIPT)
	, m_Time(0.f)
{
}

CMachKickScript::~CMachKickScript()
{
}

void CMachKickScript::Begin()
{
}

void CMachKickScript::Tick()
{
	m_Time += DT;

	if (0.1f < m_Time)
	{
		DeleteObject(GetOwner()->GetParent());
	}
}

void CMachKickScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx())
	{
		if (GetOwner()->GetParent()->GetGroundCollision())
		{
			INFO& info = _OtherObj->GetInfo();

			if (L"juris" == _OtherObj->GetName())
			{
				_OtherObj->FSM()->ChangeState(L"Stiffness");
			}

			if (L"hyungteo" == _OtherObj->GetName())
			{
				CRigidbody* pRB = _OtherObj->Rigidbody();

				if (pRB->IsGround())
				{
					pRB->SetJumpSpeed(300.f);
					pRB->SetMaxGravitySpeed(200.f);
					pRB->Jump();
					_OtherObj->FSM()->ChangeState(L"Recoil");
				}

				else
				{
					pRB->SetGround(true);
					pRB->SetJumpSpeed(100.f);
					pRB->SetMaxGravitySpeed(200.f);
					pRB->Jump();
					_OtherObj->FSM()->ChangeState(L"AirHit");
				}
			}

			if (L"direzie" == _OtherObj->GetName())
			{
				CRigidbody* pRB = _OtherObj->Rigidbody();
				if (pRB->IsGround())
					_OtherObj->FSM()->ChangeState(L"GroundHit");
				else
				{
					pRB->SetGround(true);
					pRB->SetJumpSpeed(50.f);
					pRB->SetMaxGravitySpeed(200.f);
					pRB->Jump();
					_OtherObj->FSM()->ChangeState(L"AirHit");
				}
			}
			info.HP -= 10.f;
		}
	}
}