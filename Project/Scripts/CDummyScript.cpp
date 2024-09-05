#include "pch.h"
#include "CDummyScript.h"

CDummyScript::CDummyScript()
	: CScript(SCRIPT_TYPE::DUMMYSCRIPT)
{
}

CDummyScript::~CDummyScript()
{
}

void CDummyScript::Begin()
{
	Animator2D()->Play(0, 10.f, true);
}

void CDummyScript::Tick()
{
}