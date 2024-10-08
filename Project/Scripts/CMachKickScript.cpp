#include "pch.h"
#include "CMachKickScript.h"

#include <Engine/CLevelMgr.h>
#include "CMonsterDamageFontScript.h"

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
		if (GetOwner()->GetParent()->IsGroundCollision())
		{
			INFO& info = _OtherObj->GetInfo();
			CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_hit_01.ogg")->Play(1, 0.2f, true);
			int Rand = CRandomMgr::GetInst()->GetRandom(1);

			if (L"MonsterMove" != _OtherObj->GetName() && 6 == _OtherObj->GetLayerIdx() && OBJ_DIR::DIR_LEFT == _OtherObj->GetParent()->GetDir())
			{
				Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();
				Ptr<CPrefab> pDamage = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\monsterdamage.pref");
				CGameObject* pObj = pDamage->Instantiate();
				pObj->Transform()->SetRelativePos(Vec3(vOtherPos.x + 100.f, vOtherPos.y, vOtherPos.z));

				if (0 == Rand)
				{
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1464871);
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
				}
				else
				{
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(2164554);
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::CRITICAL);
				}
				CreateObject(pObj, 0);
			}
			else if (L"MonsterMove" != _OtherObj->GetName() && 6 == _OtherObj->GetLayerIdx() && OBJ_DIR::DIR_RIGHT == _OtherObj->GetParent()->GetDir())
			{
				Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();
				Ptr<CPrefab> pDamage = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\monsterdamage.pref");
				CGameObject* pObj = pDamage->Instantiate();
				pObj->Transform()->SetRelativePos(Vec3(vOtherPos.x - 100.f, vOtherPos.y, vOtherPos.z));
				if (0 == Rand)
				{
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1464871);
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
				}
				else
				{
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(2164554);
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::CRITICAL);
				}
				CreateObject(pObj, 0);
			}

			if (L"juris" == _OtherObj->GetName())
			{
				if (info.bReflection)
				{
					CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetInfo().HP -= 60.f;
				}
				else
				{
					_OtherObj->FSM()->ChangeState(L"Stiffness");
					info.HP -= 60.f;
				}
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
				info.HP -= 60.f;
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
				info.HP -= 60.f;
			}

			if(L"meltknight" == _OtherObj->GetName())
				info.HP -= 60.f;
		}
	}
}