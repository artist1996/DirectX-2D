#include "pch.h"
#include "CRisingShotScript.h"
#include "CMonsterDamageFontScript.h"

CRisingShotScript::CRisingShotScript()
	: CScript(SCRIPT_TYPE::RISINGSHOTSCRIPT)
{
}

CRisingShotScript::~CRisingShotScript()
{
}

void CRisingShotScript::Begin()
{
	Animator2D()->Play(0, 10.f, true);

	if (OBJ_DIR::DIR_LEFT == GetOwner()->GetDir())
		Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
}

void CRisingShotScript::Tick()
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
	}


	GetOwner()->GetParent()->Transform()->SetRelativePos(vPos);
}

void CRisingShotScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
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
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1254963);
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
		}
		else
		{
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(2315136);
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
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1254963);
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
		}
		else
		{
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(2315136);
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::CRITICAL);
		}
		CreateObject(pObj, 0);
	}

	if (6 == _OtherObj->GetLayerIdx() || L"Platform" == _OtherObj->GetName())
	{
		Vec3 vPos = Transform()->GetWorldPos();
		Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();

		if (GetOwner()->GetParent()->IsGroundCollision())
		{
			DeleteObject(GetOwner()->GetParent());
		}
	}

	if (L"hyungteo" == _OtherObj->GetName() || L"direzie" == _OtherObj->GetName() && !info.bSuperArmor)
	{
		info.HP -= 10.f;
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_hit_01.ogg")->Play(1, 0.2f, true);
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
		}
	}
}