#include "pch.h"
#include "CWindmillScript.h"

#include "CMonsterDamageFontScript.h"

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
			info.HP -= 30.f;

			int Rand = CRandomMgr::GetInst()->GetRandom(1);

			if (L"MonsterMove" != _OtherObj->GetName() && 6 == _OtherObj->GetLayerIdx() && OBJ_DIR::DIR_LEFT == _OtherObj->GetParent()->GetDir())
			{
				Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();
				Ptr<CPrefab> pDamage = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\monsterdamage.pref");
				CGameObject* pObj = pDamage->Instantiate();
				pObj->Transform()->SetRelativePos(Vec3(vOtherPos.x + 100.f, vOtherPos.y, vOtherPos.z));

				if (0 == Rand)
				{
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1864871);
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
				}
				else
				{
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(2125134);
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
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1864871);
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
				}
				else
				{
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(2125134);
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::CRITICAL);
				}
				CreateObject(pObj, 0);
			}
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