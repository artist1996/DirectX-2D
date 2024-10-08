#include "pch.h"
#include "CMeltKnightAttackScript.h"

#include "CPlayerScript.h"

CMeltKnightAttackScript::CMeltKnightAttackScript()
	: CScript(SCRIPT_TYPE::MELTKNIGHTATTACKSCRIPT)
	, m_Time(0.f)
{
}

CMeltKnightAttackScript::~CMeltKnightAttackScript()
{
}

void CMeltKnightAttackScript::Begin()
{
}

void CMeltKnightAttackScript::Tick()
{
	m_Time += DT;

	if (0.3f < m_Time)
	{
		DeleteObject(GetOwner());
	}
}

void CMeltKnightAttackScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"Player" == _OtherObj->GetName())
	{
		INFO& info = _OtherObj->GetInfo();
		info.HP -= 30.f;
		info.bInvincible = true;
		if(!info.bSuperArmor)
			static_cast<CPlayerScript*>(_OtherObj->GetScripts()[0])->ChangeStateHit();
	}
}

void CMeltKnightAttackScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CMeltKnightAttackScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}