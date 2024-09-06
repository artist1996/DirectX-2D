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
	Animator2D()->Play(0.f, 7.f, false);
}

void CEffectScript::Tick()
{
	if (Animator2D()->IsFinish())
		DeleteObject(GetOwner());
}