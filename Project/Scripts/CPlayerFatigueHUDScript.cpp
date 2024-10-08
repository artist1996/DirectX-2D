#include "pch.h"
#include "CPlayerFatigueHUDScript.h"

#include <Engine/CLevelMgr.h>

CPlayerFatigueHUDScript::CPlayerFatigueHUDScript()
	: CScript(SCRIPT_TYPE::PLAYERFATIGUEHUDSCRIPT)
	, m_pTarget(nullptr)
	, m_Ratio(0.f)
{
}

CPlayerFatigueHUDScript::~CPlayerFatigueHUDScript()
{
}

void CPlayerFatigueHUDScript::Begin()
{
	m_pTarget = CLevelMgr::GetInst()->FindObjectByName(L"Player");
}

void CPlayerFatigueHUDScript::Tick()
{
	if (!m_pTarget)
		return;

	INFO& info = m_pTarget->GetInfo();

	CalculateByRatio(info);

	MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_2, m_Ratio);
}

void CPlayerFatigueHUDScript::CalculateByRatio(INFO& _info)
{
	m_Ratio = static_cast<float>(_info.Fatigue / _info.MaxFatigue);
}