#include "pch.h"
#include "CJurisAttackScript.h"
#include "CPlayerScript.h"

CJurisAttackScript::CJurisAttackScript()
	: CScript(SCRIPT_TYPE::JURISATTACKSCRIPT)
	, m_Time(0.f)
{
}

CJurisAttackScript::~CJurisAttackScript()
{
}

void CJurisAttackScript::Begin()
{
	Transform()->SetRelativeScale(Vec3(200.f, 30.f, 1.f));
}

void CJurisAttackScript::Tick()
{
	m_Time += DT;

	if (0.3f < m_Time)
	{
		DeleteObject(GetOwner());
	}
}

void CJurisAttackScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"Player" == _OtherObj->GetName())
	{
		INFO& info = _OtherObj->GetInfo();
		info.HP -= 100.f;
		info.bInvincible = true;
		static_cast<CPlayerScript*>(_OtherObj->GetScripts()[0])->ChangeStateHit();
	}
}

void CJurisAttackScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CJurisAttackScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}