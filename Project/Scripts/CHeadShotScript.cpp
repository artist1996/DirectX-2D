#include "pch.h"
#include "CHeadShotScript.h"

#include <Engine/CLevelMgr.h>
#include "CMonsterDamageFontScript.h"

CHeadShotScript::CHeadShotScript()
	: CScript(SCRIPT_TYPE::HEADSHOTSCRIPT)
	, m_HitEffectPref(nullptr)
	, m_Hit(false)
{
}

CHeadShotScript::~CHeadShotScript()
{
}

void CHeadShotScript::Begin()
{
	m_HitEffectPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\headshothiteffect.pref");

	Animator2D()->Play(0, 10.f, true);

	if (OBJ_DIR::DIR_LEFT == GetOwner()->GetDir())
		Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
}

void CHeadShotScript::Tick()
{
	Vec3 vPos = GetOwner()->GetParent()->Transform()->GetRelativePos();
	Vec3 vInitPos = GetOwner()->GetParent()->GetInitPos();

	switch (GetOwner()->GetParent()->GetDir())
	{
	case OBJ_DIR::DIR_LEFT:
		vPos.x -= 1000.f * DT;
		break;

	case OBJ_DIR::DIR_RIGHT:
		vPos.x += 1000.f * DT;
		break;
	}

	if (650.f < fabs(vPos.x - vInitPos.x))
	{
		DeleteObject(GetOwner()->GetParent());
		//DisconnectObject(GetOwner()->GetParent());
	}


	GetOwner()->GetParent()->Transform()->SetRelativePos(vPos);
}

void CHeadShotScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx() || L"Platform" == _OtherObj->GetName())
	{
		Vec3 vPos = Transform()->GetWorldPos();
		Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();

		int Rand = CRandomMgr::GetInst()->GetRandom(1);

		if (L"MonsterMove" != _OtherObj->GetName() && 6 == _OtherObj->GetLayerIdx() && OBJ_DIR::DIR_LEFT == _OtherObj->GetParent()->GetDir())
		{
			Ptr<CPrefab> pDamage = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\monsterdamage.pref");
			CGameObject* pObj = pDamage->Instantiate();
			pObj->Transform()->SetRelativePos(Vec3(vOtherPos.x + 100.f, vOtherPos.y, vOtherPos.z));
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(3754963);
			if (0 == Rand)
			{
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(3754963);
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
			}
			else
			{
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(7519926);
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::CRITICAL);
			}
			CreateObject(pObj, 0);
		}
		else if (L"MonsterMove" != _OtherObj->GetName() && 6 == _OtherObj->GetLayerIdx() && OBJ_DIR::DIR_RIGHT == _OtherObj->GetParent()->GetDir())
		{
			Ptr<CPrefab> pDamage = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\monsterdamage.pref");
			CGameObject* pObj = pDamage->Instantiate();
			pObj->Transform()->SetRelativePos(Vec3(vOtherPos.x - 100.f, vOtherPos.y, vOtherPos.z));
			if (0 == Rand)
			{
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(3754963);
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
			}
			else
			{
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(7519926);
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::CRITICAL);
			}
			CreateObject(pObj, 0);
		}

		if (GetOwner()->GetParent()->IsGroundCollision())
		{
			CGameObject* pObject = m_HitEffectPref->Instantiate();
			INFO& info = _OtherObj->GetInfo();
			CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_hit_01.ogg")->Play(1, 0.2f, true);
			if (GetOwner()->GetParent()->GetDir() == OBJ_DIR::DIR_LEFT)
			{
				pObject->Transform()->SetRelativePos(Vec3(vOtherPos.x - 150.f, vOtherPos.y, vOtherPos.z - 50.f));
				pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
			}
			else if (GetOwner()->GetParent()->GetDir() == OBJ_DIR::DIR_RIGHT)
			{
				pObject->Transform()->SetRelativePos(Vec3(vOtherPos.x + 150.f, vOtherPos.y, vOtherPos.z - 50.f));
				pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
			}
			CreateObject(pObject, 0);

			if (L"juris" != _OtherObj->GetName())
			{
				if (0 == Rand)
					info.HP -= 130.f;
				else
					info.HP -= 260.f;
			}

			if (L"hyungteo" == _OtherObj->GetName())
			{
				if (_OtherObj->Rigidbody()->IsGround())
					_OtherObj->FSM()->ChangeState(L"Hit");
				else
				{
					_OtherObj->Rigidbody()->SetGround(true);
					_OtherObj->FSM()->ChangeState(L"AirHit");
				}
				if (0 == Rand)
					info.HP -= 130.f;
				else
					info.HP -= 260.f;
			}
			else if (L"juris" == _OtherObj->GetName())
			{
				if (info.bReflection)
				{
					if (0 == Rand)
						CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetInfo().HP -= 130.f;
					else
						CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetInfo().HP -= 260.f;
				}
				else
				{
					_OtherObj->FSM()->ChangeState(L"Hit");
				}
			}
			else if (L"direzie" == _OtherObj->GetName() && !info.bSuperArmor)
			{
				if (_OtherObj->Rigidbody()->IsGround())
					_OtherObj->FSM()->ChangeState(L"GroundHit");
				else
				{
					_OtherObj->Rigidbody()->SetGround(true);
					_OtherObj->FSM()->ChangeState(L"Fall");
				}
			}

			GetOwner()->GetParent()->SetGroundCollision(false);
		}
	}
}

void CHeadShotScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}
