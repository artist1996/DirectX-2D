#include "pch.h"
#include "CGatlinggunPistolScript.h"

#include "CMonsterDamageFontScript.h"

CGatlinggunPistolScript::CGatlinggunPistolScript()
	: CScript(SCRIPT_TYPE::GATLINGGUNPISTOLSCRIPT)
	, m_Speed(1000.f)
{
}

CGatlinggunPistolScript::~CGatlinggunPistolScript()
{
}

void CGatlinggunPistolScript::Begin()
{
}

void CGatlinggunPistolScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	OBJ_DIR Dir = GetOwner()->GetDir();

	if (OBJ_DIR::DIR_LEFT == Dir)
		vPos.x -= 1.f * m_Speed * DT;
	else
		vPos.x += 1.f * m_Speed * DT;

	vPos.y += 1.f * m_Speed * DT;


	Transform()->SetRelativePos(vPos);
}

void CGatlinggunPistolScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"hyungteo" == _OtherObj->GetName() || L"direzie" == _OtherObj->GetName())
	{
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
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1427651);
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
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1427651);
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::CRITICAL);
			}
			CreateObject(pObj, 0);
		}

		INFO& info = _OtherObj->GetInfo();

		info.HP -= 5.f;
		_OtherObj->FSM()->ChangeState(L"HitBBQ");
		DeleteObject(GetOwner());
	}
}

void CGatlinggunPistolScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CGatlinggunPistolScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CGatlinggunPistolScript::SaveToFile(FILE* _pFile)
{
}

void CGatlinggunPistolScript::LoadFromFile(FILE* _pFile)
{
}
