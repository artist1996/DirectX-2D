#include "pch.h"
#include "CBossHUDScript.h"

#include <Engine/CLevelMgr.h>

CBossHUDScript::CBossHUDScript()
	: CScript(SCRIPT_TYPE::BOSSHUDSCRIPT)
	, m_pTarget(nullptr)
{
}

CBossHUDScript::~CBossHUDScript()
{
}

void CBossHUDScript::Begin()
{
	m_pTarget = CLevelMgr::GetInst()->FindObjectByName(L"direzie");
	GetOwner()->SetTarget(m_pTarget);
}

void CBossHUDScript::Tick()
{
	if (!IsValid(m_pTarget))
		DeleteObject(GetOwner());
}

void CBossHUDScript::SaveToFile(FILE* _pFile)
{
}

void CBossHUDScript::LoadFromFile(FILE* _pFile)
{
}