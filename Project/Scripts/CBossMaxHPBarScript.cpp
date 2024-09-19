#include "pch.h"
#include "CBossMaxHPBarScript.h"

#include <Engine/CLevelMgr.h>

CBossMaxHPBarScript::CBossMaxHPBarScript()
	: CScript(SCRIPT_TYPE::BOSSMAXHPBARSCRIPT)
	, m_pTarget(nullptr)
	, m_Ratio(0.f)
{
}

CBossMaxHPBarScript::~CBossMaxHPBarScript()
{
}

void CBossMaxHPBarScript::CalculateRatio(INFO& _info)
{
	m_Ratio = _info.HP / _info.MaxHP;
}

void CBossMaxHPBarScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	m_pTarget = CLevelMgr::GetInst()->FindObjectByName(L"direzie");

	MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\bosshud\\BossMaxHPBar.png"));
}

void CBossMaxHPBarScript::Tick()
{
	INFO& info = m_pTarget->GetInfo();
	CalculateRatio(info);
	MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_1, m_Ratio);
}

void CBossMaxHPBarScript::SaveToFile(FILE* _pFile)
{
}

void CBossMaxHPBarScript::LoadFromFile(FILE* _pFile)
{
}