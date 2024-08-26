#include "pch.h"
#include "CHammerScript.h"

CHammerScript::CHammerScript()
	: CScript(SCRIPT_TYPE::HAMMERSCRIPT)
{
}

CHammerScript::~CHammerScript()
{
}

void CHammerScript::Begin()
{
	Animator2D()->Play(0, 13.f, false);
}

void CHammerScript::Tick()
{
	if (Animator2D()->IsFinish())
		DeleteObject(GetOwner());
}

void CHammerScript::SaveToFile(FILE* _pFile)
{
}

void CHammerScript::LoadFromFile(FILE* _pFile)
{
}