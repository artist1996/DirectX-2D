#include "pch.h"
#include "CEffectScript.h"

CEffectScript::CEffectScript()
	: CScript(SCRIPT_TYPE::EFFECTSCRIPT)
{
}

CEffectScript::~CEffectScript()
{
}

void CEffectScript::Begin()
{
	if (L"deathcrisiscutin" == GetOwner()->GetName())
		Animator2D()->Play(0.f, 48.f, false);
	else if (L"deathcrisisboomtwo" == GetOwner()->GetName())
		Animator2D()->Play(0.f, 15.f, false);
	else
		Animator2D()->Play(0.f, 7.f, false);
}

void CEffectScript::Tick()
{
	if (Animator2D()->IsFinish())
		DeleteObject(GetOwner());
}