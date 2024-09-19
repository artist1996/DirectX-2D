#include "pch.h"
#include "CMonsterHUDScript.h"

CMonsterHUDScript::CMonsterHUDScript()
	: CScript(SCRIPT_TYPE::MONSTERHUDSCRIPT)
	, m_pTarget(nullptr)
{
}

CMonsterHUDScript::~CMonsterHUDScript()
{
}

void CMonsterHUDScript::Begin()
{
	GetOwner()->SetActive(false);
}

void CMonsterHUDScript::Tick()
{
	m_pTarget = GetOwner()->GetTarget();

	if (nullptr == m_pTarget)
		return;

	if (m_pTarget->IsDead())
	{
		GetOwner()->SetActive(false);
		GetOwner()->SetTarget(nullptr);
	}
}

void CMonsterHUDScript::SaveToFile(FILE* _pFile)
{
}

void CMonsterHUDScript::LoadFromFile(FILE* _pFile)
{
}