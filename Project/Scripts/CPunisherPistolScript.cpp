#include "pch.h"
#include "CPunisherPistolScript.h"

#include "CMonsterDamageFontScript.h"

CPunisherPistolScript::CPunisherPistolScript()
	: CScript(SCRIPT_TYPE::PUNISHERPISTOLSCRIPT)
	, m_Speed(1000.f)
{
}

CPunisherPistolScript::~CPunisherPistolScript()
{
}

void CPunisherPistolScript::Begin()
{
	Animator2D()->Play(0.f, 7.f, true);
}

void CPunisherPistolScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	OBJ_DIR Dir = GetOwner()->GetDir();

	if (OBJ_DIR::DIR_LEFT == Dir)
		vPos.x -= 1.f * m_Speed * DT;
	else
		vPos.x += 1.f * m_Speed * DT;

	vPos.y += -1.f * m_Speed * DT;


	Transform()->SetRelativePos(vPos);
}

void CPunisherPistolScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	INFO& info = _OtherObj->GetInfo();

	int Rand = CRandomMgr::GetInst()->GetRandom(1);

	if (L"MonsterMove" != _OtherObj->GetName() && 6 == _OtherObj->GetLayerIdx() && OBJ_DIR::DIR_LEFT == _OtherObj->GetParent()->GetDir())
	{
		Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();
		Ptr<CPrefab> pDamage = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\monsterdamage.pref");
		CGameObject* pObj = pDamage->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vOtherPos.x + 100.f, vOtherPos.y, vOtherPos.z));
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_hit_01.ogg")->Play(1, 0.2f, true);
		if (0 == Rand)
		{
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1675849);
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
		}
		else
		{
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1927651);
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
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1675849);
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
		}
		else
		{
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(1927651);
			static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::CRITICAL);
		}
		CreateObject(pObj, 0);
	}

	if (L"hyungteo" == _OtherObj->GetName())
	{
		info.HP -= 15.f;

		_OtherObj->FSM()->ChangeState(L"DownHit");
		DeleteObject(GetOwner());
	}
	else if (L"direzie" == _OtherObj->GetName())
	{
		info.HP -= 15.f;
		
		_OtherObj->Animator2D()->Play(10, 10.f, false);
		_OtherObj->FSM()->ChangeState(L"DownHit");
		DeleteObject(GetOwner());
	}
}

void CPunisherPistolScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPunisherPistolScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPunisherPistolScript::SaveToFile(FILE* _pFile)
{
}

void CPunisherPistolScript::LoadFromFile(FILE* _pFile)
{
}
