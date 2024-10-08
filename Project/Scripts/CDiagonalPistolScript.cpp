#include "pch.h"
#include "CDiagonalPistolScript.h"
#include <Engine/CLevelMgr.h>
#include "CDirezieScript.h"

#include "CMonsterDamageFontScript.h"

CDiagonalPistolScript::CDiagonalPistolScript()
	: CScript(SCRIPT_TYPE::DIAGONALPISTOLSCRIPT)
	, m_Speed(700.f)
	, m_DestroyPos(0.f)
{
}

CDiagonalPistolScript::~CDiagonalPistolScript()
{
}

void CDiagonalPistolScript::Begin()
{
	Animator2D()->Play(0, 10.f, true);

	if (OBJ_DIR::DIR_LEFT == GetOwner()->GetParent()->GetDir())
	{
		Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI / 3.3f));
	}

	else if (OBJ_DIR::DIR_RIGHT == GetOwner()->GetParent()->GetDir())
	{
		Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.75f));
	}
}

void CDiagonalPistolScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vParentPos = GetOwner()->GetParent()->Transform()->GetRelativePos();

	switch (GetOwner()->GetParent()->GetDir())
	{
	case OBJ_DIR::DIR_LEFT:
		vParentPos += Vec3(-1.f, 0.f, 0.f) * 1000.f * DT;
		vPos.y -= 500.f * DT;
		break;
	case OBJ_DIR::DIR_RIGHT:
		vParentPos += Vec3(1.f, 0.f, 0.f) * 1000.f * DT;
		vPos.y -= 500.f * DT;
		break;
	}

	if (vPos.y < 0.f)
		DeleteObject(GetOwner()->GetParent());

	Transform()->SetRelativePos(vPos);
	GetOwner()->GetParent()->Transform()->SetRelativePos(vParentPos);
}

void CDiagonalPistolScript::SaveToFile(FILE* _pFile)
{
}

void CDiagonalPistolScript::LoadFromFile(FILE* _pFile)
{
}

void CDiagonalPistolScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDiagonalPistolScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx())
	{
		INFO& info = _OtherObj->GetInfo();

		if (GetOwner()->GetParent()->IsGroundCollision())
		{
			int Rand = CRandomMgr::GetInst()->GetRandom(1);
			CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_hit_01.ogg")->Play(1, 0.2f, true);
			if (L"MonsterMove" != _OtherObj->GetName() && 6 == _OtherObj->GetLayerIdx() && OBJ_DIR::DIR_LEFT == _OtherObj->GetParent()->GetDir())
			{
				Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();
				Ptr<CPrefab> pDamage = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\monsterdamage.pref");
				CGameObject* pObj = pDamage->Instantiate();
				pObj->Transform()->SetRelativePos(Vec3(vOtherPos.x + 100.f, vOtherPos.y, vOtherPos.z));

				if (0 == Rand)
				{
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1475849);
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
				}
				else
				{
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1727651);
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
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1475849);
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
				}
				else
				{
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1727651);
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::CRITICAL);
				}
				CreateObject(pObj, 0);
			}

			if (L"juris" == _OtherObj->GetName())
			{
				if (info.bReflection)
				{
					CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetInfo().HP -= 10.f;
				}
				else
					info.HP -= 10.f;
			}
			else
			{
				info.HP -= 10.f;
			}
			DeleteObject(GetOwner()->GetParent());
		}
	}
}

void CDiagonalPistolScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}