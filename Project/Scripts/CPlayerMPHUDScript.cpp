#include "pch.h"
#include "CPlayerMPHUDScript.h"
#include <Engine/CLevelMgr.h>

CPlayerMPHUDScript::CPlayerMPHUDScript()
	: CScript(SCRIPT_TYPE::PLAYERMPHUDSCRIPT)
	, m_pTarget(nullptr)
	, m_Ratio(0.f)
{
}

CPlayerMPHUDScript::~CPlayerMPHUDScript()
{
}

void CPlayerMPHUDScript::CalculateByRatio(INFO& _info)
{
	m_Ratio = _info.MP / _info.MaxMP;
}

void CPlayerMPHUDScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	m_pTarget = CLevelMgr::GetInst()->FindObjectByName(L"Player");
}

void CPlayerMPHUDScript::Tick()
{
	INFO& info = m_pTarget->GetInfo();

	CalculateByRatio(info);

	MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_1, m_Ratio);
}