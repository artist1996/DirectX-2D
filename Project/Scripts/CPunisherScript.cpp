#include "pch.h"
#include "CPunisherScript.h"

#include "CPlayerScript.h"

#include <Engine/CLevelMgr.h>
#include "CPlayerScript.h"

CPunisherScript::CPunisherScript()
	: CScript(SCRIPT_TYPE::PUNISHERSCRIPT)
	, m_Time(0.f)
{
}

CPunisherScript::~CPunisherScript()
{
}

void CPunisherScript::Begin()
{
	
}

void CPunisherScript::Tick()
{
	m_Time += DT;

	if (0.15f < m_Time)
		DeleteObject(GetOwner()->GetParent());
}

void CPunisherScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx())
	{
		INFO& info = _OtherObj->GetInfo();

		if (L"hyungteo" == _OtherObj->GetName())
		{
			CPlayerScript* pScript = (CPlayerScript*)CLevelMgr::GetInst()->FindObjectByName(L"Player")->FindScriptByName(L"CPlayerScript");
			pScript->ChangeStatePunisherShoot();
			_OtherObj->FSM()->ChangeState(L"DownHit");
			DeleteObject(GetOwner()->GetParent());
		}

		else if (L"direzie" == _OtherObj->GetName() && !info.bSuperArmor)
		{
			CPlayerScript* pScript = (CPlayerScript*)CLevelMgr::GetInst()->FindObjectByName(L"Player")->FindScriptByName(L"CPlayerScript");
			pScript->ChangeStatePunisherShoot();
			_OtherObj->Animator2D()->Play(10, 10.f, false);
			_OtherObj->FSM()->ChangeState(L"DownHit");
			DeleteObject(GetOwner()->GetParent());
		}
	}
}