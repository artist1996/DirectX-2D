#include "pch.h"
#include "CDeathCrisislinetwoScript.h"

CDeathCrisislinetwoScript::CDeathCrisislinetwoScript()
	: CScript(SCRIPT_TYPE::DEATHCRISISLINETWOSCRIPT)
{
}

CDeathCrisislinetwoScript::~CDeathCrisislinetwoScript()
{
}

void CDeathCrisislinetwoScript::Begin()
{
	MeshRender()->GetDynamicMaterial();

	Animator2D()->Play(0, 20.f, false);
}

void CDeathCrisislinetwoScript::Tick()
{
}

void CDeathCrisislinetwoScript::SaveToFile(FILE* _pFile)
{
}

void CDeathCrisislinetwoScript::LoadFromFile(FILE* _pFile)
{
}