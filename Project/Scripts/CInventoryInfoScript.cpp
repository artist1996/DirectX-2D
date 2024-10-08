#include "pch.h"
#include "CInventoryInfoScript.h"
#include <Engine/CLevelMgr.h>

CInventoryInfoScript::CInventoryInfoScript()
	: CScript(SCRIPT_TYPE::INVENTORYINFOSCRIPT)
{
}

CInventoryInfoScript::~CInventoryInfoScript()
{
}

void CInventoryInfoScript::Begin()
{
	m_Owner = CLevelMgr::GetInst()->FindObjectByName(L"Player");
}

void CInventoryInfoScript::Tick()
{
}