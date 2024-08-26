#include "pch.h"
#include "CHeadShotEffectScript.h"

CHeadShotEffectScript::CHeadShotEffectScript()
	: CScript(SCRIPT_TYPE::HEADSHOTEFFECTSCRIPT)
{
}

CHeadShotEffectScript::~CHeadShotEffectScript()
{
}

void CHeadShotEffectScript::Begin()
{
	Animator2D()->Play(0, 22.f, false);
}

void CHeadShotEffectScript::Tick()
{
	if (Animator2D()->IsFinish())
		DeleteObject(GetOwner());
}