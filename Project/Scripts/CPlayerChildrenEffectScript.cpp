#include "pch.h"
#include "CPlayerChildrenEffectScript.h"

CPlayerChildrenEffectScript::CPlayerChildrenEffectScript()
	: CScript(SCRIPT_TYPE::PLAYERCHILDRENEFFECTSCRIPT)
{
}

CPlayerChildrenEffectScript::~CPlayerChildrenEffectScript()
{
}

void CPlayerChildrenEffectScript::Begin()
{
}

void CPlayerChildrenEffectScript::Tick()
{
	if (Animator2D()->IsFinish())
		GetOwner()->SetActive(false);
}