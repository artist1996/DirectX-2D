#include "pch.h"
#include "CDeathCrisisLineoneScript.h"

CDeathCrisisLineoneScript::CDeathCrisisLineoneScript()
	: CScript(SCRIPT_TYPE::DEATHCRISISLINEONESCRIPT)
{
}

CDeathCrisisLineoneScript::~CDeathCrisisLineoneScript()
{
}

void CDeathCrisisLineoneScript::Begin()
{
	MeshRender()->GetDynamicMaterial();

	Animator2D()->Play(0, 20.f, false);
}

void CDeathCrisisLineoneScript::Tick()
{
}

void CDeathCrisisLineoneScript::SaveToFile(FILE* _pFile)
{
}

void CDeathCrisisLineoneScript::LoadFromFile(FILE* _pFile)
{
}