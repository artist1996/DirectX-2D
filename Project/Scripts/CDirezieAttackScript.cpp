#include "pch.h"
#include "CDirezieAttackScript.h"

#include "CPlayerScript.h"

CDirezieAttackScript::CDirezieAttackScript()
	: CScript(SCRIPT_TYPE::DIREZIEATTACKSCRIPT)
	, m_Time(0.f)
{
}

CDirezieAttackScript::~CDirezieAttackScript()
{
}

void CDirezieAttackScript::Begin()
{
}

void CDirezieAttackScript::Tick()
{
	m_Time += DT;

	if (0.3f < m_Time)
	{
		DeleteObject(GetOwner());
	}
}

void CDirezieAttackScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if(L"Player" == _OtherObj->GetName())
		static_cast<CPlayerScript*>(_OtherObj->GetScripts()[0])->ChangeStateHit();
}

void CDirezieAttackScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDirezieAttackScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}