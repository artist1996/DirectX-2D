#include "pch.h"
#include "CSeriaScript.h"

CSeriaScript::CSeriaScript()
	: CScript(SCRIPT_TYPE::SERIASCRIPT)
{
}

CSeriaScript::~CSeriaScript()
{
}

void CSeriaScript::Begin()
{
	Animator2D()->Play(0, 5.f, true);
}

void CSeriaScript::Tick()
{
}