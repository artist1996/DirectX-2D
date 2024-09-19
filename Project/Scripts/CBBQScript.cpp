#include "pch.h"
#include "CBBQScript.h"

#include <Engine/CLevelMgr.h>
#include "CPlayerScript.h"

CBBQScript::CBBQScript()
	: CScript(SCRIPT_TYPE::BBQSCRIPT)
	, m_Time(0.f)
{
}

CBBQScript::~CBBQScript()
{
}

void CBBQScript::Begin()
{
#ifdef _DEBUG
	Collider2D()->SetRender(true);
#else
	Collider2D()->SetRender(false);
#endif
}

void CBBQScript::Tick()
{
	m_Time += DT;

	if (0.15f < m_Time)
	{
		DeleteObject(GetOwner()->GetParent());
	}
}

void CBBQScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx())
	{
		INFO& info = _OtherObj->GetInfo();

		if (L"hyungteo" == _OtherObj->GetName())
		{
			CRigidbody* pRB = _OtherObj->Rigidbody();
			CPlayerScript* pScript = static_cast<CPlayerScript*>(CLevelMgr::GetInst()->FindObjectByName(L"Player")->FindScriptByName(L"CPlayerScript"));
			pScript->ChangeStateBBQReady();

			if (pRB->IsGround())
			{
				pRB->Rigidbody()->SetJumpSpeed(800.f);
				pRB->Rigidbody()->SetMaxGravitySpeed(1000.f);
				pRB->Rigidbody()->Jump();
				_OtherObj->FSM()->ChangeState(L"HitBBQ");
			}
			else
			{
				pRB->SetGround(true);
				pRB->Rigidbody()->SetJumpSpeed(1300.f);
				pRB->Rigidbody()->SetMaxGravitySpeed(800.f);
				pRB->Rigidbody()->Jump();
				_OtherObj->FSM()->ChangeState(L"HitBBQ");
			}

			DeleteObject(GetOwner()->GetParent());
		}

		else if (L"direzie" == _OtherObj->GetName() && !info.bSuperArmor)
		{

		}
	}
}