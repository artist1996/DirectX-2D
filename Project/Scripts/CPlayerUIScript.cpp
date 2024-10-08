#include "pch.h"
#include "CPlayerUIScript.h"

#include <Engine/CLevelMgr.h>

CPlayerUIScript::CPlayerUIScript()
	: CScript(SCRIPT_TYPE::PLAYERUISCRIPT)
	, m_pTarget(nullptr)
{
}

CPlayerUIScript::~CPlayerUIScript()
{
}

void CPlayerUIScript::Begin()
{
}

void CPlayerUIScript::Tick()
{
}

void CPlayerUIScript::SaveToFile(FILE* _pFile)
{
}

void CPlayerUIScript::LoadFromFile(FILE* _pFile)
{
}
