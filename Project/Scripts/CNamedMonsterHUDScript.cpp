#include "pch.h"
#include "CNamedMonsterHUDScript.h"

CNamedMonsterHUDScript::CNamedMonsterHUDScript()
	: CScript(SCRIPT_TYPE::NAMEDMONSTERHUDSCRIPT)
	, m_pTarget(nullptr)
{
}

CNamedMonsterHUDScript::~CNamedMonsterHUDScript()
{
}

void CNamedMonsterHUDScript::Begin()
{
	GetOwner()->SetActive(false);
}

void CNamedMonsterHUDScript::Tick()
{
	m_pTarget = GetOwner()->GetTarget();

	if (nullptr == m_pTarget)
		return;

	if (m_pTarget->IsDead())
	{
		GetOwner()->SetActive(false);
		GetOwner()->SetTarget(nullptr);
	}
	
	Font();
}

void CNamedMonsterHUDScript::Font()
{
	if (L"juris" == m_pTarget->GetName())
	{
		GetOwner()->SetFont(L"Lv100 공작 유리스");
	}
	else if (L"hyungteo" == m_pTarget->GetName())
	{
		GetOwner()->SetFont(L"Lv100 흉터");
	}
}

void CNamedMonsterHUDScript::SaveToFile(FILE* _pFile)
{
}

void CNamedMonsterHUDScript::LoadFromFile(FILE* _pFile)
{
}