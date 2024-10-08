#include "pch.h"
#include "CHyungteoStingScript.h"

#include "CPlayerScript.h"

CHyungteoStingScript::CHyungteoStingScript()
	: CScript(SCRIPT_TYPE::HYUNGTEOSTINGSCRIPT)
	, m_Time(0.f)
{
}

CHyungteoStingScript::~CHyungteoStingScript()
{
}

void CHyungteoStingScript::Begin()
{
}

void CHyungteoStingScript::Tick()
{
	m_Time += DT;

	if (0.5f < m_Time)
		DeleteObject(GetOwner());
}

void CHyungteoStingScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"Player" == _OtherObj->GetName())
	{
		INFO& info = _OtherObj->GetInfo();
		info.HP -= 30.f;
		info.bInvincible = true;
		static_cast<CPlayerScript*>(_OtherObj->GetScripts()[0])->ChangeStateHit();
	}
}

void CHyungteoStingScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CHyungteoStingScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}
