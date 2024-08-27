#include "pch.h"
#include "CGunHawkExplodeScript.h"

CGunHawkExplodeScript::CGunHawkExplodeScript()
	: CScript(SCRIPT_TYPE::GUNHAWKEXPLODESCRIPT)
{
}

CGunHawkExplodeScript::~CGunHawkExplodeScript()
{
}

void CGunHawkExplodeScript::Begin()
{
	Animator2D()->Play(0, 15.f, true);
}

void CGunHawkExplodeScript::Tick()
{
}
