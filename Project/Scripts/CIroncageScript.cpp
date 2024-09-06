#include "pch.h"
#include "CIroncageScript.h"

#include <Engine/CLevelMgr.h>

CIroncageScript::CIroncageScript()
	: CScript(SCRIPT_TYPE::IRONCAGESCRIPT)
{
}

CIroncageScript::~CIroncageScript()
{
}

void CIroncageScript::Begin()
{
}

void CIroncageScript::Tick()
{
	bool bCheck = CLevelMgr::GetInst()->CheckMonster();

	if (bCheck)
		DeleteObject(GetOwner());
}