#include "pch.h"
#include "CDeathCrisisLightScript.h"

CDeathCrisisLightScript::CDeathCrisisLightScript()
	: CScript(SCRIPT_TYPE::DEATHCRISISLIGHTSCRIPT)
{
}

CDeathCrisisLightScript::~CDeathCrisisLightScript()
{
}

void CDeathCrisisLightScript::Begin()
{
}

void CDeathCrisisLightScript::Tick()
{
	CGameObject* pTarget = GetOwner()->GetTarget();
	Vec3 vPos = pTarget->Transform()->GetWorldPos();
	if (pTarget->Animator2D()->IsFinish())
		DeleteObject(GetOwner());

	Transform()->SetRelativePos(vPos);
}