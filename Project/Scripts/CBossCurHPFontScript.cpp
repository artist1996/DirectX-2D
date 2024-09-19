#include "pch.h"
#include "CBossCurHPFontScript.h"

#include <Engine/CLevelMgr.h>

CBossCurHPFontScript::CBossCurHPFontScript()
	: CScript(SCRIPT_TYPE::BOSSCURHPFONTSCRIPT)
	, m_pTarget(nullptr)
	, m_Ratio(0)
{
}

CBossCurHPFontScript::~CBossCurHPFontScript()
{
}

void CBossCurHPFontScript::Begin()
{
	m_pTarget = CLevelMgr::GetInst()->FindObjectByName(L"direzie");

	m_strPath = L"texture\\MonsterDigit\\Digit";
}

void CBossCurHPFontScript::Tick()
{
	INFO& info = m_pTarget->GetInfo();
	CalculateRatio(info);
	SetTexture();
}

void CBossCurHPFontScript::CalculateRatio(INFO& _info)
{
	m_Ratio = static_cast<int>((_info.HP / _info.MaxHP) * 37);
}

void CBossCurHPFontScript::SetTexture()
{
	if (0 == m_Ratio)
		m_Ratio = 1;

	const wstring& string = to_wstring(m_Ratio);


	MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->FindAsset<CTexture>(m_strPath + string + L".png"));
}

void CBossCurHPFontScript::SaveToFile(FILE* _pFile)
{
}

void CBossCurHPFontScript::LoadFromFile(FILE* _pFile)
{
}