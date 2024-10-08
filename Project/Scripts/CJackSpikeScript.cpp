#include "pch.h"
#include "CJackSpikeScript.h"

#include "CMonsterDamageFontScript.h"

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
	INFO& info = _OtherObj->GetInfo();

	int Rand = CRandomMgr::GetInst()->GetRandom(1);
	
	if (L"MonsterMove" != _OtherObj->GetName() && 6 == _OtherObj->GetLayerIdx() && OBJ_DIR::DIR_LEFT == _OtherObj->GetParent()->GetDir())
	{
		Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();
		Ptr<CPrefab> pDamage = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\monsterdamage.pref");
		CGameObject* pObj = pDamage->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vOtherPos.x + 100.f, vOtherPos.y, vOtherPos.z));

		if (0 == Rand)
		{
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1275849);
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
		}
		else
		{
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1754963);
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
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1275849);
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
		}
		else
		{
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1754963);
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::CRITICAL);
		}
		CreateObject(pObj, 0);
	}

	if (L"hyungteo" == _OtherObj->GetName() || L"direzie" == _OtherObj->GetName() && !info.bSuperArmor)
	{
		Vec3 vPos = Transform()->GetWorldPos();
		Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();

		Vec3 vDist = vPos - vOtherPos;

		if (GetOwner()->GetParent()->IsGroundCollision())
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

			info.HP -= 5.f;
		}
	}
}