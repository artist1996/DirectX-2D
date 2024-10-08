#include "pch.h"
#include "CSkillIconScript.h"

#include <Engine/CLevelMgr.h>
#include "CPlayerScript.h"

CSkillIconScript::CSkillIconScript()
	: CScript(SCRIPT_TYPE::SKILLICONSCRIPT)
	, m_pTarget(nullptr)
	, m_Type(PLAYER_SKILLTYPE::END)
	, m_Ratio(0.f)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_Type);
}

CSkillIconScript::~CSkillIconScript()
{
}

void CSkillIconScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	m_pTarget = CLevelMgr::GetInst()->FindObjectByName(L"Player");
}

void CSkillIconScript::Tick()
{
	if (!m_pTarget)
		return;

	CalculateRatio();
	MeshRender()->GetMaterial()->SetScalarParam(FLOAT_1, m_Ratio);
}

void CSkillIconScript::CalculateRatio()
{
	CPlayerScript* pTargetScript = static_cast<CPlayerScript*>(m_pTarget->GetScripts()[0]);
	const tPlayerSkillTime& Time = pTargetScript->GetSkillTime();

	switch (m_Type)
	{
	case PLAYER_SKILLTYPE::HEADSHOT:
		m_Ratio = Time.fHeadShotTime / Time.fHeadShotCoolTime;
		break;
	case PLAYER_SKILLTYPE::RISINGSHOT:
		m_Ratio = Time.fRisingShotTime / Time.fRisingShotCoolTime;
		break;
	case PLAYER_SKILLTYPE::WINDMILL:
		m_Ratio = Time.fWindMillTime / Time.fWindMillCoolTime;
		break;
	case PLAYER_SKILLTYPE::MACHKICK:
		m_Ratio = Time.fMachKickTime / Time.fMachKickCoolTime;
		break;
	case PLAYER_SKILLTYPE::RANDOMSHOOT:
		m_Ratio = Time.fRandomShootTime / Time.fRandomShootCoolTime;
		break;
	case PLAYER_SKILLTYPE::WESTERNFIRE:
		m_Ratio = Time.fWesternFireTime / Time.fWesternFireCoolTime;
		break;
	case PLAYER_SKILLTYPE::GUNHAWK:
		m_Ratio = Time.fGunHawkTime / Time.fGunHawkCoolTime;
		break;
	case PLAYER_SKILLTYPE::PUNISHER:
		m_Ratio = Time.fPunisherTime / Time.fPunisherCoolTime;
		break;
	case PLAYER_SKILLTYPE::BBQ:
		m_Ratio = Time.fBBQTime / Time.fBBQCoolTime;
		break;
	case PLAYER_SKILLTYPE::MULTIHEADSHOT:
		m_Ratio = Time.fHeadShotCoolTime / Time.fHeadShotTime;
		break;
	case PLAYER_SKILLTYPE::DEATHCRYSIS:
		m_Ratio = Time.fDeathCrisisTime / Time.fDeathCrisisCoolTime;
		break;
	}
}

void CSkillIconScript::SaveToFile(FILE* _pFile)
{
	fwrite(&m_Type, sizeof(PLAYER_SKILLTYPE), 1, _pFile);
}

void CSkillIconScript::LoadFromFile(FILE* _pFile)
{
	fread(&m_Type, sizeof(PLAYER_SKILLTYPE), 1, _pFile);
}