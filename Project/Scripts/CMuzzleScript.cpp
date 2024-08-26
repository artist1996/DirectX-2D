#include "pch.h"
#include "CMuzzleScript.h"

CMuzzleScript::CMuzzleScript()
	: CScript(SCRIPT_TYPE::MUZZLESCRIPT)
{
}

CMuzzleScript::~CMuzzleScript()
{
}

void CMuzzleScript::Begin()
{
	Animator2D()->Play(0, 13.f, false);
}

void CMuzzleScript::Tick()
{
	if (Animator2D()->IsFinish())
		DeleteObject(GetOwner());
}

void CMuzzleScript::SaveToFile(FILE* _pFile)
{
}

void CMuzzleScript::LoadFromFile(FILE* _pFile)
{
}